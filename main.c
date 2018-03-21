#include <stdio.h>
#include <stdlib.h>
#define TYPE Process
#define max_size 100
 //structing the nodes of th linked list
 struct node{
 int data;
 struct node*next;
 };
 //structing the linked list queue
 typedef struct {
 struct node* front;
 struct node* rear;
 }Queue;
 //structing the process which will hold the name of the phase and the start and execution time needed for each phase
 typedef struct {
     int start_time;
     int execution_time;
     char name[20];
 }Process;
//initializing the queue,setting the front and rear to null as queue is empty
void initialize(Queue *s)
{
s->front=NULL;
s->rear=NULL;
}
 int Dequeue (Queue *s)
{
    //structing a temporary node in the linked list which equals the first node in the queue
    struct node* temp=s->front;
    //checking if the queue is already empty
    if (s->front==NULL){
        printf("Queue is Empty\n");
        return;}
        //checking if the queue only has 1 node
        if (s->front==s->rear)
        {   //dequeuing the only node and setting its value to null
            s->front=s->rear=NULL;
        }  //if there is more than 1 node,we make the node after front the front node
        else s->front=s->front->next;
        //returning the value for the dequeued node
        return temp->data;
        //freeing the temporary node
        free(temp);
}
void Enqueue(Queue *s,int value)
{   //structing a temporary node in the linked list which using dynamic allocation with the size of struct node
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    //setting the value of the temp node to the value we need to enqueue
    temp->data=value;
    //setting the next node address to null
    temp->next=NULL;
    //checking if the queue is empty
    if (s->front==NULL && s->rear==NULL)
    {   //assigning front and rear to the new node as queue is empty
        s->front=s->rear=temp;
        return;
    }
    //since the queue isn't empty we assign the rear of the queue to the new node we just queued
    //and assign the next node address to the temporary node we are using to store the node we wanna queue
    s->rear->next=temp;
    s->rear=temp;
}

//returns 1 if queue is empty or 0 otherwise
int isEmpty(Queue *s)
{
    if (s->front==NULL)
    return 1;
    else return 0;
}
//fuction to scan the file with the process required to do
int scanfile(Process *array)
{
    FILE *ptrF;
    int variable;
    char process_name;
    ptrF=fopen("File.txt","r");
    //reading the name of the process and the variable
    fscanf(ptrF,"%[^=]=%d",process_name,variable);
    //loop to store the name of the phase, the starting time and the execution time in an array of type process
    while(!feof(ptrF))
    {
        fscanf(ptrF,"%s %d %d",array->name,array->start_time,array->execution_time);
    }
    fclose(ptrF);
    return variable;
}
//function to make the scheduling algorithm
void schedule(int variable,Process* array,Queue *schedule)
{
    int i=0,j=0;
    Process t;
    for(i=0;i<variable;i++)
    {
        for (j=0;j<max_size;j++)
        {
            if (i==array[i].start_time)
                Enqueue(&schedule,array);
        }
        if (isEmpty(&schedule))
            printf("idle (%d-->%d",i,i+1);
         else {
            t=Dequeue(&schedule);
            printf("%s %d-->%d",t.name,i,i+1);
            t.execution_time--;
            if (t.execution_time==0)
                printf("aborts %s",t.name);
            else Enqueue(&schedule,t);
        }
    }
    printf("stop");
}

int main()
{
    int variable;
    Queue *s;
    Queue *schedule;
    Process *array[max_size];
    initialize(&schedule);
    variable=scanfile(&array);
    initialize(&s);
    schedule(variable,&array,&schedule);
    Enqueue(&s,2);
	Enqueue(&s,4);
	Enqueue(&s,6);
	Dequeue(&s);
	Enqueue(&s,8);
	while (!isEmpty(&s))
        printf("%d\n",Dequeue(&s));
    return 0;
}
