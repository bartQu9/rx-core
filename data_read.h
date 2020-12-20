//
// Created by bartek on 17.12.2020.
//

#ifndef RX_BASE_DATA_READ_H
#define RX_BASE_DATA_READ_H
#include <stdint.h>
#include <stdio.h>

struct iq_chunk{
    double *I;      // I part of IQ signal
    double *Q;      // Q part of IQ signal
    uint32_t size;  // length of I
};

struct iq_frame{
    struct iq_chunk *this;
    struct iq_chunk *next;
    struct iq_chunk *prev;

    uint32_t idx;  // index of first IQ sample stored in "this"
};

struct iq_buff{
    struct iq_frame *last;
    uint32_t buff_size;     // samples kept in memory
};

struct wav_riff_header{
    uint32_t chunk_id;      // 'RIFF'
    uint32_t chunk_size;    // little-endian
    uint32_t format;        // 'WAVE'
};

struct wav_fmt_subchunk{
    uint32_t subchunk1_id;
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_allign;
    uint16_t bits_per_sample;

};

struct wav_data_chunk{
    uint32_t subchunk2_id;
    uint32_t subchunk2_size;
};

typedef struct wav_handler{
    struct wav_riff_header riff_header;
    struct wav_fmt_subchunk fmt_subchunk;
    struct wav_data_chunk data_chunk;

    FILE *file_handler;
    uint64_t next_sample;
}wav_handler;

wav_handler *open_wav(char *file_path);

#endif //RX_BASE_DATA_READ_H
