unsigned int   digit, number;

unsigned int digit_no;
unsigned int bcd_code = 0;
int i;

bit oldstate;                                    // Stara sostojba (flag)
unsigned int broi_1ms, flag_1s;                      //flag za sekunda, brojac za milisekundi
unsigned short  sekundi, minuti, casovi;
unsigned short sekundi_desetki, sekundi_edinici, minuti_edinici, minuti_desetki, casovi_edinici, casovi_desetki;

//BCD digits on PORTB(0 to 3)



void checkButtons(){
      if (Button(&PORTB, 4, 10, 1)) {                  // Detektira logicka edinica
          oldstate = 1;                              // ja setira flagot i pocnuva da broi
                                                     //START
      }
      if(Button(&PORTB, 5, 10, 1)){                   //tasterot STOP e pritisnat
          oldstate = 0;                              //ja vrakja na nula i ne odbrojuva
                                                     //STOP
       }
       if(Button(&PORTB, 6, 10, 1)){                   //tasterot Reset e pritisnat
          sekundi = 0;                                //ja vrakja na nula i sekundi i minuti i casovi
          minuti = 0;
          casovi = 0;
          oldstate = 0;                                // odlstate e na nula ne odbrojuva
       }
}
void InitTimer0(){
  OPTION_REG         = 0x85;
  TMR0                 = 100;
  INTCON         = 0xA0;
  //OPTION_REG         = 0x83;    za 2ms
  //TMR0                 = 6;
  //INTCON         = 0xA0;
}
void Interrupt(){
     if (TMR0IF_bit){
     
               TMR0IF_bit         = 0;
               TMR0                 = 100;

                //TMR0IF_bit         = 0;
                //TMR0                 = 6;


                if(digit_no == 0)
                {
                   PORTA = 0x00;
                   digit_no++;
                   PORTB = minuti_edinici;
                   PORTA = 1; //0001

                }
                else if(digit_no == 1)
                {
                   PORTA = 0x00;
                   digit_no++;
                   PORTB = minuti_desetki;
                   PORTA = 2; //0010

                }
                else if(digit_no == 2)
                {
                   PORTA = 0x00;
                   digit_no++;

                   PORTB = casovi_edinici;
                   PORTA = 4; //0100

                }
                else
                {
                    PORTA = 0x00;
                    digit_no = 0;
                    PORTB = casovi_desetki;
                    PORTA = 8; //1000

                }

                                     // if( oldstate == 1)
            if(oldstate == 1){
                broi_1ms++;
                if(broi_1ms > 200)
                {
                   broi_1ms = 0; // ja vrakjame promenlivata od nula da broi i da broi do 100 pak

                   sekundi++;
                }
                if(sekundi > 59)
                {
                     //imame edna minuta(60 sekundi)
                     //minuti se zgolemuvaat
                     sekundi = 0;
                     minuti++;
                }
                if(minuti > 59)
                {
                     //ako imame 99 minuti vrati gi na 00
                     minuti = 0;
                     casovi++;
                }
                if(casovi > 99)
                {
                    casovi = 0;
                    minuti = 0;
                    sekundi = 0;
                    oldstate = 0;
                }
        }


    }
}

void main() {
       InitTimer0();
       TRISA = 0x00;
       TRISB = 0b11110000;

       PORTA = 0;
       PORTB = 0;
       sekundi_edinici = 0; sekundi_desetki = 0; minuti_edinici = 0; minuti_desetki = 0;
       casovi_edinici = 0; casovi_desetki = 0;
       sekundi = 0; minuti = 0; casovi = 0;
       oldstate = 0;





       do{
                  checkButtons(); //gi proveruvame kopcinjata
                  sekundi_edinici = Dec2Bcd(sekundi % 10);  // odeluvanje na sekundi edinici
                  sekundi_desetki = Dec2Bcd((sekundi / 10u) % 10u);  //oddeluvanje na sekundi desetki
                  minuti_edinici =Dec2Bcd( minuti % 10);    //oddeluvanje na minuti edinici
                  minuti_desetki =Dec2Bcd((minuti / 10u) % 10u);    //oddeluvanje na minuti desetki
                  casovi_edinici = Dec2Bcd(casovi % 10);   //oddeluvanje na casovi edinici
                  casovi_desetki = Dec2Bcd((casovi / 10u) % 10u);   //oddeluvanje na casovi desetki

       }
       while(1);


}