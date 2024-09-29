/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/29 21:59:22 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void	create_pipes(t_cmd *cmd, t_data *minishell)
{
	int		i;
	int		pipes;
	t_cmd	*current;

	i = 0;
	pipes = 0;
	current = cmd;
	while (current)
	{
		i++;
		current = current->sub_cmd;
	}
	minishell->pipe_argv = (int **)calloc(sizeof(int *) * i, 1);
	if (minishell->pipe_argv == NULL)
		panic("malloc");
	while (pipes < i)
	{
		minishell->pipe_argv[i] = (int *)calloc(2 * sizeof(int), 1);
		if (minishell->pipe_argv[i] == NULL)
			panic("malloc");
		if (pipe(minishell->pipe_argv[i]) == -1)
			panic("pipe");
		pipes++;
	}
}

int	execute(t_data *minishell)
{
	t_cmd	*cmd;
	pid_t	last_pid;

	if (minishell->pipe_cmd)
	{
		cmd = minishell->pipe_cmd;
		runcmd(cmd, minishell);
	}
	else if (minishell->redir_cmd)
	{
		cmd = minishell->redir_cmd;
		runcmd(cmd, minishell);
		cmd = minishell->exec_cmd;
		runcmd(cmd, minishell);
	}
	else if (minishell->exec_cmd)
	{
		cmd = minishell->exec_cmd;
		if (is_builtin(cmd))
			return (run_builtin_cmd(minishell->commands[0]->argv, minishell));
		else
		{
			last_pid = fork1();
			if (last_pid == 0)
				runcmd(minishell->commands[0], minishell);
		}
		wait_for_processes(minishell, last_pid);
	}
	else
	{
		perror("No command to execute");
		return (EXIT_FAILURE);
	}
	return (0);
}
