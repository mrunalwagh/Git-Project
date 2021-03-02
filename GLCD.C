#include <lpc214x.h> 
#include "GLCD.h"
#include "font.h"
int i=0;
int main(void)
{
	PINSEL0 = 0x00000000; 	//GPIO function selection
	IODIR0  = 0xFFFFFFFF;		//all pin as output
	IOCLR0  = RW;						//clear write pin
	IOCLR0  = CS1;          //Page 1 LCD IC2
	IOCLR0  = CS2;          //Page 2 LCD IC2
  GLCD_init();
	for(i=0;i<8;i++)				//clear display for blue screan
		{
			GLCD_Putsting(null,i,0);//clear Page no 1 to 7
		}							
	delay(20);
while(1)
{
		GLCD_Putsting(string1,1,4);//Display string (LOGSUN SYSTEMS) on Page 2
		delay(2000);
		GLCD_Putsting(null,1,4);
			delay(2000);
				GLCD_Putsting(string1,2,4);//Display string (LOGSUN SYSTEMS) on Page 2
		delay(2000);
		GLCD_Putsting(null,2,4);
			delay(2000);
				GLCD_Putsting(string1,3,4);//Display string (LOGSUN SYSTEMS) on Page 2
		delay(2000);
		GLCD_Putsting(null,3,4);
			delay(2000);
				GLCD_Putsting(string1,4,4);//Display string (LOGSUN SYSTEMS) on Page 2
		delay(2000);
		GLCD_Putsting(null,4,4);
			delay(2000);
				GLCD_Putsting(string1,5,4);//Display string (LOGSUN SYSTEMS) on Page 2
		delay(2000);
		GLCD_Putsting(null,5,4);
			delay(2000);
}
}
void GLCD_init(void)
{
	int p;
	unsigned char cmd[4]={0xC0,0xB8,0x40,0x3F};
	side(0);
	for(p=0;p<4;p++)	//pass command one by one for side 1
	{
		GLCD_send(cmd[p],CMD);	
	}
	side(1);
	for(p=0;p<4;p++)	//pass command one by one for side 2
	{
		GLCD_send(cmd[p],CMD);	
	}
}

void side(unsigned int side)
{
	if(side==0)				//Side 1 select
	{
		IOSET0 |= CS1;  //Side 1 LCD IC2
		IOCLR0 = CS2;   //Side 2 LCD IC2
		delay(5);
	}
	else							//Side 2 select
	{
		IOSET0 |= CS2;  //Side 2 LCD IC2
		IOCLR0 = CS1;   //Side 1 LCD IC2
		delay(5);
	}
}
void GLCD_Putsting(char *ip,unsigned char pageno,int xpos) 
{
  int Column=0,ptr=0;
				side(0);					            //select side 1
        GLCD_send(0x40,CMD);        	//starting Y possition address command
				GLCD_send(0xb8 | pageno,CMD);	//page no selection address
           
     for (Column = 0; Column < 128; Column++)
         {
           if (Column == 64)
           {
                 side(1);                    //select side 2
                 GLCD_send(0xb8 | pageno,CMD);//side 2 page selection
                 GLCD_send(0x40,CMD);	//Y possition address for side 2									
           }	
					 if(ptr>=xpos){ GLCD_send(*ip++,DAT);}	//write string
					 else {GLCD_send(0x00,DAT);ptr++;}			//clear display 
       
   }
}

void GLCD_send(unsigned char byte,int temp) //cmd=0 for data mode,cmd=1 for command mode
 {
    int buff =0;
		buff = byte;
		buff = buff<<16;										//shift byte by 16
		IOCLR0 =(0x00FF0000);					// clear only P0.16-P0.23
		IOSET0 |= buff;									// write data on P0.16-P0.23
		if(temp==CMD){ IOCLR0 = RS;}	//command mode RS=0
		else {IOSET0 |= RS;}				 	//data mode	RS=1
		IOCLR0 = RW;           
		IOSET0 |= EN;   							//hight to low pulse to latch data
 		delay(5);    
		IOCLR0 = EN;
 }
 
 // LCD Delay Function
void delay(int k)  
{
  int a,b;
  for(a=0;a<=k;a++)
		for(b=0;b<500;b++);
}

