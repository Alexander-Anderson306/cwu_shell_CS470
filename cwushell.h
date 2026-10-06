#ifndef CWU_SHELL
#define CWU_SHELL
typedef enum {
	EXITC,
	PROMPTC,
	CPUINFOC,
	MEMINFOC,
	CDC,
	SYSTEMC
} Command;
Command input_map(char* input);
int prompt(int argc, char** argv);
#endif
