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

#define PL_IPC6G_QEMU

extern char __kernel_start[];
extern char __kernel_end[];

/*
 * Platform Layer implementation for the iPod Classic 6G.
 * Generally no DTB to parse here, so DTB pointer is ignored.
*/

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

	pinfo->machine_ram_start = 0x08000000;
	pinfo->machine_ram_size = 0x4000000;
	pinfo->machine_ram_end = pinfo->machine_ram_start + pinfo->machine_ram_size;

	pinfo->machine_has_display = true;
	
	/* Begin by initializing the serial */

#ifdef PL_IPC6G_QEMU
	/*
	 * The QEMU emulation version does not emulate the proper UART device,
	 * instead it uses semi hosting, so we have to write to the semihost
	 * rather than the UART address. This requires no initialization
	 * as of now.
	*/
#else
	/* TODO initialize uart */
#endif

	kputs("DriftlessPL: initialized uart\n");

	/*
	 * Initialize CLCD on the iPod.. not much is actually needed here as
	 * the flush does most of the work for us, so we simply black out the
	 * framebuffer to all zeros and flush to wake up the display.
	*/

	kputs("clcd wakeup\n");
	PL_clcd_fill(0x0000);
	PL_clcd_flush();
	kputs("flush clcd to all white\n");
	PL_clcd_fill(0xFFFF);
	PL_clcd_flush();

	/* done */
	kputs("DriftlessPL: Platform Layer initialized\n");
}

void PL_write_char_serial(char c)
{
#ifdef PL_IPC6G_QEMU
	/*
	 * Write to semi hosting instead of proper UART due to unimplemented
	 * QEMU artifact..
	*/
	register uint32_t r0 __asm__("r0") = 3;
	register const char *r1 __asm__("r1") = &c;
	 __asm__ volatile("svc 0x123456" : "+r"(r0) : "r"(r1) : "memory");
#else
	/* TODO write to the 0x3c.. address */
#endif
}
