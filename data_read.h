//
// Created by bartek on 17.12.2020.
//

#ifndef RX_BASE_DATA_READ_H
#define RX_BASE_DATA_READ_H
#define iq_prec double

#include <stdint.h>
#include <stdio.h>

struct IQ {
    iq_prec I;
    iq_prec Q;
};

struct wav_riff_header {
    uint32_t chunk_id;      // 'RIFF'
    uint32_t chunk_size;    // little-endian
    uint32_t format;        // 'WAVE'
};

struct wav_fmt_subchunk {
    uint32_t subchunk1_id;
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_allign;
    uint16_t bits_per_sample;

};

struct wav_data_chunk {
    uint32_t subchunk2_id;
    uint32_t subchunk2_size;
};

typedef struct wav_handler {
    struct wav_riff_header riff_header;
    struct wav_fmt_subchunk fmt_subchunk;
    struct wav_data_chunk data_chunk;

    FILE *file_handler;
    uint64_t next_sample;
} wav_handler;

wav_handler *open_wav(char *file_path);

uint32_t
readtobuff(struct iq_buff *buff, uint32_t n, uint32_t (*fhandler)(struct IQ *samples, uint32_t n));


#endif //RX_BASE_DATA_READ_H
