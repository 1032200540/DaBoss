#ifndef __buzzer_H
#define __buzzer_H	 

#include "sys.h"
#include "delay.h"

#define Beep PCout(3) 
void Buzzer_IOinit(void);
void Buzzer_BEEP(void);

#endif  



