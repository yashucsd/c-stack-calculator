#include <string.h>
#include "stack.h"

/*
 * Initializes a stack
 * Return:
 *   Normal: An empty stack
 *   When there is no memory available to allocate: null pointer
 */
Stack * stack_init() {
	// allocates stack
	Stack * stk = (Stack *) malloc(sizeof(Stack *));
	// sets stack size
	stk->array = (char**) malloc(sizeof(char*) * STACK_SIZE);
	stk->top = STACK_EMPTY;
	return stk;
}

int isEmpty(Stack* stk) {
	if(stk->top == -1)
		return 1;
	else return 0;
}

/*
 * Pushes to a stack
 * Param:
 *   item - the stuff to be pushed
 */
void push(Stack* stk, char* str) {
	stk->top++;
	// allocates space for new element
	stk->array[stk->top] = (char*) malloc(sizeof(char*) * sizeof(str));
	stk->array[stk->top] = strdup(str);
}

/*
 * Pops from a stack
 * Return:
 *	Normal: Item at top of stack
 * 	When stack is empty: null
 */
char* pop(Stack* stk) {
	if(isEmpty(stk)) return NULL; 
	char* r = (char*) malloc(sizeof(char*) * sizeof((stk->array)[stk->top]));
	// copies element value to r
	strcpy(r, (stk->array)[stk->top]);
	// frees space of former element
	free((stk->array)[stk->top]);
	stk->top--;
	return r;
}

/*
 * Returns top element of stack
 * Return:
 *	Normal: Item at top of stack
 * 	When stack is empty: null
 */
char* peek(Stack* stk) {
	if(isEmpty(stk)) return NULL; 
	char* r = stk->array[stk->top];
	return r;
}

/*
 * Prints out the information of a stack
 */
void print(Stack* stk) {
	if(isEmpty(stk)){
		printf("%s\n", STR_PRINT_NO_ITEMS);
		return;
	}
	printf("%s ", STR_PRINT_ITEMS);
	int i;
	for(i = 0; i <= stk->top; i++){
		printf("%s ", stk->array[i]);
	}
	printf("\n");
}

/*
 * Destructs a stack
 */
void stack_delete(Stack* stk) {
	int i;
	// first frees each element
	for (i = stk->top; i >= 0; i--)
		free(stk->array[i]);
	// then frees the array
	free(stk->array);
}