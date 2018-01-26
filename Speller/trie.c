/* PROGRAM:  tire.c 
   AUTHOR:    
   DATE:     22/03/17
   TOPIC:    trie implementation 
   PURPOSE:   
   NOTES:   
             
*/

/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include "trie.h"

/**************************************************************************/
/* Helper Functions
 * trie_node_t * trie_new(  void );
 *         Allocates memory for a new trie node
 *         Returns NULL if memory allocation was not possible or
 *         a memory address to a trie_node in the heap
 **************************************************************************/
trie_node_t * trie_new(  void ){
	
	trie_node_t * tmp = NULL;
	int i;
	
	if ( ( tmp = ( trie_node_t * ) malloc ( sizeof( trie_node_t ) ) ) == NULL )
		return NULL;

	for( i = 0; i < ALPHA_SIZE; i++ ) { 
		tmp->child[ i ] = NULL;
		tmp->end = 1;
	}
	return tmp;
}

/**************************************************************************/
/* Functions functions       
 * int trie_size     ( trie_node_t *  root );
 *         Returns the number of words in the trie
 * int trie_contains ( trie_node_t *  root,    char word[ ] );
 *         Returns 1 if a the word is in the trie
 *                 0 otherwise
 * int trie_insert   ( trie_node_t ** rootRef, char word[ ] );
 *         Returns 1 if the word is inserted in the trie
 *                 0 otherwise
 * int trie_remove  ( trie_node_t ** rootRef, char word[ ] );
 *         Returns 1 if the word is removed from the trie
 *                 0 otherwise
 * int trie_destroy  ( trie_node_t ** Tref );
 *         Returns 1 if the trie and all its node are destroyed
 **************************************************************************/
int trie_size     ( trie_node_t *  root ) {
	int count =0;
	int i;
	if(root == NULL){
        	return 0;
	}
	if(root->end == '\0'){
		count++;
	}

	for(i = 0; i < ALPHA_SIZE; i++){

		if(root->child[i] != NULL) {
			count += trie_size (root->child[i]);
		}
	}

	return count;
}

/**************************************************************************/
int trie_contains ( trie_node_t *  root,    char word[ ] ){
	int index;
	int ind ;
	int length = strlen (word);

	if(root == NULL){
		return 0;
	}

	for( index = 0 ; index < length ; index++)
	{

		if(!isalpha (word[index])  && word[index] != '\'' ){
			return 0;
		}

		if(word[index] == '\''){
			ind = ALPHA_SIZE-1;
		}

		else{
			ind = (int)word[index] - (int)'a';
		}

		if(!root-> child[ind] ){
			return 0;
		}

		root = root->child[ind];
	}

	if(root->end == '\0'){    
		return 1;
	}   

	return 0;
}
/**************************************************************************/
int trie_insert   ( trie_node_t ** rootRef, char word[ ] ){
	int i, ind;
	int len = strlen(word);

	trie_node_t *temp = *rootRef;

	if (*rootRef == NULL) return 0;

	for (i = 0; i < len; i++) {
		if(!isalpha (word[i])  && word[i] != '\'' ){
			return 0;
		}
        
		if(word[i] == '\''){
			ind = ALPHA_SIZE-1;
		}

		else{
			ind = (int)word[i] - (int)'a';
           
		}

		if(!temp-> child[ind] ){
           
			temp->child[ind]= trie_new();
		}

		temp = temp->child[ind];
	}

	if(temp->end == '\0'){    
		return 0;
	}
    	else{
		temp->end = '\0';
		return 1;
	}
    	return 0;
}
/**************************************************************************/
int trie_remove  ( trie_node_t ** rootRef, char word[ ] ){
	int i, ind;
	int len = strlen(word);

	trie_node_t *temp = *rootRef;

	if (*rootRef == NULL)
		return 0;

	if(trie_contains(temp , word) == 0){
		return 1;
	}
	for (i = 0; i < len; i++) {
		if(word[i] == '\''){
			ind = ALPHA_SIZE-1;
		}
		else{
			ind = (int)word[i] - (int)'a';
           	}

		temp = temp->child[ind];
	}
	if(temp->end == '\0'){    
        	temp->end = '1';
		return 0;
	}
	return 0;
}
/**************************************************************************/
int trie_destroy  ( trie_node_t ** rootRef ){

    trie_node_t * temp = *rootRef;
    int i;
    int count =0;
    
	if(temp == NULL)
		return 1;
    
	if(temp->child == NULL)
		return 1;
   
	for(i =0; i<ALPHA_SIZE; i++){

		if(temp->child[i] != NULL){
			trie_destroy(&temp->child[i]);            
		}

		free(temp->child[i]);
		temp->child[i]=NULL;
	}
	return 1;
}


