//
// Created by bartek on 28.12.2020.
//

#ifndef RX_BASE_DSP_H
#define RX_BASE_DSP_H

#include "globopts.h"

typedef enum dsp_status {
    DSP_SUCCESS,
    DSP_RUNTIME_FAILURE
} dsp_status;

struct dsp_generic_opts {
    iq_prec complex *in_chunk;
    iq_prec complex *out_chunk;
    iq_prec complex *loc_buff;
    size_t in_n, out_n, loc_buff_n;

    void *dsp_spec_opts;
};

typedef dsp_status (*dsp_func)(struct dsp_generic_opts *opts);

#endif //RX_BASE_DSP_H
