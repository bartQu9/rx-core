//
// Created by bartek on 17.12.2020.
//

#ifndef RX_BASE_GLOBOPTS_H
#define RX_BASE_GLOBOPTS_H

#include <stdint.h>
#include <unistd.h>
#include <complex.h>

#define iq_prec double

uint8_t flag_verbose;

enum resource_type{
    wav_file = 1
};

struct RXopts{
    uint32_t fs;            // frequency sampling
    double dt;              // 1/fs

    uint8_t analitical;     // real=0 IQ=1
    size_t chunk_size;      // size in IQ sample
    uint8_t eof;            // 1 if EOF

    void *src_handler;
    iq_prec complex *(*src_get_chunk)(struct RXopts *src_handler);

};


#endif //RX_BASE_GLOBOPTS_H
