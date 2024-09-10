/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:30:09 by luicasad          #+#    #+#             */
/*   Updated: 2024/09/07 09:29:43 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int	er(char *s, char *av)
{
	while (*s)
		write(2, s++, 1);
	if (av)
	{
		write(2, " ", 1);
		while (*av)
			write(2, av++, 1);
	}
	write(2, "\n", 1);
	return (1);
}

int	cd(char **av, int i)
{
	if (i != 2)
		return (er("error: cd: bad arguments", NULL));
	if (chdir(av[1]) == -1)
		return (er("error: cd: cannot change directory to", av[1]));
	return (0);
}

int	exec(char **av, char **env, int i)
{
	int	status;
	int	fd[2];
	int	pipes;
	int	pid;

	pipes = (av[i] && !strcmp(av[i], "|"));
	if (pipes && pipe(fd) == -1)
		return (er("error: fatal", NULL));
	pid = fork();
	if (!pid)
	{
		av[i] = 0;
		if (pipes
			&& (dup2(fd[1], 1) == -1 || close(fd[1]) == -1
				|| close(fd[0]) == -1))
			return (er("error: fatal", NULL));
		execve(*av, av, env);
		return (er("error: cannot execute", *av));
	}
	waitpid(pid, &status, 0);
	if (pipes
		&& (dup2(fd[0], 0) == -1 || close(fd[0]) == -1
			|| close(fd[1]) == -1))
		return (er("error: fatal", NULL));
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int ac, char **av, char **envp)
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
		if (strcmp(*av, "cd") == 0)
			status = cd(av, i);
		else if (i)
			status = exec(av, envp, i);
		av += i;
	}
	return (status);
}
