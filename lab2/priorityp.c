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


int shortest(struct process plist[],int n,int t,int flag[])
{
	int minp=100000,k=0;
	for(int i=0;i<n;i++)
	{
		if(plist[i].a_t <= t && flag[i]==1 && plist[i].pr < minp) 
		{
			minp=plist[i].pr;
			k=i;
		}
	}
	return k;
}


void find_time(struct process plist[],int n,int flag[])
{
	
	int t=0,k=0,j;
	while(k<n)
	{
		j=shortest(plist,n,t,flag);
		plist[j].b_t-=1;
		
		if(plist[j].r_t==-1)
		{
			plist[j].r_t=t;
		}
		printf("%d ",plist[j].pid);
		t=t+1;
		if(plist[j].b_t==0)
		{
			flag[j]=0;								
			k++;
			plist[j].w_t=t-plist[j].a_t-plist[j].copy;
			plist[j].ta_t=t-plist[j].a_t;
		}
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
	fp=fopen("pr_process.dat","r");
	if(fp==NULL)
	{
		printf("Error in Opening File Peocess.dat\n");
		exit(0);
	}
	int n;
	fscanf(fp,"%d",&n);
	
	struct process plist[n];
	int i=0;
	int flag[n];
	while(i<n)
	{
		fscanf(fp,"%d",&plist[i].pid);
		fscanf(fp,"%d",&plist[i].a_t);
		fscanf(fp,"%d",&plist[i].pr);
		fscanf(fp,"%d",&plist[i].b_t);
		flag[i]=1;
		plist[i].copy=plist[i].b_t;
		plist[i].r_t=-1;
		i++;
	}
	
	find_time(plist,n,flag);
	
	printf("\npid    Arrival_t Response_t Waiting_t Turnaround_t\n");
	for(int i=0;i<n;i++)
	{
		
		printf("%d           %d         %d        %d       %d\n",plist[i].pid,plist[i].a_t,plist[i].r_t,plist[i].w_t,plist[i].ta_t);
	}
	find_avg_time(plist,n);
	
	fclose(fp);
}
