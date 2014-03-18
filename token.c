#include "token.h"

//int tok_type, void* data, stroken token* next
#define NEW_TOKEN(X) X->next=malloc(sizeof(struct token));X=X->next

//Tokenizes input stream into list of tokens
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
		
		if(isalpha(*src)){ //testing new parsing function
			char* temp=single_to_str(src,&isalpha);
			src+=strlen(temp);
			head->tok_type=STRING;
			head->data = (void*)strdup(temp);
			free(temp);
			NEW_TOKEN(head);
			//head->next=malloc(sizeof(struct token));
			//head=head->next;
			continue;	
		}
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

//Function for accepting tokens in parser. Prints type/data
int accept(struct token* src,int curr){
	if(src->tok_type!=curr)
		return 0;
	else{
		char* temp;
		if(curr==STRING){
			temp=(char*)src->data;
			printf("ACCEPTED:%s,%s\n",put_token(curr),temp);
		}
		printf("ACCEPTED:%s\n",put_token(curr));
		return 1;
	}
}

//Function for expected tokens in parser. 
int expect(struct token* src,int curr){
	if(accept(src,curr))
		return 1;
	else{
		printf("error: expected %i and found %i instead.\n",curr,src->tok_type);
		//cleanup here somewhere
		exit(0);
	}
}

//Function for checking type of string.
//Essentially compressed replacement for isX()
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

//Lazy string return for types
char* put_token(int type){
	switch(type){
		case TOK_NULL:
			return "NULL";
		case OPEN_BRACE:
			return "OPEN_BRACE";
		case CLOSE_BRACE:
			return "CLOSE_BRACE";
		case STRING:
			return "STRING";
		case L_OR:
			return "LEFT_OR";
		case SEMICOLON:
			return "SEMICOLON";
		case COLON:
			return "COLON";
		case APOS:
			return "APOSTROPHE";
		default:
			return "UNKNOWN";
	}
}
