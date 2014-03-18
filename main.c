#include "main.h"

//Global lists for source tokens and head of token list.
struct token* src;
struct token* curr;

//Define for moving through list of tokens
#define T_NEXT(X) X=X->next

//Main function, takes input from terminal as string
int main(int argc, char** argv){
	//Nothing to see here- if there's an argument, tokenize/parse.
	if(argc>1){
		src=tokenize(argv[1]);
		curr=src;
		main_block();
	}
	return 0;
}

//Main block of language parser
int main_block(){
	if(accept(curr,OPEN_BRACE)){
		T_NEXT(curr);
		if(accept(curr,STRING)){ //Parse lex rules before block closes
			do{
				lex_rule();
			}while(!accept(curr,CLOSE_BRACE));//temp
			T_NEXT(curr);
			printf("lex_rule end\n");
		}
		else{
			expect(curr, CLOSE_BRACE);T_NEXT(curr);
		}
		expect(curr,OPEN_BRACE);
		T_NEXT(curr);
		if(accept(curr,STRING)){ //Parse parse rules before block closes
			do{
				parse_rule();
			}while(!accept(curr,CLOSE_BRACE));
			T_NEXT(curr);
			printf("parse_rule end\n");
		}
		else{
			expect(curr, CLOSE_BRACE);T_NEXT(curr);	
		}
	}
}

//Self explanatory for the most part.
int lex_rule(){
	printf("entering lex_rule()\n");
	expect(curr,STRING);
	T_NEXT(curr);
	expect(curr,COLON);
	T_NEXT(curr);
	if(accept(curr,APOS)){
		T_NEXT(curr);
		if(accept(curr,STRING)){
			T_NEXT(curr);
		}
		expect(curr,APOS);
		T_NEXT(curr);
	}
	expect(curr,SEMICOLON);
	T_NEXT(curr);
	return 0;
}

//See above.
int parse_rule(){
	printf("entering parse_rule()\n");
	expect(curr, STRING);
	T_NEXT(curr);
	expect(curr,COLON);
	T_NEXT(curr);

	while(!accept(curr,SEMICOLON)){ //get all strings / ors
		if(accept(curr,STRING)){
			T_NEXT(curr);
		}
		if(accept(curr,L_OR)){
			T_NEXT(curr);
		}
	}
	
	T_NEXT(curr);
	return 0;
}
