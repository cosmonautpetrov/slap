#include "token.h"

//int tok_type, void* data, stroken token* next

struct token* tokenize(char* src){
	//Create a list and a head for it
	struct token* t_list = malloc(sizeof(struct token));
	struct token* head = t_list;

	while(*src!='\0'){
		//ignore whitespace, exit on null
		while(isspace(*src)){
			src++;
		}
		if(*src=='\0')
			break;
		
		if(isalpha(*src)){
			char* temp=single_to_str(src,&isalpha);
			src+=strlen(temp);
			head->tok_type=STRING;
			head->data = (void*)strdup(temp);
			free(temp);
			head->next=malloc(sizeof(struct token));
			head=head->next;
			continue;	
		}
		//if alpha character found
		/*if(isalpha(*src)){
			char* temp=malloc(sizeof(char)*1);
			int i;
			//copy over string
			for(i=0;isalpha(*src);i++){
				temp[i]=*src;
				temp=realloc(temp,sizeof(char)*i+1);
				src++;
			}
			temp[i]='\0';
			//setup STRING TOKEN
			head->tok_type=STRING;
			head->data = (void*)strdup(temp);
			free(temp);
			//next token
			head->next = malloc(sizeof(struct token));
			head=head->next;
			continue;
		}
		*/
		//if digit character found (identical thing for above parser, merge in a single function (fpointer)
		//check for misc. single-character tokens
		switch(*src){
			case '{':
				head->tok_type=OPEN_BRACE;
				head->next=malloc(sizeof(struct token));
				head=head->next;
				break;
			case '}':
				head->tok_type=CLOSE_BRACE;
				head->next=malloc(sizeof(struct token));
				head=head->next;
				break;
			case '|':
				head->tok_type=L_OR;
				head->next=malloc(sizeof(struct token));
				head=head->next;
				break;
			case ';':
				head->tok_type=SEMICOLON;
				head->next=malloc(sizeof(struct token));
				head=head->next;
				break;
			case ':':
				head->tok_type=COLON;
				head->next=malloc(sizeof(struct token));
				head=head->next;
				break;
			case '\'':
				head->tok_type=APOS;
				head->next=malloc(sizeof(struct token));
				head=head->next;
				break;
			default:
				break;
		}
		src++;		
	}
	//final NULL token, end of program
	head->tok_type=TOK_NULL;
	head->next = 0;
	return t_list;	
}

int accept(struct token* src,int curr){
	if(src->tok_type!=curr)
		return 0;
	else
		return 1;	
}

int expect(struct token* src,int curr){
	if(accept(src,curr))
		return 1;
	else{
		printf("error: expected %i and found %i instead.\n",curr,src->tok_type);
		//cleanup here somewhere
		exit(0);
	}
}

char* single_to_str(char* src, int (*fpointer)(int)){
	if(fpointer(*src)){
		char* temp=malloc(sizeof(char)*1);
		int i=0;
		for(i=0;fpointer(*src);i++){
			temp[i]=*src;
			temp=realloc(temp,sizeof(char)*i+1);
			src++;
		}
		temp[i]='\0';
		return temp;
	}	
	return 0;
}
