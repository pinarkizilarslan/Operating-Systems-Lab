#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h> //for usleep(); if you need to sleep shorter than 1 sec. //usleep((int)(100000)); for 0.1 sec.s
#include <pthread.h>
#include <string.h>

char *pathServer;
struct stat attr1, attr2;
int flag = 0;

void *funcprintTimeAndChanges(void *_pathClient) {

	char pathLogFile[250];
	char copy[250];
	char info[1000];
	int count=1;
	char *pathClient=_pathClient;
	
	//Commands were created for system functions to work
	sprintf(pathLogFile, "%s171063_uyg3A_logAll.log", pathServer);
	sprintf(info, "cd %s && ls -hs >> %s171063_uyg3A_logAll.log \n", pathClient, pathServer);
	sprintf(info, "wc -wcl %s*", pathClient);

	while (1) {
		//Checked for change in funcChecker function. If there is a change, the global flag variable is set to 1
		if (flag == 1) {
					
			sprintf(copy, "cat %s* >> %sclientTest%d.0.txt", pathClient,pathServer,count);
			system(copy);
			fflush(stdout); //clear output buffer
			usleep((int)(100000));
								
			sprintf(info,"echo '\nVersion %d.0' | tee -a %s", count, pathLogFile);
			system(info);
			sprintf(info,"echo '--------------------------------------------' | tee -a %s", pathLogFile);
			system(info);
			sprintf(info,"echo 'Last modified time: %s'", ctime(&attr1.st_mtime));
			system(info);
			
			sprintf(info, "cat %s* | tee -a %s", pathClient, pathLogFile);
			system(info);
						
			sprintf(info,"echo -n '\nLines: ' | tee -a %s", pathLogFile);
			system(info);
			sprintf(info,"wc -l %s* | tee -a %s", pathClient, pathLogFile);
			system(info);
			sprintf(info,"echo -n 'Words: ' | tee -a %s", pathLogFile);
			system(info);
			sprintf(info,"wc -w %s* | tee -a %s", pathClient, pathLogFile);
			system(info);
			sprintf(info,"echo -n 'Characters: ' | tee -a %s", pathLogFile);
			system(info);
			sprintf(info,"wc -c %s* | tee -a %s", pathClient, pathLogFile);
			system(info);
			sprintf(info,"echo '--------------------------------------------' | tee -a %s", pathLogFile);
			system(info);
			
			flag = 0;
			count++;
		}
		
		usleep(1000000);
	}

	printf("This line should never be executed. Server program must always be running!\n");
}

void *funcChecker(void *pathClient) {
	stat(pathClient, &attr1);
	
	while (1) {	
		stat(pathClient, &attr2);

		//If there is a change during the run time, the change value is transferred to the attr1 variable. 
		if (attr1.st_mtime != attr2.st_mtime) {
			attr1 = attr2;
			flag = 1;
		}
		usleep(1000000);
	}

	printf("This line should never be executed. Server program must always be running!\n");
}


int main(int argc, char *argv[]) {
	
	if (argc < 3) {
		printf("Typed arg count is %d.\n\n",argc);
		printf("%s must be executed with exactly two addtional arguments (pathServer,pathClient)!\n",argv[0]);
		printf("Aborted automatically...\n");
		return -1;
	}

	else if (argc > 3) {
		printf("Typed arg count is %d.\n\n",argc);
		printf("Too many arguments!\n");
		printf("%s must be executed with exactly two addtional arguments (pathServer,pathClient)!\n",argv[0]);
		printf("Aborted automatically...\n");
		return -1;
	}

	else {
		pathServer = argv[1];
		char *pathClient = argv[2];
	
		char command[100];
		sprintf(command, "mkdir -p %s | mkdir -p %s", pathServer, pathClient);
		system(command);
		sprintf(command, "> %s171063_uyg3A_logAll.log | > %sclientText.txt", pathServer, pathClient);
		system(command);
		
	
		pthread_t timeAndChanges, checker;
		
		printf("Typed arg count is %d.\n\n", argc);
		printf("Main Function ->\n");
		printf("pathServer: %s\n", argv[1]);
		printf("pathClient: %s\n\n", argv[2]);
		
		printf("funcChecker ->\n");
		printf("pathClient: %s\n\n",argv[2]);
		pthread_create (&checker, NULL, funcChecker, argv[2]);
		
		printf("funcprintTimeAndChanges ->\n");
		printf("pathClient: %s\n", argv[2]);
		printf("pathLog: %s171063_uyg3A_logAll.log\n\n", argv[1]);
		pthread_create (&timeAndChanges, NULL, funcprintTimeAndChanges, argv[2]);
		
		//Threadlerin birbirlerinin işlemlerini bekleyerek çalışması sağlandı.
		pthread_join (checker, NULL);
		pthread_join (timeAndChanges, NULL);
	}

	return 0;
}
