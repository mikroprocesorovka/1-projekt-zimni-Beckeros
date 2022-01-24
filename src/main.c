#include "stm8s.h"
#include "stm8_hd44780.h"
#include "delay.h"
#include <stdio.h>
#define _ISOC99_SOURCE
#define _GNU_SOURCE

void delay_ms(uint16_t ms) {
    uint16_t  i;
    for (i=0; i<ms; i = i+1){
        _delay_us(250);
        _delay_us(248);
        _delay_us(250);
        _delay_us(250);
    }
}

void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    lcd_init(); //inicializace LCD
    GPIO_Init(GPIOB,GPIO_PIN_7,GPIO_MODE_OUT_PP_LOW_SLOW); // výstup pro bzučák
    GPIO_WriteHigh(GPIOB,GPIO_PIN_7);
    GPIO_Init(GPIOD, GPIO_PIN_6,GPIO_MODE_IN_FL_NO_IT); // nastavíme PD6 jako vstup

}


int main(void)
{
    uint8_t pocet_pruchodu = 0;
    char text[32];
    setup();


    while (1) {
        if(GPIO_ReadInputPin(GPIOD,GPIO_PIN_6)==RESET){ //pruchod před opto bránou
            pocet_pruchodu += 1;
            lcd_gotoxy(0, 0);
            sprintf(text,"Pruchody: %1u",pocet_pruchodu); //zobrazení na displeji
            lcd_puts(text);
            GPIO_WriteLow(GPIOB,GPIO_PIN_7);
            delay_ms(600);
            GPIO_WriteHigh(GPIOB,GPIO_PIN_7);
        }


    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
