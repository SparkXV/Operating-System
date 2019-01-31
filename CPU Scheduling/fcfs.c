#include<stdio.h>

struct process{
    int pid;
    int a_t;
    int r_t;
    int b_t1;
    int b_t2;
    int b_t3;
    int t_t;
    int w_t;
};

void sort(struct process p[],int n)         
{
  int i,j;
  struct process temp;
  for(i=0;i<n-1;i++)
  {
     for(j=0;j<n-i-1;j++)
     {
        if(p[j].a_t>p[j+1].a_t)
        {
          temp=p[j];
          p[j]=p[j+1];
          p[j+1]=temp;
        }
     }
  }
}
void wait(struct process p[],int n)
{
   int i;
   p[0].w_t=0;
   for(i=1;i<n;i++)
   {
      p[i].w_t=p[i-1].w_t+p[i-1].b_t1+p[i-1].b_t2+p[i-1].b_t3-(p[i].a_t-p[i-1].a_t);
      if(p[i].w_t<0)
           p[i].w_t=0;
   }
}
      
void turn(struct process p[],int n)
{
   int i;
   for(i=0;i<n;i++)
   {
      p[i].t_t=p[i].w_t+p[i].b_t1+p[i].b_t2+p[i].b_t3;
   }
}
void avg(struct process p[],int n)
{
   int i;
   float sum=0.0,count=0.0;
   for(i=0;i<n;i++)
   {
      sum=sum+p[i].t_t;
      count=count+p[i].w_t;
   }
   printf("\nAvg Turn around time=%f\n",sum/n);
   printf("\nAvg Waiting time=%f\n",count/n);
}
void time(struct process p[],int n)
{
    sort(p,n);
    int i;
    printf("Execution of process:\n");
    for(i=0;i<n;i++)
    {
       printf("%d ",p[i].pid);
    }
    printf("\n");
    wait(p,n);  
    turn(p,n);
}

int main()
{
   FILE *f=fopen("1.dat","r");
   int n,i;
   fscanf(f,"%d",&n);
   struct process p[n];
   for(i=0;i<n;i++)
   {
       fscanf(f,"%d %d %d %d %d",&p[i].pid,&p[i].a_t,&p[i].b_t1,&p[i].b_t2,&p[i].b_t3);
   }
   time(p,n);
   printf("\nPid   Arr_t   Burst_t   Burst_tIO   Burst_tC    Res_t     Wait_t      TA_t\n");
   for(i=0;i<n;i++)
   {
     p[i].r_t=p[i].t_t+p[i].w_t;
     printf("%d\t%d\t%d\t  %d\t\t%d\t  %d\t    %d\t\t%d\n",p[i].pid,p[i].a_t,p[i].b_t1,p[i].b_t2,p[i].b_t3,p[i].r_t,p[i].w_t,p[i].t_t);
   }
   avg(p,n);
   fclose(f);
}
