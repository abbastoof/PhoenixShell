/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:33:05 by mtoof             #+#    #+#             */
/*   Updated: 2023/11/02 20:28:48 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phoenix.h"

int	empty_key_with_equal(t_env **tmp)
{
	if ((*tmp)->value != NULL)
		free((*tmp)->value);
	(*tmp)->value = NULL;
	return (0);
}

int	need_add_back(t_env **env, char *var, char **split)
{
	if (add_back_env(env, new_env_node(var)) == -1)
	{
		if (split != NULL)
			free_double_ptr(split);
		return (-1);
	}
	if (split != NULL)
		free_double_ptr(split);
	return (0);
}
