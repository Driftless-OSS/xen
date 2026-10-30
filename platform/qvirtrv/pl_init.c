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
#include <qvirtrv/ramfb.h>

#define UART0_BASE 0x10000000
#define PL_QVIRTRV_QEMU_RAM_SIZE 0x40000000

extern char __kernel_start[];
extern char __kernel_end[];

static fb_info *g_fb;

/*
 * Platform Layer implementation for the QEMU VIRT RISC-V
 * Generally no DTB to parse here, so DTB pointer is ignored.
*/

/*
 * Routine PL_put_pixel
 *
 * Outputs a single pixel of RGB format to the display.
 *
 * Parameters
 *  x, y - Coordinates.
 *  r, g, b - Color.
*/
void PL_put_pixel(u16 x, u16 y, u8 r, u8 g, u8 b)
{
	static u8 fbclr[4];

	fbclr[0] = r;
	fbclr[1] = g;
	fbclr[2] = b;
	fbclr[3] = 0;

	ramfb_xrgb256_pixel(g_fb, x, y, fbclr);
}

/*
 * Routine PL_clear_display
 *
 * Clears the display with a single color.
 *
 * Parameters
 *  r, g, b - Color.
*/
void PL_clear_display(u8 r, u8 g, u8 b)
{
	static u8 fbclr[4];

	fbclr[0] = r;
	fbclr[1] = g;
	fbclr[2] = b;
	fbclr[3] = 0;

	u64 active_row_bytes = g_fb->fb_width * g_fb->fb_bpp;
	u8 row_buffer[g_fb->fb_width*4];

	for (u32 x=0; x<g_fb->fb_width; x++) {
		kmemcpy(&row_buffer[x*g_fb->fb_bpp], fbclr, g_fb->fb_bpp);
	}

	for (u32 y=0; y<g_fb->fb_height; y++) {
		u8 *row_dst = (u8*)g_fb->fb_addr + (y*g_fb->fb_stride);
		kmemcpy(row_dst, row_buffer, active_row_bytes);
	}
}

/*
 * Routine PL_init_platform
 *
 * Initializes the platform by setting up the serial for early output, the
 * CLCD and other peripheral or clocks needed. DTB pointer is ignored here
 * as it is generally empty anyways on this device. Parses boot arguments
 * before returning.
 *
 * Parameters
 *  pinfo - Platform Layer Information pointer.
*/
void PL_init_platform(struct pl_info *pinfo)
{
	PL_set_info(pinfo);
	PL_param_setup(pinfo->boot_args);

	/* set parameters */
	pinfo->kernel_start_address = (uptr)__kernel_start;
	pinfo->kernel_end_address = (uptr)__kernel_end;
	pinfo->kernel_size = (u64)(__kernel_end - __kernel_start);

	pinfo->machine_ram_start = 0x80000000;
	pinfo->machine_ram_size = PL_QVIRTRV_QEMU_RAM_SIZE;
	pinfo->machine_ram_end = pinfo->machine_ram_start + pinfo->machine_ram_size;

	pinfo->machine_has_display = true;
	
	/* Not much needs to be done for serial init.. */
	kputs("DriftlessPL: initialized uart\n");

	/* Initialize the QEMU RAMFB display with 480x800 */
	if (ramfb_check_fw_cfg_dma()) {
		kputs("clcd wakeup\n");
		g_fb = ramfb_init(480, 800);

		if (!g_fb) {
			kputs("unexpected clcd settings\n");
			for(;;);
		}
		
		kputs("clcd flush to all white\n");
		PL_clear_display(255, 255, 255);
	} else {
		/* no display? no P  A  S  S */
		kputs("unexpected clcd error\n");
		for(;;);
	}

	/* done */
	kputs("DriftlessPL: Platform Layer initialized\n");
}

void PL_write_char_serial(char c)
{
    *(volatile uint8_t *)(UART0_BASE) = c;	
}
