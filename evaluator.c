#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
// #include "stack.c"

// type convertors //

/*
*	changes a character to a string
* 	param:
* 		c - the character to be converted
*	return:
*		a char* of one element, c
*/
char* charToString(char c) {
	char *str = (char*)malloc(sizeof(char)*TWO);
	str[ZERO] = c;
	str[ONE] = '\0';
	return str;
}

/*
*	changes a string to a character
* 	param:
* 		str - the string to be converted
*	return:
*		the first character of the string
*/
char stringToChar(char* str) {
	return str[ZERO];
}

/*
*	changes an integer to a string
* 	param:
* 		res - the integer to be converted
*	return:
*		a char* of numbers
*/
char* intToString(int res) {
	char *str = (char*)malloc(BUFSIZ);
	sprintf(str,"%d",res);
	return str;
}

/*
*	changes a string to a integer
* 	param:
* 		str - the string to be converted
*	return:
*		an integer
*/
int stringToInt(char* str) {
	return atoi(str);
}

// type convertors end here //

#define GRTR 1
#define LSSR -1
#define EQIV 0
#define PLUS '+'
#define SUBT '-'
#define DIVI '/'
#define MULT '*'
#define MODO '%'

// helper functions //

/*
*	compare two operators to establish precesendce
* 	param:
* 		x - the first operator
*		y - the second operator
*	return:
*		GRTR - x's operator has precedence over y's
* 		EQIV - x & y share precedence
* 		LSSR - y's operator has precedence over x's
*/
int comp(char x, char y) {
	if(x == PLUS || x == SUBT)
		x = ONE;
	else x = TWO;
	if(y == PLUS || y == SUBT)
		y = ONE;
	else y = TWO;

	if(x > y)
		return GRTR;
	else if(x == y)
		return EQIV;
	else return LSSR;
}

/*
*	checks if a character is an operator
* 	param:
* 		c - the character to be surveyed
*	return:
*		true (1) or false (0) response
*/
int isOperator(char c) {
	if(	c == PLUS || 
		c == SUBT || 
		c == DIVI || 
		c == MULT || 
		c == MODO
	)		return ONE;
	else 	return ZERO;
}

/*
*	evaluates an operations effect on two integers
* 	param:
* 		a - the first integer
* 		b - the second integer
* 		c - the operator
*	return:
*		Normal: the value of a operating on b
* 		Incorrent input: 0
*/
int eval(int a, int b, char c) {
	if(c == PLUS) return a + b;
	if(c == SUBT) return a - b;
	if(c == DIVI) return a / b;
	if(c == MULT) return a * b;
	if(c == MODO) return a % b;
	return ZERO;
}

// helper functions end here //

/*
*	converts an infix string to a postfix string
* 	param:
* 		str - the string to be converted
*	return:
*		the converted postfix string
*/
char* convertToPostFix(char* str) {
	// allocates space for the output string, postfix
	char* postfix = (char*)malloc(sizeof(char)*sizeof(str));
	Stack * operatorStack = stack_init();
	
	// scans input (infix) string, acts on each character
	int i = ZERO;
	while (str[i] != '\0') {
		char c = str[i];
        if(isdigit(c)) // adds digits straight to output
            strcat(postfix, charToString(c));
		else if(c == '(') // pushes an open paren to the stack
			push(operatorStack, charToString(c));
		else if(c == ')'){ // case for closed paren
			char* s = (char*) malloc(sizeof(char));
			// pops through stack, adding elements to output until finding the
			// opening paren
			while(stringToChar(s) != '('){
				strcat(postfix, s);
				s = pop(operatorStack);
			}
			free(s);
		} else if(isOperator(c)) { // case for operator
			char* s = peek(operatorStack);
			// pops through stack for subsequent find operators with greater
			// or equal precedence
			while(s != NULL &&
                  isOperator(stringToChar(s)) &&
                  comp(stringToChar(s), c) >= ZERO){
				// adds those to output
				strcat(postfix, pop(operatorStack));
				s = peek(operatorStack);
			}
			// once those are added, adds this operator back in stack
			push(operatorStack, charToString(c));
		}
		i++;
	}

	//adds any remaining elements in the stack to the output
	while(!isEmpty(operatorStack))
		strcat(postfix, pop(operatorStack));

	return postfix;
}

/*
*	evaluates the value of a postfix expression
* 	param:
* 		str - a postfix expression
*	return:
*		the integer value of the result
*/
int calculateExpression(char* str) {
	Stack * storage = stack_init();
	
	// scans input (postfix) string, acts on each character
	int i = ZERO;
	while (str[i] != '\0') {
		char c = str[i];
        if(!isOperator(c)) // adds digits directly to the stack
			push(storage, charToString(c));
		else { // case for operators
			int b = stringToInt(pop(storage));
			int a = stringToInt(pop(storage));
			// takes the final last two elements as integers and pushes their
			// evaluation to the stack
            push(storage, intToString(eval(a, b, c)));
		} 
        i++;
	}
    
    // returns the last remaining value in the stack as the answer
	return stringToInt(pop(storage));
}


int main(int argc, char **argv) {
	
	if(argc < TWO)
		printf(STR_INCORRECT_ARGUMENT);
	else {
		char* input = (char*) malloc(sizeof(char) * sizeof(argv[1]));
		char* postfix = (char*) malloc(sizeof(char) * sizeof(argv[1]));
		strcpy(input, argv[1]); 
		postfix = convertToPostFix(input);
		int answer = calculateExpression(postfix);
		
		printf(STR_POSTFIX_EXPRESSION,postfix);
		printf(STR_RESULT,answer);
		printf("\n");
		
		free(input);
		free(postfix);
	}
	return EXIT_SUCCESS;
}
