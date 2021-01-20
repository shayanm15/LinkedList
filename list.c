	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "list.h"


struct Performance *newPerformance() {

	struct Performance *newNode;
	newNode = (struct Performance*)malloc(sizeof(struct Performance)); /* Allocating mmemory for struct performance pointer */

	newNode -> reads = 0;
	newNode -> writes = 0;
	newNode -> mallocs = 0;		/* Assigning number of reads, writes, mallocs, frees to zero  */
	newNode -> frees = 0;

	if (newNode == NULL) {
		printf("Malloc has failed\n"); /* Error checking if malloc failed if pointer is null*/
		exit(0);
	} 

	return newNode;

}

void push (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {

 struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
  
  	newNode ->data = malloc(width);

  	memcpy(newNode->data,src,width); /*Copy the data into the new node*/
  
    newNode->next = (*list_ptr); /*The next node of the new node is list_ptr*/

    (*list_ptr)    = newNode; /*Make list_ptr be equal to the head of the list*/

		if (newNode == NULL) {
		
		printf("Malloc has failed\n"); /* Error checking if malloc failed if pointer is null*/
		
		exit(0);
	} 

	

	performance -> mallocs = performance -> mallocs +1;
	performance -> writes = performance -> writes +1;



}

void readHead(struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width) {

	if (*list_ptr == NULL) {

		printf("Empty list\n"); /*Error checking to see if list empty*/
		
		exit(0);
	}


	memcpy(dest, (*list_ptr)->data, width); /*Copy the data from list_ptr into dest*/


	performance->reads = performance-> reads +1;

}


void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width) {
	
	struct Node *popNode = *list_ptr; /*Make node that needs to be removed be the head of list*/
	
	if (*list_ptr == NULL) {

		printf("Empty list\n"); /*Error checking to see if list empty*/
		
		exit(0);
	}


	memcpy(dest, (*list_ptr) ->data, width); /*Copy the data from list_ptr into dest*/

	

	 *list_ptr = (popNode)->next; /*Make list_ptr be the next node of the head*/ 
	 
	 free(popNode ->data); /*Free the data*/
        
     free(popNode);    /*Free the node*/           
        
    

	performance->reads = performance ->reads + 1;
	
	performance->frees = performance -> frees+ 1;

}


struct Node **next (struct Performance *performance, struct Node **list_ptr) {

	if (*list_ptr == NULL) {

		printf("Empty list\n"); /*Error checking to see if list empty*/
		exit(0);
	}

	performance->reads = performance->reads + 1;

	
	 return &(*list_ptr) -> next; /*Return the next pointer*/

}

int isEmpty(struct Performance *performance, struct Node **list_ptr) {

	if (*list_ptr == NULL) {

		return 1; /*If list empty return 1*/

	} else {

		return 0; /*Else return 0*/
	}


}

void freeList(struct Performance *performance, struct Node **list_ptr) {


	void *contents;

	int listNode;
	unsigned int widthVal;
	
	widthVal = 0;

	for (listNode = 0; *list_ptr != NULL; ++listNode)
	{
	
	pop(performance, list_ptr, &contents, widthVal); /*Free the list using pop until the list is NULL*/

		
	}


}

void readItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width) {

	int listNode;	
	listNode = 0;

	while (listNode < index)
	{
		list_ptr= next(performance, list_ptr); /*Use the next function to find the node of the specific index*/
		
		listNode++;
	}
	
	readHead(performance, list_ptr, dest, width); /*Call readHead to read in the data at that node*/



}

void appendItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {

	int listNode;

	for ( listNode = 0; isEmpty(performance, list_ptr) !=  1; ++listNode)
	{
		list_ptr = next(performance, ((list_ptr))); /*Use the next function to find the last node of the list*/
	
	}

		
	push(performance, ((list_ptr) ), src, width); /*Call push to push a node at the end of the list */



}

void insertItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width) {

	

	int listNode;
	listNode = 0;

	while (listNode < index)
	{
		list_ptr=next(performance, list_ptr); /*Use the next function to find the node of the specific index*/

		listNode++;
	} 

	struct Node *newNode = *list_ptr; /*Make the newNode be at the same node of list_ptr*/

	
	 push(performance, list_ptr, src, width); /*Push a node at the specific index*/

	
	 (*list_ptr) -> next = newNode; /*To shift down the list so nodes are not being replaced, make the next node of list_ptr be newNode*/



}


void prependItem (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {



	insertItem(performance, list_ptr, 0, src, width);

}


void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index) {

	void *contents;

	int listNode;
	listNode = 0;


	
while (listNode < index)

	{
		list_ptr = next(performance, list_ptr); /*Use the next function to find the node of the specific index*/

		listNode++;

		
	} 


	pop(performance, list_ptr, &contents, sizeof(index)); /*Remove the node using pop function*/



}


int findItem( struct Performance *performance, struct Node**list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width ) {

	int listNode;
	listNode = 0;

	char *item_searched = malloc(sizeof(char) * width);
	
	int similarity = 0;

	while ( *list_ptr != NULL)
	{
		
		readHead(performance, list_ptr, item_searched, width);

		

		if (compar(target, item_searched) == similarity) { /* If the compar function returns a similarity of 0, it has found match */

			free(item_searched);
            return listNode; /*return the macthed index */
        }

       	list_ptr = next(performance, list_ptr);

       	listNode++;

	}

	free(item_searched);
	return -1;


}



