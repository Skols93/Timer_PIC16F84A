# Timer for hours and minutes with PIC16F84A written in MikroC for PIC (99H:59M)

## Introduction

Timer with buttons to control Start and Stop position of it.Seven segment displays decoded with BCD decoder and multiplexed to reduce the pin count.
Multiplexing is done by four displays controlled with transistor BC547.When it counts seconds, minutes and hours the multiplexing will allow 
the display to display the digits on it with fast refreshing rate.Refreshing rate is done with interrupt depending on timer.

## Functions and variables
Interrupt is used and implemented by Timer0 for  1ms and detects 1 second while counting 1000 counts.
Timer calculator program from MikroElektronika allows us to generate code for MikroC for PIC for our Timer0.Great tool to have in other projects.

CheckButtons() is a function when used is checking for buttons states and starts or stops the timer to count time, or it resets the timer to 00:00(hours:minutes).

digit_no is variable selector for the digit displays.In every moment of the code it has 4 values, shifting them and determining the position of the seven segment displays.

On PORTB are connected with wires the four bits for the BCD decoder, and the three buttons for starting, stoping and reseting the timer.

PORTA is port on which are connected the four common cathodes.MSB is A3, LSB is A0.

For better refreshing rate of the display use timer that counts 1ms, 2ms or other value.

## Maintainer

<table>
  <tbody>
    <tr>
      <td align="center">
        <a href="[https://github.com/natterstefan](https://skols93.github.io/)">
          <img width="150" height="150" src="(https://skols93.github.io/stefan.jpg)">
          </br>
          Stefan Vasilevski
        </a>
        <div>
          <a href="(https://www.instagram.com/_vasilevski_s/)">
            <img src="" />
          </a>
        </div>
      </td>
    </tr>
  <tbody>
</table>


