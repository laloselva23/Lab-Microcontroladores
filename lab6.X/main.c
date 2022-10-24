/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F57Q43
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <math.h>

#define SWEEP_FREQ 500

uint8_t char_to_seg(uint8_t num);
void send_to_disp(uint32_t disp_word);
void send_to_disp1(uint8_t disp_word1);
uint8_t key_scanner(void);

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
   
    while (1){
        
        uint8_t key = key_scanner();
        uint32_t num = 0x01020304;
      //send_to_disp(num);
        send_to_disp1(key);
        
        
        
    }
}  

uint8_t char_to_seg(uint8_t num){
    uint8_t segments;
    switch(num){
        case 0:  segments = 0b00111111; break;
        case 1:  segments = 0b00000110; break;
        case 2:  segments = 0b01011011; break;
        case 3:  segments = 0b01001111; break;
        case 4:  segments = 0b01100110; break;
        case 5:  segments = 0b01101101; break;
        case 6:  segments = 0b01111101; break;
        case 7:  segments = 0b00000111; break;
        case 8:  segments = 0b01111111; break;
        case 9:  segments = 0b01100111; break;
        case 10: segments = 0b01110111; break;
        case 11: segments = 0b01111100; break;
        case 12: segments = 0b01011000; break;
        case 13: segments = 0b01011110; break;
        case 14: segments = 0b01111001; break;
        default: segments = 0b01110001; break;
    }
    return segments;
}

void send_to_disp(uint32_t disp_word){
    for (char i = 0; i < 4; i++){
        int internal_sweep = (int) pow(2, i);
        int sweep = internal_sweep;
        //LATC = (char) sweep;
        LATC=1;
        uint8_t num_disp = 0x000000FF & (disp_word >> i*8);
        LATB = char_to_seg(num_disp);
        //LATB = 0b00000111;
        __delay_ms(SWEEP_FREQ);
    }
}

void send_to_disp1(uint8_t disp_word1){
    
        LATC=1;
        LATB = char_to_seg(disp_word1);
        __delay_ms(SWEEP_FREQ);
    
}
uint8_t key_scanner(void){
    KRO1_LAT  = 0;
    KRO2_LAT  = 1;
    KRO3_LAT  = 1;
    KRO4_LAT  = 1;
    __delay_ms(SWEEP_FREQ);
    if      (KCI1_PORT == 0) {__delay_ms(SWEEP_FREQ); return 1;}
    else if (KCI2_PORT == 0) {__delay_ms(SWEEP_FREQ); return 2;}
    else if (KCI3_PORT == 0) {__delay_ms(SWEEP_FREQ); return 3;}
    else if (KCI4_PORT == 0) {__delay_ms(SWEEP_FREQ); return 10;}
    KRO1_LAT  = 1;
    KRO2_LAT  = 0;
    KRO3_LAT  = 1;
    KRO4_LAT  = 1;
    __delay_ms(SWEEP_FREQ);
    if      (KCI1_PORT == 0) {__delay_ms(SWEEP_FREQ); return 4;}
    else if (KCI2_PORT == 0) {__delay_ms(SWEEP_FREQ); return 5;}
    else if (KCI3_PORT == 0) {__delay_ms(SWEEP_FREQ); return 6;}
    else if (KCI4_PORT == 0) {__delay_ms(SWEEP_FREQ); return 11;}
    KRO1_LAT  = 1;
    KRO2_LAT  = 1;
    KRO3_LAT  = 0;
    KRO4_LAT  = 1;
    __delay_ms(SWEEP_FREQ);
    if      (KCI1_PORT == 0) {__delay_ms(SWEEP_FREQ); return 7;}
    else if (KCI2_PORT == 0) {__delay_ms(SWEEP_FREQ); return 8;}
    else if (KCI3_PORT == 0) {__delay_ms(SWEEP_FREQ); return 9;}
    else if (KCI4_PORT == 0) {__delay_ms(SWEEP_FREQ); return 12;}
    KRO1_LAT  = 1;
    KRO2_LAT  = 1;
    KRO3_LAT  = 1;
    KRO4_LAT  = 0;
    __delay_ms(SWEEP_FREQ);
    if      (KCI1_PORT == 0) {__delay_ms(SWEEP_FREQ); return 14;}
    else if (KCI2_PORT == 0) {__delay_ms(SWEEP_FREQ); return 0;}
    else if (KCI3_PORT == 0) {__delay_ms(SWEEP_FREQ); return 15;}
    else if (KCI4_PORT == 0) {__delay_ms(SWEEP_FREQ); return 13;}   
    else return 'x';
}


