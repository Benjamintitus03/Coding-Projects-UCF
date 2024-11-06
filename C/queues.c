#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void* data[15];
    size_t front;
    size_t rear;
    size_t size;

} Queue;

void initiliazeQueue(Queue* pQueue)
{
pQueue->front=0;
pQueue->rear=-1;
pQueue->size=0;
}
void enQueue(Queue* pQueue, void* item){
    if(pQueue->size =15){
        printf("\nThe queue is full!\n");
         
    
    }
    else{
        (pQueue->rear)++;
        (pQueue->rear) %=15;
        (pQueue->data)[pQueue->rear]=item;
        (pQueue->size)++;
    }
}
void* dequeue(Queue* pQueue)
{
    void* item=NULL;
    if (isEmpty(&pQueue))
    {
        printf("Queue is empty\n");
    }
    else{
        item =(pQueue->data)[pQueue->front];
        (pQueue->front)++;
        (pQueue->front) %= 15;
        (pQueue->size)--;

    }
    return item;
}
void* insertion(Queue* pQueue){
    if(isEmpty(pQueue==NULL)){
        return EXIT_FAILURE;
    }
    
}
/*int isEmpty(Queue* pQueue)
{
    return pQueue->size == 0;

}
*/
