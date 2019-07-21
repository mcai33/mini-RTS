#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void MQ_Init(QUEUE* me, int (*isFullFunction)(QUEUE* const me),
    int (*isEmptyFunction)(QUEUE* const me),
    int (*getSizeFunction)(QUEUE* const me),
    void (*insertFunction)(QUEUE* const me, int k),
    int (*removeFunction)(QUEUE* const me)){

    me->head=0;
    me->tail=0;
    me->size=0;

    me->isFull=isFullFunction;
    me->isEmpty=isEmptyFunction;
    me->getSize=getSizeFunction;
    me->insert=insertFunction;
    me->remove=removeFunction;
}

void MQ_Cleanup(QUEUE* const me){


}

int MQ_isFull(QUEUE* const me){

    return (me->head+1)%QUEUE_SIZE==me->tail;
}

int MQ_isEmpty(QUEUE* const me){

    return me->head==me->tail;
}

int MQ_getSize(QUEUE* const me){

    return me->size;
}

void MQ_insert(QUEUE* const me, int k){

    if (!me->isFull(me))
    {
        me->buffer[me->head]=k;
        me->head=(me->head+1)%QUEUE_SIZE;
        ++me->size;
    }
}

int MQ_remove(QUEUE* const me){

    int value=-9999;

    if(!me->isEmpty(me))
    {
        value=me->buffer[me->tail];
        me->tail=(me->tail+1)%QUEUE_SIZE;
        --me->size;
    }

    return value;
}

QUEUE* MQ_Create(void){

    QUEUE* me=(QUEUE*)malloc(sizeof(QUEUE));

    if (me!=NULL)
    {
        MQ_Init(me,MQ_isFull,MQ_isEmpty,MQ_getSize,
            MQ_insert,MQ_remove);
    }

    return me;
}

void MQ_Destroy(QUEUE* const me){

    if (me!=NULL)
    {
        MQ_Cleanup(me);
    }

    free(me);
}
