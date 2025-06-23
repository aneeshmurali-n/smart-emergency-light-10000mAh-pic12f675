/* 
 * File:   6v_slabattery _charger_vl.c
 * Author: Aneesh Murali Nariyampully
 * Created on June 2, 2025, 2:24 PM
 * 
 * Compiler : xc8 v2.50
 * IDE      : MPLAB X IDE v6.20
 */

#include <xc.h>

// CONFIG
#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config BOREN = ON
#pragma config CP = ON
#pragma config CPD = ON

#define _XTAL_FREQ 4000000

#define RELAY     GP1    // Charging relay
#define CHG_LED   GP2    // Charging status LED
#define CHG_BUTTON GP3   // Charging button // fot activate force charging  need external pullup
#define LOW_LED   GP4    // Low battery warning LED
unsigned char charging = 0; // to track the charging process
void ADC_Init(void) 
{
    ANSEL  = 0x01;         // AN0 input (GP0)
    CMCON  = 0x07;         // Disable comparators
    VRCON  = 0x00;         // Disable voltage reference
    ADCON0 = 0b10000001;   // ADC ON, AN0 selected, Fosc/8
    __delay_ms(2);
}

unsigned int ADC_Read(void) 
{
    __delay_us(20);
    GO_nDONE = 1;
    while (GO_nDONE);
    return ((unsigned int)ADRESH << 8) | ADRESL;
}

void main(void) 
{
    TRISIO = 0x09;  // GP0 (AN0) and GP3 input, rest output
    GPIO = 0x00;

    ADC_Init();

    while (1) 
    {
        unsigned int adcVal = ADC_Read();
        unsigned long millivolts = ((unsigned long)adcVal * 5000UL * 2) / 1023;

       
        if (CHG_BUTTON == 0)
        {
            __delay_ms(20);
            RELAY = 1;        // Start charging
            charging = 1;     // set flag to track charging state for led indication
        }
        
        if(millivolts <= 6300)
        {
            RELAY = 1;        // Start charging
            charging = 1;     // set flag to track charging state for led indication
        }
        

        if (millivolts >= 6900) 
        {
            RELAY = 0;        // Stop charging
            charging = 0;     // clear flag
        }
        
        if(charging)
        {
         // Blink CHG_LED while charging
            CHG_LED = 1;
            __delay_ms(300);
            CHG_LED = 0;
            __delay_ms(300);   
        }
        else
        {
         CHG_LED = 1;      // Solid ON when full
         __delay_ms(1000);
        }
        
        // Low battery warning
        LOW_LED = (millivolts < 5800);
    }  
}
