#ifndef _MAIN_H_
#define _MAIN_H_

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "token.h"
#include "table.h"
/*
 SLAP (student parser generator, what does the acronym stand for again) Language basic
 {
	token : 'string'
	token : 123
 }
 {
	rule : token | rule ;
	rule : ;
 }
*/

int main_block(); //main block lex/parse
int lex_rule(); //lexer rule
int parse_rule(); //introduction of parser rule
	
#endif
