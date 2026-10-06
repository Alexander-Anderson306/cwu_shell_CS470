#include "cpuinfo.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
int main(int argc, char** argv) {
	char c_flag = 0;
	char t_flag = 0;
	char n_flag = 0;
	char h_flag = 0;
	char unknown_flag = 0;
	int opt;


	while ((opt = getopt(argc, argv, "ctnh")) != -1) {
        	switch (opt) {
            		case 'c':
                		c_flag = 1;
                		break;

            		case 't':
                		t_flag = 1;
                		break;

            		case 'n':
                		n_flag = 1;
                		break;

            		case 'h':
                		h_flag = 1;
                		break;

            		case '?':
                		unknown_flag = 1;
        	        	break;
      	  	}

        	if (unknown_flag)
            	break;
    	}

    	if (unknown_flag) {
		fprintf(stderr, "ERROR: Unknown option entered\nExpected format cpuinfo [-c | -t | -n | -h]\n");
        	return 1;
	}

	if(h_flag) {
		printf(
                    "cpuinfo - Display CPU information.\n"
                    "\n"
                    "Usage:\n"
                    "    cpuinfo [OPTION]\n"
                    "\n"
                    "Options:\n"
                    "    -c              Print the CPU clock speed.\n"
                    "    -t              Print the CPU type.\n"
                    "    -n              Print the number of CPU cores.\n"
                    "    -h		 Display this help message and exit.\n"
                    "\n"
                    "Examples:\n"
                    "    cpuinfo -c\n"
                    "    cpuinfo -t\n"
                    "    cpuinfo -n\n"
		);
		return 0;
	}

	if (c_flag){
		uint64_t freq;
		size_t size = sizeof(freq);

		if (sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0) == 0) {
			printf("CPU Clock: %.2f GHz\n", freq / 1000000000.0);
	    	} else {
			fprintf(stderr, "ERROR: Unable to determine CPU clock.\n");
	    	}
	}

	if (t_flag){
		char cpu[256];
	    	size_t size = sizeof(cpu);

	    	if (sysctlbyname("machdep.cpu.brand_string", cpu, &size, NULL, 0) == 0){
			printf("CPU Type: %s\n", cpu);
	    	} else {
			fprintf(stderr,"ERROR: Unable to determine CPU type.\n");
		}
	}

	if (n_flag){
		int cores;
		size_t size = sizeof(cores);

		if (sysctlbyname("hw.physicalcpu", &cores, &size, NULL, 0) == 0){
			printf("CPU Cores: %d\n", cores);
		} else {
			fprintf(stderr,"ERROR: Unable to determine number of CPU cores.\n");
		}
	}

    return 0;
}
