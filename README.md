# Shell In C

#### An interactive user defined shell in c

### About The Shell:
An interactive user defined bash-like shell which supports semi-colon separated list of commands and any number of spaces 
between words.It can take commands in input check if a builtin exists if exists then run the builtin else run it as 
separate process(execvp). The shell also supports input and output redirection along with piping of commands.

### Running the program:
* make

* ./a.out

### Supported builtin commands:

command | description | flags_supported | arguements 
--- | --- | :---: | :---: 
ls| shows file and directories | -a,-l | 0 or 1
cd | changes current directory| - | 0 or 1
pwd | shows current directory | - | 0 
echo | print on terminal | - | 0 or more
pinfo | information of the given pid or shell | - | 0 or 1
history | shows commands history | - | 1
nightswatch | shows the number of times each cpu is interrupted or size of memory which is dirty | - | 3
quit | exit from shell | - | -
c | clear the screen | - | - 
setenv | used to set or change environment variable | - | 1 0r 2
nsetenv | used to unset environment variable | - | 1
getenv | get the value of environment | - | 1
cronjob | executes a particular command in fixed time interval for a certain period | - | 6
jobs | Shows all background process with status and index | - | -
kjob | Used to send kill signal to process listed in jobs | - | 2
overkill | kills all background process at once | - | -
bg | changes a stopped background job to a running background job | - | 1
fg | brings a running or a stopped background job with given job number to foreground | - | 1

### Fearutes

* Supports semi-colon separated commands
* Supports any number of space separated words
* Modular code structure
* Supports background process creation when command followed by '&'.
* Prints exit message when background exits
* Supports input and output file redirection
* Supports piping of commands
* Supports Ctrl + C signal.
* Unique builtins like pinfo, jobs, kjob, overkill ,quit,c(clear)


### Things to keep in mind:
* The directory from which the shell is invoked will be the home directory of the shell and should be indicated by "~"
* If you press up key n times then the nth command in the history will run.
* All the commands executed are stored in a file named history.
