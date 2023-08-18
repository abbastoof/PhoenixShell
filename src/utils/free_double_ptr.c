/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:31:20 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/18 18:09:48 by atoof            ###   ########.fr       */
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
