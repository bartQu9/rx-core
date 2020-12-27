#include <stdio.h>
#include <unistd.h>
#include "globopts.h"
#include "core.h"
#include "data_read.h"

uint8_t flag_verbose;

void test(char *arg) {

    struct RXopts *opts = init_source(wav_file, arg, 1000);
    iq_prec complex *chunk;
    size_t idx = 1;
    while (!opts->eof) {
        chunk = wav_get_chunk(opts);
        for (int i = 0; i < opts->chunk_size; i++, idx++) {
            //printf("%ld:  I=%le  Q=%le\n", idx, creal(chunk[i]), cimag(chunk[i]));
        }
    }
}

int main(int argc, char **argv) {
    int c;
    while ((c = getopt(argc, argv, "hvt:")) != -1) {
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
