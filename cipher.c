#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CONSTANT 100000
#define ALPHABET_SIZE 26
#define DEFAULT_ARGS 5
#define DEFAULT_ARGS_CHECK 4
#define UPPER_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER_LETTERS "abcdefghijklmnopqrstuvwxyz"
#define ERROR_VALUE -1

int check_valid_args(int argc, char *argv[]){
    if(strcmp(argv[1], "check") == 0){
        if(argc != DEFAULT_ARGS_CHECK){
            fprintf(stderr, "Usage: cipher <encode|decode|check>"
                            " [k] <source path file> <output path file>\n");
            return EXIT_FAILURE;
        }
    }
    else if(argc != DEFAULT_ARGS){
        fprintf(stderr, "Usage: cipher <encode|decode|check>"
                        " [k] <source path file> <output path file>\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int check_valid_command(char *argv[]){
    if(strcmp(argv[1], "decode") != 0 &&
    strcmp(argv[1], "encode") != 0 && strcmp(argv[1], "check") != 0){
        fprintf(stderr, "The given command is invalid\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int check_valid_file_input(char **argv){
    FILE *my_file;
    my_file = fopen(argv[3], "r");
    if(my_file == NULL){
        fprintf(stderr, "The given file is invalid\n");
        return EXIT_FAILURE;
    }
    fclose(my_file);
    return EXIT_SUCCESS;
}
int module_k(int k){
    if(k < 0){
        return k + abs(ALPHABET_SIZE);
    }
    else{
        return k;
    }
}

void convert_cipher(const char *input_array,
                    char *output_array, unsigned long my_size, int k){
    for(unsigned long i = 0; i < my_size; i++){
        for(int j = 0; j < ALPHABET_SIZE; j++){
            if(input_array[i] == UPPER_LETTERS[j]){
                int curr = (j + k) % ALPHABET_SIZE;
                output_array[i] = UPPER_LETTERS[curr];
                break;
            }
            if(input_array[i] == LOWER_LETTERS[j]){
                int curr = (j + k) % ALPHABET_SIZE;
                output_array[i] = LOWER_LETTERS[curr];
                break;
            }
            if(j == ALPHABET_SIZE - 1){
                output_array[i] = input_array[i];
            }
        }
    }
}

int check_op(char *original_array, char *crypt_array,
             char *check_array, unsigned long my_size){
    for(int k = 0; k < ALPHABET_SIZE; k++){
        convert_cipher(&original_array[0],
                       &check_array[0], my_size, k);
        if(strcmp(crypt_array, check_array) == 0){
            return k;
        }
    }
    return ERROR_VALUE;
}

int main(int argc, char *argv[]){
    if(check_valid_args(argc, argv) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    if(check_valid_command(argv) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    if(check_valid_file_input(argv) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    FILE * out_file;
    FILE * in_file;
    FILE * comp_file;
    int k = module_k(atoi(argv[2]));
    if(strcmp(argv[1], "decode") == 0){
        k = ALPHABET_SIZE - k;
    }
    int val;
    char buffer[MAX_CONSTANT];
    char output_array[MAX_CONSTANT];
    char check_array[MAX_CONSTANT];

    if(strcmp(argv[1], "check") == 0){
        in_file = fopen(argv[2], "r");
        comp_file = fopen(argv[3], "r");
        while((fgets(buffer, MAX_CONSTANT + 1, in_file) != NULL) &&
        ((fgets(output_array, MAX_CONSTANT + 1, comp_file) != NULL))){
            val = check_op(&buffer[0], &output_array[0],
                           &check_array[0],
                           strlen(output_array) + 1);
        }
        if(val == ERROR_VALUE){
            fprintf(stdout, "Invalid encrypting\n");
        }
        else{
            fprintf(stdout, "Valid encrypting with k = %d\n", val);
        }
        return EXIT_SUCCESS;
    }
    else{
        in_file = fopen(argv[3], "r");
        out_file = fopen(argv[4], "w");
        while(fgets(buffer, MAX_CONSTANT + 1, in_file) != NULL){
            convert_cipher(&buffer[0],
                           &output_array[0],
                           strlen(buffer) + 1, k);
            fputs(output_array, out_file);
        }
    }
    fclose(in_file);
    fclose(out_file);
    return 0;
}

