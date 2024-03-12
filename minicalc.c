#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

double squareRoot(double num) {
    if (num < 0) {
        return -1;
    }
    return sqrt(num);
}

bool isAnagram(char *str1, char *str2) {
    int count[256] = {0};
    int i;

    if (strlen(str1) != strlen(str2)) {
        return false;
    }

    for (i = 0; str1[i]; i++) {
        count[tolower(str1[i])]++;
    }

    for (i = 0; str2[i]; i++) {
        count[tolower(str2[i])]--;
    }

    for (i = 0; i < 256; i++) {
        if (count[i]) {
            return false;
        }
    }

    return true;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "Minicalc requires at least one command-line argument.\n");
        exit(1);
        return 1;
    }

    double result;
    int last_arg = argc - 1;
    char *endptr_sqrt;

    switch (argv[1][0]) {
        case '+':
            if (argc != 4) {
                fprintf(stderr, "Addition requires two integer inputs\n", argv[0]);
                exit(3);
                return 3;
            }

            char *endptr;
            long n1 = strtol(argv[2], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "Invalid argument for addition operation.\n");
                exit(4);
                return 4;
            }

            long n2 = strtol(argv[3], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "Invalid argument for addition operation.\n");
                exit(4);
                return 4;
            }

            result = n1 + n2;
            printf("%f\n", result);
            break;

        case 'g':
            if (argc < 4 || strcmp(argv[1], "gcd") != 0) {
                fprintf(stderr, "GDC requires at least 2 integer inputs\n", argv[0]);
                exit(3);
                return 3;
            }

            result = strtod(argv[2], &endptr_sqrt);
            
            for (int i = 3; i < argc; ++i) {
                char *endptr;
                long n = strtol(argv[i], &endptr, 10);
                
                if (*endptr != '\0') {
                    fprintf(stderr, "Invalid argument for gcd operation.\n");
                    exit(4);
                }

                if (n <= 0) {
                    fprintf(stderr, "Inputs of the gcd operation must all be greater than zero.\n");
                    exit(7);
                }
                
                result = gcd(result, n);
                printf("%f\n", result);
            }

            break;

        case 's':
            if (argc != 3 || strcmp(argv[1], "sqrt") != 0) {
                fprintf(stderr, "Square Root requires 1 positive integer\n", argv[0]);
                exit(3);
                return 3;
            }

            char *endptr_sqrt;
            double a1 = strtod(argv[2], &endptr_sqrt);

            if (*endptr_sqrt != '\0') {
                fprintf(stderr, "Invalid argument for square root operation.\n");
                exit(4);
                return 4;
            }

            if (a1 < 0) {
                fprintf(stderr, "Input of the square root operation must be nonnegative.\n");
                exit(5);
                return 5;
            }

            result = squareRoot(a1);
            printf("%f\n", result);
            break;

        case 'a':

            if (argc != 4 || (strcmp(argv[1], "anagram") != 0 && strcmp(argv[1], "Anagram") != 0)) {
                fprintf(stderr, "Anagram requires 2 string inputs\n", argv[0]);
                exit(3);
                return 3;
            }

            for (int i = 2; i < argc; ++i) {
                for (char *p = argv[i]; *p != '\0'; ++p) {
                    if (!islower(*p)) {
                        fprintf(stderr, "Inputs of the anagram operation must consist only of lowercase letters.\n");
                        exit(6);
                        return 6;
                    }
                }
            }

            char result_str[10];
            bool result = isAnagram(argv[2], argv[3]);
            sprintf(result_str, "%s", result ? "true" : "false");
            printf("%s\n", result_str);
            break;

        default:
            fprintf(stderr, "Invalid operation.\n");
            exit(2);
            return 2;
    }

    return 0;
}