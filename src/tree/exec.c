/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/07/11 18:54:29 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  The last line of exec_tree is needed because we
	want our exit code to always remain between 0 and 255*/

/*  X_OK for execute/search permission),
	the existence test (F_OK)*/

static void	exit_status_chk(void)
{
	if (WIFEXITED(g_exit_status))
		return ;
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == 2)
		{
			ft_putchar('\n');
			g_exit_status += 128;
		}
		else if (WTERMSIG(g_exit_status) == 3)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			g_exit_status += 128;
		}
	}
}

void	error_access_filename(char *file_name)
{
	if (access(file_name, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
		exit(1);
	}
	else if ((access(file_name, W_OK) != 0) || access(file_name, R_OK) != 0
		|| access(file_name, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_status = 1;
		exit(1);
	}
}

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
		if (access(unix_cmd, X_OK) == 0)
			return (unix_cmd);
		free(unix_cmd);
		paths++;
	}
	return (NULL);
}

static void	run_cmd_token(t_tree *tree, t_env *env)
{
	tree->cmd_paths = NULL;
	tree->paths = find_path(env->env_var, "PATH=");
	if (tree->paths != NULL && tree->paths[0] != '\0')
		tree->cmd_paths = ft_split(tree->paths, ':');
	free(tree->cmd);
	if (is_absolute_path(tree->args[0]))
		tree->cmd = ft_strdup(tree->args[0]);
	else
		tree->cmd = get_cmd(tree->cmd_paths, tree->args[0]);
	if (child_proc_defsig() == 0)
	{
		if (execve(tree->cmd, tree->args, env->env_var) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tree->cmd, 2);
			ft_putstr_fd("command not found\n", 2);
			exit(127);
		}
	}
	wait(&(g_exit_status));
	g_exit_status = g_exit_status % 255;
	exit_status_chk();
	if (tree->cmd)
		free(tree->cmd);
}

static void	exec_cmd(t_tree *tree, t_env *env)
{
	if (tree->redir != NULL)
	{
		if (exec_redir(tree->redir, tree, env))
			run_cmd_token(tree, env);
		else
			return ;
	}
	else
		run_cmd_token(tree, env);
}

// static void	exec_heredoc(t_tree *tree)
// {
// 	int	fd;

// }

t_tree	*next_redirect(t_tree *tree, t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == TOKEN_OUTPUT)
			fd = open(redir->file_name,
					O_CREAT | O_TRUNC | O_WRONLY,
					0644);
		else if (redir->type == TOKEN_OUTPUT_APPEND)
			fd = open(redir->file_name,
					O_CREAT | O_APPEND | O_WRONLY,
					0644);
		else if (redir->type == TOKEN_INPUT)
		{
			fd = open(redir->file_name, O_RDONLY);
			if (fd == -1)
				error_access_filename(redir->file_name);
		}
		close (fd);
		redir = redir->next;
	}
	return (tree);
}

int	exec_redir(t_redir *redir, t_tree *tree, t_env *env)
{
	int	fd;

	fd = 0;
	if (child_proc_defsig() == 0)
	{
		if (redir->type == TOKEN_OUTPUT)
		{
			fd = open(redir->file_name, O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				error_access_filename(redir->file_name);
			dup2(fd, STDOUT_FILENO);
		}
		else if (redir->type == TOKEN_INPUT)
		{
			fd = open(redir->file_name, O_RDONLY);
			if (fd == -1)
				error_access_filename(redir->file_name);
			dup2(fd, STDIN_FILENO);
		}
		else if (redir->type == TOKEN_OUTPUT_APPEND)
		{
			fd = open(redir->file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd == -1)
				error_access_filename(redir->file_name);
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		if (redir->next != NULL)
			next_redirect(tree, redir->next);
		exec_tree(tree, env);
		exit(0);
	}
	wait(&(g_exit_status));
	return (1);
}

int	chk_blt(t_tree *tree, t_env *env)
{
	if (!(ft_strcmp(tree->cmd, "exit")))
		ft_exit(tree);
	else if (!(ft_strcmp(tree->cmd, "echo")))
		echo(tree->args);
	// else if (!(ft_strcmp(tree->cmd, "cd")))
	// 	ft_cd(env->env_var, tree->cmd);
	else if (!(ft_strcmp(tree->cmd, "env")))
		ft_env(env);
	else if (!(ft_strcmp(tree->cmd, "export")))
		ft_export(env, tree->args);
	else if (!(ft_strcmp(tree->cmd, "pwd")))
		pwd();
	// else if (!(ft_strcmp(tree->cmd, "unset")))
	// 	ft_unset();
	else
		return (0);
	return (1);
}

void	exec_tree(t_tree *tree, t_env *env)
{
	if (tree != NULL)
	{
		if (tree->type == TOKEN_PIPE)
			create_pipe(tree, env);
		else if (tree->type >= TOKEN_INPUT
			&& tree->type <= TOKEN_OUTPUT_APPEND)
			exec_redir(tree->redir, tree, env);
		else if (tree->type == TOKEN_CMD)
		{
			if (chk_blt(tree, env) == 0)
				exec_cmd(tree, env);
		}
		// else if (tree->type == TOKEN_HEREDOC)
		// 	exec_heredoc(tree);
		g_exit_status = g_exit_status % 255;
	}
}
