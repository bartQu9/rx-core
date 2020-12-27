//
// Created by bartek on 20.12.2020.
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void err_exit(uint8_t status, char *status_string){
    dprintf(2, status_string);
    exit(status);
}

