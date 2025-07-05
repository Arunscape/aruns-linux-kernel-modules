#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("AGPL-3.0-only");
MODULE_AUTHOR("Arun Woosaree <no-reply@arun.gg>");
MODULE_DESCRIPTION("threads example for a kernel module");

static struct task_struct *kthread_1;
static struct task_struct *kthread_2;
static int t1 = 1;
static int t2 = 2;

int thread_function(void *thread_number) {
  unsigned int i = 0;
  int n = *(int *)thread_number;

  while (!kthread_should_stop()) {

    printk("Hello from thread %d\n; counter: %d", n, i++);
    msleep(n * 1000);
  }
  printk("kthread %d finished execution\n");
}

static int __init my_init(void) {
  printk("hello, world! This is my (Arun's) first kernel module!\n");
  return 0;
}

static void __exit mu_exit(void) {
  printk("goodbye, world! (Arun's first kernel module is exiting...\n");
}

module_init(my_init);
module_exit(mu_exit);

// https://www.youtube.com/watch?v=YfVQt3CD8hk&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa&index=14A
