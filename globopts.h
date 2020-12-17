//
// Created by bartek on 17.12.2020.
//

#ifndef RX_BASE_GLOBOPTS_H
#define RX_BASE_GLOBOPTS_H
#include <stdint.h>
int flag_verbose;

typedef struct RXopts{
    uint32_t fs;    // frequency sampling
    uint8_t iq;     // real=0 IQ=1
    double fc;      // carrier frequency


}Rxopts;


#endif //RX_BASE_GLOBOPTS_H
