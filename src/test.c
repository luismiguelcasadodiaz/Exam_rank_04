/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:33:07 by luicasad          #+#    #+#             */
/*   Updated: 2024/09/10 09:00:42 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int	err(char *s)
{
	while (*s)
		write(2, s++, 1);
	return (1);
}

int	cd(char **av, int i)
{
	if (i != 2)
		return (err("error: cd: bad argument\n"));
	if (chdir(*av) == -1)
		return (err("error: cd: cannot change directory to"),
			err(*av), err("\n"));
	return (0);
}

int	executor(char **av, int i, char **env)
{
	int	status;
	int	pid;
	int	fd[2];
	int	has_pipe;

	has_pipe = (av[i] && !strcmp(av[i], "|"));
	if (has_pipe && (pipe(fd) == -1))
		return (err("error: fatal1\n"));
	pid = fork ();
	if (!pid)
	{
		if (has_pipe && ((dup2(fd[1], 1) == -1) || (close(fd[1]) == -1)
				|| (close(fd[0]) == -1)))
			return (err("error: fatal2\n"));
		av[i] = NULL;
		execve(*av, av, env);
		return (err("error: cannot execute" ), err(*av), err("\n"));
	}
	waitpid(pid, &status, 0);
	if (has_pipe && ((dup2(fd[0], 0) == -1) || (close(fd[1]) == -1)
			|| (close(fd[0]) == -1)))
		return (err("error: fatal2\n"));
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	int	status;
	int	i;

	(void)ac;
	status = 0;
	while (*av && *(av +1))
	{
		av++;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (!strcmp(*av, "cd"))
			status = cd(av, i);
		else if (i)
			status = executor(av, i, env);
		av += i;
	}
	return (status);
}
