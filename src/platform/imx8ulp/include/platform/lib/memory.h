/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright 2021 NXP
 *
 * Zhang Peng <peng.zhang_8@nxp.com>
 */

#ifdef __SOF_LIB_MEMORY_H__

#ifndef __PLATFORM_LIB_MEMORY_H__
#define __PLATFORM_LIB_MEMORY_H__

#include <sof/lib/cache.h>


/* data cache line alignment */
#define PLATFORM_DCACHE_ALIGN	sizeof(void *)

/* physical DSP addresses */

#define IRAM_BASE	0x21170000
#define IRAM_SIZE	0x10000

#define DRAM0_BASE	0x21180000
#define DRAM0_SIZE	0x10000

#define SDRAM0_BASE	0x1a000000
#define SDRAM0_SIZE	0x800000

#define SDRAM1_BASE	0x1a800000
#define SDRAM1_SIZE	0x800000

/* physical address in Arm side */
#define MEM_RESERVED    0x8e000000

/* MU3: ASide (A35) BSide (HIFI4) */
#define XSHAL_MU3_SIDEB_BYPASS_PADDR 0x2DA20000
#define MU_BASE		XSHAL_MU3_SIDEB_BYPASS_PADDR

#define EDMA2_BASE	0x2D810000
#define EDMA2_SIZE	0x10000

#define SAI_5_BASE	0x29890000
#define SAI_5_SIZE	0x00010000
#define SAI_6_BASE	0x2DA90000
#define SAI_6_SIZE	0x00010000
#define SAI_7_BASE	0x2DAA0000
#define SAI_7_SIZE	0x00010000

#define UUID_ENTRY_ELF_BASE	0x1FFFA000
#define UUID_ENTRY_ELF_SIZE	0x6000

#define LOG_ENTRY_ELF_BASE	0x20000000
#define LOG_ENTRY_ELF_SIZE	0x2000000

#define EXT_MANIFEST_ELF_BASE	(LOG_ENTRY_ELF_BASE + LOG_ENTRY_ELF_SIZE)
#define EXT_MANIFEST_ELF_SIZE	0x2000000

/*
 * The Heap and Stack on i.MX8 are organised like this :-
 *
 * +--------------------------------------------------------------------------+
 * | Offset              | Region         |  Size                             |
 * +---------------------+----------------+-----------------------------------+
 * | SDRAM_BASE          | RO Data        |  SOF_DATA_SIZE                    |
 * |                     | Data           |                                   |
 * |                     | BSS            |                                   |
 * +---------------------+----------------+-----------------------------------+
 * | HEAP_SYSTEM_BASE    | System Heap    |  HEAP_SYSTEM_SIZE                 |
 * +---------------------+----------------+-----------------------------------+
 * | HEAP_RUNTIME_BASE   | Runtime Heap   |  HEAP_RUNTIME_SIZE                |
 * +---------------------+----------------+-----------------------------------+
 * | HEAP_BUFFER_BASE    | Module Buffers |  HEAP_BUFFER_SIZE                 |
 * +---------------------+----------------+-----------------------------------+
 * | SOF_STACK_END       | Stack          |  SOF_STACK_SIZE                   |
 * +---------------------+----------------+-----------------------------------+
 * | SOF_STACK_BASE      |                |                                   |
 * +---------------------+----------------+-----------------------------------+
 */

/* Mailbox configuration */
#define SRAM_OUTBOX_BASE	SDRAM1_BASE
#define SRAM_OUTBOX_SIZE	0x1000
#define SRAM_OUTBOX_OFFSET	0

#define SRAM_INBOX_BASE		(SRAM_OUTBOX_BASE + SRAM_OUTBOX_SIZE)
#define SRAM_INBOX_SIZE		0x1000
#define SRAM_INBOX_OFFSET	SRAM_OUTBOX_SIZE

#define SRAM_DEBUG_BASE		(SRAM_INBOX_BASE + SRAM_INBOX_SIZE)
#define SRAM_DEBUG_SIZE		0x2800
#define SRAM_DEBUG_OFFSET	(SRAM_INBOX_OFFSET + SRAM_INBOX_SIZE)

#define SRAM_EXCEPT_BASE	(SRAM_DEBUG_BASE + SRAM_DEBUG_SIZE)
#define SRAM_EXCEPT_SIZE	0x800
#define SRAM_EXCEPT_OFFSET	(SRAM_DEBUG_OFFSET + SRAM_DEBUG_SIZE)

#define SRAM_STREAM_BASE	(SRAM_EXCEPT_BASE + SRAM_EXCEPT_SIZE)
#define SRAM_STREAM_SIZE	0x1000
#define SRAM_STREAM_OFFSET	(SRAM_EXCEPT_OFFSET + SRAM_EXCEPT_SIZE)

#define SRAM_TRACE_BASE		(SRAM_STREAM_BASE + SRAM_STREAM_SIZE)
#define SRAM_TRACE_SIZE		0x1000
#define SRAM_TRACE_OFFSET (SRAM_STREAM_OFFSET + SRAM_STREAM_SIZE)

#define SOF_MAILBOX_SIZE	(SRAM_INBOX_SIZE + SRAM_OUTBOX_SIZE \
				+ SRAM_DEBUG_SIZE + SRAM_EXCEPT_SIZE \
				+ SRAM_STREAM_SIZE + SRAM_TRACE_SIZE)

/* Heap section sizes for module pool */
#define HEAP_RT_COUNT8		0
#define HEAP_RT_COUNT16		48
#define HEAP_RT_COUNT32		48
#define HEAP_RT_COUNT64		32
#define HEAP_RT_COUNT128	32
#define HEAP_RT_COUNT256	32
#define HEAP_RT_COUNT512	4
#define HEAP_RT_COUNT1024	4
#define HEAP_RT_COUNT2048	4

/* Heap section sizes for system runtime heap */
#define HEAP_SYS_RT_COUNT64	128
#define HEAP_SYS_RT_COUNT512	16
#define HEAP_SYS_RT_COUNT1024	8

/* Heap configuration */

#define HEAP_SYSTEM_BASE	(SDRAM1_BASE + SOF_MAILBOX_SIZE)
#define HEAP_SYSTEM_SIZE	0xe000

#define HEAP_SYSTEM_0_BASE	HEAP_SYSTEM_BASE

#define HEAP_SYS_RUNTIME_BASE	(HEAP_SYSTEM_BASE + HEAP_SYSTEM_SIZE)
#define HEAP_SYS_RUNTIME_SIZE \
	(HEAP_SYS_RT_COUNT64 * 64 + HEAP_SYS_RT_COUNT512 * 512 + \
	HEAP_SYS_RT_COUNT1024 * 1024)

#define HEAP_RUNTIME_BASE	(HEAP_SYS_RUNTIME_BASE + HEAP_SYS_RUNTIME_SIZE)
#define HEAP_RUNTIME_SIZE \
	(HEAP_RT_COUNT8 * 8 + HEAP_RT_COUNT16 * 16 + \
	HEAP_RT_COUNT32 * 32 + HEAP_RT_COUNT64 * 64 + \
	HEAP_RT_COUNT128 * 128 + HEAP_RT_COUNT256 * 256 + \
	HEAP_RT_COUNT512 * 512 + HEAP_RT_COUNT1024 * 1024 + \
	HEAP_RT_COUNT2048 * 2048)

#define HEAP_BUFFER_BASE	(HEAP_RUNTIME_BASE + HEAP_RUNTIME_SIZE)
#define HEAP_BUFFER_SIZE \
	(SDRAM1_SIZE - SOF_MAILBOX_SIZE - HEAP_RUNTIME_SIZE - SOF_STACK_TOTAL_SIZE -\
	HEAP_SYS_RUNTIME_SIZE - HEAP_SYSTEM_SIZE)

#define HEAP_BUFFER_BLOCK_SIZE		0x100
#define HEAP_BUFFER_COUNT	(HEAP_BUFFER_SIZE / HEAP_BUFFER_BLOCK_SIZE)

#define PLATFORM_HEAP_SYSTEM		1 /* one per core */
#define PLATFORM_HEAP_SYSTEM_RUNTIME	1 /* one per core */
#define PLATFORM_HEAP_RUNTIME		1
#define PLATFORM_HEAP_BUFFER		1

/* Stack configuration */
#define SOF_STACK_SIZE		(CONFIG_SOF_STACK_SIZE)
#define SOF_STACK_TOTAL_SIZE	SOF_STACK_SIZE
#define SOF_STACK_BASE		(SDRAM1_BASE + SDRAM1_SIZE)
#define SOF_STACK_END		(SOF_STACK_BASE - SOF_STACK_TOTAL_SIZE)

/* Vector and literal sizes - not in core-isa.h */
#define SOF_MEM_VECT_LIT_SIZE		0x4
#define SOF_MEM_VECT_TEXT_SIZE		0x1c
#define SOF_MEM_VECT_SIZE		(SOF_MEM_VECT_TEXT_SIZE + SOF_MEM_VECT_LIT_SIZE)

#define SOF_MEM_RESET_TEXT_SIZE		0x2e0
#define SOF_MEM_RESET_LIT_SIZE		0x120
#define SOF_MEM_VECBASE_LIT_SIZE	0x178

#define SOF_MEM_RO_SIZE			0x8

#define HEAP_BUF_ALIGNMENT		DCACHE_LINE_SIZE

/** \brief EDF task's default stack size in bytes. */
#define PLATFORM_TASK_DEFAULT_STACK_SIZE	3072

#if !defined(__ASSEMBLER__) && !defined(LINKER)

struct sof;

/**
 * \brief Data shared between different cores.
 * Does nothing, since IMX doesn't support SMP.
 */
#define SHARED_DATA

void platform_init_memmap(struct sof *sof);

#define uncache_to_cache(address)	address
#define cache_to_uncache(address)	address
#define is_uncached(address)		0

static inline void *platform_shared_get(void *ptr, int bytes)
{
	return ptr;
}

/**
 * \brief Function for keeping shared data synchronized.
 * It's used after usage of data shared by different cores.
 * Such data is either statically marked with SHARED_DATA
 * or dynamically allocated with SOF_MEM_FLAG_SHARED flag.
 * Does nothing, since IMX doesn't support SMP.
 */
static inline void platform_shared_commit(void *ptr, int bytes) { }

static inline void *platform_rfree_prepare(void *ptr)
{
	return ptr;
}

#endif

#define host_to_local(addr) (SDRAM0_BASE + ((addr) - MEM_RESERVED))
#define local_to_host(addr) (MEM_RESERVED + ((addr) - SDRAM0_BASE))

#endif /* __PLATFORM_LIB_MEMORY_H__ */

#else

#error "This file shouldn't be included from outside of sof/lib/memory.h"

#endif /* __SOF_LIB_MEMORY_H__ */
