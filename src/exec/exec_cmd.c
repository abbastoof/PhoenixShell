/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:21:36 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 18:15:03 by mtoof            ###   ########.fr       */
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

	while (*paths && cmd != NULL)
	{
		temp = ft_strjoin(*paths, "/");
		if (!temp)
		{
			ft_putstr_fd("Malloc get_cmd\n", 2);
			return (NULL);
		}
		unix_cmd = ft_strjoin(temp, cmd);
		if (!unix_cmd)
		{
			ft_putstr_fd("Malloc get_cmd\n", 2);
			return (NULL);
		}
		free(temp);
		temp = NULL;
		if (access(unix_cmd, X_OK) == 0)
			return (unix_cmd);
		free(unix_cmd);
		paths++;
	}
	return (cmd);
}

int	built_in(t_tree **tree, t_env **env, pid_t parent_flag)
{
	int	exit_sig;

	if (!(ft_strcmp((*tree)->cmd, "exit")))
		exit_sig = ft_exit((*tree), env, parent_flag);
	else if (!(ft_strcmp((*tree)->cmd, "echo")))
		exit_sig = ft_echo(*tree);
	else if (!(ft_strcmp((*tree)->cmd, "cd")))
		exit_sig = ft_cd(env, *tree);
	else if (!(ft_strcmp((*tree)->cmd, "env")))
		exit_sig = ft_env(env);
	else if (!(ft_strcmp((*tree)->cmd, "export")))
		exit_sig = ft_export(env, *tree);
	else if (!(ft_strcmp((*tree)->cmd, "pwd")))
		exit_sig = pwd();
	else if (!(ft_strcmp((*tree)->cmd, "unset")))
		exit_sig = ft_unset(*tree, env);
	else
		return (0);
	exit_status_chk(exit_sig);
	return (1);
}

void	run_cmd_token(t_tree *tree, t_env **env)
{
	char	**env_to_char_ptr;
	int		exit_sig;

	env_to_char_ptr = NULL;
	tree->paths = NULL;
	tree->paths = find_path(env, "PATH");
	if (tree->paths != NULL && tree->paths[0] != '\0')
		tree->cmd_paths = ft_split(tree->paths, ':');
	if (is_absolute_path(tree->cmd))
		;
	else
	{
		if (tree->paths != NULL)
			replace_cmd_absolute_path(tree);
	}
	env_to_char_ptr = env_char_ptr(env, env_to_char_ptr);
	run_cmd_in_child(tree, env_to_char_ptr);
	if (env_to_char_ptr != NULL)
		free_double_ptr(env_to_char_ptr);
	wait(&(exit_sig));
	exit_status_chk(exit_sig);
}

void	exec_cmd(t_tree **tree, t_env **env, pid_t parent_flag)
{
	if ((*tree)->redir != NULL)
		exec_cmd_redir((*tree)->redir, &(*tree), env, parent_flag);
	else
	{
		if (built_in(&(*tree), env, parent_flag) == 0)
			run_cmd_token((*tree), env);
	}
}
