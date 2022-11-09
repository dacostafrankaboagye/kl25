

// lcd.h


#include <stdio.h>
#include <stdio.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include <string.h>



void makeRsLow();
void makeRsHigh();
void makeRwLow();
void makeRwHigh();
void makeEnLow();
void toggleEnable();
void LCD_command(uint8_t hexValue);
void setClock();
void setDataPins();
void setControlPins();
void performOperation();
void LCD_init();
void LCD_write_char(uint8_t letter);
void LCD_write_word();
void LCD_write_string(char letter);
void clear();


