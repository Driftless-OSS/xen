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

#ifndef _PLATFORM_LAYER_IPC6G_CLCD_H_
#define _PLATFORM_LAYER_IPC6G_CLCD_H_

#include <stdint.h>

#define LCD_BASE 0x38300000u
#define LCD_CMD (*(volatile uint32_t *)(LCD_BASE + 0x04))
#define LCD_STATUS (*(volatile uint32_t *)(LCD_BASE + 0x1c))
#define LCD_DATA (*(volatile uint32_t *)(LCD_BASE + 0x40))
#define LCD_CON (*(volatile uint32_t *)(LCD_BASE + 0x00))
#define LCD_FE_SIZE (*(volatile uint32_t *)(LCD_BASE + 0x74))
#define LCD_FE_GO (*(volatile uint32_t *)(LCD_BASE + 0x70))

#define LCD_W 320
#define LCD_H 240

void PL_clcd_flush(void);
void PL_clcd_fill(uint16_t c);
void PL_clcd_pixel(int x, int y, uint16_t c);

#endif
