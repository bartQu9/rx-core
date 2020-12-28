//
// Created by bartek on 27.12.2020.
//

#ifndef RX_BASE_CORE_H
#define RX_BASE_CORE_H

#include "globopts.h"
#include "dsp.h"


struct stage {
    struct dsp_generic_opts *dsp_opts;
    dsp_func dsp;
    //void *_future_sink_;
};

struct chain {
    struct stage *stages[STAGES_N_MAX];
};

struct RXopts *init_source(enum resource_type src_type, void *res_spec_info, size_t chunk_size);

void chain_add_stage(struct stage *s, struct chain *c);

#endif //RX_BASE_CORE_H
