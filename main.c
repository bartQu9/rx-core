#include <stdio.h>
#include <unistd.h>
#include "globopts.h"

int main(int argc, char **argv) {
    int c;
    while(( c = getopt(argc, argv, "hv")) != -1){
        switch (c) {
            case 'h':
                printf("Base RX functionality\n"
                       "Usage: rx-base [-h] [-v]\n");
                break;
            case 'v':
                flag_verbose = 1;
                break;
            default:
                break;
        }
    }
    return 0;
}
