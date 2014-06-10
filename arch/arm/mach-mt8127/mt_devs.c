#include <generated/autoconf.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/ioport.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/memblock.h>
#include <asm/setup.h>
#include <asm/mach/arch.h>
#include <linux/sysfs.h>
#include <asm/io.h>
#include <linux/spi/spi.h>
#include <linux/amba/bus.h>
#include <linux/amba/clcd.h>
#include "mach/memory.h"
#include "mach/irqs.h"
#include <mach/mt_reg_base.h>
#include <mach/devs.h>
#include <linux/version.h>


/*=======================================================================*/
/* MT6589 UART Ports                                                     */
/*=======================================================================*/
#if defined(CFG_DEV_UART1)
static struct resource mtk_resource_uart1[] = {
	{
		.start		= IO_VIRT_TO_PHYS(UART1_BASE),
		.end		= IO_VIRT_TO_PHYS(UART1_BASE) + MTK_UART_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.start		= MT_UART1_IRQ_ID,
		.flags		= IORESOURCE_IRQ,
	},
};
#endif

#if defined(CFG_DEV_UART2)
static struct resource mtk_resource_uart2[] = {
	{
		.start		= IO_VIRT_TO_PHYS(UART2_BASE),
		.end		= IO_VIRT_TO_PHYS(UART2_BASE) + MTK_UART_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.start		= MT_UART2_IRQ_ID,
		.flags		= IORESOURCE_IRQ,
	},
};
#endif

#if defined(CFG_DEV_UART3)
static struct resource mtk_resource_uart3[] = {
	{
		.start		= IO_VIRT_TO_PHYS(UART3_BASE),
		.end		= IO_VIRT_TO_PHYS(UART3_BASE) + MTK_UART_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.start		= MT_UART3_IRQ_ID,
		.flags		= IORESOURCE_IRQ,
	},
};
#endif

#if defined(CFG_DEV_UART4)
static struct resource mtk_resource_uart4[] = {
	{
		.start		= IO_VIRT_TO_PHYS(UART4_BASE),
		.end		= IO_VIRT_TO_PHYS(UART4_BASE) + MTK_UART_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.start		= MT_UART4_IRQ_ID,
		.flags		= IORESOURCE_IRQ,
	},
};
#endif


static struct platform_device mtk_device_uart[] = {

    #if defined(CFG_DEV_UART1)
    {
    	.name			= "mtk-uart",
    	.id				= 0,
    	.num_resources	= ARRAY_SIZE(mtk_resource_uart1),
    	.resource		= mtk_resource_uart1,
    },
    #endif
    #if defined(CFG_DEV_UART2)
    {
    	.name			= "mtk-uart",
    	.id				= 1,
    	.num_resources	= ARRAY_SIZE(mtk_resource_uart2),
    	.resource		= mtk_resource_uart2,
    },
    #endif
    #if defined(CFG_DEV_UART3)
    {
    	.name			= "mtk-uart",
    	.id				= 2,
    	.num_resources	= ARRAY_SIZE(mtk_resource_uart3),
    	.resource		= mtk_resource_uart3,
    },
    #endif

    #if defined(CFG_DEV_UART4)
    {
    	.name			= "mtk-uart",
    	.id				= 3,
    	.num_resources	= ARRAY_SIZE(mtk_resource_uart4),
    	.resource		= mtk_resource_uart4,
    },
    #endif
};

#if defined(CONFIG_SERIAL_AMBA_PL011)
static struct amba_device uart1_device =
{
    .dev =
    {
        .coherent_dma_mask = ~0,
        .init_name = "dev:f1",
        .platform_data = NULL,
    },
    .res =
    {
        .start  = 0xE01F1000,
        .end = 0xE01F1000 + SZ_4K - 1,
        .flags  = IORESOURCE_MEM,
    },
    .dma_mask = ~0,
    .irq = MT_UART1_IRQ_ID,
};
#endif

/*=======================================================================*/
/* MT8127 MSDC Hosts                                                       */
/*=======================================================================*/
#if defined(CFG_DEV_MSDC0)
static struct resource mt_resource_msdc0[] = {
    {
        .start  = IO_VIRT_TO_PHYS(MSDC_0_BASE),
        .end    = IO_VIRT_TO_PHYS(MSDC_0_BASE) + 0x108,
        .flags  = IORESOURCE_MEM,
    },
    {
        .start  = MT_MSDC0_IRQ_ID,
        .flags  = IORESOURCE_IRQ,
    },
};
#endif

#if defined(CFG_DEV_MSDC1)
static struct resource mt_resource_msdc1[] = {
    {
        .start  = IO_VIRT_TO_PHYS(MSDC_1_BASE),
        .end    = IO_VIRT_TO_PHYS(MSDC_1_BASE) + 0x108,
        .flags  = IORESOURCE_MEM,
    },
    {
        .start  = MT_MSDC1_IRQ_ID,
        .flags  = IORESOURCE_IRQ,
    },
};
#endif

#if defined(CFG_DEV_MSDC2)
static struct resource mt_resource_msdc2[] = {
    {
        .start  = IO_VIRT_TO_PHYS(MSDC_2_BASE),
        .end    = IO_VIRT_TO_PHYS(MSDC_2_BASE) + 0x108,
        .flags  = IORESOURCE_MEM,
    },
    {
        .start  = MT_MSDC2_IRQ_ID,
        //.start  = MSDC2_IRQ_ID,
        .flags  = IORESOURCE_IRQ,
    },
};
#endif

#if defined(CFG_DEV_MSDC3)
static struct resource mt_resource_msdc3[] = {
    {
        .start  = IO_VIRT_TO_PHYS(MSDC_3_BASE),
        .end    = IO_VIRT_TO_PHYS(MSDC_3_BASE) + 0x108,
        .flags  = IORESOURCE_MEM,
    },
    {
        .start  = MT_MSDC3_IRQ_ID,
        .flags  = IORESOURCE_IRQ,
    },
};
#endif
#if defined(CFG_DEV_MSDC4)
static struct resource mt_resource_msdc4[] = {
    {
        .start  = IO_VIRT_TO_PHYS(MSDC_4_BASE),
        .end    = IO_VIRT_TO_PHYS(MSDC_4_BASE) + 0x108,
        .flags  = IORESOURCE_MEM,
    },
    {
        .start  = MT_MSDC4_IRQ_ID,
        .flags  = IORESOURCE_IRQ,
    },
};
#endif

#if defined(CONFIG_MTK_FB)
static u64 mtkfb_dmamask = ~(u32)0;

static struct resource resource_fb[] = {
	{
		.start		= 0, /* Will be redefined later */
		.end		= 0,
		.flags		= IORESOURCE_MEM
	}
};

static struct platform_device mt6575_device_fb = {
    .name = "mtkfb",
    .id   = 0,
    .num_resources = ARRAY_SIZE(resource_fb),
    .resource      = resource_fb,
    .dev = {
        .dma_mask = &mtkfb_dmamask,
        .coherent_dma_mask = 0xffffffff,
    },
};
#endif

static struct platform_device mt_device_msdc[] =
{
#if defined(CFG_DEV_MSDC0)
    {
        .name           = "mtk-msdc",
        .id             = 0,
        .num_resources  = ARRAY_SIZE(mt_resource_msdc0),
        .resource       = mt_resource_msdc0,
        .dev = {
            .platform_data = &msdc0_hw,
        },
    },
#endif
#if defined(CFG_DEV_MSDC1)
    {
        .name           = "mtk-msdc",
        .id             = 1,
        .num_resources  = ARRAY_SIZE(mt_resource_msdc1),
        .resource       = mt_resource_msdc1,
        .dev = {
            .platform_data = &msdc1_hw,
        },
    },
#endif
#if defined(CFG_DEV_MSDC2)
    {
        .name           = "mtk-msdc",
        .id             = 2,
        .num_resources  = ARRAY_SIZE(mt_resource_msdc2),
        .resource       = mt_resource_msdc2,
        .dev = {
            .platform_data = &msdc2_hw,
        },
    },
#endif
#if defined(CFG_DEV_MSDC3)
    {
        .name           = "mtk-msdc",
        .id             = 3,
        .num_resources  = ARRAY_SIZE(mt_resource_msdc3),
        .resource       = mt_resource_msdc3,
        .dev = {
            .platform_data = &msdc3_hw,
        },
    },
#endif
#if defined(CFG_DEV_MSDC4)
    {
        .name           = "mtk-msdc",
        .id             = 4,
        .num_resources  = ARRAY_SIZE(mt_resource_msdc4),
        .resource       = mt_resource_msdc4,
        .dev = {
            .platform_data = &msdc4_hw,
        },
    },
#endif

};

void mt_fixup(struct tag *tags, char **cmdline, struct meminfo *mi)
{
}

/*=======================================================================*/
/* MT6589 Board Device Initialization                                    */
/*=======================================================================*/
__init int mt_board_init(void)
{
    int i = 0, retval = 0;

#if defined(CONFIG_MTK_SERIAL)
    for (i = 0; i < ARRAY_SIZE(mtk_device_uart); i++){
        retval = platform_device_register(&mtk_device_uart[i]);
        printk("register uart device\n");
        if (retval != 0){
            return retval;
        }
    }
#endif

#if defined(CONFIG_MTK_MMC)
    for (i = 0; i < ARRAY_SIZE(mt_device_msdc); i++){
        retval = platform_device_register(&mt_device_msdc[i]);
			if (retval != 0){
				return retval;
			}
		}
#endif

    return 0;
}

void mt_reserve(void)
{
}

