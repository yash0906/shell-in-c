#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/utsname.h>
#include<dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include<error.h>

#ifndef MISC_H
#define MISC_H
#define pf printf
struct jjoobb{
    char p_name[1000];
    pid_t pid;
    char status[20];
};
struct jjoobb bg_jobs[200];
int bgn;
char local_home[200];
char hist[200][200];
char qwer[3];
int hist_n;
pid_t shell_pid;
char current_path[200];
void handle_sigint(int sig);
void ls(char arr[200]);
void cd(char arr[200]);
void pwd();
void echo(char arr[200]);
void pinfo(char arr[200]);
void editor(char arr[200]);
void history(char arr[200]);
void nightswatch(char arr[200]);
void check(char arr[200]);	
void fg(char arr[200]);
void bg(char arr[200]);
void upkey(char arr[200]);
void piping(char arr[200]);
void set(char arr[200]);
void unset(char arr[200]);
void get(char arr[200]);
void mainloop(char input[200]);
void jobs();
void kjobs(char arr[200]);
int str_to_int(char arr[200]);
void bgup(char arr[200]);
void overkill();
void start();
void fgup(char arr[200]);
int original_out;
int original_in;
int curr_running;
int fd[2];
#endif