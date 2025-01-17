#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/slab.h>

struct vkeyboard 
{
	struct input_dev* inputdev;
	struct timer_list keyboardtimer;
};

static void tratainterrupt (struct timer_list* t)
{
	struct vkeyboard* vkb = from_timer(vkb, t, keyboardtimer);

	input_report_key (vkb->inputdev,KEY_A,1);
	input_sync(vkb->inputdev);

	input_report_key(vkb->inputdev,KEY_A,0);
	input_sync(vkb->inputdev);

	mod_timer (&vkb->keyboardtimer,jiffies+1000);
}

static int __init vkeyboard_init (void)
{
	static vkeyboard* vkb;

	vkb = kzalloc(sizeof(struct vkeyboard),GFP_KERNEL);

	vkb->inputdev = input_allocate_device();
	vkb->inputdev->name = "Teclado relógio";
	vkb->inputdev->phys = "ps2/input0";
	vkb->inputdev->id.bustype = BUS_USB;
	vkb->inputdev->id.vendor = 0x1234;
	vkb->inputdev->id.product = 0x5670;

	set_bit(EV_KEY,vkb->inputdev->evbit);
	set_bit(KEY_A,vkb->inputdev->keybit);

	input_register_device(vkb->inputdev);

	timer_setup(&vkb->keyboardtimer,tratainterrupt, 0);
	mod_timer(&vkb->keyboardtimer, jiffies+ 1000);

	return 0;
}

static void __exit vkeyboar_exit(void)
{
	static vkeyboard* vkb;

	del_timer_sync(&vkb->keyboardtimer);

	input_unregister_device(vkb->inputdev);

	kfree(vkb);
}
module_init (vkeyboard_init);
module_exit (vkeyboar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO");
MODULE_DESCRIPTION("VIRTUAL KEYBOARD");