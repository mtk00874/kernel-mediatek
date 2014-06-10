#include <linux/pm.h>
#include <linux/bug.h>
#include <linux/of_platform.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <asm/mach/map.h>
#include <asm/mach-types.h>
#include <asm/smp_scu.h>
#include <asm/page.h>
#include <mach/mt_reg_base.h>

#include <mach/irqs.h>

extern void arm_machine_restart(char mode, const char *cmd);
extern struct sys_timer mt6582_timer;
extern void mt_fixup(struct tag *tags, char **cmdline, struct meminfo *mi);
extern void mt_reserve(void);

void __init mt_init(void)
{
    /* enable bus out of order command queue to enhance boot time */
#if 1
    volatile unsigned int opt;
    opt = readl(IOMEM(MCU_BIU_BASE));
    opt |= 0x1;
    writel(opt, IOMEM(MCU_BIU_BASE));
    dsb();
#endif

	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

static struct map_desc mt_io_desc[] __initdata =
{
    {
        .virtual = INFRA_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(INFRA_BASE)),
        .length = (SZ_1M - SZ_4K),
        .type = MT_DEVICE
    },
    /* Skip the mapping of 0xF0130000~0xF013FFFF to protect access from APMCU */
    {
        .virtual = (DEBUGTOP_BASE - SZ_4K),
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS((DEBUGTOP_BASE - SZ_4K))),
        .length = (0x30000 + SZ_4K),
        .type = MT_DEVICE
    },
    {
        .virtual = (DEBUGTOP_BASE + 0x40000),
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(DEBUGTOP_BASE + 0x40000)),
        .length = 0xC0000,
        .type = MT_DEVICE
    },
    {
        .virtual = MCUSYS_CFGREG_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(MCUSYS_CFGREG_BASE)),
        .length = SZ_2M,
        .type = MT_DEVICE
    },
    /* //// */
    {
        .virtual = AP_DMA_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(AP_DMA_BASE)),
        .length = SZ_2M + SZ_1M,
        .type = MT_DEVICE
    },
    {
        /* virtual 0xF2000000, physical 0x00200000 */
        .virtual = SYSRAM_BASE,
        .pfn = __phys_to_pfn(0x00200000),
        .length = SZ_128K,
        .type = MT_MEMORY_RWX_NONCACHED
    },
    {
        .virtual = G3D_CONFIG_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(G3D_CONFIG_BASE)),
        .length = SZ_128K,
        .type = MT_DEVICE
    },
    {
        .virtual = DISPSYS_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(DISPSYS_BASE)),
        .length = SZ_16M,
        .type = MT_DEVICE
    },
    {
        .virtual = IMGSYS_CONFG_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(IMGSYS_CONFG_BASE)),
        .length = SZ_16M,
        .type = MT_DEVICE
    },
    {
        .virtual = VDEC_GCON_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(VDEC_GCON_BASE)),
        .length = SZ_16M,
        .type = MT_DEVICE
    },
    {
        /* virtual 0xF7000000, physical 0x08000000 */
        .virtual = DEVINFO_BASE,
        .pfn = __phys_to_pfn(0x08000000),
        .length = SZ_64K,
        .type = MT_DEVICE
    },
    {
        .virtual = CONN_BTSYS_PKV_BASE,
        .pfn = __phys_to_pfn(IO_VIRT_TO_PHYS(CONN_BTSYS_PKV_BASE)),
        .length = SZ_1M,
        .type = MT_DEVICE
    },
    {
        /* virtual 0xF9000000, physical 0x00100000 */
        .virtual = INTER_SRAM,
        .pfn = __phys_to_pfn(0x00100000),
        .length = SZ_64K,
        .type = MT_MEMORY_RWX_NONCACHED
    },
};

void __init mt_map_io(void)
{
    iotable_init(mt_io_desc, ARRAY_SIZE(mt_io_desc));
}


extern void __init mt8127_timer_init(void);// eddie

static const char *const mt8127_dt_match[] = { "mediatek,mt8127", NULL };

DT_MACHINE_START(MT8127, "MT8127")
//MACHINE_START(MT8127, "MT8127")
//	.smp            = smp_ops(mt65xx_smp_ops),  // eddie, reference arm/mach-mt8135/mt-smp.c
	.dt_compat      = mt8127_dt_match,
	.map_io         = mt_map_io,
	.init_irq       = mt_init_irq,
	.init_time      = mt8127_timer_init,
	//.init_early     = mt_init_early,  // if use TEE, the call mt_init_early function
	.init_machine   = mt_init,
	.fixup          = mt_fixup,
//	.restart        = arm_machine_restart,  // eddie, kernel 3.14.4 no arm_machine_restart function
	.reserve        = mt_reserve,
MACHINE_END

