#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>

int main(int argc,char *argv[]) 
{
	int h=0,c=0,i,status;
	pid_t pid[c],m_pid;
	
	if(argc!=3) 
	{
		printf("Error: Invalid arguments\n");
		exit(0);
	}
  	h =atoi(argv[1]);
	c= atoi(argv[2]);
	printf( "%*s", 2*h, "" );
	printf("(%d): Process starting..\n",getpid());
	printf( "%*s", 2*h, "" );
	printf("(%d): Parent's id= (%d)\n",getpid(),getpid());
	printf( "%*s", 2*h, "" );
	printf("(%d): Height of the tree = %d\n",getpid(),h);
	printf( "%*s", 2*h, "" );
	printf("(%d): Creating %d children at height %d\n",getpid(),c,h-1);
	
	if(h>1) 
	{	
		for(i=0;i<c;i++) 
		{
			pid[i]=fork();
			if(pid[i] < 0) 
			{
				fprintf(stderr,"Error in fork system call!");
				exit(1);
			}
			else if(pid[i]==0) 
			{
				char ch[2],hnew[2];
				sprintf(ch,"%d",c);
				sprintf(hnew,"%d",h-1);
				if(execlp(argv[0],argv[0],hnew,ch,(char *) NULL) == -1) 
				{
					fprintf(stderr, "execlp failed %d\n",errno);
				}
				exit(0);
			}		
		}
		while(c>0)
		{
				m_pid=wait(&status);
				c--;
		}
		printf( "%*s", 2*h, "" );
		printf("(%d):Terminating at height %d\n",getpid(),h);
		
	}
	else 
	{
		printf( "%*s", 2*h, "" );
		printf("(%d):Terminating at height %d\n",getpid(),h);
	}
     return 0;
}	

