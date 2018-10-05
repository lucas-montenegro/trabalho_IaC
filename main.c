#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void cpu_usage(int pid) {
    char c1[10] = "ps -p";                     /* first piece of command */
    char c2[40] = "-o %cpu | grep -v %CPU";    /* final piece of command */
    char bash_cmd[256];                        /* receives the "complete" command after concatenation */
    sprintf(bash_cmd,"%s %d %s", c1, pid, c2); /* concatenates the string to include the pid */
    system(bash_cmd);                          /* performs the system call to evaluate cpu usage */
}

void mem_usage(int pid) {
    char m1[10] = "pmap";                               /* first piece of command */
    char m2[40] = "| grep -i total | awk '{print $2}'"; /* final piece of command */
    char bash_cmd2[256];                                /* receives the "complete" command after concatenation */
    sprintf(bash_cmd2,"%s %d %s", m1, pid, m2);         /* concatenates the string to include the pid */
    system(bash_cmd2);                                  /* performs the system call to evaluate memory usage */
}

int main (int argc, char *argv[], char *envp[]) {
    int pid = fork(); /* creates identical child process and returns its id */
    int i = 1; /* seconds counter */

    if ( pid < 0 ) { /* if fork was unsuccessful */
        perror ("Error: ") ;
        exit (-1) ;
    }
    else if( pid > 0 ) /* parent process instance */
    {
        while(i <= 10) {
            printf("CPU consumption (in %%):\n");
            cpu_usage(pid); /* returns child process's cpu usage in percentage */

            if(strcmp(argv[1], "ucp-mem") == 0) /* cpu and memory intensive */
            {
                printf("Memory consumption (in Kilobytes):\n");
                mem_usage(pid); /* returns child process's memory usage in KB */
            }
            printf("-----------------------------------\n");
            i++;
            sleep(1); /* puts parent process on hold for 1 second */
        }
        kill(pid, SIGKILL); /* kills child process */
    }
    else /* child process instance */
    {
        if(strcmp(argv[1], "ucp") == 0) { /* cpu intensive */
            for(;;) {}
        }
        else if(strcmp(argv[1], "ucp-mem") == 0) {  /* cpu and memory intensive */
            clock_t start_t, end_t, total_t;

            start_t = clock(); /* "cronometer's" start */
            for(;;)
            {
                end_t = clock(); /* "cronometer's" end in each iteration */
                total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC; /* total of seconds passed */

                if (total_t >= 0 && total_t <= 10)
                {
                    malloc(10 * sizeof(int));
                }
            }
        }
    }

    return 0;
}
