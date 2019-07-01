#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/current.h>
#include <asm/page.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <asm/types.h>
#include <asm/processor.h>
// #include <unistd.h>

MODULE_LICENSE ("GPL");

int init (void)
{
    printk ("hello\n");
    struct task_struct* task_list;
    struct mm_struct* mm;
    void* cr3_virt;
    unsigned long cr3_phys;
    for_each_process(task_list)
    {
        if (strstr(task_list->comm, "chao_test"))
        {
            mm = task_list->mm;
            if (mm == NULL)
                return 0;
            cr3_virt = (void*) mm->pgd;
            cr3_phys = virt_to_phys(cr3_virt);
            printk ("commL: %s\n", task_list->comm);
            printk ("cr3_phys: %lx\n", cr3_phys);
        }
    }

    return 0;
}

void clean (void)
{
    printk (KERN_INFO "Goodbye\n");
}

module_init (init);
module_exit (clean);
