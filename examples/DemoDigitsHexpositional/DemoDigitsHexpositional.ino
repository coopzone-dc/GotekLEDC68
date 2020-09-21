/***********************************************************/
//Demo for positional digit for TM1651 when used on Gotek board LEDC68
//It also includes HEX digits
//Hardware: Re-Used Gotek 3 digit LED
//Board:  Arduino UNO R3
//IDE:    Arduino
//Function:  Demo using specific digit
//Modified record:
//Autor:        Derek Cooper
//Mail: derek_cooper@hotmail.com
//Date:         18.09.2020
/***************************************************************/

#include "TM1651.h"
#define CLK 3//pins definitions for TM1651 and can be changed to other ports       
#define DIO 2
#define COUNTTO 16 //digits from 0-f (use 10 to count from 0-9)

TM1651 Display(CLK,DIO);
void setup()
{
  Display.displaySet(2);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void loop()
{
 numbers();
}

void numbers()
{
  for(uint8_t pos = 0; pos < 3; pos++)
  { 
    for(uint8_t num = 0; num < COUNTTO; num ++)
    {
     Display.displayNum(pos,num);    
           delay(250);
    }
   delay(1000);
  }
}
