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
//Autor: 	Detlef Giessmann Germany 
//Mail:	derek_cooper@hotmail.com
//Library to drive LEDC68 Gotek 3 digit LED display
//IDE:  	Arduino-1.8.12
/***************************************************************/
//

#ifndef TM1651_H
#define TM1651_H
#include <inttypes.h>
#include <Arduino.h>
	//************definitions for TM1651*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
#define STARTADDR  0xc0 

	/**** definitions for the decimal point, it's not well implememnted in hardwar */
        /**** and of little use.  *******/
#define DP_ON   1
#define DP_OFF  0
	/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

class TM1651
{
  public:
	uint8_t Cmd_SetData;
	uint8_t Cmd_SetAddr;
	uint8_t Cmd_DispCtrl;
	TM1651(uint8_t, uint8_t);
	//void init();
	int writeByte(int8_t wr_data);//write 8bit data to tm1651
	void start(void);//send start bits
	void stop(void); //send stop bits
	void displayNum(uint8_t pos, uint8_t num);
	void displayInteger(uint16_t num);
	void displayDP(uint8_t pos);
	void frame(boolean FrameFlag);
	void displayClear(void);
	void displaySet(uint8_t = BRIGHT_TYPICAL);
	void displayOff();
        void bitDelay(void);
  private:
	uint8_t Clkpin;
	uint8_t Datapin;
};
#endif
