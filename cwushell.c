#include "cwushell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
int main() {
	//check if there is a shell avaliable for use on this system
	int ret_var = 0;
	char shell_flag = 1;
	if(!system(NULL)) {
		fprintf(stderr, "WARNING: no subshell detected, functionality of cwushell limited\n");
		shell_flag = 0;
	}
	char* input_buff = malloc(BUFFER_SIZE * sizeof(char));
	input_buff[0] = '\0';
	char* current_path = "temp";
	char* current_prompt = "cwushell";
	const char* ex = "exit\0";
	//loop exits when user enters exit command
	while(strstr(input_buff, ex) == NULL) {
		//could read more than one byte at a time here
		//ask dr vajda for a better way to do this  I KNOW ABOUT freads but it would be cool to implement pipes in the future.
		char input_c;
		int buff_index = 0;
		int buff_scale = 1;
		printf("%s%s> ",current_path, current_prompt);
		//clear and resize input buffer
		if(buff_scale > 1) {
			free(input_buff);
			input_buff = malloc(BUFFER_SIZE * sizeof(char));
			input_buff[0] = '\0';
			buff_scale = 1;
		} else {
			memset(input_buff, 0, BUFFER_SIZE);
		}
		while((input_c = fgetc(stdin)) != EOF && input_c != '\n') {
			//resize buffer if buffer is too small
			if(buff_index >= buff_scale * BUFFER_SIZE) {
				buff_scale*=2;
				char* temp = realloc(input_buff, BUFFER_SIZE * buff_scale * sizeof(char));
				free(input_buff);
				if(temp == NULL){
					fprintf(stderr, "realloc error, not enough memory for input.\n");
					exit(-1);
				}
				input_buff = temp;
			}
			input_buff[buff_index++] = input_c;
		}

		//pass command to info
		ret_var = external_command(input_buff);

	}
	free(input_buff);
	return ret_var;
	
}


int prompt(char* new_prompt){
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
