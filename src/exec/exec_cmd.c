/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:21:36 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 16:29:30 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_absolute_path(char *path)
{
	if ((access(path, F_OK) == 0) && (access(path, X_OK) == 0))
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
		if (!temp)
			return (NULL);
		unix_cmd = ft_strjoin(temp, cmd);
		if (!unix_cmd)
			return (NULL);
		free(temp);
		if (access(unix_cmd, X_OK) == 0)
			return (unix_cmd);
		free(unix_cmd);
		paths++;
	}
	return (cmd);
}

int	built_in(t_tree **tree, t_env **env, pid_t parent_pid)
{
	if (!(ft_strcmp((*tree)->cmd, "exit")))
		g_tree.exit_status = ft_exit((*tree), env, parent_pid);
	else if (!(ft_strcmp((*tree)->cmd, "echo")))
		g_tree.exit_status = ft_echo((*tree)->args);
	else if (!(ft_strcmp((*tree)->cmd, "cd")))
		g_tree.exit_status = ft_cd(env, (*tree)->args);
	else if (!(ft_strcmp((*tree)->cmd, "env")))
		g_tree.exit_status = ft_env(env);
	else if (!(ft_strcmp((*tree)->cmd, "export")))
		g_tree.exit_status = ft_export(env, (*tree)->args);
	else if (!(ft_strcmp((*tree)->cmd, "pwd")))
		g_tree.exit_status = pwd();
	else if (!(ft_strcmp((*tree)->cmd, "unset")))
		g_tree.exit_status = ft_unset((*tree)->args, env);
	else
		return (0);
	return (1);
}

void	run_cmd_token(t_tree *tree, t_env **env)
{
	char	**env_to_char_ptr;

	init_signals(0);
	env_to_char_ptr = NULL;
	tree->paths = NULL;
	tree->paths = find_path(env, "PATH");
	if (tree->paths != NULL && tree->paths[0] != '\0')
		tree->cmd_paths = ft_split(tree->paths, ':');
	if (is_absolute_path(tree->cmd))
		tree->cmd = ft_strdup(tree->args[0]);
	else
		replace_cmd_absolute_path(tree);
	env_to_char_ptr = env_char_ptr(env, env_to_char_ptr);
	run_cmd_in_child(tree, env_to_char_ptr);
	if (env_to_char_ptr != NULL)
		free_double_ptr(env_to_char_ptr);
	wait(&(g_tree.exit_status));
	init_signals(1);
	g_tree.exit_status = g_tree.exit_status % 255;
	exit_status_chk();
}

void	exec_cmd(t_tree **tree, t_env **env, pid_t parent_pid)
{
	if ((*tree)->redir != NULL)
		exec_cmd_redir((*tree)->redir, &(*tree), env, parent_pid);
	else
	{
		if (built_in(&(*tree), env, parent_pid) == 0)
			run_cmd_token((*tree), env);
	}
}
