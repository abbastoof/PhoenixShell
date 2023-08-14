/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:31:20 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/15 03:31:40 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **args)
{
	int	index;

	index = 0;
	if (args[index] != NULL)
	{
		while (args[index])
		{
			free(args[index]);
			index++;
		}
		free(args);
	}
	args = NULL;
}
