//cached queue means the memory does not have enough space to store the whole queue
//so we divide the queue into two sides:
//one store in memory
//another store in disk

#ifndef MessageQueue_H
#define MessageQueue_H

#include "queue.h"

typedef struct MessageQueue
{
    QUEUE* queue;       //base class
    char *msg;  //new attributes
//    int numberElementsOnDisk;
//    QUEUE* outputQueue; //aggregation in subclass

    //Inherited virtual functions
    int (*isFull)(struct MessageQueue* const me);
    int (*isEmpty)(struct MessageQueue* const me);
    int (*getSize)(struct MessageQueue* const me);
    void (*insert)(struct MessageQueue* const me, int k);
    int (*remove)(struct MessageQueue* const me);

    //new virtual functions
    void (*flush)(struct MessageQueue* const me);
    void (*load)(struct MessageQueue* const me);

}MessageQueue;

void MessageQueue_Init(MessageQueue* const me, char* filename,
    int (*isFullFunction)(MessageQueue* const me),
    int (*isEmptyFunction)(MessageQueue* const me),
    int (*getSizeFunction)(MessageQueue* const me),
    void (*insertFunction)(MessageQueue* const me),
    int (*removeFunction)(MessageQueue* const me),
    void (*flushFunction)(MessageQueue* const me),
    void (*loadFunction)(MessageQueue* const me));
void MessageQueue_Cleanup(MessageQueue* const me);

int MessageQueue_isFull(MessageQueue* const me);
int MessageQueue_isEmpty(MessageQueue* const me);
int MessageQueue_getSize(MessageQueue* const me);
void MessageQueue_insert(MessageQueue* const me, int k);
int MessageQueue_remove(MessageQueue* const me);
void MessageQueue_flush(MessageQueue* const me);
void MessageQueue_load(MessageQueue* const me);

MessageQueue* MessageQueue_Create(void);
void MessageQueue_Destroy(MessageQueue* const me);

#endif
