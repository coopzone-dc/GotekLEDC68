//  Auther: Derek Cooper
//  Based on the work of and credit given to:
//  Fred.Chu
//  Detlef Giessmann Germany
//
//  Date:20 September 2020
//
//  Applicable Module:
//                     Gotek 3-digit LED display driver
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//Modified record:
//Autor:        Detlef Giessmann Germany
//Mail: derek_cooper@hotmail.com
//Library to drive LEDC68 Gotek 3 digit LED display
//IDE:          Arduino-1.8.12
//
// 03/02/21 Changed the value for the digit 6 from 0x7c to 0x7d, ie added a top bar in the display
//          to distinguish it from a letter b. Credit to solarmon 
//
/***************************************************************/
//

#include "TM1651.h"
#include <Arduino.h>
static int8_t NumTab[] = 
{ 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
  0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71,
  0x00, 0x63, 0x5c, 0x01, 0x40, 0x08
}; //numbers 0-9, A-F, special chars

TM1651::TM1651(uint8_t Clk, uint8_t Data)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
}

//void TM1651::init()
//{
//  set(BRIGHT_TYPICAL);
//  clearDisplay();
//}

int TM1651::writeByte(int8_t wr_data)
{
  uint8_t i,count1;       
  for(i=0;i<8;i++)        //sent 8bit data
  { 
    digitalWrite(Clkpin,LOW);
    if(wr_data & 0x01)digitalWrite(Datapin,HIGH);//LSB first
    else digitalWrite(Datapin,LOW);
    wr_data >>= 1;
    digitalWrite(Clkpin,HIGH);
  
  }
  digitalWrite(Clkpin,LOW); //wait for the ACK
  digitalWrite(Datapin,HIGH);
  digitalWrite(Clkpin,HIGH);
  pinMode(Datapin,INPUT);
  
  bitDelay(); 
  uint8_t ack = digitalRead(Datapin);
  if (ack == 0)
  {  
     pinMode(Datapin,OUTPUT);
     digitalWrite(Datapin,LOW);
  }
  bitDelay();
  pinMode(Datapin,OUTPUT);
  bitDelay();
  
  return ack;
}

//send start signal to TM1651
void TM1651::start(void)
{
  digitalWrite(Clkpin,HIGH);//send start signal to TM1637
  digitalWrite(Datapin,HIGH);
  digitalWrite(Datapin,LOW);
  digitalWrite(Clkpin,LOW);
} 
//End signal
void TM1651::stop(void)
{
  digitalWrite(Clkpin,LOW);
  digitalWrite(Datapin,LOW);
  digitalWrite(Clkpin,HIGH);
  digitalWrite(Datapin,HIGH);
}

//******************************************
void TM1651::displayNum(uint8_t dig, uint8_t number)
{
  start();          //start signal sent to TM1651 from MCU
  writeByte(ADDR_FIXED);//
  stop();           //
  start();          //
  writeByte(STARTADDR + dig);// digit pos 0-2
  writeByte(NumTab[number]);//
  stop();            //
  start();          //
  writeByte(Cmd_DispCtrl);// 88+0 to 7 brightness, 88=display on
  stop();           //
}
//******************************************
void TM1651::displayInteger(uint16_t number)
{
 uint8_t i;   

  if(number > 999) number=999;
  start();          //start signal sent to TM1651 from MCU
  writeByte(ADDR_AUTO);// auto increment the address
  stop(); 
  start();
  writeByte(STARTADDR);// start at 0
   writeByte(NumTab[(number/100) % 10]);
   writeByte(NumTab[(number/10) % 10]);
   writeByte(NumTab[number % 10]);
  stop();
  start();
  writeByte(Cmd_DispCtrl);// 88+0 to 7 brightness, 88=display on
  stop();
}

//******************************************
void TM1651::displayDP(uint8_t dp)
{
  uint8_t SegData;

  //if (dp == 1) SegData = 0x08;
  //else SegData = 0x00;
  start();          //start signal sent to TM1651 from MCU
  writeByte(ADDR_FIXED);
  stop();  
  start();
  writeByte(STARTADDR + 3);// digit pos 3 controls decimal point
  //writeByte(SegData);
  writeByte(dp);
  stop();      
  start();  
  writeByte(Cmd_DispCtrl);// 88+0 to 7 brightness, 88=display on
  stop();  
}

void TM1651::displayClear(void)
{
 displayDP(0);
 displayInteger(0);
}

void TM1651::displaySet(uint8_t brightness)
{
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and turn on
}

void TM1651::displayOff()
{
  Cmd_DispCtrl = 0x80;
  start();
  writeByte(Cmd_DispCtrl);// 88+0 to 7 brightness, 88=display on
  stop();
}

void TM1651::bitDelay(void)
{
        delayMicroseconds(50);
}

