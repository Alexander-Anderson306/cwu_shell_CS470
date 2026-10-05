#include "cwushell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_BUFFER 1024 * 4
#define PATH_BUFFER 512
#define DELIMITERS " \t\r\n"
#define MAX_ARGS 128

typedef enum {
	EXITC,
	PROMPTC,
	CPUINFOC,
	MEMINFOC,
	SYSTEMC
} Commands;

char current_path[PATH_BUFFER];
char current_prompt[PATH_BUFFER];
char* parsed_input[MAX_ARGS];
int main() {
	//check if there is a shell avaliable for use on this system
	int ret_var = 0;
	char shell_flag = 1;
	int arg_count = 0;
	if(!system(NULL)) {
		fprintf(stderr, "WARNING: no subshell detected, functionality of cwushell limited\n");
		shell_flag = 0;
	}
	char* input_buff = malloc(INPUT_BUFFER * sizeof(char));
	input_buff[INPUT_BUFFER-1] = '\0';
	const char* ex = "exit";
	//avoid assignment warning by having ret_tok point to input_buff real assignment done in do while loop
	char* ret_tok = input_buff; 
	char* command;
	//loop exits when user enters exit command
	do{
		//reset input buffer
		memset(input_buff, 0, INPUT_BUFFER * sizeof(char));
		printf("%s%s> ",current_path, current_prompt);
		fgets(input_buff, INPUT_BUFFER, stdin);
		//check if input fits in buffer
		if(input_buff[INPUT_BUFFER-1] != '\0') {
			ret_var = -1;
			fprintf(stderr, "ERROR: input buffer overflow, cwushell cannot handle inputs larger that %d bytes\n", INPUT_BUFFER);
			continue;
		}
		input_buff[INPUT_BUFFER-1] = '\0';
		
		//combe through input
		char* tok = strtok(input_buff, DELIMITERS);
		while(tok != NULL && arg_count < MAX_ARGS-1) {
			parsed_input[arg_count++] = tok;
			tok = strtok(NULL, DELIMITERS);
		}

		//check for too many arguments error
		if(arg_count >= MAX_ARGS-1){
			fprintf(stderr, "ERROR: argument bufer overflow, cwushell cannot handle more than %d arguments", MAX_ARGS-1);
			ret_var = -1;
			continue;
		}

		//command is always first token
		//in the case the command is exit, the second token should be the exit number
		command = parsed_input[0];
		ret_tok = parsed_input[1];
		
		//get the command being exicuted
		//pass command to info
		ret_var = external_command(input_buff);
	} while(strcmp(command, ex)); //loop exits when exit command is entered

	//handle edge cases with the return value
	int temp = 0;
	if(ret_tok != NULL) {
		temp = atoi(ret_tok);
	}

	if(temp != 0) {
		ret_var = temp;
	} else if(ret_tok != NULL && ret_tok[0] == '0') {
		ret_var = 0;
	}

	free(input_buff);
	return ret_var;
	
}


int prompt(char* new_prompt){
	strcpy(current_prompt, new_prompt);
	return 0;
}

int cpuinfo(int argc, char** argv){
	return 0;
}

int meminfo(int argc, char** argv){
	return 0;
}

int external_command(char* str){
	//pass variables to system function
	return system(str);
}
