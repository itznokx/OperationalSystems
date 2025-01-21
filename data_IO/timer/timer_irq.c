#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static irqreturn_t trata_interrupt(int irq, void *dev_id)
{
      printk(KERN_INFO "Tick de relÃ³gio!\n");
      
      return IRQ_HANDLED;
}

static int __init inicio(void)
{
      int ret = request_irq(0, trata_interrupt, IRQF_SHARED, "trata_interrupt", NULL);
      
      return ret;
}

static void __exit fim(void)
{
      free_irq(0, NULL);
}

module_init(inicio);
module_exit(fim);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO");
MODULE_DESCRIPTION("Exemplo IRQ timer");
