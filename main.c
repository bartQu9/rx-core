#include <stdio.h>
#include <unistd.h>
#include "globopts.h"
#include "data_read.h"

void test(char *arg){

    wav_handler *h = open_wav(arg);

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
