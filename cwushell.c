#include "cwushell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
int main() {
	char* input_buff = malloc(BUFFER_SIZE * sizeof(char));
	input_buff[0] = '\0';
	char* current_path = "temp";
	char* current_prompt = "cwushell";
	const char* ex = "exit";
	//loop exits when user enters exit command
	while(strstr(input_buff, ex) == NULL) {
		//could read more than one byte at a time here
		//but I wont
		char input_c;
		int buff_index = 0;
		int buff_scale = 1;
		printf("%s%s> ",current_path, current_prompt);
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

		//test
		printf("%s", input_buff);
		return 0;
	}
	free(input_buff);
	return 0;
	
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

int external_command(int argc, char **argv){
	return 0;
}
