Gotek 3-digit LED display driver

New Version, this version uses different timing for the clk/dao signals. The original can be found in the releases drop down menu.

  Author: Derek Cooper
  
  Based on the work of and credit given to:
  
  Fred.Chu and Detlef Giessmann


  Date:20 May 2021


This repository is based on an article found here [[TM1651 Arduino Library]](https://www.instructables.com/id/Arduino-Library-and-Examples-for-TM1651-New-Style-/) 

The original work was a library for a 10 bar LED display, but it used the same TM1651 chip as the Gotek 3 digit LED display. So I re-worked it to drive the LEDC68 circuit board from Gotek drives. You can find plenty of these displays from people who have upgraded to OLED.

There is a datasheet in the docs directory.

Connections to the board are (viewed from the rear):

![LEDC68 Pinout](https://github.com/coopzone-dc/GotekLEDC68/blob/master/docs/LEDC68-pin.png)

<pre>
!----------------------------!
! x1 x3  c                   !
!        c                   !
! x2 x4  c                   !
!                            !
! !--------|                 !
! ! TM1651 !                 !
! !--------|                 !
!----------------------------!

x1=clk
x2=dio
x3=GND
x4=+5v (3.3-5v)
</pre>

Once you install the library zip file (i.e. unzip it in your Arduino/libraries folder) you will be able to use the library by selecting add library from the "Sketch/include library" menu. See the examples included from the "file/examples/GotekLEDC68-master" menu.

The examples don't show the use of the displayDP(uint8_t dp) function, it's not of much use - i can only get it to turn on/off the decimal point(s) together not independent of each other. It appears from the circuit diagram that this is the only way to use them?

More info on the Wiki page above.

Have fun.
