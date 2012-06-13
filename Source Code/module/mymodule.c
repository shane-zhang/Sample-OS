#include <linux/module.h>
#include <linux/kernel.h>

static int hi(void)
{
     printk("The new created module has been loaded.\n");
     return 0;
}

static void bye(void)
{
     printk("The new created module has been removed.\n");
}

module_init(hi);
module_exit(bye);
