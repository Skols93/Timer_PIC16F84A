# Timer_PIC16F84A
Timer with buttons to control Start and Stop of it.Seven segment display decoded with BCD coder and multiplexed to reduce the pin count.
Multiplexing is done by four displays.When it counts seconds and minutes the multiplexing will allow 
the display to display the digits on it with fast refreshing rate.
In the code interrupt is used which is implemented by Timer0 for  1ms and detects 1 second while counting 1000 counts.
