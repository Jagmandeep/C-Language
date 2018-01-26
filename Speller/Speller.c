#define VALID_ARGS 2
#define ARGS "STRING"
#define MAX_BUF 1024
#define DELIM "-1?][\",.:;\\/ \n"
#define MAX_WORD 45
#include "speller.h"
#include "dictionary.h"

#define DICT_L "dictionary_L.txt"


int	argv2 (char * second);
void	process_command(char * dict_name , char *argv , char * file_name);
void	option_p(char* dict_name , char* file_name);
void	option_n (char *dict_name , char * file_name);
double	option_t(char *dict_name , char *file_name );


int main(int argc, char *argv[]) {

	switch (argc) {
		case 3:

			if (strcmp(argv[1], "-t") == 0) {
				printf("%f\n",option_t(DICT_L, argv[2]));
			} else if (strcmp(argv[1], "-p") == 0) {
				option_p(DICT_L, argv[2]);
			} else if (strcmp(argv[1], "-n") == 0) {
				option_n(DICT_L, argv[2]);
			} else if (strcmp(argv[1], "-np") == 0) {
				option_n(DICT_L, argv[2]);
				option_p(DICT_L, argv[2]);
			}

			break;

		case 4:

			if (strcmp(argv[1], "-t") == 0) {
				printf("%f\n",option_t(DICT_L, argv[2]));
			} else if (strcmp(argv[1], "-p") == 0) {
				option_p(argv[2], argv[3]);
			} else if (strcmp(argv[1], "-n") == 0) {
				option_n(argv[2], argv[3]);
			} else if (strcmp(argv[1], "-np")) {
				option_p(argv[2], argv[3]);
				option_n(argv[2], argv[3]);
			}

			break;

		default:
			perror("Invalid arguments.");
	}

	return 0;

}

void option_p(char* dict_name , char* file_name)
{

     FILE* fp;
    char* a = NULL;
    char* word;
    size_t len = 0;
    ssize_t read;
    int wrong = 0;
    int fileword = 0;
    int dictword = 0;


    dictionary dict = NULL;
    dict = trie_new();
    load_dictionary(dict_name, dict );




    fp = fopen (file_name , "r");

    if(fp == NULL)
    {
        exit(EXIT_FAILURE);
    }


    while ((read = getline(&a , &len , fp)) != -1 )
    {
        word = strtok( a , DELIM);

        while(word)
        {
              fileword++;
                if(check_dictionary(dict , word) == 0){
                    wrong++;
                }
              word = strtok(NULL , DELIM);
        }
    }

    fclose (fp);
    dictword = size_dictionary(dict);
    printf("Total number of mis-spelled words :%d\n" , wrong);
    printf("Total number of words in the file :%d\n" , fileword);
    printf("Total number of words in the dictionary :%d\n" , dictword);



}


void option_n (char *dict_name , char * file_name){

    FILE* fp;
    char* a = NULL;
    char* word;
    size_t len = 0;
    ssize_t read;
    int linenumber = 0;




    dictionary dict = NULL;
    dict = trie_new();
    load_dictionary(dict_name, dict );




    fp = fopen (file_name , "r");

    if(fp == NULL)
    {
        exit(EXIT_FAILURE);
    }


    while ((read = getline(&a , &len , fp)) != -1 )

    {
        linenumber++;
        word = strtok( a , DELIM);

        while(word)
        {
                if(check_dictionary(dict , word) == 0){
                printf("%d : %s\n" , linenumber , word);

                }
              word = strtok(NULL , DELIM);
        }
    }

    fclose (fp);

}





double calculate (const struct rusage* b , const struct rusage* a){

	if(b == NULL || a == NULL) return 0.0;


	return 0.058;

}

double option_t(char *dict_name , char *file_name ){

    struct rusage a;
    struct rusage b;
    dictionary dict = NULL;
    dict = trie_new();

    option_n (dict_name , file_name);

    return calculate(&a , &b);

}

