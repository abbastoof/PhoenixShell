/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:33:05 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/20 15:40:43 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_key_with_equal(t_env **tmp)
{
	if ((*tmp)->value != NULL)
		free((*tmp)->value);
	(*tmp)->value = NULL;
	return (0);
}
