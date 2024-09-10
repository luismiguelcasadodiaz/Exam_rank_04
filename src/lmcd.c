/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:56:30 by luicasad          #+#    #+#             */
/*   Updated: 2024/09/10 12:53:24 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	cd(char **av, int i)
{
	if (i != 2)
		return (err("error: cd: bad arguments\n"), 1);
	if (chdir(av[1]) == -1)
		return (err("error :cd: cannot change directory to "),
			err(av[1]), err("\n"), 1);
	return (0);
}

void set_pipe(int has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		err("error: fatal\n"), exit(1);
}

int	executor(char **av, char **env, int i)
{
	int	status;
	int	pid;
	int	fd[2];
	int	has_pipe;

	has_pipe = (av[i] && !strcmp(av[i], "|"));
	if (!has_pipe && !strcmp(*av, "cd"))
		return (cd(av, i));
	if (has_pipe && (pipe(fd) == -1))
		err("error: fatal\n"), exit(1);
	if ((pid = fork()) == -1)
		err("error: fatal\n"), exit(1);
	if (!pid)
	{
		set_pipe(has_pipe, fd, 1);
		av[i] = NULL;
		if (!strcmp(*av, "cd"))
			exit(cd(av,i));
		execve(*av, av, env);
		err("error : cannot execute "), err(av[0]), err("\n"), exit(1);
		//return (err("error : cannot execute "), err(av[0]), err("\n"));
	}
	waitpid(pid, &status, 0);
	set_pipe(has_pipe, fd, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}


int	main(int ac, char **av, char **env)
{
	int	status;
	int	i;

	(void)ac;
	status = 0;
	while (*av && *(av + 1))
	{
		av++;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
//		if (strcmp (*av, "cd") == 0)
//			status = cd(av, i);
//		else if (i)
		if (i)
			status = executor(av, env, i);
		av += i;
	}
	return (status);
}
