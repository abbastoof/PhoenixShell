/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:47:38 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/09 12:15:02 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tokens(t_token *tokens, int wd_count)
{
	int	index;

	index = 0;
	while (index < wd_count)
	{
		tokens[index].type = 0;
		tokens[index].value = NULL;
		index++;
	}
}
