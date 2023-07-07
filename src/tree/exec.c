/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/07/07 16:47:40 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The last line of exec_tree is needed because we want our exit code to always remain between 0 and 255.

static int	is_absolute_path(char *path)
{
	if (access(path, F_OK) == 0)
		return (TRUE);
	else
		return (FALSE);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*temp;
	char	*unix_cmd;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		unix_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(unix_cmd, 0) == 0)
			return (unix_cmd);
		free(unix_cmd);
		paths++;
	}
	return (NULL);
}

static void	exec_cmd(t_tree *tree)
{
	t_env	*env;

	tree->cmd_paths = NULL;
	tree->paths = find_path(env->env_var, "PATH=");
	if (tree->paths != NULL && tree->paths[0] != '\0')
		tree->cmd_paths = ft_split(tree->paths, ':');
	free(tree->cmd);
	tree->cmd = get_cmd(tree->cmd_paths, tree->args[0]);
	if (child_proc_defsig() == 0)
	{
		if (execve(tree->cmd, tree->args, NULL) == -1)
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd(tree->cmd, 2);
			ft_putstr_fd("command not found\n", 2);
			exit(127);
		}
	}
	wait(&(g_exit_status));
	g_exit_status = g_exit_status % 255;
	exit_status_checking(g_exit_status);
	if (tree->cmd)
		free(tree->cmd);
}

static void	exec_heredoc(t_tree *tree)
{
	
}

static void	exec_redir(t_tree *tree)
{
	int	fd;

	fd = 0;
	if (child_proc_defsig() == 0)
	{
		if (tree->type == TOKEN_OUTPUT)
		{
			fd = open(tree->redir->file_name, O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				error_handling(tree->redir->file_name);//TODO
			dup2(fd, STDOUT_FILENO);
		}
		else if (tree->type == TOKEN_INPUT)
		{
			fd = open(tree->redir->file_name, O_RDONLY);
			if (fd == -1)
				error_handling(tree->redir->file_name);//TODO
			dup2(fd, STDIN_FILENO);
		}
		else if (tree->type == TOKEN_OUTPUT_APPEND)
		{
			fd = open(tree->redir->file_name, O_CREAT | O_APPEND | O_WRONLY,
					0644);
			if (fd == -1)
				error_handling(tree->redir->file_name);//TODO
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		exec_tree(select_next(tree->right));
		exit(0);
	}
	wait(&(g_exit_status));
}

void	exec_tree(t_tree *tree)
{
	if (tree)
	{
		if (tree->type == TOKEN_PIPE)
			create_pipe(tree);
		else if (tree >= TOKEN_INPUT && tree->type <= TOKEN_OUTPUT_APPEND)
			exec_redir(tree);
		else if (tree->type == TOKEN_CMD)
			exec_cmd(tree);
		else if (tree->type == TOKEN_HEREDOC)
			exec_heredoc(tree);
		g_exit_status = g_exit_status % 255;
	}
}
