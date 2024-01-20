unsigned short shifter, portd_index;
unsigned int   digit, number;
unsigned short portd_array[4];

bit oldstate;                                    // Stara sostojba (flag)
unsigned int broi_1ms, flag_1s;                      //flag za sekunda, brojac za milisekundi
unsigned int  sekundi = 0, minuti = 0;
unsigned int sekundi_desetki=0, sekundi_edinici=0, minuti_edinici=0, minuti_desetki=0;


sbit LED1 at PORTA.B0;
sbit LED2 at PORTA.B1;
sbit LED3 at PORTA.B2;



unsigned int  sevenBCD[10] = {
  0B0000, //'0'
  0B0001, //'1'
  0B0010, //'2'
  0B0011, //'3'
  0B0100, //'4'
  0B0101, //'5'
  0B0110, //'6'
  0B0111, //'7'
  0B1000, //'8'
  0B1001, //'9'
 };

void checkButtons(){
      if (Button(&PORTB, 4, 1, 1)) {                  // Detektira logicka edinica
          oldstate = 1;                              // ja setira flagot i pocnuva da broi
      }
      if(Button(&PORTB, 5, 1, 1)){                   //tasterot STOP e pritisnat
          oldstate = 0;                              //ja vrakja na nula i ne odbrojuva
       }
}
void InitTimer0(){
  OPTION_REG         = 0x82;
  TMR0                 = 6;
  INTCON         = 0xA0;
}
void Interrupt(){
            if (TMR0IF_bit){
            
                PORTA = 0;                             // Turn off all 7seg displays
                PORTB = portd_array[portd_index];      // bring appropriate value to PORTD
                PORTA = shifter;                       // turn on appropriate 7seg. display

                // move shifter to next digit
                 shifter <<= 1;
                  if (shifter > 8u)
                      shifter = 1;

                      // increment portd_index
                 portd_index++ ;
                 if (portd_index > 3u)
                    portd_index = 0;             // turn on 1st, turn off 2nd 7seg.
                TMR0IF_bit         = 0;
                TMR0                 = 6;
                                     // if( oldstate == 1)
            if(oldstate == 1){
            broi_1ms++;
            if(broi_1ms > 1000)
            {
               broi_1ms = 0; // ja vrakjame promenlivata od nula da broi i da broi do 100 pak
               flag_1s = 1; // imame izbrojano edna sekunda
               sekundi++;
            }
            if(sekundi == 60)
            {
                 //imame edna minuta(60 sekundi)
                 //minuti se zgolemuvaat
                 sekundi = 0;
                 minuti++;
            }
            if(minuti == 99)
            {
                 //ako imame 99 minuti vrati gi na 00
                 minuti = 0;
            }
        }
    }
}

void main() {
       InitTimer0();
       TRISA = 0x00;
       TRISB = 0xF0;
       portd_index = 0;
       shifter = 1;
       


       do{
       
          sekundi_edinici = sekundi % 10;
           portd_array[0] = sevenBCD[sekundi_edinici];
           sekundi_desetki = sekundi / 10;
           portd_array[1] = sevenBCD[sekundi_desetki];
           minuti_edinici = minuti % 10;
           portd_array[2] = sevenBCD[minuti_edinici];
           minuti_desetki = minuti / 10;
           portd_array[3] = sevenBCD[minuti_desetki];
           checkButtons(); //gi proveruvame kopcinjata
          // updateDisplay();


       }
       while(1);


}