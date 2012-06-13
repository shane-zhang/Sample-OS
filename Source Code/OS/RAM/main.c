#include <stdio.h>

#define Page_Range 200
#define Page_Queue 40000
#define Page_Slot 150


int main(void)
{
    srand(time(0));
    int i;
    int Queue[Page_Queue];
    int Slot[Page_Slot];

    for(i=0;i<Page_Queue;i++)
    {
        Queue[i]=rand()%Page_Range+1;
        //printf("%d\n",Queue[i]);
    }

    int PTR,Fault;

    for(i=0;i<Page_Slot;i++)
    {
        Slot[i]=0;
    }

    for(i=0,Fault=0;i<Page_Queue;i++)
    {//OPT()
        int j;
        for(j=0;j<Page_Slot;j++)
        {
            if(Slot[j]==Queue[i])
            {
                //printf("hit!\n");
                break;
            }
        }
        if(j==Page_Slot)
        {
            int Distance[Page_Slot],temp1,temp2;
            for(temp1=0;temp1<Page_Slot;temp1++)
            {
                if(Slot[temp1]!=0)
                {
                    for(temp2=i;temp2<Page_Queue;temp2++)
                    {
                        if(Slot[temp1]==Queue[temp2])
                        {
                            Distance[temp1]=temp2;
                            break;
                        }
                    }
                }
                else
                {

                    Distance[temp1]=Page_Queue+1;
                }
            }
            int temp3,Max_Distance,Max_Slot;
            for(temp3=0,Max_Distance=0,Max_Slot=0;temp3<Page_Slot;temp3++)
            {
                if(Distance[temp3]>Max_Distance)
                {
                    Max_Distance=Distance[temp3];
                    Max_Slot=temp3;
                }
            }
            Slot[Max_Slot]=Queue[i];
            //printf("Page Fault!\n");
            Fault++;
        }
    }
    printf("OPT\tMethod:\t%f\n",1-(Fault/(float)Page_Queue));


    for(i=0;i<Page_Slot;i++)
    {
        Slot[i]=0;
    }

    for(i=0,PTR=0,Fault=0;i<Page_Queue;i++)
    {//FCFS()
        int j;
        for(j=0;j<Page_Slot;j++)
        {
            if(Slot[j]==Queue[i])
            {
                //printf("hit!\n");
                break;
            }
        }
        if(j==Page_Slot)
        {
            //printf("Page Fault!\n");
            Slot[PTR]=Queue[i];
            PTR=(PTR+1)%Page_Slot;
            Fault++;
        }
    }
    printf("FCFS\tMethod:\t%f\n",1-(Fault/(float)Page_Queue));

    for(i=0;i<Page_Slot;i++)
    {
        Slot[i]=0;
    }

    for(i=0,Fault=0;i<Page_Queue;i++)
    {//LRU()
        int j;
        for(j=0;j<Page_Slot;j++)
        {
            if(Slot[j]==Queue[i])
            {
                //printf("hit!\n");
                break;
            }
        }
        if(j==Page_Slot)
        {
            int Distance[Page_Slot],temp1,temp2;
            for(temp1=0;temp1<Page_Slot;temp1++)
            {
                if(Slot[temp1]!=0)
                {
                    for(temp2=0;temp2<i;temp2++)
                    {
                        if(Slot[temp1]==Queue[temp2])
                        {
                            Distance[temp1]=temp2;
                            break;
                        }
                    }
                    if(temp2==i)
                    {
                        Distance[temp1]=Page_Queue+1;
                    }
                }
                else
                {

                    Distance[temp1]=0;
                }
            }
            int temp3,Max_Distance,Max_Slot;
            for(temp3=0,Max_Distance=0,Max_Slot=0;temp3<Page_Slot;temp3++)
            {
                if(Distance[temp3]<=Max_Distance)
                {
                    Max_Distance=Distance[temp3];
                    Max_Slot=temp3;
                }
            }
            Slot[Max_Slot]=Queue[i];
            //printf("Page Fault!\n");
            Fault++;
        }
    }
    printf("LRU\tMethod:\t%f\n",1-(Fault/(float)Page_Queue));

    for(i=0;i<Page_Slot;i++)
    {
        Slot[i]=0;
    }

    for(i=0,Fault=0;i<Page_Queue;i++)
    {//LRU()
        int j;
        for(j=0;j<Page_Slot;j++)
        {
            if(Slot[j]==Queue[i])
            {
                //printf("hit!\n");
                break;
            }
        }
        if(j==Page_Slot)
        {
            int Distance[2][Page_Slot],temp1,temp2;

            for(temp1=0;temp1<Page_Slot;temp1++)
            {
                Distance[0][temp1]=0;
                Distance[1][temp1]=0;
            }
            for(temp1=0;temp1<Page_Slot;temp1++)
            {
                if(Slot[temp1]!=0)
                {
                    for(temp2=0;temp2<i;temp2++)
                    {
                        if(Slot[temp1]==Queue[temp2])
                        {
                            Distance[0][temp1]=temp2;
                            Distance[1][temp1]=1;
                            break;
                        }
                    }
                    if(temp2==i)
                    {
                        Distance[0][temp1]=Page_Queue+1;
                    }
                }
                else
                {

                    Distance[0][temp1]=0;
                }
            }
            int temp3,Max_Distance,Max_Slot;

            for(temp3=0;temp3<Page_Slot;temp3++)
            {
                if(Distance[1][temp3]==1)
                {

                }
                else
                {
                    break;
                }
            }

            if(temp3==Page_Slot)
            {
                //printf("Full\n");
                for(temp3=0;temp3<Page_Slot;temp3++)
                {
                    if(Distance[1][temp3]==0);
                }
            }

            for(temp3=0,Max_Distance=0,Max_Slot=0;temp3<Page_Slot;temp3++)
            {
                if(Distance[0][temp3]<=Max_Distance&&Distance[1][temp3]==0)
                {
                    Max_Distance=Distance[0][temp3];
                    Max_Slot=temp3;
                }
            }
            Slot[Max_Slot]=Queue[i];
            //printf("Page Fault!\n");
            Fault++;
        }
    }
    printf("LRU_I\tMethod:\t%f\n",1-(Fault/(float)Page_Queue));
}
