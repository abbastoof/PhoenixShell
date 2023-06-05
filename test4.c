/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:28:01 by atoof             #+#    #+#             */
/*   Updated: 2023/06/05 16:05:06 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TOKEN_CMD 1
#define TOKEN_ARG 2
#define TOKEN_PIPE 3
#define TOKEN_INPUT 4
#define TOKEN_OUTPUT 5
#define TOKEN_OUTPUT_APPEND 6
#define TOKEN_HEREDOC 7
#define TOKEN_VARIABLE 8
#define TOKEN_EXIT_STATUS 9
#define TOKEN_QUOTE 10
#define TOKEN_DQUOTE 11

typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct s_lexer
{
	int		indx;
	char	*crnt_str;
	char	*start;
	int		flag;
	int		i;
	int		inquote;
	int		indquote;
	int		token_indx;
	char	*tmp;
	char	*res;
	char	*var;
	char	*path;
	char	*des;
	t_token	*token;
}			t_lexer;

typedef struct s_cmdsplit
{
	char	**result;
	int		wd_count;
	int		index;
	int		start;
	char	quote;
}			t_cmdsplit;

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}

void	*ft_memcpy(void *to, const void *from, unsigned int size)
{
	unsigned int	i;
	char			*from_cpy;
	char			*to_cpy;

	from_cpy = (char *)from;
	to_cpy = (char *)to;
	i = 0;
	if (!to && !from)
		return ((void *)0);
	while (i < size)
	{
		to_cpy[i] = from_cpy[i];
		i++;
	}
	return (to_cpy);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = c;
	return (s);
}

void	ft_bzero(void *s, size_t len)
{
	ft_memset((void *)s, 0, len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	size_t	mult;

	mult = count * size;
	if (count > 0 && size > 0)
	{
		if (mult % count != 0 || mult % size != 0)
			return (NULL);
	}
	pointer = malloc(mult);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, mult);
	return (pointer);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_length;
	char			*sub;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (i < n && ss1[i] != '\0' && ss2[i] != '\0')
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i != n)
		return (ss1[i] - ss2[i]);
	return (0);
}

static int	redirectors(char *str, t_cmdsplit *cmd)
{
	if (ft_strncmp(str + cmd->index, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(str + cmd->index, "<", 1) == 0)
		return (TOKEN_INPUT);
	else if (ft_strncmp(str + cmd->index, ">", 1) == 0)
		return (TOKEN_OUTPUT);
	else if (ft_strncmp(str + cmd->index, ">>", 2) == 0)
		return (TOKEN_OUTPUT_APPEND);
	else if (ft_strncmp(str + cmd->index, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (str[0] == '$')
	{
		if (ft_strncmp(str + cmd->index, "$?", 2) == 0)
			return (TOKEN_EXIT_STATUS);
		else
			return (TOKEN_VARIABLE);
	}
	else
		return (0);
}

static int	words_count(char *str, t_cmdsplit *cmd)
{
	int	return_res = 0;
	while (str[cmd->index] != '\0')
	{
		if (ft_isquote(str[cmd->index]))
		{
			cmd->quote = str[cmd->index];
			cmd->start = cmd->index;
			cmd->index++;
			while (str[cmd->index] != '\0' && str[cmd->index] != cmd->quote)
				cmd->index++;
			cmd->wd_count++;
		}
		else if (redirectors(str, cmd) != 0)
		{
			cmd->start = cmd->index;
			return_res = redirectors(str, cmd);
			if (return_res == TOKEN_OUTPUT_APPEND || return_res == TOKEN_HEREDOC
				|| return_res == TOKEN_EXIT_STATUS)
				cmd->index += 2;
			else if (return_res == TOKEN_VARIABLE)
			{
				while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index]))
					cmd->index++;
			}
			else
				cmd->index++;
			cmd->wd_count++;
		}
		else if (str[cmd->index] != ' ')
		{
			cmd->start = cmd->index;
			while (str[cmd->index] != '\0')
			{
				if (ft_isspace(str[cmd->index])
					|| ft_isquote(str[cmd->index]) || redirectors((str
							+ cmd->index + 1), cmd))
					break ;
				cmd->index++;
			}
			cmd->wd_count++;
		}
		cmd->index++;
	}
	return (cmd->wd_count);
}

static void	init_cmdsplit(t_cmdsplit *cmd)
{
	cmd->index = 0;
	cmd->index = 0;
	cmd->quote = 0;
	cmd->result = NULL;
	cmd->wd_count = 0;
}

void	init_result(char *str, t_cmdsplit *cmd)
{
	int	return_res = 0;

	if (ft_isquote(str[cmd->index]))
	{
		cmd->quote = str[cmd->index];
		cmd->start = cmd->index;
		cmd->index++;
		while (str[cmd->index] != '\0' && str[cmd->index] != cmd->quote)
			cmd->index++;
		cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, (cmd->index
					- cmd->start) + 1);
		cmd->wd_count++;
	}
	else if (redirectors(str, cmd) != 0)
	{
		cmd->start = cmd->index;
		return_res = redirectors(str, cmd);
		if (return_res == TOKEN_OUTPUT_APPEND || return_res == TOKEN_HEREDOC
			|| return_res == TOKEN_EXIT_STATUS)
			cmd->index += 2;
		else if (return_res == TOKEN_VARIABLE)
		{
			while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index]))
				cmd->index++;
		}
		else
			cmd->index++;
		cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, (cmd->index
					- cmd->start) + 1);
		cmd->wd_count++;
	}
	else if (!ft_isspace(str[cmd->index]))
	{
		cmd->start = cmd->index;
		while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index])
			&& !ft_isquote(str[cmd->index]) && !redirectors((str
					+ cmd->index + 1), cmd))
			cmd->index++;
		cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, (cmd->index
					- cmd->start) + 1);
		cmd->wd_count++;
	}
}

char	**ft_cmdsplit(char *str)
{
	t_cmdsplit	cmd;

	init_cmdsplit(&cmd);
	cmd.wd_count = words_count(str, &cmd);
	printf("wd_count = %d\n", cmd.wd_count);
	cmd.result = ft_calloc((cmd.wd_count + 1), sizeof(char *));
	if (!cmd.result)
		return (NULL);
	cmd.wd_count = 0;
	cmd.index = 0;
	while (str[cmd.index] != '\0')
	{
		init_result(str, &cmd);
		cmd.index++;
	}
	return (cmd.result);
}

int	main(void)
{
	char	*input;
	char	**result;
	int		i;

	// Read input using readline
	printf("Enter a string: ");
	input = readline(NULL);
	if (!input)
	{
		printf("Error reading input.\n");
		return (1);
	}
	result = ft_cmdsplit(input);
	// Print the result
	printf("Result:\n");
	if (result)
	{
		i = -1;
		while (result[++i])
		{
			printf("%s\n", result[i]);
		}
		while (i--)
		{
			free(result[i]);
		}
		free(result);
		result = NULL;
	}
	else
	{
		printf("Splitting failed.\n");
	}
	free(input);
	return (0);
}
