
#include <iostm8s003f3.h>

#define     knopka_open1        PD_IDR_IDR3
#define     knopka_close1       PA_IDR_IDR2
#define     knopka_open2        PB_IDR_IDR5
#define     knopka_close2       PB_IDR_IDR4

#define     open1               PD_IDR_IDR6    
#define     close1              PA_IDR_IDR1
#define     open2               PC_IDR_IDR4
#define     close2              PC_IDR_IDR3

#define     out_open1           PC_ODR_ODR5    
#define     out_close1          PC_ODR_ODR6
#define     out_open2           PC_ODR_ODR7
#define     out_close2          PD_ODR_ODR2


void delay_ms(int delay); 
void delay_us(int delay);
void servo1(int number);
void servo2(int number);
void servo(int number, int serv_number);

int main()
{ 
   
    
  PC_DDR |=(1<<7)|(1<<6)|(1<<5)|(0<<4)|(0<<3);
  PC_CR1 |=(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
  PC_CR2 |=(1<<7)|(1<<6)|(1<<5)|(0<<4)|(0<<3);
  
  PD_DDR |=(1<<2)|(1<<4)|(1<<5)|(0<<3)|(0<<6);
  PD_CR1 |=(1<<2)|(1<<4)|(1<<5)|(1<<3)|(1<<6);
  PD_CR2 |=(1<<2)|(1<<4)|(1<<5)|(0<<3)|(0<<6);

  PA_DDR |=(0<<2)|(0<<1)|(0<<3);
  PA_CR1 |=(1<<2)|(1<<1)|(1<<3);
  PA_CR2 |=(0<<2)|(0<<1)|(0<<3);
  
  PB_DDR |= (0<<5)|(0<<4);
  PB_CR1 |= (1<<5)|(1<<4);
  PB_CR2 |= (0<<5)|(0<<4);
  
  CLK_CKDIVR = 0;
  
  servo(2230, 1);
  servo(2330, 2);
  
  while(1)
  { 
    if (knopka_close1 == 0 || close2 == 0) 
        {
         servo(1170, 1);
        }  
    
     if (knopka_open1 == 0 || open2 == 0) 
       {
         servo(2230, 1);  
       }     
    
    if (knopka_close2 == 0|| close1 == 0) 
        {
         servo(1270, 2);
        }  

     if (knopka_open2 == 0|| open1 == 0) 
       {
         servo(2320, 2);  
       }    

  }
  return 0;
}

void servo(int number, int serv_number)
{
  switch(serv_number)
  {
  case 1: servo1(number); break;
  case 2: servo2(number); break;
  default: break;
  }
}
void servo1(int number)
{

  for (int i=0;i<50;i++)
    {
      PD_ODR_bit.ODR4= 1;
      delay_us(number);
      PD_ODR_bit.ODR4= 0; 
      delay_ms(10);
    }
  if (number == 1170)
  {
    out_close2 = 1;
    out_open2 = 0;
  }
  else
  {
    out_close2 = 0;
    out_open2 = 1;
  }
}

void servo2(int number)
{

  for (int i=0;i<50;i++)
    {
      PD_ODR_bit.ODR5= 1;
      delay_us(number);
      PD_ODR_bit.ODR5= 0; 
      delay_ms(10);
    }
  if (number == 1270)
    {
    out_close1 = 1;
    out_open1 = 0;
    }
  else
    {
    out_close1 = 0;
    out_open1 = 1;
    }
}


void delay_ms(int delay)
{
  for(int i = 0; i < delay ; i++)
    {
    int us=3160;
    while(us)
     us--;      
    } 
}

void delay_us(int delay)
{
  for(int i = 0; i < delay ; i++)
  {
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
  }
}