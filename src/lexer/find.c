/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:39:50 by atoof             #+#    #+#             */
/*   Updated: 2023/06/20 20:06:04 by mtoof            ###   ########.fr       */
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

void	get_command_arguments(t_cmd *s_cmd, t_token *token)
{
	if (is_absolute_path(token->value))
		s_cmd->cmd = ft_strdup(token->value);
	else
		s_cmd->cmd = get_cmd(s_cmd->cmd_paths, token->value);
	if (s_cmd->cmd != NULL)
	{
		free(s_cmd->cmd);
		s_cmd->cmd = NULL;
		token->type = TOKEN_CMD;
	}
}
