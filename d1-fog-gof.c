#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    char fg_arg = '\0';
    int n = 0, m = 0;
    int f = 0, g = 0;

    while ((opt = getopt(argc, argv, ":f:g:")) != -1) {
        switch (opt) {
            case 'f':
                f = 1;
                n = atoi(optarg);
                break;
            case 'g':
                g = 1;
                m = atoi(optarg);
                break;
            case ':':
                fg_arg = optopt;
                break;
            case '?':
                printf("Erreur : Option '-%c' inconnue.\n", optopt);
                break;
        }
    }

    if (fg_arg != '\0') {
        
        if (strcmp(argv[1], "-f") == 0) {
            printf("fog(%d) = %.0f\n", n, pow(2, 2 * n));
        } 
        else if (strcmp(argv[1], "-g") == 0) {
            printf("gof(%d) = %.0f\n", m, 2 * pow(2, m));
        }
    } else {
        if (f)
            printf("f(%d) = %.0f\n", n, pow(2, n));
        if (g)
            printf("g(%d) = %d\n", m, 2 * m);
    }

    return 0;
}
