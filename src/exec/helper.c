/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:50:02 by atoof             #+#    #+#             */
/*   Updated: 2023/08/02 17:22:47 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_last(t_redir *redir)
{
	t_redir	*last_input;
	t_redir	*last_outfile;

	last_input = NULL;
	last_outfile = NULL;
	while (redir != NULL)
	{
		if (redir->type == TOKEN_HEREDOC || redir->type == TOKEN_INPUT)
			last_input = redir;
		if (redir->type == TOKEN_OUTPUT || redir->type == TOKEN_OUTPUT_APPEND)
			last_outfile = redir;
		redir = redir->next;
	}
	if (last_input != NULL)
		last_input->last = 1;
	if (last_outfile != NULL)
		last_outfile->last = 1;
}
