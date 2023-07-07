/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:40:38 by atoof             #+#    #+#             */
/*   Updated: 2023/07/07 13:54:04 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_command_arguments(t_tree *tree, char **argv)
{
	tree->cmd_arguments = ft_split(argv[2], ' ');
	if (is_absolute_path(tree->cmd_arguments[0]))
		tree->cmd = ft_strdup(tree->cmd_arguments[0]);
	else
		tree->cmd = get_cmd(tree->cmd_paths, tree->cmd_arguments[0]);
}
