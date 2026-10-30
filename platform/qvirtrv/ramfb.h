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

#ifndef _PLATFORM_LAYER_QVRV_RAMFB_H_
#define _PLATFORM_LAYER_QVRV_RAMFB_H_

#include <stdint.h>

#define QEMU_CFG_FILE_DIR 0x19

#define QEMU_CFG_DMA_CTL_ERROR 0x01
#define QEMU_CFG_DMA_CTL_READ 0x02
#define QEMU_CFG_DMA_CTL_SKIP 0x04
#define QEMU_CFG_DMA_CTL_SELECT 0x08
#define QEMU_CFG_DMA_CTL_WRITE 0x10

#define BASE_ADDR 0x10100000
#define BASE_ADDR_SELECTOR 0x10100008
#define BASE_ADDR_DATA 0x10100000
#define BASE_ADDR_ADDR 0x10100010

#define fourcc_code(a, b, c, d) ((uint32_t)(a) | ((uint32_t)(b) << 8) | ((uint32_t)(c) << 16) | ((uint32_t)(d) << 24))

#define DRM_FORMAT_XRGB8888 fourcc_code('X', 'R', '2', '4')

union fw_cfg_sig_read {
	uint32_t theInt;
	char bytes[sizeof(int)];
};

typedef struct {
	uint32_t control;
	uint32_t length;
	uint64_t address;
} __attribute__((__packed__)) qemu_cfg_dma_access;

struct __attribute__((__packed__)) qemu_ramfb_cfg {
	uint64_t addr;
	uint32_t fourcc;
	uint32_t flags;
	uint32_t width;
	uint32_t height;
	uint32_t stride;
};

struct qemu_cfg_file {
	uint32_t size;
	uint16_t select;
	uint16_t reserved;
	char name[56];
};

typedef struct {
	uint64_t fb_addr;
	uint32_t fb_width;
	uint32_t fb_height;
	uint32_t fb_bpp;

	uint32_t fb_stride;
	uint32_t fb_size;
} fb_info;

fb_info *ramfb_init(int w, int h);
int ramfb_check_fw_cfg_dma();
void ramfb_xrgb256_pixel(fb_info *fb, uint16_t x, uint16_t y, uint8_t pixel[4]);

#endif
