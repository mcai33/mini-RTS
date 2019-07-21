#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQ.h"

void MQ_Init(MQ* me, int (*isFullFunction)(MQ* const me),
    int (*isEmptyFunction)(MQ* const me),
    int (*getSizeFunction)(MQ* const me),
    int (*enQueueFunction)(MQ* const me, char *msg),
    int (*deQueueFunction)(MQ* const me, char **msg) ){

    me->head = 0;
    me->tail = 0;
    me->size = 0;

    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getSize = getSizeFunction;
    me->enQueue = enQueueFunction;
    me->deQueue = deQueueFunction;
}

void MQ_Cleanup(MQ* const me){


}

int MQ_isFull(MQ* const me){

    return (me->head+1)%MQ_SIZE==me->tail;
}

int MQ_isEmpty(MQ* const me){

    return me->head==me->tail;
}

int MQ_getSize(MQ* const me){

    return me->size;
}

int MQ_enQueue(MQ* const me, char *msg){

    if (!me->isFull(me))
    {
		me->buffer[me->head] = (char *)malloc(strlen(msg));
        me->head = (me->head+1)%MQ_SIZE;
        ++me->size;
		return RT_OK;
    }
	else{
		return RT_FAIL;
	}
}

int MQ_deQueue(MQ* const me, char **msg){


		if(!me->isEmpty(me)){
        msg = &(me->buffer[me->tail]);
		free(me->buffer[me->tail]);
        me->tail=(me->tail+1)%MQ_SIZE;
        --me->size;
		return RT_OK;		
    }
	else{
		return RT_FAIL;
	}

}

MQ* MQ_Create(void){

    MQ* me=(MQ*)malloc(sizeof(MQ));

    if (me!=NULL)
    {
        MQ_Init(me,MQ_isFull,MQ_isEmpty,MQ_getSize,
            MQ_enQueue,MQ_deQueue);
    }

    return me;
}

void MQ_Destroy(MQ* const me){

    if (me!=NULL)
    {
        MQ_Cleanup(me);
    }

    free(me);
}
