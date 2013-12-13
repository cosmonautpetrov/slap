#ifndef _TABLE_H_
#define _TABLE_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "token.h"

struct rule{
	struct token* tlist;
	char* name;	
};

struct ruleset{
	struct rule* rlist;
	int rnum;	
};

struct ruleset* new_ruleset();
int new_rule(struct ruleset*,char*,struct token*);//creates a new rule and adds it
int add_to_rule(struct token*);//adds a token to the rule

struct ruleset* global_ruleset;

#endif
