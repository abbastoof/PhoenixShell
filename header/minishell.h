/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:39:59 by atoof             #+#    #+#             */
/*   Updated: 2023/05/22 17:12:34 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/syslimits.h>

# define TRUE 1
# define FALSE 0

extern char	**environ;

typedef struct s_minishell
{
	pid_t	pid;
	int		end[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_arguments;
	char	*cmd;
	char	**args;
}			t_minishell;

typedef struct s_environment
{
	char	**env_var;
	int		counter;
}			t_environment;

int			ft_strcmp(const char *s1, const char *s2);
void		ft_free_strarray(char **str_array);
char		**ft_realloc(char **ptr, size_t size);
void		commands(char *cmd);
// void		initialize_minishell(t_minishell *line);
void		handle_command(t_environment *env, const char *cmd);
void		free_env(t_environment *env);
char		*find_path(char **envp, char *str, char *replace, int flag);
void		cd(t_environment *env, char *args);
void		set_environment_variable(const char *name, const char *value,
				char **env);
void		pwd(char **env);
void		ft_strjoin_inplace(char *dest, const char *s1, const char *s2);

# define TOKEN_CMD 1
# define TOKEN_ARG 2
# define TOKEN_PIPE 3
# define TOKEN_INPUT 4
# define TOKEN_OUTPUT 5
# define TOKEN_OUTPUT_APPEND 6
# define TOKEN_HEREDOC 7
# define TOKEN_VARIABLE 8
# define TOKEN_EXIT_STATUS 9
# define TOKEN_QUOTE 10
# define TOKEN_DQUOTE 11

# define TRUE 1
# define FALSE 0

#endif