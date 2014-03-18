#include "main.h"

struct token* src;
struct token* curr;

#define T_NEXT(X) X=X->next

int main(int argc, char** argv){
	if(argc>1){
	src=tokenize(argv[1]);
	curr=src;
	main_block();	
	/*
		printf("%s\n",argv[1]);
		struct token* temp=tokenize(argv[1]);
		struct token* head=temp;
		while(head->next){
			printf("%i\n",head->tok_type);
			head=head->next;
		}			
	}
	*/
	}
	return 0;
}

int main_block(){
	if(accept(curr,OPEN_BRACE)){
		T_NEXT(curr);
		if(accept(curr,STRING)){
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
		if(accept(curr,STRING)){
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
