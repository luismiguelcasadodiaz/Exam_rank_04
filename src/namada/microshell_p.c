/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:10:03 by luicasad          #+#    #+#             */
/*   Updated: 2024/09/07 09:20:57 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

int	cd(char **av, int i)
{
	if (i != 2)
		return (err("error: cd: bad arguments\n"));
	if (chdir(av[1]) == -1)
		return (err("error: cd: cannot change directory to"),
			err(av[1]), err("\n"));
	return (0);
}

int	exec(char **av, int i, char **env)
{
	int	fd[2];
	int	status;
	int	has_pipe;
	int	pid;

	has_pipe = av[i] && !strcmp(av[i], "|");
	if (!has_pipe && !strcmp(*av, "cd"))
		return (cd (av, i));
	if (has_pipe && pipe(fd) == -1)
		return (err("error: fatal\n"));
	pid = fork();
	if (!pid)
	{
		av[i] = 0;
		if (has_pipe
			&& (dup2(fd[1], 1) == -1
				|| close(fd[1]) == -1 || close(fd[0] == -1)))
			return (err("error: fatal1\n"));
		if (!strcmp(*av, "cd"))
			return (cd(av, i));
		execve(*av, av, env);
		return (err("error: cannot execute "), err(*av), err("\n"));
	}
	waitpid(pid, &status, 0);
	if (has_pipe
		&& (dup2(fd[0], 0) == -1 || close(fd[0]) == -1
			|| close(fd[1]) == -1))
		return (err("error: fatal2\n"));
	return (WIFEXITED(status && WEXITSTATUS(status)));
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (ac > 1)
	{
		while (av[i] && av[++i])
		{
			av += i;
			i = 0;
			while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
				i++;
			if (i)
				status = exec(av, i, envp);
		}
	}
	return (status);
}
