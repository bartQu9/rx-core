//
// Created by bartek on 17.12.2020.
//
#include "data_read.h"
#include "lutils.h"
#include "globopts.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

void u8bit_norm(const uint8_t *buff, iq_prec *dst, size_t n) {
    // converts 8-bit (0-255) samples to double <-1;1>
    // buff - tab of uint8_t
    size_t i;
    for (i = 0; i < n; i++) {
        dst[i] = (iq_prec) (buff[i] - 128) / 128;
    }
}

void norm_mkcomplex(iq_prec *norm, iq_prec complex *z, uint8_t channels, size_t n) {
    // n - pairs of IQ
    if (channels == 2) {
        for (int i = 0; i < n; i++) {
            z[i] = norm[2 * i] + norm[2 * i + 1] * I;
        }
    } else if (channels == 1) {
        for (int i = 0; i < n; i++) {
            z[i] = norm[i] + 0 * I;
        }
    }

}

wav_handler *open_wav(char *file_path) {
    FILE *file;
    if ((file = fopen(file_path, "r")) == NULL) {
        perror("open_wav(): failed to open wav file");
        return NULL;
    }
    uint8_t buff[256];
    static wav_handler handler;
    if (fread(&handler.riff_header, 4, 3, file) == 0)
        err_exit(EXIT_SRC_ERR, "open_wav(): failed to read RIFF header I/O err");
    if (fread(&handler.fmt_subchunk, 1, 24, file) == 0)
        err_exit(EXIT_SRC_ERR, "open_wav(): failed to read fmt subchunk I/O err");
    if (fread(&handler.data_chunk, 4, 2, file) == 0)
        err_exit(EXIT_SRC_ERR, "open_wav(): failed to read data subchunk I/O err");

    // check if file RIFF header is as we expected
    if (strncmp((char *) &handler.riff_header.chunk_id, "RIFF", 4) ||
        strncmp((char *) &handler.riff_header.format, "WAVE", 4)) {
        dprintf(2, "open_wav(): malformed RIFF header, got %s.4/%s.4",
                (char *) &handler.riff_header.chunk_id,
                (char *) &handler.riff_header.format);
        return NULL;
    }

    // check fmt sub-chunk
    if (strncmp((char *) &handler.fmt_subchunk.subchunk1_id, "fmt ", 4) ||
        handler.fmt_subchunk.subchunk1_size != 16 || handler.fmt_subchunk.audio_format != 1 ||
        handler.fmt_subchunk.num_channels != 2) {
        dprintf(2, "open_wav(): unsupported fmt, got id=\"%.4s\" size=%u format=%u numchann=%u",
                (char *) &handler.fmt_subchunk.subchunk1_id,
                handler.fmt_subchunk.subchunk1_size, handler.fmt_subchunk.audio_format,
                handler.fmt_subchunk.num_channels);
        return NULL;
    }

    // check it this chunk is data
    if (strncmp((char *) &handler.data_chunk.subchunk2_id, "data", 4)) {
        dprintf(2, "open_wav(): expected data chunk, got %s.4",
                (char *) &handler.data_chunk.subchunk2_id);
        return NULL;
    }

    //wav seems be alright
    handler.file_handler = file;
    handler.next_sample = 0;
    return &handler;

}

size_t wav_read_samples(iq_prec complex *dst, wav_handler *src, size_t n) {
    // read n (I,Q) samples
    // return: number of items read; when return < n further calls won't return any value
    // n - number of IQ samples to read
    size_t nread, iq_size;
    iq_size = src->fmt_subchunk.bits_per_sample * src->fmt_subchunk.num_channels / 8;   // size of one IQ
    uint8_t *buff = malloc(n * iq_size);
    nread = fread(buff, iq_size, n, src->file_handler);

    if (nread != n) {
        // EOF or err
        if (feof(src->file_handler)) {
            printf("wav_read_raw_samples(): reached end of file\n");
            fclose(src->file_handler);
        }
        if (ferror(src->file_handler)) {
            perror("wav_read_raw_samples():");
            fclose(src->file_handler);
        }
    }

    //convert samples to iq_prec
    iq_prec *norm_buff = malloc(n * sizeof(iq_prec) * src->fmt_subchunk.num_channels);
    switch (src->fmt_subchunk.bits_per_sample) {
        case 8:
            u8bit_norm(buff, norm_buff, n * src->fmt_subchunk.num_channels);
            norm_mkcomplex(norm_buff, dst, src->fmt_subchunk.num_channels, n);
            break;
        default:
            printf("wav_read_samples(): No available handler for given data type\n");
            break;
    }

    free(buff);
    free(norm_buff);
    return nread;
}

iq_prec complex *wav_get_chunk(struct RXopts *opts) {
    // get n IQ samples by returning ptr to IQ array
    // further calls MUST NOT get more samples than in initial call of this function
    static iq_prec complex *samples;
    size_t nread;

    if (!samples) {
        //first call, create buff
        samples = malloc(
                opts->chunk_size * ((wav_handler *) (opts->src_handler))->fmt_subchunk.num_channels *
                sizeof(iq_prec complex));
    }

    nread = wav_read_samples(samples, ((wav_handler *) (opts->src_handler)), opts->chunk_size);

    if (nread < opts->chunk_size){
        //read less than chunk, set EOF and fulfill rest of the chunk with zeroes
        opts->eof = 1;
        iq_prec complex zero = 0 + 0 * I;
        for(int i=nread; i < opts->chunk_size; i++){
            samples[i] = zero;
        }
    }

    return samples;
}


