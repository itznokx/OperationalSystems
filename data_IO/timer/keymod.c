#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/slab.h>

//Compilar: make
//instalar: sudo insmod keymod.ko
//remover: sudo rmmod keymod 

struct vkeyboard {
    struct input_dev *inputdev;
    struct timer_list keyboardtimer;
};

struct vkeyboard *vkb;

// FunÃ§Ã£o de interrupÃ§Ã£o do timer
static void vkeyboard_interrupt(struct timer_list *t)
{
    struct vkeyboard *vkb = from_timer(vkb, t, keyboardtimer);

    // Emite uma tecla aleatÃ³ria a cada chamada do timer
    input_report_key(vkb->inputdev, KEY_A, 1);
    input_sync(vkb->inputdev);  // Sincroniza o evento de entrada

    // Reporta a tecla como liberada (solta)
    input_report_key(vkb->inputdev, KEY_A, 0);
    input_sync(vkb->inputdev);

    // Reconfigura o timer para ser reexecutado
    mod_timer(&vkb->keyboardtimer, jiffies + 1000);
}

// FunÃ§Ã£o de inicializaÃ§Ã£o do driver
static int __init vkeyboard_init(void)
{

    // Aloca memÃ³ria para o teclado virtual
    vkb = kzalloc(sizeof(struct vkeyboard), GFP_KERNEL);

    // Cria o dispositivo de entrada
    vkb->inputdev = input_allocate_device();

    // Configura o dispositivo de entrada
    vkb->inputdev->name = "Virtual A";
    vkb->inputdev->phys = "ps2/input0";
    vkb->inputdev->id.bustype = BUS_USB;
    vkb->inputdev->id.vendor = 0x1234;
    vkb->inputdev->id.product = 0x5678;

    // Defina as teclas que o teclado pode emular
    set_bit(EV_KEY, vkb->inputdev->evbit);  // Ativa os eventos de chave

    set_bit(KEY_A, vkb->inputdev->keybit);

    // Registra o dispositivo de entrada
    input_register_device(vkb->inputdev);

    // Inicializa o temporizador
    timer_setup(&vkb->keyboardtimer, vkeyboard_interrupt, 0);
    mod_timer(&vkb->keyboardtimer, jiffies + 1000); 


    return 0;
}

// FunÃ§Ã£o de limpeza do driver
static void __exit vkeyboard_exit(void)
{

    // Libera o temporizador
    del_timer_sync(&vkb->keyboardtimer);

    // Desregistra o dispositivo de entrada
    input_unregister_device(vkb->inputdev);
    kfree(vkb);

}

module_init(vkeyboard_init);
module_exit(vkeyboard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("S.O.");
MODULE_DESCRIPTION("Driver de teclado PS/2 virtual que emite a tecla A periodicamente.");
