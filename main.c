
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <linux/limits.h>
#include <sys/times.h>



typedef long long int num;

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

num total_time;
long hertz;
double cpu_usage;
num seconds;

long tickspersec;

FILE *stat_input;
FILE *uptime_input;


void readone2(num *x) { fscanf(uptime_input, "%lld ", x); };

void readone(num *x) { fscanf(stat_input, "%lld ", x); }
void readunsigned(unsigned long long *x) { fscanf(stat_input, "%llu ", x); }
void readstr(char *x) {  fscanf(stat_input, "%s ", x);}
void readchar(char *x) {  fscanf(stat_input, "%c ", x);}

void printone(char *name, num x) {  printf("%20s: %lld\n", name, x);}
void printonex(char *name, num x) {  printf("%20s: %016llx\n", name, x);}
void printunsigned(char *name, unsigned long long x) {  printf("%20s: %llu\n", name, x);}
void printchar(char *name, char x) {  printf("%20s: %c\n", name, x);}
void printstr(char *name, char *x) {  printf("%20s: %s\n", name, x);}
void printtime(char *name, num x) {  printf("%20s: %f\n", name, (((double)x) / tickspersec));}

int gettimesinceboot() {
    FILE *procuptime;
    int sec, ssec;

    procuptime = fopen("/proc/uptime", "r");
    fscanf(procuptime, "%d.%ds", &sec, &ssec);
    fclose(procuptime);
    return (sec*tickspersec)+ssec;
}

void printtimediff(char *name, num x) {
    int sinceboot = gettimesinceboot();
    int running = sinceboot - x;
    time_t rt = time(NULL) - (running / tickspersec);
    char buf[1024];

    strftime(buf, sizeof(buf), "%m.%d %H:%M", localtime(&rt));
    printf("%20s: %s (%u.%us)\n", name, buf, running / tickspersec, running % tickspersec);
}

int main(int argc, char *argv[]) {
    tickspersec = sysconf(_SC_CLK_TCK);
    stat_input = NULL;

    if(argc > 1) {

        uptime_input = fopen("/proc/uptime", "r");

        chdir("/proc");
        if(chdir(argv[1]) == 0) { stat_input = fopen("stat", "r"); }
        if(!stat_input) {
            perror("open");
            return 1;
        }
    } else {
        stat_input = stdin;
    }

    readone2(&uptime);

    printf("%u\n", uptime);



    readone(&pid);
    readstr(tcomm);
    readchar(&state);
    readone(&ppid);
    readone(&pgid);
    readone(&sid);
    readone(&tty_nr);
    readone(&tty_pgrp);
    readone(&flags);
    readone(&min_flt);
    readone(&cmin_flt);
    readone(&maj_flt);
    readone(&cmaj_flt);
    readone(&utime);
    readone(&stimev);
    readone(&cutime);
    readone(&cstime);
    readone(&priority);
    readone(&nicev);
    readone(&num_threads);
    readone(&it_real_value);
    readunsigned(&start_time);
    readone(&vsize);
    readone(&rss);
    readone(&rsslim);
    readone(&start_code);
    readone(&end_code);
    readone(&start_stack);
    readone(&esp);
    readone(&eip);
    readone(&pending);
    readone(&blocked);
    readone(&sigign);
    readone(&sigcatch);
    readone(&wchan);
    readone(&zero1);
    readone(&zero2);
    readone(&exit_signal);
    readone(&cpu);
    readone(&rt_priority);
    readone(&policy);

    total_time = utime + stimev;

    printf("utime: %u\n", utime);
    printf("stimev: %u\n", stimev);
    printf("total time 1: %u\n", total_time);

    total_time = total_time + cutime + cstime;

    printf("total time 2: %u\n", total_time);

    hertz = sysconf(_SC_CLK_TCK);

    seconds = uptime - (start_time / hertz);
    printf("seconds: %u\n", seconds);

    printf("hertz: %u\n", hertz);


    printf("val 1: %u\n", (total_time / hertz));

    cpu_usage = 100.0 * ((total_time / hertz) / (double)seconds );


    printf("cpu usage: %f\n", cpu_usage);


    return 0;
}
