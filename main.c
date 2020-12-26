#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "globopts.h"
#include "data_read.h"

void test(char *arg){

    wav_handler *h = open_wav(arg);
    int n = 10000;
    size_t i = 0;
    size_t readn;
    iq_prec complex iq[n];
    while ((readn = wav_read_samples(iq, h, n)) == n){
       // printf("%ld: I=%.6E Q=%.12E\n", i, creal(iq[0]), cimag(iq[0]));
        i++;
    }

}

int main(int argc, char **argv) {
    int c;
    while(( c = getopt(argc, argv, "hvt:")) != -1){
        switch (c) {
            case 'h':
                printf("Base RX functionality\n"
                       "Usage: rx-base [-h] [-v] [-t FILE]\n");
                break;
            case 'v':
                flag_verbose = 1;
                break;
            case 't':
                test(optarg);
                break;
            default:
                break;
        }
    }
    return 0;
}
