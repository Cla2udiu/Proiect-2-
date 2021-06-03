/*******************************************************
This program was created by the CodeWizardAVR V3.32 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Hangamn
Version : 
Date    : 5/25/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega164
Program type            : Application
AVR Core Clock frequency: 20.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega164.h>

// Alphanumeric LCD functions
#include <alcd.h>


#include <alcd.h>
#include <string.h> 
#include <stdlib.h>
#include <delay.h>  
#include <stdbool.h>  
#include <stdio.h>

#define LED1 PORTD.6 // output

int row1 = 0;    

int key1 = 0;    
int key2 = 0;

int col1 = 0;    

int ok = 0;       
int check = 0;
int noOfLives = 5;
int noOfCorrectGuesses = 0;
int checkIfWon = 0;

int i, dim, count = 0;
  
unsigned char x;  
unsigned char guessedLetter[1];           
unsigned char word[16] = "draguta";
unsigned char stars[16] = "***";

//only for verifying stuff



void getrow (int pos){                  //select the line (write 1)

    if(pos == 0)PORTB.0 = 1;                //PB0 = 1 
        else PORTB.0 = 0;            
        
    if(pos == 1)PORTB.1 = 1;                //PB1 = 1
        else PORTB.1 = 0;     
        
    if(pos == 2)PORTB.2 = 1;                //PB2 = 1
        else PORTB.2 = 0;   
        
    if(pos == 3)PORTB.3 = 1;                //PB3 = 1
        else PORTB.3 = 0;  
        
}

int getcol(){                               //look at every column and see which one has a presed button
  
    if(PINB.6 == 1){ 
        while(PINB.6 == 1)  
            delay_ms(20);   //waits for release
        return 0;           //return the column
    }
      
    else if(PINB.5 == 1){ 
        while(PINB.5 == 1)  
            delay_ms(20);
        return 1;                           
    }
  
    else if(PINB.4 == 1){ 
        while(PINB.4 == 1)  
            delay_ms(20);
        return 2; 
    }
   
    else 
    {   
        //lcd_puts("verificat");
        return 3;  //then no column  
    }
} 

unsigned char dostuff(int key1, int key2)
{ 
    lcd_puts("am intrat");
    delay_ms(500);                        
    switch (key1)
    {   case 0:             
            if (key2 == 9)     x = 'a';   
            if (key2 == 10)    x = 'b';
            if (key2 == 11)    x = 'c';
            break;
        case 1:              
            if (key2 == 9)     x = 'd';     
            if (key2 == 10)    x = 'e';
            if (key2 == 11)    x = 'f';
            break;
        case 2:           
            if (key2 == 9)     x = 'g';     
            if (key2 == 10)    x = 'h';
            if (key2 == 11)    x = 'i';
            break;
        case 3:
            if (key2 == 9)     x = 'j';     
            if (key2 == 10)    x = 'k';
            if (key2 == 11)    x = 'l';
            break;  
        case 4:
            if (key2 == 9)     x = 'm';     
            if (key2 == 10)    x = 'n';
            if (key2 == 11)    x = 'o';
            break;  
        case 5:
            if (key2 == 9)     x = 'p';     
            if (key2 == 10)    x = 'q';
            if (key2 == 11)    x = 'r';
            break;  
        case 6:
            if (key2 == 9)     x = 's';     
            if (key2 == 10)    x = 't';
            if (key2 == 11)    x = 'u';
            break; 
        case 7:
            if (key2 == 9)     x = 'v';     
            if (key2 == 10)    x = 'w';
            if (key2 == 11)    x = 'x';
            break; 
        case 8:
            if (key2 == 9)     x = 'y';     
            if (key2 == 10)    x = 'z';
            break;        
    default:            //default statements idk   
    } //end switch     
    
    key1 = 0;           //reset the key for new press    
    key2 = 0; 
    
    return x;
}



void main(void)
{
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef OPTIMIZE_SIZE
#pragma optsize+
#endif

 

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

 

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

 

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

 

// Port D initialization
// Function: Bit7=In Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (1<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

 

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

 

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 19.531 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 1.0001 s
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x4C;
OCR1AL=0x4C;
OCR1BH=0x00;
OCR1BL=0x00;

 

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=(0<<EXCLK) | (0<<AS2);
TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

 

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);

 

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

 

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);

 

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-15: Off
// Interrupt on any change on pins PCINT16-23: Off
// Interrupt on any change on pins PCINT24-31: Off
EICRA=(0<<ISC21) | (0<<ISC20) | (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
EIMSK=(0<<INT2) | (0<<INT1) | (0<<INT0);
PCICR=(0<<PCIE3) | (0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);

 

// USART0 initialization
// USART0 disabled
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (0<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);

 

// USART1 initialization
// USART1 disabled
UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (0<<RXEN1) | (0<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);

 

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
ADCSRB=(0<<ACME);
// Digital input buffer on AIN0: On
// Digital input buffer on AIN1: On
DIDR1=(0<<AIN0D) | (0<<AIN1D);

 

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

 

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

 

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

 

// Alphanumeric  initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 3
// D5 - PORTA Bit 4
// D6 - PORTA Bit 5
// D7 - PORTA Bit 6
// Characters/line: 16


    lcd_init(16);


    dim = strlen(word);
    
    for(i = 0; i < dim; i++)
        stars[i] = '*';
    stars[dim] = '\0';
      
     
    #asm("sei")      //activeaza intreruperi globale pt timer1
    LED1=1;

    while (noOfLives)
    {
        for(row1 = 0; row1 < 4; row1++)     //for the first time we press a button
        {                                   
            getrow(row1);                   //write on row
            col1 = getcol();                //read on column      
            
            delay_ms(1000); 
            lcd_clear();
            //itoa(col1, aux1);
            //lcd_puts(aux1);
            
            if(col1 < 3)
            {                               //if a button was pressed
                key1 = col1 + 3 * row1;     //get the position of the key as in number (0, 1, ...   
                ok = 1;                     //so something did happen   
                count++;                    
            }
        }
        
    
       if(count % 2 == 1)   //daca numarul de taste e impar, salveaza key-ul pentru cand vine urmatoarea 
            key2 = key1;
            
       
       delay_ms(1000); 
       lcd_clear();
      
       
       
       if(ok && count % 2 == 0)     //if something did happen + avem 2 taste, deci o litera
        {                                   
            guessedLetter[0] = dostuff(key2, key1);  //trebuie inversate pentru ca asa s-au salvat      
            for(i = 0; i < dim; i++)
                if(word[i] == guessedLetter[0]) 
                {
                    stars[i] = guessedLetter[0];    //verificam existenta literei respective in cuvant 
                    //lcd_puts("verificat"); 
                    check = 1;                      //daca am gasit-o, tinem minte    
                    noOfCorrectGuesses++;           //ca sa verificam mai tarziu daca am ghicit toate literele
                }              
            if(check == 0)                          //daca nu am gasit-o, trebuie sa scadem numarul de vieti
                noOfLives--;        
            ok = 0;         //reset for the next time smth is pressed
            check = 0;      //reset the flag for the next letter                                     
        }      
        
        if(noOfCorrectGuesses == dim)               //daca am ghicit tot, am castigat
        {               
            checkIfWon = 1;     
            lcd_clear();
            lcd_gotoxy(0, 0); 
            lcd_puts("You won!!!");
            break;
        }   
        
        //delay_ms(1000); 
        lcd_clear(); 
        lcd_puts(stars);
        //lcd_puts("final while"); 
    }  
    
    if(checkIfWon == 0) 
    {
        lcd_gotoxy(0, 0);                    
        lcd_clear();
        lcd_puts("Game over."); //daca iese din while, inseamna ca noOfLives e nul, deci clar am pierdut    
    }
}
