// Write a C program such that it initializes itself as a Daemon Process.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>

void create_daemon() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);
    if (setsid() < 0) exit(EXIT_FAILURE);

    umask(0);
    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_WRONLY);
}

int main() {
    printf("Starting daemon...\n"); 

    create_daemon(); 

    openlog("daemon_ex", LOG_PID, LOG_DAEMON);

    FILE *fp = fopen("/tmp/daemon_log.txt", "a");
    fprintf(fp, "Daemon is running...\n");
    fclose(fp);

    while (1) {
        syslog(LOG_NOTICE, "Daemon is still running...");
        sleep(20);
    }

    closelog();
    return EXIT_SUCCESS;
}
