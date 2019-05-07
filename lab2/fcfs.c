#include<stdio.h>
#include<stdlib.h>
struct process
{
	int pid;
	int a_t;
	int b_t;
	int w_t;
	int ta_t;
	int r_t;
};

void sort(struct process plist[],int n)
{
	struct process temp;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			if(plist[j].a_t>plist[j+1].a_t)
			{
				temp=plist[j];
				plist[j]=plist[j+1];
				plist[j+1]=temp;
			}
		}
	}
}

void find_ta_t(struct process plist[],int n)
{
	for(int i=0;i<n;i++)
	{
		plist[i].ta_t=plist[i].w_t+plist[i].b_t;
	}
}

void find_w_t(struct process plist[],int n)
{
	plist[0].w_t=0;
	for(int i=1;i<n;i++)
	{
		plist[i].w_t=plist[i-1].w_t+plist[i-1].b_t-(plist[i].a_t-plist[i-1].a_t);
	}
}

void find_time(struct process plist[],int n)
{
	sort(plist,n);					                              //sort according to arrival time
	
	for(int i=0;i<n;i++)
	{
		printf("%d ",plist[i].pid);
	}
	
	
	find_w_t(plist,n);
	find_ta_t(plist,n);
	
}
void find_avg_time(struct process plist[],int n)
{
	float avg_wt=0.0,avg_tat=0.0;
	float twt=0.0,ttat=0.0;
	int i;
	for(i=0;i<n;i++)
	{
		ttat+=plist[i].ta_t;
		twt+=plist[i].w_t;
	}
	printf("Avg Waiting Time:%f\n",twt/n);
	printf("Avg TurnAround Time:%f\n",ttat/n);
	
}
void main()
{
	FILE *fp;
	fp=fopen("fcfs_process.dat","r");
	if(fp==NULL)
	{
		printf("Error in Opening File Process.dat\n");
		exit(0);
	}
	int n;
	fscanf(fp,"%d",&n);
	
	struct process plist[n];
	int i=0;
	while(i<n)
	{
		fscanf(fp,"%d",&plist[i].pid);
		fscanf(fp,"%d",&plist[i].a_t);
		fscanf(fp,"%d",&plist[i].b_t);
		i++;
	}
	find_time(plist,n);
	
	printf("\npid   Arrival_t   Burst_t    Response_t     Waiting_t     Turnaround_t\n");
	for(int i=0;i<n;i++)
	{
		plist[i].r_t=plist[i].a_t+plist[i].w_t;
		
		printf("%d         %d            %d           %d            %d              %d\n",plist[i].pid,plist[i].a_t,plist[i].b_t,plist[i].r_t,plist[i].w_t,plist[i].ta_t);
	}
	
	find_avg_time(plist,n);
	
	fclose(fp);
}
