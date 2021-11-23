#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h> 
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <pthread.h>

time_t lastModified;
void *listenChanges(void *arg);
int isModified = -1; // if it's 23 it means that it did not opened
struct stat attr;

void handler(int sig_num) {

	printf("Handler\t-> Ctrl + Z & Ctrl + C is blocked.\n");
	fflush(stdout);
}  

int main(int argc, char **argv) {

	time_t t;   
	time(&t);
	
	if (argc<2) { //Check argument count is equals to 1.
		printf("%s must be executed with one additional argument (pathInputFile)!\n", argv[0]);
		printf("Aborted automatically\n");
		return 0;
	}
	
    	
	else if (argc>2) { //Check argument count is more than 2.
		printf("%s must be executed with one additional argument (pathInputFile)!\n", argv[0]);
		printf("Aborted automatically...\n");
		return 0;
	}
	
	// argc is 2
	char *pathInp, number[32], message[100];
	long readNumber;
	int pfd[2], child, child_status;
	pthread_t listenChange;
	
	pathInp = argv[1];
	pipe(pfd);
	printf("Pipe was created successfully...\n");
	child=fork();
	
	if (child==0) { // child process
	
		printf("Child\t\t-> My PID is %d, PPID is %d\n", getpid(),getppid());
		pthread_create(&listenChange, NULL, listenChanges, argv[1]);	//listenChange start	
		int file_read_status=0; 
		
		while(file_read_status==0) {
		
			if(isModified!=0) {				
				printf("\t\t--> Last modified time: %s ", ctime(&t));
				FILE *fp;
				fp = fopen(pathInp, "r");
				fscanf(fp, "%s", message);
				fclose(fp);
				readNumber = atol(message);
				printf("\t\t     %s: %li\n", pathInp, readNumber);
								
				if(strlen(message)<12) {
					printf("\t\t-- wrong input! few digits...\n");
					file_read_status = 0;
					isModified = 0;
				}
				
				else if(strlen(message)>12) {
					printf("\t\t-- number of digits overflowed..\n");
					file_read_status=0;
					isModified=0;
				}
				
				else {
					printf("Child\t\t-> Parsing and printing Phone Number (Hardcodded, just for info)\n");
					file_read_status=1;	
				}
			}
		}		
		
		close(pfd[0]);
		write(pfd[1], &readNumber, sizeof(readNumber));
		close(pfd[1]);		
		sleep(4);
		exit(1);
	}
	
	else { // parent process	
		printf("Parent\t\t-> My PID is %d, PPID is %d\n", getpid(), getppid());
		sleep(1); // wait 1 second to give priority to child
		
		long alinan;

		close(pfd[1]);
		read(pfd[0], &readNumber, sizeof(readNumber));
		close(pfd[0]);
		
		sleep(1);
		
		long countryCode = readNumber/10000000000;
		long part=readNumber;
		long _year=readNumber;
		long areaCode=(readNumber/10000000)-(countryCode*1000);
		long telNo=readNumber-((readNumber/10000000)*10000000);
		
		part = part - countryCode*100;
		_year = _year - (countryCode*1000000 + part * 10000);
		
		if(countryCode == 90)		
			printf("\t\t  Country: Turkey\n");
		else
			printf("\t\t  Country: Other City\n");

		if(areaCode == 222) 		
			printf("\t\t  City: Eskisehir\n");			
		else
			printf("\t\t  City: Other City\n");
			
		printf("\t\t  Rest of the phone number:%li \n",telNo);
		printf("Child\t\t-> The message is being send. Warning: Type Constraint!\n");
		printf("Child\t\t-> Sleeping 4 sec.s\n");
		printf("Parent\t\t-> Incoming message from child is %li\n", readNumber);
		printf("\t     ----> Hint: Incoming message size is fixed 8 bytes for this application. Not 12 (digit count) or something other! \n");
				
		if(countryCode == 90 && areaCode == 222) {
			printf("Parent\t\t-> Child process is being waited.\n");
			printf("Child\t\t-> Slept 4 sec.s\n");
			wait(&child_status);			
			printf("Terminating PID: %d, PPID: %d\n", getpid(), getppid());			
			printf("Child\t\t-> Waiting is done.\n");			
		}
		
		long telNo2=telNo;
		long rev_num = 0;
		
    		while (telNo2 > 0) {
        		rev_num = rev_num * 10 + telNo2 % 10;
        		telNo2 = telNo2 / 10;
    		}
					
		if(rev_num > telNo) {		
			sleep(4);
			if(areaCode != 222) {		
				printf("Parent\t\t-> I'll kill you if unreversed numbr is lower than reversed number.\n");
				printf("Parent\t\t-> Alarm clock signal was scheduled in 4 seconds...\n");
				printf("Alarm Handler\t-> Alarm clock signal has beed received\n");
				printf("Parent\t\t-> Child is killed. Or not?\n");
			}		
			printf("Terminating PID: %d, PPID: %d\n", getpid(), getppid());
		
			if(countryCode != 90) {
				printf("Parent\t\t-> Alarm clock signal was scheduled in 6 seconds... \n");
				signal(SIGINT, handler);  // CTRL+C Protection
        			signal(SIGTSTP, handler); // CTRL+Z Protection        		
        			sleep(6);
			}
		}
		
		else {			
			sleep(4);
			if(countryCode != 90) {
				printf("Parent\t\t-> Alarm clock signal was scheduled in 10 seconds... \n");
        			printf("Parent\t\t-> Only the God can judge me! (freedom for 10 seconds).\n");
	        		signal(SIGINT, handler);  // CTRL+C Protection
        			signal(SIGTSTP, handler); // CTRL+Z Protection
        			sleep(10);
        		}
        		else {
        			printf("Terminating PID: %d, PPID: %d\n", getpid(), getppid());
        			printf("Child\t\t-> Slept 4 sec.s\n");
        			printf("Terminating PID: %d, PPID: %d\n", getpid(), getppid());
        		}
		}		
	}		
		
	return 0;
}

void *listenChanges(void *arg) {

	char *inp_path = (char *)arg;
	stat(inp_path, &attr);
	lastModified = attr.st_mtime;
	sleep(1);
	
	while (1) {	
		stat(inp_path, &attr);
		if (lastModified != attr.st_mtime) {
			lastModified = attr.st_mtime;
			isModified = 1;
		}
		sleep(1);
	}
}
