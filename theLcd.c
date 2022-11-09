
#include <stdio.h>
#include <stdio.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include <string.h>
#include "theLcd.h"

#define rs (0)
#define rw (1)
#define en (2)


#define MASK(X) (1UL<<X)


void delay_ms(uint16_t delay){
	for(int i=0; i<delay*1000; i++){
		__asm volatile("nop");
		__asm volatile("nop");
	}
}

void delay_us(uint16_t delay){
	for(int i=0; i<delay; i++){
		__asm volatile("nop");
		__asm volatile("nop");
	}
}




void makeRsLow(){ PTB->PDOR &= ~(1 << rs);}
void makeRsHigh(){PTB->PDOR |= (1 << rs);}
void makeRwLow(){PTB->PDOR &= ~(1 << rw);}
void makeRwHigh(){PTB->PDOR |= (1 << rw);}
void makeEnLow(){PTB-> PCOR = 1UL<<en;}

void clear(){

    PTB -> PDOR &= ~(1 << rw);
    PTB -> PDOR &= ~(1 << rs);
    PTC -> PDOR &= ~(1 << 0);
    PTC -> PDOR &= ~(1 << 1);
    PTC -> PDOR &= ~(1 << 1);
    PTC -> PDOR &= ~(1 << 3);
    PTC -> PDOR &= ~(1 << 4);
    PTC -> PDOR &= ~(1 << 5);
    PTC -> PDOR &= ~(1 << 6);
    PTC -> PDOR &= ~(1 << 7);

}

void toggleEnable(){
	PTB-> PSOR = 1UL<<en;
	delay_ms(1);
	PTB-> PCOR = 1UL<<en;
	delay_ms(1);
}

void LCD_command(uint8_t hexValue){
	makeEnLow();
	PTC-> PDOR = hexValue;
	toggleEnable();
}

void setClock(int x){
	SIM->SCGC5|= (1UL<<x); // using scgc5 clock
}

void setDataPins(){

	SIM->SCGC5|= (1UL<< 11);  // timing to port c

	PORTC->PCR[0] &= ~0x700;
	PORTC->PCR[0] |= (1UL<<8);
	PTC->PDDR |=  (1 << 0);

	PORTC->PCR[1] &= ~0x700;
	PORTC->PCR[1] |= (1UL<<8);
	PTC->PDDR |=  (1 << 1);

	PORTC->PCR[2] &= ~0x700;
	PORTC->PCR[2] |= (1UL<<8);
	PTC->PDDR |=  (1 << 2);

	PORTC->PCR[3] &= ~0x700;
	PORTC->PCR[3] |= (1UL<<8);
	PTC->PDDR |=  (1 << 3);

	PORTC->PCR[4] &= ~0x700;
	PORTC->PCR[4] |= (1UL<<8);
	PTC->PDDR |=  (1 << 4);

	PORTC->PCR[5] &= ~0x700;
	PORTC->PCR[5] |= (1UL<<8);
	PTC->PDDR |=  (1 << 5);

	PORTC->PCR[6] &= ~0x700;
	PORTC->PCR[6] |= (1UL<<8);
	PTC->PDDR |=  (1 << 6);

	PORTC->PCR[7] &= ~0x700;
	PORTC->PCR[7] |= (1UL<<8);
	PTC->PDDR |=  (1 << 7);

}

void setControlPins(){

		SIM->SCGC5|= (1UL<< 10);  // timing to port b

		PORTB->PCR[rs] &= ~0x700;
		PORTB->PCR[rs] |= (1UL<<8);
		PTB->PDDR |=  (1UL << rs);

		PORTB->PCR[rw] &= ~0x700;
		PORTB->PCR[rw] |= (1UL<<8);
		PTB->PDDR |=  (1UL << rw);

		PORTB->PCR[en] &= ~0x700;
		PORTB->PCR[en] |= (1UL<<8);
		PTB->PDDR |=  (1UL << en );
}






void LCD_init(){

	// from the data sheet
	clear();
	delay_ms(30);

	makeRsLow();
	makeRwLow();

	LCD_command(0x30);
	delay_ms(10);
	LCD_command(0x30);
	delay_us(200);

	LCD_command(0x30);

	LCD_command(0x38);  // change to 3C

//	performOperation(0x08); //displayOff
//	performOperation(0x01); //displayClear
//	performOperation(0x0F); //LCD_DisplayOn
//	LCD_command(0x06);
//	 delay_us(100);

	LCD_command(0X08);
	delay_us(100);

	LCD_command(0X01);
	delay_ms(10);
	LCD_command(0X0F);
	delay_us(100);

	LCD_command(0X06);
	delay_us(100);
}

void LCD_write_char(uint8_t letter){

	PTB->PDOR |= (1 << rs);
	PTB->PDOR &= ~(1 << rw);
	LCD_command(letter);

}

void LCD_write_string(char letter){

	PTB->PDOR |= (1 << rs);
	PTB->PDOR &= ~(1 << rw);
	LCD_command(letter);

}

void LCD_write_word(char word[])
{
	PTB->PDOR |= (1 << rs);
	makeRwLow(); PTB->PDOR &= ~(1 << rw);

	for(int i=0; i<strlen(word); i++){
		LCD_command(word[i]);
	}

}

