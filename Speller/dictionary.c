/* PROGRAM:  dictionary.c 
   AUTHOR:    
   DATE:     01/04/16
   TOPIC:    Dictionary implementation 
   PURPOSE:   
   NOTES:              
*/

/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include "dictionary.h"


/**************************************************************************/
/* Dictionary functions   
 * int load_dictionary ( const char *dictionay_name, dictionary dict );
 *         Loads dictionary into memory from file dictionary_name
 *         Return the number of words in the dictionary
 *                and dict points to a valid dictionary
 *                0 otherwise and dict points to NULL   
 * int check_dictionary ( dictionary dict, const char *word );
 *         Returns 1 if the word is part of the dictionary
 * int size_dictionary ( dictionary dict );
 *         Returns the number of words in the dictionary
 * int unload_dictionary ( dictionary dict );
 *         Unloads dictionary from memory
 *         Returns 1 if successful, 0 otherwise
 **************************************************************************/
int load_dictionary   ( const char *dictionary_name, dictionary dict ){
	FILE* fp;
	char* a = NULL;
    
	size_t len = 0;
	ssize_t read;
	int length;

	printf("Name of file is : %s\n " , dictionary_name);
	fp = fopen (dictionary_name , "r");

	if(fp == NULL){    
		printf("File \n");
		exit(EXIT_FAILURE);    
	}
	while ((read = getline(&a , &len , fp)) != -1 ){
		length = strlen(a);
		a[length-1] = '\0';
		if ( trie_insert (&dict  , a) == 0 ){

			dict = NULL;
			fclose (fp);
			return 0;
		}

	}
    
	fclose (fp);
	return 1;
}
/**************************************************************************/
int check_dictionary  ( dictionary dict,  char *word ) {

    int i ;
    int len = strlen (word);

	for (i = 0; i<len; i++){ 
		if(word[i] != '\'')
			word[i] = tolower(word[i]);        
	}
	if(trie_contains(dict , word) == 1)
		return 1;

	else 
		return 0;
	
}
/**************************************************************************/
int size_dictionary   ( dictionary dict ) {

	int count = trie_size(dict); 
	return count;

}
/**************************************************************************/
int unload_dictionary ( dictionary dict ) {

	int load = trie_destroy(&dict);

	if(load == 1)
		return 1;

	else 
		return 0;

}


