#ifndef __MT_MEMORY_H__
#define __MT_MEMORY_H__

/*
 * Define constants.
 */

/*
 * Define macros.
 */

/* IO_VIRT = 0xF0000000 | IO_PHYS[27:0] */
#define IO_VIRT_TO_PHYS(v) (0x10000000 | ((v) & 0x0fffffff))
#define IO_PHYS_TO_VIRT(p) (0xf0000000 | ((p) & 0x0fffffff))

#define PLAT_PHYS_OFFSET		UL(0x80000000)

#ifndef CONFIG_ARM_LPAE
/* Maximum of 256MiB in one bank */
#define MAX_PHYSMEM_BITS	32
#define SECTION_SIZE_BITS	28
#else
#define MAX_PHYSMEM_BITS	36
#define SECTION_SIZE_BITS	31
#endif

#endif  /* !__MT_MEMORY_H__ */
