/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:39:50 by atoof             #+#    #+#             */
/*   Updated: 2023/06/13 18:42:04 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute_path(char *path)
{
	if (access(path, F_OK) == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	get_command_paths(t_cmd *lst, t_env *env)
{
	lst->paths = find_path(env->env_var, "PATH=");
	lst->cmd_paths = NULL;
	if (lst->paths != NULL && lst->paths[0] != '\0')
		lst->cmd_paths = ft_split(lst->paths, ':');
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

void	get_command_arguments(t_cmd *lst, t_token *cmd)
{
	if (is_absolute_path(cmd->value))
		lst->cmd = ft_strdup(cmd->value);
	else
		lst->cmd = get_cmd(lst->cmd_paths, cmd->value);
	if (lst->cmd != NULL)
		cmd->type = TOKEN_CMD;
}
