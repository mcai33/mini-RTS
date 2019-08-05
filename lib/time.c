#include "time.h"



void RunTime_Click(RunTime *prun_time)
{

	prun_time->byte[0]++;
	for(u8 i = 0; i < 3; i++){
		if(255 == prun_time->byte[i]){
			prun_time->byte[i] = 0;
			prun_time->byte[i + 1] += 1;
		}	
	}
	if( 255 == prun_time->byte[3]){
		RunTime_Reset(prun_time);
	}

	
}



void RunTime_Reset(RunTime *prun_time)
{
	for(u8 i = 0; i < 3; i++){
		prun_time->byte[i] = 0;
	}
}
