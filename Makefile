CC=gcc
all:
	$(CC) -g shell.c ls.c cd.c pwd.c echo.c pinfo.c history.c watch.c bg.c fg.c check.c upkey.c pipe.c env.c jobs.c kjob.c
clean:
	re -f all