/***********************************************************/
//Demo for TM1651 when used on Gotek board LEDC68
//Hardware: Re-Used Gotek 3 digit LED
//Board:  Arduino UNO R3
//IDE:    Arduino
//Function:  Demo displaying number counter 0 - 999
//Modified record:
//Autor:        Derek Cooper
//Mail: derek_cooper@hotmail.com
//Date:         18.09.2020
/***************************************************************/

#include "TM1651.h"
#define CLK 3//pins definitions for TM1651 and can be changed to other ports       
#define DIO 2
TM1651 Display(CLK,DIO);
void setup()
{
  Display.displaySet(2);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void loop()
{
 count();
}

void count()
{
    for(uint16_t num = 0; num < 1000; num ++)
    {
     Display.displayInteger(num);    
           delay(150);
    }
}
