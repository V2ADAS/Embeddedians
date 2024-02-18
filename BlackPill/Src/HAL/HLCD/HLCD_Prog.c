
/** Put this in the src folder **/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "HLCD_Config.h"
#include "HLCD_Int.h"
#include "../../MCAL/MI2C/MI2C_int.h"
#include "../../MCAL/MSTK/MSYSTICK_Int.h"

/** Put this in the src folder **/

#include "HLCD_Int.h"

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	u8 data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	MI2C_vMasterTx(I2C1, SLAVE_ADDRESS_LCD, data_t, 4, WithStop);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	u8 data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	MI2C_vMasterTx(I2C1, SLAVE_ADDRESS_LCD, data_t, 4, WithStop);
}

void lcd_clear (void)
{
	lcd_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}


void lcd_init (void)
{
	// 4 bit initialisation
	MSYSTICK_vDelayms(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	MSYSTICK_vDelayms(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	MSYSTICK_vDelayms(1);  // wait for >100us
	lcd_send_cmd (0x30);
	MSYSTICK_vDelayms(10);
	lcd_send_cmd (0x20);  // 4bit mode
	MSYSTICK_vDelayms(10);

  // dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	MSYSTICK_vDelayms(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	MSYSTICK_vDelayms(1);
	lcd_send_cmd (0x01);  // clear display
	MSYSTICK_vDelayms(1);
	MSYSTICK_vDelayms(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	MSYSTICK_vDelayms(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

