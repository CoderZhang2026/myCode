#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	pid_t pid;

	int cnt = 0;
	
	pid = vfork();
		
	if(pid > 0)
	{
		while(1){
			printf("cnt=%d\n",cnt);
			printf("this is father print, pid = %d\n",getpid());
			sleep(1);
		}	
	}
	
	else if(pid == 0){
		
		while(1){
			printf("this is chilid print, pid = %d\n",getpid());
			sleep(1);
			cnt++;
			if(cnt == 3){
				exit(0);
				break;
			}
		}	
	}

	return 0;
}
