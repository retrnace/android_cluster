#ifndef __KRG_NAMESPACE_H__
#define __KRG_NAMESPACE_H__

#include <linux/nsproxy.h>
#include <linux/rcupdate.h>
#include <asm/atomic.h>

struct task_struct;

struct krg_namespace {
	atomic_t count;
	struct nsproxy root_nsproxy;
	struct user_namespace *root_user_ns;
	struct task_struct *root_task;
	struct rcu_head rcu;
};

int copy_krg_ns(struct task_struct *task, struct nsproxy *new);
void free_krg_ns(struct krg_namespace *ns);

struct krg_namespace *find_get_krg_ns(void);

static inline void get_krg_ns(struct krg_namespace *ns)
{
	atomic_inc(&ns->count);
}

static inline void put_krg_ns(struct krg_namespace *ns)
{
	if (atomic_dec_and_test(&ns->count))
		free_krg_ns(ns);
}

bool can_create_krg_ns(unsigned long flags);

void krg_ns_root_exit(struct task_struct *task);

#endif /* __KRG_NAMESPACE_H__ */
