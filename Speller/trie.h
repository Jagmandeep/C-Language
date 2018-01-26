/* PROGRAM:  trie.h
   AUTHOR:
   DATE:     19/03/17
   TOPIC:    Trie implementation
   PURPOSE:
   NOTES:

*/
#ifndef __TRIE_H
#define __TRIE_H


/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

#define ALPHA_SIZE 27
#define MAX_WORD 45
#define WORD '\0'
#define CHAR_TO_INDEX( c ) ((int)(c) - (int)('a'))

/**************************************************************************/
/* Struct Definitions
 **************************************************************************/
typedef struct trie_node {
	char end;
	struct trie_node *child[ ALPHA_SIZE ];
}trie_node_t;

/**************************************************************************/
/* Helper Functions
 * trie_node_t * trie_new(  void );
 *         Allocates memory for a new trie node
 *         Returns NULL if memory allocation was not possible or
 *         a memory address to a trie_node in the heap
***************************************************************************/
trie_node_t * trie_new(  void );

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
int trie_size     ( trie_node_t *  root );
int trie_contains ( trie_node_t *  root,    char word[ ] );
int trie_insert   ( trie_node_t ** rootRef, char word[ ] );
int trie_remove	  ( trie_node_t ** rootRef, char word[ ] );
int trie_destroy  ( trie_node_t ** rootRef );

#endif
