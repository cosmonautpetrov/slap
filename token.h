#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "stdio.h"

/* tokenizes slap language
	{
		lexer
	}
	{
		parser
	}
*/

#define TOK_NULL 0
#define OPEN_BRACE 1
#define CLOSE_BRACE 2
#define STRING 3
#define L_OR 4
#define SEMICOLON 5
#define COLON 6
#define APOS 7

struct token{
	int tok_type;
	void* data;
	struct token* next;
};

struct token* tokenize(char*); //tokenizes string of inputs
char* single_to_str(char*,int (*fpointer)(int)); //pass source and function pointer to isX() function, returns string
int accept(struct token*,int type); //"accepts" a token
int expect(struct token*,int type); //"expects" a token
struct token* tlast(struct token*); //returns the last token in the list
struct token* tname(struct token*,char*);//returns a list of all of type "name" in the list

#endif
