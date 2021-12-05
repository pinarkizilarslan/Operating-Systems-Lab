#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int createTree(int height, int n) {
	
	int PID = getpid();
	char myChar[300];
	sprintf(myChar, "pstree -p %d", PID);
	
	for (int i=0;i<=height;i++) {
	
		PID = fork();
		
		if (PID == 0) {
			if (n == 0) {
				sleep(2);
				printf("PID:%d, PPID:%d \n", getpid(), getppid());
				return 0;
			}

			else {
				printf("PID:%d, PPID:%d \n", getpid(), getppid());
				if (height == i) {
					system(myChar);
					return 0;
				}
			}
		}
						
		else {
			sleep(1);
			n++;
			if (n == 2) return 0;        
			printf("PID:%d, PPID:%d \n", getpid(), getppid());
			printf("Waiting for 2 seconds...\n");
			sleep(2);
		}
	}
}

int main(int argc, char *argv[]) {
		
	if (argv[1] == NULL) {
		printf("Please enter a dept!\n");
		return 0;
	}	
	
	int height = atoi(argv[1]); //char* to int in C
	int n=0;
	char opt;
	
	if (height < 2) {
		printf("Please enter an integer of at least 2!\n");
		return 0;
	}		
	
	for (int i=1;i<argc;i++){
			
		opt = argv[i][0];		
		switch (opt) {
			case 'i':
				printf("152120171063 @pinarkizilarslan wrote this masterpiece. :) \n");
				break;
			case 'd':
				height=height*2;
				printf("New Depth : %d \n",height);
				break;
		}
		
		opt = argv[i][1];
		switch (opt) {
			case 'i':
				printf("152120171063 @pinarkizilarslan wrote this masterpiece. :) \n");
				break;
			case 'd':
				height=height*2;
				printf("New Depth : %d \n",height);
				break;
		}
	}
	
	createTree(height, n);
	return 0;
}
