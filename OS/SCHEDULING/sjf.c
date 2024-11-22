#include<stdio.h>
#include<stdlib.h>
typedef struct process{
	int ID, AT, BT, CT, TAT, WT, isComp;
}pro;

pro p[15];

void main(){
	int n, total_WT=0, total_TAT=0;
	float avg_WT=0, avg_TAT=0, idleTime=0;
	printf("Enter the no of processes:\n");
	scanf("%d",&n);
	printf("Enter AT & BT\n");
	for(int i=0; i<n; i++){ 
		p[i].ID=(i+1);
		scanf("%d%d",&p[i].AT,&p[i].BT);
		p[i].isComp=0;
	}
	int minidx, minbt, completed=0,curtime=0;
	printf("\nGantt chart\n");
	while(completed != n){
		minidx = -1;
		minbt = 9999;
		for(int i=0; i<n; i++){
			if(p[i].AT <= curtime && p[i].isComp==0){
				if(p[i].BT <= minbt || (p[i].BT==minbt && p[i].AT < p[minidx].AT)){
					minbt=p[i].BT;
					minidx = i;
				}
			}
		}
		if(minidx == -1){
			curtime++;
			idleTime++;
		}else{
			if(idleTime > 0){
				printf("Idle till %f\n", idleTime);
				idleTime = 0;
			}
			curtime += p[minidx].BT;
			p[minidx].CT = curtime;
			p[minidx].TAT = p[minidx].CT - p[minidx].AT;
			p[minidx].WT += p[minidx].TAT - p[minidx].BT;
			total_TAT += p[minidx].TAT;
			total_WT += p[minidx].WT;
			p[minidx].isComp = 1;
			completed++;
			printf("| P%d(%d) %d",p[minidx].ID, p[minidx].BT, p[minidx].CT);
			
		}
	}
	printf("|\n");
	avg_TAT = (float)total_TAT/n;
	avg_WT = (float)total_WT/n;
	//table
	printf("\nPID\tTAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0; i<n; i++){
		printf("\n%d\t%d\t%d\t%d\t%d\t%d",p[i].ID, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
	}
	printf("\nAvg TAT = %.2f\n",avg_TAT);
	printf("Avg WT = %.2f\n",avg_WT);
}