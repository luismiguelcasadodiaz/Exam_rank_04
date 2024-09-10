# Exam_rank_04

[subject]()

# 
According to the subject commands are separated by ";" or "|".

Microshell scan its arguments ``` (char **av) ```. 

If there are no two arguments ``` (*av && *(av + 1)) ``` returns zero, otherwise
skips the first one ``` av++; ``` and looks for ";" or "|" ```while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";")) i++; ```.

Once a separator found, there is something to execute.

If it is a change directory command ``` (!strcmp(*av, "cd")) ``` returns exit status of cd builtin execution.

if  (i == 0) means that *av was void so there is nothing to do. Otherwise returns exit status of executor execution.

Advances av pointer the number i of arguments till separator. ``` av += i ```.     

### cd built in

Only can execute cd <path>, so if ```(i != 2) ``` it is an error.

if the change directory execution is wrong ``` (chdir(av[1]) == -1)``` shows a message.

### executor

Gets a pointer to list of arguments ```av``` and the number of arguments till the separator ```i ```.

Checks  ``` (av[i] %% !strcmp(av[i], "|")) ``` if the separator exists and it is a pipe.

If it is a pipe,  creates the pipe ```((pipe(fd) == -1) ```,   printing a error if fails.

Forks the process.
Either child and father, when there is a pipe, duplicate standart input/output.

Child duplicates standart output ``` dup2(fd[1], 1) ```and closes both sides of pipe.

Child executes execve(). if every thing is ok, finish here. Child's return only happens when execve() was wrong.

Father waits child termination with ```waitpid(pid, &status, 0)``` .
Father duplicates standard input ``` dup2(fd[0], 0) ```and closes both sides of pipe.
father returns child execution status detected with ``` (WIFEXITED(status) && (WEXITSTATUS(status)) ```.

### error writer
Aside of writing in stderr (2), returns 1, reporting a error status.

## tests

