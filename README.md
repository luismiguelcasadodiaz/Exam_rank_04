# Exam_rank_04

[subject](https://github.com/luismiguelcasadodiaz/Exam_rank_04/blob/main/doc/exam_rank04-subject.c)

# 
According to the subject commands are separated by ";" or "|".

Microshell scans its arguments ``` (char **av) ```. 

If there are no two arguments ``` (*av && *(av + 1)) ``` returns zero, otherwise
skips the first one ``` av++; ``` and looks for ";" or "|" ```while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";")) i++; ```.

Once a separator is found, there is something to execute.

If it is a change directory command ``` (!strcmp(*av, "cd")) ``` returns the exit status of cd builtin execution.

if  (i == 0) means that *av was void. there is nothing to do. Otherwise, it returns the exit status of executor execution.

Advances av pointer the number i of arguments till separator. ``` av += i ```.     

### cd built in

Only cd <path> can be executed, so if ```(i != 2) ``` it is an error.

if the change directory execution is wrong ``` (chdir(av[1]) == -1)``` shows a message.

### executor

Gets a pointer to the arguments list ```av``` and the number of arguments till the separator ```i ```.

Checks  ``` (av[i] %% !strcmp(av[i], "|")) ``` if the separator exists and it is a pipe.

If it is a pipe,  create the pipe ```((pipe(fd) == -1) ```,   printing an error if fails.

Forks the process.
child and father, when there is a pipe, duplicate standard input/output.

Child duplicates standard output ``` dup2(fd[1], 1) ``` and closes both sides of pipe.

Child executes execve(). if everything is ok, finish here. The child's return only happens when execve() was wrong.

Father waits child termination with ```waitpid(pid, &status, 0)``` .
Father duplicates standard input ``` dup2(fd[0], 0) ``` and closes both sides of pipe.
father returns child execution status detected with ``` (WIFEXITED(status) && (WEXITSTATUS(status)) ```.

### error writer
Aside from writing in stderr (2), returns 1, reporting an error status.

## tests
Test it with ```bash make test```.
There is a Makefile in folder tests to launch two .sh scripts.
