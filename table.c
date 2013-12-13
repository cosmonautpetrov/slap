#include "table.h"

struct ruleset* new_ruleset(){
	struct ruleset* temp=malloc(sizeof(struct ruleset));
	temp->rlist=malloc(sizeof(struct rule));
	temp->rnum=0;
	return temp;
}

int new_rule(struct ruleset* dest, char* name, struct token* dat){
	dest->rlist=realloc(dest->rlist,sizeof(struct rule)*(dest->rnum+1));
	if(name){
		dest->rlist[dest->rnum].name=name;
	}
	if(dat){
		dest->rlist[dest->rnum].tlist;
	}
	dest->rnum++;
}	
