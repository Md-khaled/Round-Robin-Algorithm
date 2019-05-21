#include<stdio.h>
int  queue[10],front=-1,rear=-1;
/*here queue variable use for
 enqueue , dqueue of process*/
void enqueue(int i) /*function use for enter value in queue*/
{
    if(rear==10)
        printf("overflow");
    rear++;
    queue[rear]=i;
    if(front==-1)
        front=0;

}
int dequeue()/*function use for enter value in queue*/
{
    if(front==-1)
        printf("underflow");
    int temp=queue[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
/* check whether process in queue or not*/
int isRunningQueue(int i)
{
    int k;
    for(k=front; k<=rear; k++)
    {
        if(queue[k]==i)
            return 1;
    }
    return 0;

}
int main()
{
    /*
    Here n=numner of process,sum_bt=total Brust time,tq=time quantum.
    atat=average turn arounnt time,awt=average waiting time,c=process name
    */
    int n,i,j,time=0,sum_bt=0,tq;
    float atat=0,awt=0;
    char process;
    printf("Enter no of processes:");
    scanf("%d",&n);

    char name[n*2];
    /*
    at=arival time, bt=brust time,rt=remain time, ft=completion time
    */
    int at[n],bt[n],rt[n],ft[n];
    int completed[n];//completed=1 means process complete otherwise not
    for(i=0,process='A'; i<n; i++,process++)
    {
        name[i]=process;
        printf("\nEnter the arrival time and burst time of process %c: ",name[i]);
        scanf("%d%d",&at[i],&bt[i]);
        rt[i]=bt[i];
        completed[i]=0;
        ft[i]=0;
        sum_bt+=bt[i];

    }
    printf("\nEnter the time quantum:");
    scanf("%d",&tq);
    printf("\n--------------------------------------------------------------------------------------------------------");

    /*sort*/
    int t;
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(at[i] > at[j])
            {
                t=name[i];
                name[i]= name[j];
                name[j]=t;

                t=at[i];
                at[i]= at[j];
                at[j]=t;

                t=bt[i];
                bt[i]=bt[j];
                bt[j]=t;

                t=rt[i];
                rt[i]=rt[j];
                rt[j]=t;

            }
        }
    }

    if(at[0]!=0)
    {
        time=at[0];
        sum_bt=sum_bt+at[0];
    }
    enqueue(0);/*enter value in queue*/
    printf("\nProcess Gantt Chart: |");
    /* run until the total burst time reached*/
    for(time=at[0]; time<sum_bt;)
    {
        i=dequeue();/*dqueue value from queue*/

        if(rt[i]<=tq)/* for processes having remaining time with -
less than or  equal  to time quantum  */
        {
            time+=rt[i];
/*printf("\ntime %d ",time);*/
            rt[i]=0;/*rt=0 means remain time is finished*/
            completed[i]=1;
            printf(" %c |",name[i]);
            ft[i]=time;
            for(j=0; j<n; j++)/*enqueue the processes
                        which have come  while scheduling */
            {
                if(at[j]<=time && completed[j]!=1 && isRunningQueue(j)!=1)
                {
                    enqueue(j);

                }

            }
        }
        else               /*more than time quantum*/
        {

            time+=tq;
            rt[i]-=tq;
            printf(" %c |",name[i]);
            for(j=0; j<n; j++)  /*first enqueue the processes
                which have come while scheduling */
            {
                if(at[j]<=time && completed[j]!=1&& i!=j&& isRunningQueue(j)!=1)
                {
                    enqueue(j);/*access process when remaining
                     time with less than or  equal  to time quantum */
                }
            }
            enqueue(i);   /*then enqueue the uncompleted process*/
        }
    }
    printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("\n\nName\tArrival Time\tBurst Time\tComplication Time\tTurnAround Time\tWaiting Time");
    for(i=0; i<n; i++)
    {
        printf("\n%c\t\t%d\t\t%d\t\t%d\t\t     %d\t\t   %d",name[i],at[i],bt[i],ft[i],ft[i]-at[i],(ft[i]-at[i])-bt[i]);
        atat=atat+ft[i]-at[i];
        awt+=((ft[i]-at[i])-bt[i]);
    }
    printf("\nAverage TurnAround Time :->%f",atat/n);
    printf("\nAverage Waiting Time :->%f ",awt/n);
    return 0;
}
