//
// Created by bartek on 27.12.2020.
//

#ifndef RX_BASE_CORE_H
#define RX_BASE_CORE_H

#include "globopts.h"
#include "dsp.h"

struct RXopts *init_source(enum resource_type src_type, void *res_spec_info, size_t chunk_size);

struct stage{
    struct dsp_generic_opts *dsp_opts;
    dsp_func dsp;
};

struct chain{
    struct stage stages[STAGES_N_MAX];
};
#endif //RX_BASE_CORE_H
