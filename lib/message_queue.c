#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message_queue.h"

void MessageQueue_Init(MessageQueue* const me, char* filename,
    int (*isFullFunction)(MessageQueue* const me),
    int (*isEmptyFunction)(MessageQueue* const me),
    int (*getSizeFunction)(MessageQueue* const me),
    void (*insertFunction)(MessageQueue* const me),
    int (*removeFunction)(MessageQueue* const me),
    void (*flushFunction)(MessageQueue* const me),
    void (*loadFunction)(MessageQueue* const me)){

    me->queue=Queue_Create();
    me->numberElementsOnDisk=0;
    strcpy(me->filename,filename);
    me->outputQueue=Queue_Create();

    me->isFull=isFullFunction;
    me->isEmpty=isEmptyFunction;
    me->getSize=getSizeFunction;
    me->insert=insertFunction;
    me->remove=removeFunction;
    me->flush=flushFunction;
    me->load=loadFunction;
}

void MessageQueue_Cleanup(MessageQueue* const me){

    Queue_Cleanup(me->queue);
}

int MessageQueue_isFull(MessageQueue* const me){

    return me->queue->isFull(me->queue) &&
           me->outputQueue->isFull(me->outputQueue);
}

int MessageQueue_isEmpty(MessageQueue* const me){

    return me->queue->isEmpty(me->queue) &&
           me->outputQueue->isEmpty(me->outputQueue) &&
           (me->numberElementsOnDisk==0);
}

int MessageQueue_getSize(MessageQueue* const me){

    return me->queue->getSize(me->queue)+
           me->outputQueue->getSize(me->outputQueue)+
           me->numberElementsOnDisk;
}

void MessageQueue_insert(MessageQueue* const me,int k){

    if (me->queue->isFull(me->queue))
    {
        me->flush(me);
    }

    me->queue->insert(me->queue,k);
}

int MessageQueue_remove(MessageQueue* const me){

    if (!me->outputQueue->isEmpty(me->outputQueue))
    {
        return me->outputQueue->remove(me->outputQueue);
    }
    else if (me->numberElementsOnDisk>0)
        {
            me->load(me);
            return me->queue->remove(me->remove);
        }
        else
        {
            return me->queue->remove(me->remove);
        }
}

void MessageQueue_flush(MessageQueue* const me){

    //while not queue->isEmpty()
    //          queue->remove();
    //          write date to disk
    //          numberElementsOnDisk++
    //end while
}

void MessageQueue_load(MessageQueue* const me){

    //while (!outputQueue->isFull()&&(numberElementsOnDisk>0))
    //      read from start of file
    //      numberElementsOnDisk--;
    //      outputQueue->insert();
    //end while
}

MessageQueue* MessageQueue_Create(MessageQueue* const me){

    MessageQueue* me=(MessageQueue*)malloc(sizeof(MessageQueue));

    if(me!=NULL)
    {
        MessageQueue_Init(me,"C:\\queuebuffer.dat",
            MessageQueue_isFull,MessageQueue_isEmpty,
            MessageQueue_getSize,MessageQueue_insert,
            MessageQueue_remove,MessageQueue_flush,MessageQueue_load);
    }

    return me;
}

void MessageQueue_Destroy(MessageQueue* const me){

    if(me!=NULL)
    {
        MessageQueue_Cleanup(me);
    }

    free(me);
}
