// resources
// https://learning.oreilly.com/library/view/operating-system-concepts/9781118063330/14_chapter07.html#sec7.5
// https://www.youtube.com/watch?v=qPuf5B5xPCs&ab_channel=Jenny%27slecturesCS%2FITNET%26JRF
// https://tutorialspoint.dev/computer-science/operating-systems/operating-system-bankers-algorithm
// Banker's Algorithm/Safety Algorithm
//
// Assumptions:
//              There is one resource instance of each resource type only 
//              Each process can request multiple resources
#include <stdio.h>
#include <stdbool.h>

// ************* deadlock
//  simple 2 resources two processes in a loop
// 
//#define nPr 2
//#define nRes 2
//int alloc[nPr][nRes] = { { 0, 1 },
//                  { 1, 0 } };
//
//
//int request[nPr][nRes] = { { 1, 0 },
//                        { 0, 1 } };
//
//int avail[nRes] = { 0, 0 };

// 
// 

// ************* safe
// jenny video ex 2
//#define nPr 3
//#define nRes 2
//    int alloc[nPr][nRes] = { { 0, 1 }, 
//                { 1, 0},
//                { 1, 0 } }; 
//
//
//    int request[nPr][nRes] = { { 1, 0 },
//                    { 0, 0},
//                      { 0, 1 } };
//
//    int avail[nRes] = {  0, 0 };


// ************** deadlock
// jenny video ex 1
//#define nPr 3
//#define nRes 3
//
//    int alloc[nPr][nRes] = { { 0, 0, 1 },
//                    { 1, 0, 1 },
//                    { 0, 1, 0 } };
//
//
//    int request[nPr][nRes] = { { 1, 0, 0 },
//                      { 0, 1, 0 },
//                      { 0, 0, 1 } };
//
//    int avail[nPr] = { 0, 0, 0 };


    // ************** safe
     // jenny video ex 1 with p1 -> r1 taken out
    #define nPr 3
    #define nRes 3
    
    int alloc[nPr][nRes] = 
                    { { 0, 0, 1 },
                    { 1, 0, 1 }, 
                    { 0, 1, 0 } }; 
    
    
    int request[nPr][nRes] = 
                        { { 0, 0, 0 }, 
                        { 0, 1, 0 }, 
                        { 0, 0, 1 } }; 
    
    int avail[nRes] = { 0, 0, 0 };


void analyseProcesses(bool procFinishStatus[], int procFinishSeq[])
{
    int procsFinished = 0,
        execTime = 0;

    bool deadlockExists = false;

    for (int i = 0; i < nPr; i++)
        procFinishStatus[i] = false;   // flag all processes are current running

    while ((execTime++ < nPr) && (procsFinished < nPr))
    {
        for (int procNum = 0; procNum < nPr; procNum++) // iterate over process list
        {
            if (procFinishStatus[procNum] == 0) // only do this if current process is still running
            {
                bool canSatisfyResReq = true;
                for (int res = 0; res < nRes; res++) // iterate over resources to see if resouce request for this process can be satisfied
                {
                    if (request[procNum][res] > avail[res]) // are there available resources to satisfy this processes request
                    {
                        canSatisfyResReq = false;   // no, hence move on, this process must remain blocked
                        break;
                    }
                }

                if (canSatisfyResReq == true) // if process procNum can have its request satisfied, flag it as completed and release its resources
                {
                    procFinishSeq[procsFinished++] = procNum;
                    for (int res = 0; res < nRes; res++)
                        avail[res] += alloc[procNum][res];    // return allocated resources for process to available pool

                    procFinishStatus[procNum] = true;    // flag this process as having completed
                    printf("Process %d completed in %d time units\n", procNum, execTime);
                }
            }
        }
    }

    printf("Total run time:%d\n", execTime);
}


void main()
{
    int procFinishSeq[nPr] = { 0 };
    bool procFinishStatus[nPr] = { false };

    // createMatrices
    analyseProcesses(procFinishStatus, procFinishSeq);

    bool deadlockExists = false;

    for (int i = 0; i < nPr; i++)
    {
        if (procFinishStatus[i] == false) // if process flagged as not finished, it has deadlocked
        {
            deadlockExists = true;
            printf("Deadlocked process P%d\n", i);
        }
    }

    if (deadlockExists == false)
    {
        printf("Completion order\n");
        for (int procNum = 0; procNum < nPr; procNum++)
            printf(" P%d ", procFinishSeq[procNum]);
    }

    _getch();
}


