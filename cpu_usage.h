
#ifndef READ_CPU_CPU_USAGE_H
#define READ_CPU_CPU_USAGE_H

#include <linux/limits.h>

typedef long long int num;

struct {
    num uptime;

    num pid;
    char tcomm[PATH_MAX];
    char state;

    num ppid;
    num pgid;
    num sid;
    num tty_nr;
    num tty_pgrp;

    num flags;
    num min_flt;
    num cmin_flt;
    num maj_flt;
    num cmaj_flt;
    num utime;
    num stimev;

    num cutime;
    num cstime;
    num priority;
    num nicev;
    num num_threads;
    num it_real_value;

    unsigned long long start_time;

    num vsize;
    num rss;
    num rsslim;
    num start_code;
    num end_code;
    num start_stack;
    num esp;
    num eip;

    num pending;
    num blocked;
    num sigign;
    num sigcatch;
    num wchan;
    num zero1;
    num zero2;
    num exit_signal;
    num cpu;
    num rt_priority;
    num policy;
};

#endif //READ_CPU_CPU_USAGE_H
