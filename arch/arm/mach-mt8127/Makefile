# arch/arm/mach-mt8127/Makefile
# Licensed under GPLv2

obj-y				:=
obj-m				:=
obj-n				:=
obj-				:=

# Core

#ifeq ($(CONFIG_SMP),y)
#ccflags-y += -I$(srctree)
#obj-y += mt-smp.o hotplug.o mt-headsmp.o mt_hotplug.o mt_hotplug_mechanism.o
#endif

obj-y := core.o mt_dbg.o irq.o
obj-y += mt_devs.o board.o
#obj-y += mt_boot.o
obj-y += mt_dma.o
#obj-y += mt_reg_dump.o
#obj-y += mt_pm_init.o

#obj-$(CONFIG_ARCH_MT8127) += board-mt8127.o

#obj-$(CONFIG_S5P_PM)		+= pm.o
#obj-$(CONFIG_PM_GENERIC_DOMAINS) += pm_domains.o
#obj-$(CONFIG_CPU_IDLE)		+= cpuidle.o
#obj-$(CONFIG_HOTPLUG_CPU)	+= hotplug.o
