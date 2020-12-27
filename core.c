//
// Created by bartek on 27.12.2020.
//

#include "core.h"
#include "globopts.h"
#include "data_read.h"

struct RXopts *init_source(enum resource_type src_type, void *res_spec_info, size_t chunk_size) {
    static struct RXopts src_opts;

    switch (src_type) {
        case wav_file:
            src_opts.src_handler = open_wav((char *) res_spec_info);
            src_opts.src_get_chunk = wav_get_chunk;

            if (((wav_handler *) src_opts.src_handler)->fmt_subchunk.num_channels == 2) {
                src_opts.analitical = 1;
            } else {
                src_opts.analitical = 0;
            }

            src_opts.fs = ((wav_handler *) src_opts.src_handler)->fmt_subchunk.sample_rate;
            src_opts.dt = 1.f / src_opts.fs;

            src_opts.eof = 0;
            src_opts.chunk_size = chunk_size;
            break;

        default:
            dprintf(2, "init_source(): cannot handle given src_type\n");
            return NULL;
    }

    return &src_opts;
}

