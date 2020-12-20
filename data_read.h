//
// Created by bartek on 17.12.2020.
//

#ifndef RX_BASE_DATA_READ_H
#define RX_BASE_DATA_READ_H
#include <stdint.h>
typedef struct iq_chunk{
    double *I;      // I part of IQ signal
    double *Q;      // Q part of IQ signal
    uint32_t size;  // length of I

}chunk;


#endif //RX_BASE_DATA_READ_H
