#include<stdio.h>

typedef struct node{
    int pid;
    int at;
    int bt;
    int ct;
    int rt;
    int tat;
    int wt;
}Process;

void fcfs(Process p[],int n)
{
    int elapsed=0;
    int ttat=0;
    int twt=0;
    int trt=0;
    float avgtat=0;
    float avgwt=0;
    float avgrt=0;
    printf("Gantt chart\n");
    for(int i=0;i<n;i++)
    {
        if(p[i].at > elapsed)
            elapsed=p[i].at;
        int temp=elapsed;
        p[i].rt=elapsed-p[i].at;
        elapsed+=p[i].bt;
        p[i].ct=elapsed;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].at;
        printf("%d\tP%d\t%d\t",temp,p[i].pid,elapsed);
    }

    printf("Observation Table\nPID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
        ttat+=p[i].tat;
        twt+=p[i].wt;
        trt+=p[i].rt;
    }
        printf("\n");
    avgtat=(float)ttat/n;
    avgwt=(float)twt/n;
    avgrt=(float)trt/n;
   printf("Average TAT = %f\n",avgtat);
   printf("Average WT = %f\n",avgwt);
   printf("Average RT = %f\n",avgrt);
}

void main()
{
    int n;
	printf("enter the number of processses:");
	scanf("%d",&n);
	Process processes[n];
	for(int i=0; i<n; i++){
		printf("process %d\n", i+1);
		printf("enter arrival time: ");
		scanf("%d",&(processes[i].at));
		printf("enter burst time: ");
		scanf("%d",&processes[i].bt);
		processes[i].pid = i+1;
		printf("\n");
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n-1-i; j++){
			if(processes[j].at > processes[j+1].at){
				Process temp = processes[j];
				processes[j] = processes[j+1];
				processes[j+1] = temp;
			}
		}
	}
	fcfs(processes,n);
	return 0;
}