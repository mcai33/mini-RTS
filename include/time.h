#ifndef _TIME_H
#define _TIME_H
#include "type.h"




typedef struct{
	u8 sec;
	u8 min;
	u8 hour;
	u8 day;
	u8 month;
	u8 year;
}Date;

typedef struct {
	u8 byte[4];
}RunTime;

extern void RunTime_Click(RunTime *prun_time);
extern void RunTime_Reset(RunTime *prun_time);
#endif
