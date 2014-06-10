#include <linux/init.h>
#include <linux/delay.h>
#include "mach/devs.h"
#include "mach/pm_common.h"
#include "cust/cust_eint.h"



/*
 * board_init: entry point for board initialization.
 * Always return 1.
 */
static __init int board_init(void)
{
    /*
     * NoteXXX: There are two board init related functions.
     *          One is mt65xx_board_init() and another is custom_board_init().
     *
     *          mt65xx_board_init() is used for chip-dependent code.
     *          It is suggested to put driver code in this function to do:
     *          1). Capability structure of platform devices.
     *          2). Define platform devices with their resources.
     *          3). Register MT65XX platform devices.
     *
     *          custom_board_init() is used for customizable code.
     *          It is suggested to put driver code in this function to do:
     *          1). Initialize board (PINMUX, GPIOs).
     *          2). Perform board specific initialization:
     *              1-1). Register MT65xx platform devices.
     *              1-2). Register non-MT65xx platform devices.
     *                    (e.g. external peripheral GPS, BT, ¡K etc.)
     */
    // mt6582_power_management_init();

    mt_board_init();

    /* init low power PMIC setting after PMIC is ready */
    // mt6582_pmic_low_power_init();

    /* BUG BUG: temporarily marked since customization is not ready yet */
# if 0
    custom_board_init();
#endif

    return 0;
}

late_initcall(board_init);

#define MSDC_SDCARD_FLAG  (MSDC_SYS_SUSPEND | MSDC_WP_PIN_EN | MSDC_CD_PIN_EN | MSDC_REMOVABLE | MSDC_HIGHSPEED)

#if defined(CFG_DEV_MSDC0)
	struct msdc_hw msdc0_hw = {
	    .clk_src        = MSDC_CLKSRC_200MHZ,
	    .cmd_edge       = MSDC_SMPL_FALLING,
		.rdata_edge 	= MSDC_SMPL_FALLING,
		.wdata_edge 	= MSDC_SMPL_FALLING,
	    .clk_drv        = 4,
	    .cmd_drv        = 2,
	    .dat_drv        = 2,
	    .data_pins      = 8,
	    .data_offset    = 0,
	    .flags          = MSDC_SYS_SUSPEND | MSDC_HIGHSPEED | MSDC_UHS1 | MSDC_DDR,
	    .dat0rddly		= 0xa,
			.dat1rddly		= 0,
			.dat2rddly		= 0,
			.dat3rddly		= 0,
			.dat4rddly		= 0,
			.dat5rddly		= 0,
			.dat6rddly		= 0,
			.dat7rddly		= 0,
			.datwrddly		= 0,
			.cmdrrddly		= 0,
			.cmdrddly		= 0,
	    .host_function	= MSDC_EMMC,
	    .boot			= MSDC_BOOT_EN,
	};
#endif


#if defined(CFG_DEV_MSDC1)
struct msdc_hw msdc1_hw = {
    .clk_src        = MSDC_CLKSRC_200MHZ,
    .cmd_edge       = MSDC_SMPL_FALLING,
    .rdata_edge     = MSDC_SMPL_FALLING,
    .wdata_edge     = MSDC_SMPL_FALLING,
    .clk_drv        = 6,
    .cmd_drv        = 6,
    .dat_drv        = 6,
    .clk_drv_sd_18	= 3,               /* sdr104 mode */
    .cmd_drv_sd_18	= 3,
    .dat_drv_sd_18	= 2,
    .clk_drv_sd_18_sdr50	= 3,       /* sdr50 mode */
    .cmd_drv_sd_18_sdr50	= 3,
    .dat_drv_sd_18_sdr50	= 2,
    .clk_drv_sd_18_ddr50	= 3,       /* ddr50 mode */
    .cmd_drv_sd_18_ddr50	= 3,
    .dat_drv_sd_18_ddr50	= 2,
    .data_pins      = 4,
    .data_offset    = 0,
#ifdef CUST_EINT_MSDC1_INS_NUM
    .flags          = MSDC_SYS_SUSPEND | MSDC_WP_PIN_EN | MSDC_CD_PIN_EN | MSDC_REMOVABLE | MSDC_HIGHSPEED | MSDC_UHS1 |MSDC_DDR |MSDC_SD_NEED_POWER,

#else
    .flags          = MSDC_SYS_SUSPEND | MSDC_WP_PIN_EN | MSDC_HIGHSPEED | MSDC_UHS1 |MSDC_DDR,
#endif
  	  .dat0rddly		= 0,
			.dat1rddly		= 0,
			.dat2rddly		= 0,
			.dat3rddly		= 0,
			.dat4rddly		= 0,
			.dat5rddly		= 0,
			.dat6rddly		= 0,
			.dat7rddly		= 0,
			.datwrddly		= 0,
			.cmdrrddly		= 0,
			.cmdrddly		= 0,
    .host_function	= MSDC_SD,
    .boot			= 0,
    .cd_level		= MSDC_CD_LOW,
};
#endif
