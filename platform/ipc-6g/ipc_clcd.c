/*
 * Copyright (c) 2026 Driftless Software Pvt. Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
*/

#include <stdint.h>
#include <player.h>
#include <klib.h>
#include <ipc-6g/clcd.h>

/*
 * iPod Classic 6G Color LCD driver.
*/

/* Consider moving this into dynamic allocation.. */
static uint16_t clcd_fb[LCD_W*LCD_H] __attribute__((aligned(32)));

static void lcd_cmd(uint8_t c) {
	while (!(LCD_STATUS & (1u<<1)));
	LCD_CMD = c;
}

static void lcd_data(uint32_t d) {
	while ((LCD_STATUS & (1u<<4)));
	LCD_DATA = d;
}

static inline uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
	return (uint16_t)(((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3));
}

/*
 * Routine PL_clcd_flush
 *
 * Flushes the CLCD with data on the global framebuffer.
 *
*/
void PL_clcd_flush(void)
{
	LCD_CON = 0x80000c21;

	lcd_cmd(0x2A);
	lcd_data(0);
	lcd_data(0);
	lcd_data(0x01);
	lcd_data(0x3f);
	lcd_cmd(0x2B);
	lcd_data(0);
	lcd_data(0);
	lcd_data(0x00);
	lcd_data(0xef);
	lcd_cmd(0x2C);

	LCD_CON = 0x80100db1;

	for (int i = 0; i < LCD_W * LCD_H; i++)
		lcd_data(clcd_fb[i]);

	LCD_FE_SIZE = 0x014000f0;
	LCD_FE_GO = 1;
}

void PL_clcd_fill(uint16_t c)
{
	for (int i = 0; i < LCD_W*LCD_H; i++)
		clcd_fb[i] = c;
}

void PL_clcd_pixel(int x, int y, uint16_t c)
{
	if ((unsigned)x < LCD_W && (unsigned)y < LCD_H) clcd_fb[y * LCD_W + x] = c;
}
