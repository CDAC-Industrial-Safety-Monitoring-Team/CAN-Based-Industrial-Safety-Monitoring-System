 /*
 * lcd.c
 *
 *  Created on: 21-Mar-2026
 *      Author: Moeen Sheikh
 */

#include "lcd.h"
#include <stdio.h>

//extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

void lcd_init(void)
{
	// LCD initialization sequence
	HAL_Delay(20);
	lcd_write_nibble(LCD_CMD, 0x03);
	HAL_Delay(5);
	lcd_write_nibble(LCD_CMD, 0x03);
	HAL_Delay(1);
	lcd_write_nibble(LCD_CMD, 0x03);
	HAL_Delay(1);
	lcd_write_nibble(LCD_CMD, 0x02);
	HAL_Delay(1);

	// LCD initization commands
	lcd_write_byte(LCD_CMD, FUNCTION_SET);
	lcd_write_byte(LCD_CMD, DISPLAY_ON_OFF_CONTROL);
	lcd_write_byte(LCD_CMD, ENTRY_MODE_SET);
	lcd_write_byte(LCD_CMD, LCD_CLEAR);
	HAL_Delay(20);
}

void lcd_write_nibble(uint8_t rs, uint8_t val)
{
	// change RS to 0 for instruction or RS to 1 for data
	uint8_t rs_flag = (rs == LCD_DATA)? BV(LCD_RS_Pos) : 0;
	// write data with RW = 0, EN = 1, and rs flag
	uint8_t data = (val << LCD_DB4_Pos) | rs_flag | BV(LCD_BL_Pos) | BV(LCD_EN_Pos);
	HAL_I2C_Master_Transmit(&hi2c2, LCD_SLAVE_ADDR, &data, 1, HAL_MAX_DELAY);
	// delay
	HAL_Delay(1);
	// write data again with RW = 0, EN = 0, and rs flag
	data = (val << LCD_DB4_Pos) | rs_flag | BV(LCD_BL_Pos);
	HAL_I2C_Master_Transmit(&hi2c2, LCD_SLAVE_ADDR, &data, 1, HAL_MAX_DELAY);
}

void lcd_write_byte(uint8_t rs, uint8_t val)
{
	uint8_t high = val >> 4, low = val & 0x0F;
	lcd_write_nibble(rs, high);
	lcd_write_nibble(rs, low);
	HAL_Delay(3);
}

void lcd_puts(uint8_t line, char str[])
{
	//set line address
	lcd_write_byte(LCD_CMD, line);
	// send characters to lcd one by one
	for(int i = 0 ; str[i] != '\0' ; i++)
		lcd_write_byte(LCD_DATA, str[i]);
}

void lcd_shift_display(void)
{
	// Future use
	// Send command to shift display.
}

/******************************************************************************
 * Function : LCD_Update
 * Purpose  : Update LCD according to machine status
 ******************************************************************************/
void LCD_Update(SensorData_t *sensor)
{
    char line1[17];
    char line2[17];

    lcd_write_byte(LCD_CMD, LCD_CLEAR);

    if(sensor->Status == STATUS_NORMAL)
    {
        sprintf(line1, "STATUS: SAFE");
    }
    else
    {
        sprintf(line1, "STATUS: EMERG");
    }

    sprintf(line2,
            "T:%2dC H:%2d%%",
            sensor->Temperature,
            sensor->Humidity);

    lcd_puts(LCD_LINE1, line1);
    lcd_puts(LCD_LINE2, line2);
}

/******************************************************************************
 * Function : LCD_ShowWaiting
 * Purpose  : Display startup screen
 ******************************************************************************/
void LCD_ShowWaiting(void)
{
    lcd_write_byte(LCD_CMD, LCD_CLEAR);

    lcd_puts(LCD_LINE1, "SAFETY SYSTEM");
    lcd_puts(LCD_LINE2, "WAITING...");
}
