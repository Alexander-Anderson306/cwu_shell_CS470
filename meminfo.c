#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <mach/mach.h>

int main(int argc, char** argv) {
	char t_flag = 0;
	char u_flag = 0;
	char c_flag = 0;
	char h_flag = 0;
	char unknown_flag = 0;
	int opt;

	if(argc == 1) {
		fprintf(stderr, "ERROR: No option entered\nExpected format meminfo [-t | -u | -c | -h]\n");
		return 2;
	}

	while ((opt = getopt(argc, argv, "tuch")) != -1) {
        	switch (opt) {
            		case 't':
                		t_flag = 1;
                		break;

            		case 'u':
                		u_flag = 1;
                		break;

            		case 'c':
                		c_flag = 1;
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

	if(optind < argc){
		fprintf(stderr, "ERROR: Unknown argument or command entered\nmeminfo does not expect any argument\n");
		return 3;
	}

    	if(unknown_flag) {
		fprintf(stderr, "ERROR: Unknown option entered\nExpected format meminfo [-t | -u | -c | -h]\n");
        	return 1;
	}

	if(h_flag) {
		printf(
                    "meminfo - Display memory information.\n"
                    "\n"
                    "Usage:\n"
                    "	meminfo [OPTION]\n"
                    "\n"
                    "Options:\n"
                    "    -t		Print the total RAM memory available in bytes.\n"
                    "    -u		Print the used RAM memory in bytes.\n"
                    "    -c		Print the size of the L2 cache/core in bytes.\n"
                    "    -h		Display this help message and exit.\n"
                    "\n"
                    "Examples:\n"
                    "		meminfo -t\n"
                    "		meminfo -u\n"
                    "		meminfo -c\n"
		);
		return 0;
	}

	if(t_flag){
		uint64_t memory;
		size_t size = sizeof(memory);

		if (sysctlbyname("hw.memsize", &memory, &size, NULL, 0) == 0) {
			printf("Total RAM: %llu bytes\n", memory);
	    	} else {
			fprintf(stderr, "ERROR: Unable to determine total RAM memory.\n");
	    	}
	}

    //the u flag code was generated using AI
	if(u_flag){
	    vm_statistics64_data_t vm_stats;
	    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
	    vm_size_t page_size;

	    if (host_page_size(mach_host_self(), &page_size) != KERN_SUCCESS) {
		    fprintf(stderr, "ERROR: Unable to determine memory page size.\n");
	    } else if (host_statistics64(
			mach_host_self(),
			HOST_VM_INFO64,
			(host_info64_t)&vm_stats,
			&count) == KERN_SUCCESS) {

		    uint64_t used_memory =
			(uint64_t)(vm_stats.active_count +
			vm_stats.inactive_count +
			vm_stats.wire_count +
			vm_stats.compressor_page_count)
			* page_size;
		    printf("Used RAM: %llu bytes\n", used_memory);
	    } else {
		    fprintf(stderr, "ERROR: Unable to determine used RAM memory.\n");
	    }
	}

	if(c_flag){
		uint64_t cache;
		size_t size = sizeof(cache);

		if (sysctlbyname("hw.l2cachesize", &cache, &size, NULL, 0) == 0){
			printf("L2 Cache/Core: %llu bytes\n", cache);
		} else {
			fprintf(stderr,"ERROR: Unable to determine L2 cache size.\n");
		}
	}

	return 0;
}
