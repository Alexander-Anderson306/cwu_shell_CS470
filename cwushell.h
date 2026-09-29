#ifndef CWU_SHELL
#define CWU_SHELL
int prompt(char* new_prompt);
int cpuinfo(int argc, char** argv);
int meminfo(int argc, char** argv);
int external_command(int argc, char** argv);
#endif
