#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static struct timer_list meu_timer;

void trata_timer_interrupt(struct timer_list *t)
{
   printk(KERN_INFO "Temporizador expirado!\n");
   
   mod_timer(&meu_timer, jiffies + 100);
}

static int __init inicio_modulo(void)
{
    timer_setup(&meu_timer, trata_timer_interrupt, 0);
    
    mod_timer(&meu_timer, jiffies + 100);
    
    return 0;
}

static void __exit saida_modulo(void)
{
    del_timer(&meu_timer);
}

module_init(inicio_modulo);
module_exit(saida_modulo);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO");
MODULE_DESCRIPTION("Exemplo timer");
