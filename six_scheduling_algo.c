#include <stdio.h>
#include <limits.h>
#define MIN -9999
/*GANTT CHART*/
void print_gantt_chart(int n, int bt[], int wt[], int tat[])
{
    int i, j, time = 0;
    printf("\nGantt Chart:\n");
    // printing top bar
    printf(" ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i]; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    // printing process id in the middle
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i] - 1; j++)
        {
            printf(" ");
        }
        printf("P%d", i + 1);
        for (j = 0; j < bt[i] - 1; j++)
        {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i]; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    // printing timeline
    printf("0");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i]; j++)
        {
            printf(" ");
            time++;
        }
        if (tat[i] > 9)
            printf("\b"); // backspace : remove 1 space
        printf("%d", time);
    }
    printf("\n");
}
// Waiting time for all processes
/* A) FCFS*/
int waitingtime_FCFS(int proc[], int n, int burst_time[], int wait_time[])
{
    wait_time[0] = 0; // waiting time for the first process is 0
    // Calculating the waiting time
    for (int i = 1; i < n; i++)
        wait_time[i] = burst_time[i - 1] + wait_time[i - 1];
    return 0;
}
// Calculating turn around time
int turnaroundtime_FCFS(int proc[], int n, int burst_time[], int wait_time[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = burst_time[i] + wait_time[i];
    return 0;
}
// Calculating average time
int avgtime_FCFS(int proc[], int n, int burst_time[])
{
    int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
    // Finding waiting time of all processes
    waitingtime_FCFS(proc, n, burst_time, wait_time);
    // Turn around time for all processes
    turnaroundtime_FCFS(proc, n, burst_time, wait_time, tat);
    // Display processes & calculate total waiting time and total turn around time
    printf("\nProcesses\tBurst\t\tWaiting\t\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wait_time[i];
        total_tat = total_tat + tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", proc[i], burst_time[i], wait_time[i], tat[i]);
    }
    // Printing average waiting time and average turn around time
    printf("\nAverage waiting time = %f\n", (float)total_wt / (float)n);
    printf("Average turnaround time = %f\n\n", (float)total_tat / (float)n);
    // Print Gantt Chart
    print_gantt_chart(n, burst_time, wait_time, tat);
    return 0;
}
void FCFS()
{
    // process id's
    int n;
    printf("***First Come First Serve***\n");
    printf("Enter number of process:");
    scanf("%d", &n);
    // int proc[] = { 1, 2, 3};
    int proc[n], burst_time[n];
    printf("\nEnter Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        printf("p%d:", i + 1);
        scanf("%d", &burst_time[i]);
        proc[i] = i + 1;
    }
    avgtime_FCFS(proc, n, burst_time);
}
/*B) SJF*/
void SJF()
{
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;
    printf("***Shortest Job First***\n");
    printf("Enter number of process:");
    scanf("%d", &n);
    printf("\nEnter Burst Time:\n");
    for (i = 0; i < n; i++)
    {
        printf("p%d:", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }
    // Sorting the burst times
    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (bt[j] < bt[pos])
                pos = j;
        }
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
    wt[0] = 0;
    // Calculating waiting time of all processes
    for (i = 1; i < n; i++)
    {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];
        total += wt[i];
    }
    avg_wt = (float)total / n;
    total = 0;
    // Calculating turn around time of all processes and printing results & Gantt Chart
    printf("\nProcesses\tBurst\t\tWaiting\t\tTurnaround\n");
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }
    avg_tat = (float)total / n;
    printf("\n\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f\n", avg_tat);
    // Printing Gantt Chart
    print_gantt_chart(n, bt, wt, tat);
}
/*C)SHORTEST REMAINING TIME FIRST*/
void findWaitingTime_SRTF(int p[], int n, int bt[], int at[], int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
        // rt[i] = proc[i].bt;
        rt[i] = bt[i];
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;
    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }
        if (check == 0)
        {
            t++;
            continue;
        }
        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
        if (rt[shortest] == 0)
        {
            complete++;
            check = 0;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}
void findTurnAroundTime_SRTF(int p[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
void findavgTime_SRTF(int p[], int n, int at[], int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime_SRTF(p, n, bt, at, wt);
    findTurnAroundTime_SRTF(p, n, bt, wt, tat);
    printf("\nProcesses\tBurst\t\tWaiting\t\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("\nAverage waiting time = %.2f", avg_wt);
    printf("\nAverage turn around time = %.2f", (float)total_tat / (float)n);
    print_gantt_chart(n, bt, wt, tat);
}
void SRTF()
{
    int at[20], bt[20], p[20], wt[20], tat[20], n, total = 0;
    printf("***Shortest remaining Job First***\n");
    printf("Enter number of process:");
    scanf("%d", &n);
    printf("\nEnter the Arrival and Burst time\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter the Arrival and Burst time of the Process %d\n", i + 1);
        printf("Arrival time is: "); // Accept arrival time
        scanf("%d", &at[i]);
        printf("Burst time is: "); // Accept the Burst time
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }
    findavgTime_SRTF(p, n, at, bt);
}
/*D)ROUND ROBIN*/
void RR()
{
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10], TAT[10], WT[10];
    float avg_wt, avg_tat;
    printf("***Round Robin***\n");
    printf("Enter number of process: ");
    scanf("%d", &NOP);
    y = NOP; // Assigning the number of process to variable y
    printf("\nEnter the Arrival and Burst time\n");
    // Enter the details of the process
    for (i = 0; i < NOP; i++)
    {
        printf("\nArrival time of process %d is: ", i + 1); // Accept arrival time
        scanf("%d", &at[i]);
        printf("Burst time of process %d is: ", i + 1); // Accept the Burst time
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // store the burst time in temp array
    }
    // Time Quantum
    printf("Enter the Time Quantum for the process: \t");
    scanf("%d", &quant);
    // printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
    printf("\nProcesses\tBurst\t\tTurnaround\tWaiting\n");
    for (sum = 0, i = 0; y != 0;)
    {
        if (temp[i] <= quant && temp[i] > 0) // Defining the conditions
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if (temp[i] == 0 && count == 1)
        {
            y--; // Decrementing the process no.
            printf("P%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];
            WT[i] = wt;
            tat = tat + sum - at[i];
            TAT[i] = tat;
            count = 0;
        }
        if (i == NOP - 1)
        {
            i = 0;
        }
        else if (at[i + 1] <= sum)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    // Calculating average waiting time and turn around time
    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;
    printf("\nAverage Turn Around Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    print_gantt_chart(NOP, bt, WT, TAT);
}
/*E) PRIORITY NON PREEMPTIVE*/
void read2(int i, int at[], int bt[], int pri[], int pno[])
{
    printf("\nProcess No: %d\n", i + 1);
    pno[i] = i + 1;
    printf("Enter Arrival Time: ");
    scanf("%d", &at[i]);
    printf("Enter Burst Time: ");
    scanf("%d", &bt[i]);
    printf("Enter Priority: ");
    scanf("%d", &pri[i]);
}
void NP()
{
    int n, c, remaining, max_val, max_index;
    int pno[10], at[10], bt[10], ct[10], wt[10], tat[10], pri[10];
    float avgtat = 0, avgwt = 0;
    printf("***Non-Preemptive Priority Scheduling***\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        read2(i, at, bt, pri, pno);
    }
    remaining = n;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pri[j] < pri[j + 1])
            {
                int tmp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = tmp;
                tmp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = tmp;
                tmp = pri[j];
                pri[j] = pri[j + 1];
                pri[j + 1] = tmp;
                tmp = pno[j];
                pno[j] = pno[j + 1];
                pno[j + 1] = tmp;
            }
        }
    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
    for (int i = 1; i < n; i++)
    {
        ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgtat += tat[i];
        avgwt += wt[i];
    }
    printf("\nProcesses\tArrival\t\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", pno[i], at[i], bt[i], pri[i], ct[i], tat[i], wt[i]);
    }
    avgtat /= n;
    avgwt /= n;
    printf("\nAverage TurnAroundTime=%.2f\nAverage WaitingTime=%.2f\n", avgtat, avgwt);
    print_gantt_chart(n, bt, wt, tat);
}
/*F) PRIORITY PREEMPTIVE*/
void read1(int i, int at[], int bt[], int pri[], int temp[], int rt[])
{
    printf("\nProcess No: %d\n", i + 1);
    printf("Enter Arrival Time: ");
    scanf("%d", &at[i]);
    printf("Enter Burst Time: ");
    scanf("%d", &bt[i]);
    rt[i] = bt[i];
    printf("Enter Priority: ");
    scanf("%d", &pri[i]);
    temp[i] = pri[i];
}
void PP()
{
    int n, c, remaining, max_val, max_index;
    int pno[10], at[10], bt[10], rt[10], ct[10], wt[10], tat[10], pri[10], temp[10];
    float avgtat = 0, avgwt = 0;
    printf("***Highest Priority First(Preemptive)***\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        pno[i] = i + 1;
        read1(i, at, bt, pri, temp, rt);
    }
    remaining = n;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                int tmp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = tmp;
                tmp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = tmp;
                tmp = pri[j];
                pri[j] = pri[j + 1];
                pri[j + 1] = tmp;
                tmp = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = tmp;
            }
        }
    max_val = temp[0], max_index = 0;
    for (int j = 0; j < n && at[j] <= at[0]; j++)
    {
        if (temp[j] > max_val)
        {
            max_val = temp[j];
            max_index = j;
        }
    }
    int i = max_index;
    c = ct[i] = at[i] + 1;
    rt[i]--;
    if (rt[i] == 0)
    {
        temp[i] = MIN;
        remaining--;
    }
    while (remaining > 0)
    {
        max_val = temp[0], max_index = 0;
        for (int j = 0; j < n && at[j] <= c; j++)
        {
            if (temp[j] > max_val)
            {
                max_val = temp[j];
                max_index = j;
            }
        }
        i = max_index;
        ct[i] = c = c + 1;
        rt[i]--;
        if (rt[i] == 0)
        {
            temp[i] = MIN;
            remaining--;
        }
    }
    // printf("\nProcessNo\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    printf("\nProcesses\tArrival\t\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        avgtat += tat[i];
        wt[i] = tat[i] - bt[i];
        avgwt += wt[i];
        printf("P%d\t\t%d\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", pno[i], at[i], bt[i], pri[i], ct[i], tat[i], wt[i]);
    }
    avgtat /= n;
    avgwt /= n;
    printf("\nAverage TurnAroundTime=%.2f\nAverage WaitingTime=%.2f\n", avgtat, avgwt);
    print_gantt_chart(n, bt, wt, tat);
}
int main()
{
    int ch;
    while (1)
    {
        printf("1. First Come First Serve (FCFS)\n2. Shortest Job First (SJF)\n3. Shortest remaining Job First (SRTF)\n4. Round Robin (RR)\n5. Priority non preemptive\n6. Priority Prepemptive.\n\n");
        printf("Enter choice :");
        scanf("%d",&ch);
        if(ch>6){
                    break;
        }
        switch(ch){
                case 1:
                    FCFS();
                    break;
                case 2:
                    SJF();
                    break;
                case 3:
                    SRTF();
                    break;
                case 4:
                    RR();
                    break;
                case 5:
                    NP();
                    break;
                case 6:
                    PP();
                    break;
        }
    }
}
