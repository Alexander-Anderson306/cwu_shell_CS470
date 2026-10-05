#ifndef CWU_SHELL
#define CWU_SHELL
typedef enum {
	EXITC,
	PROMPTC,
	CPUINFOC,
	MEMINFOC,
	SYSTEMC
} Command;
Command input_map(char* input);
int prompt(int argc, char** argv);
int cpuinfo(int argc, char** argv);
int meminfo(int argc, char** argv);
#endif
