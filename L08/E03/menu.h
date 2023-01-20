#include <cstdio>
#include <stdio.h>
#include <string.h>


typedef struct Choice {
	char description[50];
	char trigger[50];
} Choice;

int scan_choice(Choice* choices, int size){
	char answer[50];
	printf("\n\nInserisci un comando: ");
	scanf("%s", answer);
	for(int i = 0; i < size; i++){
		if(strcmp(answer, choices[i].trigger) == 0)
			return i;
	}	
	return -1;
}

void print_menu(Choice* choices, int size){
	for(int i = 0; i < size; i++){
		printf("\"%s\": %s\n", choices[i].trigger, choices[i].description);
	}
	printf("\n");

}


int menu_print_and_scan(Choice* choices, int size){
	print_menu(choices, size);
	return scan_choice(choices, size);

}
