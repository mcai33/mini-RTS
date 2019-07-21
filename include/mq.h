#ifndef _MQ_H_
#define _MQ_H_

#define MQ_SIZE 50
#ifndef RT_OK
	#define RT_OK 0
#endif
#ifndef RT_FAIL
	#define RT_FAIL 1
#endif




typedef struct MQ
{
    char *buffer[MQ_SIZE];
    int head;
    int size;
    int tail;

    int (*isFull)(struct MQ* const me);
    int (*isEmpty)(struct MQ* const me);
    int (*getSize)(struct MQ* const me);
    int (*enQueue)(struct MQ* const me, char *msg);
    char* (*deQueue)(struct MQ* const me);
}MQ;

void MQ_Init(MQ* me, int (*isFullFunction)(MQ* const me),
    int (*isEmptyFunction)(MQ* const me),
    int (*getSizeFunction)(MQ* const me),
    int (*enQueueFunction)(MQ* const me, char *msg),
    char* (*deQueueFunction)(MQ* const me));
void MQ_Cleanup(MQ* const me);

int MQ_isFull(MQ* const me);
int MQ_isEmpty(MQ* const me);
int MQ_getSize(MQ* const me);
int MQ_enQueue(MQ* const me, char *msg);

char *MQ_deQueue(MQ* const me);

MQ* MQ_Create(void);
void MQ_Destroy(MQ* const me);

#endif
