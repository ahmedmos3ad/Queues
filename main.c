#include <stdio.h>
#include <stdlib.h>

 struct node{
 int data;
 struct node*next;
 };
 typedef struct {
 struct node* front;
 struct node* rear;
 }Queue;
void initialize(Queue *s)
{
s->front=NULL;
s->rear=NULL;
}
 int Dequeue (Queue *s)
{
    struct node* temp=s->front;
    if (s->front==NULL){
        printf("Queue is Empty\n");
        return;}
        if (s->front==s->rear)
        {
            s->front=s->rear=NULL;
        }
        else s->front=s->front->next;
        return temp->data;
        free(temp);
}
void Enqueue(Queue *s,int value)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->data=value;
    temp->next=NULL;
    if (s->front==NULL && s->rear==NULL)
    {
        s->front=s->rear=temp;
        return;
    }
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

int main()
{   Queue *s;
    initialize(&s);
    Enqueue(&s,2);
	Enqueue(&s,4);
	Enqueue(&s,6);
	Dequeue(&s);
	Enqueue(&s,8);
	while (!isEmpty(&s))
        printf("%d\n",Dequeue(&s));
    return 0;
}
