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
	int pr;
	int copy;
};

int quantum;

void sort(struct process plist[],int n)
{
	struct process temp;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			if(plist[j].a_t > plist[j+1].a_t)
			{
				temp=plist[j];
				plist[j]=plist[j+1];
				plist[j+1]=temp;
			}
		}
	}
}


int fr=0,rr=0;
int que[100];
void enq(int pid)
{
	que[rr++]=pid;
}
int deq()
{
	return que[fr++];
}
int isemp()
{
	if(fr==rr)
		return 1;
	return 0;
}

void enqueue(struct process plist[],int n,int t,int flag[])
{
	int mint=100000;
	for(int i=0;i<n;i++)
	{
		if(plist[i].a_t<=t && flag[i]==0)
		{
			enq(i);						
			flag[i]=1;
		}
	}
}

void find_time(struct process plist[],int n,int flag[])
{
	
	int t=0,j;
	sort(plist,n);
	enq(0);
	flag[0]=1;
	while(!isemp())
	{
		j=deq();
		if(plist[j].r_t==-1)
		{
			plist[j].r_t=t;
			
		}
		if(plist[j].b_t > quantum)
		{
			plist[j].b_t-=quantum;
			t=t+quantum;
			enqueue(plist,n,t,flag);
			enq(j);	
		}
		else
		{
			t=t+plist[j].b_t;
			plist[j].w_t=t-plist[j].a_t-plist[j].copy;
			plist[j].ta_t=t-plist[j].a_t;
		}
		
		printf("%d ",plist[j].pid);
	}
	
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
	fp=fopen("rr_process.dat","r");
	if(fp==NULL)
	{
		printf("Error in Opening File Peocess.dat\n");
		exit(0);
	}
	int n;
	fscanf(fp,"%d",&n);
	fscanf(fp,"%d",&quantum);
	

	
	struct process plist[n];
	int i=0;
	int flag[n];
	while(i<n)
	{
		fscanf(fp,"%d",&plist[i].pid);
		fscanf(fp,"%d",&plist[i].a_t);
		fscanf(fp,"%d",&plist[i].b_t);
		plist[i].copy=plist[i].b_t;
		plist[i].r_t=-1;
		flag[i]=0;
		i++;
	}
	
	
	find_time(plist,n,flag);
	
	printf("\npid Arrival_t Burst_t Response_t Waiting_t Turnaround_t\n");
	for(int i=0;i<n;i++)
	{	
		printf("%d         %d        %d         %d         %d          %d\n",plist[i].pid,plist[i].a_t,plist[i].copy,plist[i].r_t,plist[i].w_t,plist[i].ta_t);
	}
	find_avg_time(plist,n);
	
	fclose(fp);
}
