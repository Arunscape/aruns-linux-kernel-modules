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

static int thread_function(void *thread_number) {
  unsigned int i = 0;
  int n = *(int *)thread_number;

  while (!kthread_should_stop()) {

    printk("Hello from thread %d\n; counter: %d", n, i++);
    msleep(n * 1000);
  }
  printk("kthread %d finished execution\n", n);
  return 0;
}

static int __init my_init(void) {
  printk(
      "hello, world! This is my (Arun's) first kernel module with kthreads!\n");

  // just 2 different ways to start threads
  kthread_1 = kthread_create(thread_function, &t1, "kthread 1");
  if (kthread_1 != NULL) {
    wake_up_process(kthread_1);
    printk("kthread 1 was created and is runnning\n");
  } else {
    printk("failed to create kthread1\n");
    return -1;
  }

  kthread_2 = kthread_run(thread_function, &t2, "kthread 2");
  if (kthread_2 != NULL) {
    printk("kthread 2 was created and is runnning\n");
  } else {
    printk("failed to create kthread2\n");
    kthread_stop(kthread_1);
    return -1;
  }

  return 0;
}

static void __exit mu_exit(void) {
  printk("goodbye, world!");

  kthread_stop(kthread_1);
  kthread_stop(kthread_2);
}

module_init(my_init);
module_exit(mu_exit);

// https://www.youtube.com/watch?v=YfVQt3CD8hk&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa&index=14A
