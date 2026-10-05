#include "cwushell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define INPUT_BUFFER_SIZE 1024 * 4
#define PATH_BUFFER 512
#define DELIMITERS " \t\r\n"
#define MAX_ARGS 128


char current_path[PATH_BUFFER];
char current_prompt[PATH_BUFFER];
char* parsed_input[MAX_ARGS];
int main() {
	//check if there is a shell avaliable for use on this system
	int ret_var = 0;
	char shell_flag = 1;
	char ex_flag = 0;
	int arg_count = 0;
	if(!system(NULL)) {
		fprintf(stderr, "WARNING: no subshell detected, functionality of cwushell limited\n");
		shell_flag = 0;
	}
	char* input_buff = malloc(INPUT_BUFFER_SIZE * sizeof(char));
	char* input_copy = malloc(INPUT_BUFFER_SIZE * sizeof(char));
	input_buff[INPUT_BUFFER_SIZE-1] = '\0';
	//avoid assignment warning by having ret_tok point to input_buff real assignment done in do while loop
	char* ret_tok = input_buff; 
	Command command;

	//setting current path and prompt
	//loop exits when user enters exit command
	strcpy(current_prompt, "cwushell");
	do{
		getcwd(current_path, sizeof(current_path));
		//reset input buffer
		memset(input_buff, 0, INPUT_BUFFER_SIZE * sizeof(char));
		arg_count = 0;
		printf("%s (%s)> ",current_path, current_prompt);
		fgets(input_buff, INPUT_BUFFER_SIZE, stdin);
		//check if input fits in buffer
		if(input_buff[INPUT_BUFFER_SIZE-1] != '\0') {
			ret_var = 2;
			fprintf(stderr, "ERROR: input buffer overflow, cwushell cannot handle inputs larger that %d bytes\n", INPUT_BUFFER_SIZE);
			continue;
		}
		input_buff[INPUT_BUFFER_SIZE-1] = '\0';
		//deep copy of input since strtok is not memory safe (or whatever the term is)
		strcpy(input_copy, input_buff);

		
		//combe through input
		char* tok = strtok(input_buff, DELIMITERS);
		while(tok != NULL && arg_count < MAX_ARGS-1) {
			parsed_input[arg_count++] = tok;
			tok = strtok(NULL, DELIMITERS);
		}

		//check for too many arguments error
		if(arg_count >= MAX_ARGS-1){
			fprintf(stderr, "ERROR: argument bufer overflow, cwushell cannot handle more than %d arguments", MAX_ARGS-1);
			ret_var = 3;
			continue;
		}

		//command is always the first token
		command = input_map(parsed_input[0]);
		
		//get the command being exicuted
		//pass command to info
		switch (command) {
			case EXITC:
				ret_tok = parsed_input[1];
				ex_flag = 1;
				break;
			case PROMPTC:
				prompt(arg_count, parsed_input);
				break;
			case MEMINFOC:
				meminfo(arg_count, parsed_input);
				break;
			case CPUINFOC:
				cpuinfo(arg_count, parsed_input);
				break;
			case CDC:
				if(parsed_input[1] == NULL) {
					chdir("$HOME");
				} else if((ret_var = chdir(parsed_input[2])) == -1) {
					fprintf(stderr, "ERROR: Target directory does not exist\n");
				}
				break;
			case SYSTEMC:
				if(shell_flag) {
					ret_var = system(input_copy);
				} else {
					fprintf(stderr, "ERROR: No subshell detected, unable to execute given command\n");
				}
				break;
				
		}
		
	} while(ex_flag == 0); //loop exits when exit command is entered

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

Command input_map(char* input) {
	if(strcmp(input, "exit") == 0) return EXITC;
	if(strcmp(input, "prompt") == 0) return PROMPTC;
	if(strcmp(input, "cpuinfo") == 0) return CPUINFOC;
	if(strcmp(input, "meminfo") == 0) return CPUINFOC;
	if(strcmp(input, "cd") == 0) return CDC;

	//if we cant match the command, pass it to system and let the native shell handle it
	return SYSTEMC;
}
int prompt(int argc, char** argv){
	if(argc > 2) {
		printf("ERROR: Too many arguments\nExpected input form: prompt [new_prompt]\n");
		return 1;
	}

	if(argc == 1) {
		strcpy(current_prompt, "cwushell");
		return 0;
	}


	if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		//did not feel like typing this so i generated this text with AI.
		printf(
		    "Usage: prompt [new_prompt]\n"
		    "       prompt [OPTION]\n"
		    "\n"
		    "Change the current shell prompt.\n"
		    "\n"
		    "If new_prompt is provided, the shell prompt is changed to new_prompt.\n"
		    "If no new_prompt is provided, the prompt is reset to the default\n"
		    "prompt \"cwushell>\".\n"
		    "\n"
		    "Options:\n"
		    "  -h, --help    Display this help message and exit.\n"
		    "\n"
		    "Examples:\n"
		    "  prompt mysh>      Change the prompt to \"mysh>\"\n"
		    "  prompt            Restore the default prompt \"cwushell>\"\n"
		    "  prompt --help     Display this help message\n"
		);
	} else {
		strcpy(current_prompt, argv[1]);
	}
	return 0;
}

int cpuinfo(int argc, char** argv){
	return 0;
}

int meminfo(int argc, char** argv){
	return 0;
}
