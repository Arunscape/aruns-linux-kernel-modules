#include <linux/init.h>
#include <linux/module.h>

static int __init my_init(void) {
  printk("hello, world! This is my (Arun's) first kernel module!\n");
  return 0;
}

static void __exit mu_exit(void) {
  printk("goodbye, world! (Arun's first kernel module is exiting...\n");
}

module_init(my_init);
module_exit(mu_exit);

MODULE_LICENSE("AGPL-3.0-only");
MODULE_AUTHOR("Arun Woosaree <no-reply@arun.gg>");
MODULE_DESCRIPTION("Arun's second kernel module");
