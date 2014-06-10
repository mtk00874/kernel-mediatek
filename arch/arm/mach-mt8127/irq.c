
#include <linux/io.h>
#include <linux/module.h>
#include <linux/smp.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/irqchip.h>

#include <mach/mt_reg_base.h>
#include <mach/irqs.h>


#define INT_POL_CTL0 (MCUSYS_CFGREG_BASE + 0x100)


static int (*org_gic_set_type) (struct irq_data *data, unsigned int flow_type);
static spinlock_t irq_lock;

/*
 * mt_irq_set_polarity: set the interrupt polarity
 * @irq: interrupt id
 * @polarity: interrupt polarity
 */
static void mt_irq_set_polarity(unsigned int irq, unsigned int polarity)
{
	unsigned long flags;
	u32 offset, reg_index, value;

	if (irq < (NR_GIC_SGI + NR_GIC_PPI)) {
		pr_crit("Fail to set polarity of interrupt %d\n", irq);
		return;
	}

	offset = (irq - GIC_PRIVATE_SIGNALS) & 0x1F;
	reg_index = (irq - GIC_PRIVATE_SIGNALS) >> 5;

	spin_lock_irqsave(&irq_lock, flags);

	if (polarity == 0) {
		/* active low */
		value = readl((void *)(INT_POL_CTL0 + reg_index * 4));
		value |= (1 << offset);
		writel(value, (void*)(INT_POL_CTL0 + reg_index * 4));
	} else {
		/* active high */
		value = readl((void *)(INT_POL_CTL0 + reg_index * 4));
		value &= ~(0x1 << offset);
		writel(value, (void*)(INT_POL_CTL0 + reg_index * 4));
	}

	spin_unlock_irqrestore(&irq_lock, flags);
}

/*
 * mt_irq_polarity_set_type: set interrupt type wrapper for GIC
 * Check/set IRQ polarity for GIC interrupts
 */
static int mt_irq_polarity_set_type(struct irq_data *d, unsigned int type)
{
	unsigned int gicirq = d->hwirq;

	/* Set IRQ polarity */
	mt_irq_set_polarity(gicirq, (type == IRQ_TYPE_LEVEL_HIGH || 
				     type == IRQ_TYPE_EDGE_RISING) ? 1 : 0);

	/* Adjust type for GIC. */
	if (type == IRQ_TYPE_LEVEL_LOW)
		type = IRQ_TYPE_LEVEL_HIGH;
	else if (type == IRQ_TYPE_EDGE_FALLING)
		type = IRQ_TYPE_EDGE_RISING;

	return org_gic_set_type(d, type);
}

void __init mt_init_irq(void)
{
	struct irq_chip *gic_chip;

	irqchip_init();

	spin_lock_init(&irq_lock);
	gic_chip = irq_get_chip(MT_WDT_IRQ_ID);
	org_gic_set_type = gic_chip->irq_set_type;
	gic_chip->irq_set_type = mt_irq_polarity_set_type;
}
