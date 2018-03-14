#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct node {
	char word[100];
	int count;
	struct node* next;

} list;

typedef struct nodet {
	char character;
	int count;
	struct nodet* next;

} list2;

int main(int argc, char **argv ){

	//argument handling

	if(argc == 1){
		printf("No input files were given\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return 0;
	}

	int m;
	int scaleState = 0, wordState=0, lenval=10, characterState = 0;
	char arg[1000][1000];
	int argcou=0;
	for(m=1; m<argc; m++){
		if(argv[m][0] == '-'){
			if ( strcmp(argv[m], "-w")== 0 ){
				wordState = 1;
			} else if ( strcmp(argv[m], "-c")== 0  ){
				characterState = 1;
			} else if (strcmp(argv[m],"--scaled")== 0 ){
				scaleState = 1;
			} else if ( strcmp(argv[m], "-l")== 0  ){
				if (argc == (m+1)){
					printf("Not enough options for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
					return 0;
				}
				int length = strlen (argv[m+1]);
				int g;
				for(g=0;g<length;g++){
					if(!isdigit(argv[m+1][g])){
						printf("Invalid options for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
						return 0;

					} 
				}
				lenval = atoi(argv[m+1]);
				if(lenval == 0){
					return 0;
				}
				m++;
			} else{
				printf("Invalid option [%s]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n", argv[m]);
				return 0;
			}
		} else {
			strcpy(arg[argcou], argv[m]);
			argcou++;

		}
		
	}

	if( (wordState==1) && (characterState == 1) ){
		printf("[-c] and [-w] cannot use together\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return 0;
	} else if ( (wordState==0) && (characterState == 0)){
		wordState = 1;
	}
	
	if(argcou == 0){
		printf("No input files were given\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return 0;
	}

	int p;
	for(p=0; p<argcou; p++){
		FILE *f = fopen(arg[p],"r");
		if(f == NULL){
			printf("Cannot open one or more given files\n");
			return 0;
		}
	}

	// end of argument handling


	return 0;
}

void alpha(char* word) {                             //     ALPHA NUMERIC CHECKING
   while (*word) {
      if (!(*word >= 'a' && *word <= 'z') && !(*word >= '0' && *word <= '9')) {
         strcpy(word, word + 1);
         word--;
      }
      word++;
   }
}

void pushBack(list * head1, char *word2) {        //            ADDING ELEMENTS TO LIST
    list * current = head1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (list*)malloc(sizeof(list));
    strcpy(current->next->word, word2);
    current->next->count = 1;
    current->next->next = NULL;
    return;
}

void print_list(list * head1) {    //   PRINTING LIST
    list * current = head1;
    while (current != NULL) {
        printf("%s= %d \n",current->word, current->count);
        current = current->next;
    }
    return;
}

int checkList(list* head1, char *word2){                   // CHECKING LIST
	list * current = head1;
	while (current != NULL){
		if(strcmp(word2, current->word) == 0){
			return 0;
		}
		current = current->next;
	}
	return 1;
}

void increaseCount(list* head1, char *word2){                //   INCREASING COUNT
	list * current = head1;
	while (current != NULL){
		if(strcmp(word2, current->word) == 0){
			current->count = current->count + 1;
			return;
		}
		current = current->next;
	}
}