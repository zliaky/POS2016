#include <list.h>
#include <sync.h>
#include <proc.h>
#include <sched.h>
#include <assert.h>

void
wakeup_proc(struct proc_struct *proc) {
    assert(proc->state != PROC_ZOMBIE && proc->state != PROC_RUNNABLE);
    proc->state = PROC_RUNNABLE;
}

void
print_state(void) {
	cprintf("state: ");
//        cprintf("state: %d ", current->state);
	switch (current->state) {
		case PROC_UNINIT:
			cprintf("PROC_UNINIT ");
			break;
		case PROC_SLEEPING:
			cprintf("PROC_SLEEPING ");
			break;
		case PROC_RUNNABLE:
			cprintf("PROC_RUNNABLE ");
			break;
		case PROC_ZOMBIE:
			cprintf("PROC_ZOMBIE ");
			break;
		default:
			cprintf("UNKNOWN ");
	}
}

void
schedule(void) {
    print_state();
    bool intr_flag;
    list_entry_t *le, *last;
    struct proc_struct *next = NULL;
    local_intr_save(intr_flag);
    {
        current->need_resched = 0;
        last = (current == idleproc) ? &proc_list : &(current->list_link);
        le = last;
        do {
            if ((le = list_next(le)) != &proc_list) {
                next = le2proc(le, list_link);
                if (next->state == PROC_RUNNABLE) {
                    break;
                }
            }
        } while (le != last);
        if (next == NULL || next->state != PROC_RUNNABLE) {
            next = idleproc;
        }
        next->runs ++;
        if (next != current) {
            proc_run(next);
        }
    }
    local_intr_restore(intr_flag);
    print_state();
}

