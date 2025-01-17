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
}