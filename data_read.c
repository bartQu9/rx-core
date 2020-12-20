//
// Created by bartek on 17.12.2020.
//
#include "data_read.h"
#include "lutils.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>


wav_handler *open_wav(char *file_path) {
    FILE *file;
    if ((file = fopen(file_path, "r")) == NULL){
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

//uint8_t wav_read_samples(uint32_t n, )