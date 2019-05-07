#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>

char s[100],st[100],st1[100],st2[2],st3[2];
int count=0;
int main()
{
    int fd1[2];
    int fd2[2];
    int fd3[2];
    pid_t p,p2;
    
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd3)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    p=fork();
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
    
    else if (p > 0)                                       // 1st process
    {  
        printf("Enter String:");
        fgets(s,100,stdin);
        close(fd1[0]);  
        write(fd1[1],s,strlen(s)+1); 
        close(fd1[1]); 

        wait(NULL); 
  
        close(fd3[1]); 
        read(fd3[0],st3,sizeof(st3)); 
        int count1;
        count1 = (int)st3[0];
        printf("No of words in string:%d\n",count1);
        close(fd3[0]);
    } 
    else                                               // 2nd process
    { 
        close(fd1[1]);
        read(fd1[0],st,100);
        close(fd1[0]); 
        int i=0,j=0;
        bool flag=false;
        while(st[i] != '\0')   
        {
             if(st[i]!= ' ')  
             {
                 st1[j++] = st[i];
                 flag=false;
             }
             if(st[i]==' ' && flag==false)
             {
               st1[j++]=st[i];
               flag=true;
             }
             i++;
        }
        st1[j] = '\0';
        
        close(fd2[0]);
        write(fd2[1],st1,strlen(st1)+1);
        close(fd2[1]);
        p2=fork();
        wait(NULL);
        
        if(p2==0)                                             // 3rd process
        {
           close(fd2[1]);
           read(fd2[0],st1,100);
           close(fd2[0]);
           int i;
           for(i=0;st1[i]!='\0';i++)
           {
				if(i==0)
				{
					if((st1[i]>='a' && st1[i]<='z'))
						st1[i]=st1[i]-32; 
					continue; 
				}
				if(st1[i]==' ')
				{
					i++;
					if(st1[i]>='a' && st1[i]<='z')
					{
						st1[i]=st1[i]-32; 
						continue; 
					}
				}
				else
			    {
					if(st1[i]>='A' && st1[i]<='Z')
						st1[i]=st1[i]+32;
				}
            }
           
            printf("\nOutput String:%s\n",st1);
            
		    i=0;
		    while(st1[i]!='\0')                          // To count no of words in a string
		    {
		       if(st1[i]==' ')
		             count++;
		       i++;
		    }
		    st2[0] = count+1;
		    st2[1] = '\0';
		    close(fd3[0]);
		    write(fd3[1],st2,sizeof(st2));
		    close(fd3[1]);
		    exit(0); 
	    }
     } 
} 
