/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:45:52 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/22 16:46:10 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_consecutive_redirs(t_result res, t_token *tmp)
{
	if (res.token_1 == TOKEN_EXIT_STATUS && tmp->next != NULL)
		return (1);
	if ((res.token_1 != 0) && tmp->next == NULL)
		return (2);
	if (res.token_1 == TOKEN_PIPE && (res.token_2 >= 4 \
			&& res.token_2 <= 7 && tmp->next->next != NULL))
		return (3);
	if (res.token_1 == TOKEN_PIPE && res.token_2 == TOKEN_PIPE)
		return (4);
	if (res.token_1 != 0 && res.token_2 != 0 \
		&& res.token_2 != TOKEN_EXIT_STATUS && tmp->next->next == NULL)
		return (5);
	if (res.token_1 >= 4 && res.token_1 <= 7 && res.token_2 >= 4 \
			&& res.token_2 <= 7)
		return (6);
	return (0);
}
