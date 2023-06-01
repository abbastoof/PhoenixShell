/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:39:59 by atoof             #+#    #+#             */
/*   Updated: 2023/06/01 15:47:30 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/syslimits.h>

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

extern char	**environ;

typedef struct s_lst
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
}			t_lst;

typedef struct s_token
{
	int		type;
	char	*value;
	t_lst	*lst;
}			t_token;

typedef struct s_lexer
{
	int		indx;
	char	*crnt_str;
	char	*start;
	int		flag;
	char	*path;
	int		i;
	int		inquote;
	int		indquote;
	int		token_indx;
	char	*tmp;
	char	*res;
	char	*var;
	t_token	*token;
}			t_lexer;

typedef struct s_environment
{
	char	**env_var;
	int		counter;
}			t_environment;

void		pwd(void);
void		echo(char **args);
void		commands(char *cmd);
int			ft_isquote(int c);
int			ft_isspace(int c);
void		sigint_handler(int signum);
void		free_env(t_environment *env);
char		*find_path(char **envp, char *str);
char		**ft_realloc(char **ptr, size_t size);
void		ft_cd(t_environment *env, char *args);
// void		initialize_minishell(t_minishell *line);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_chrjoin(char const *s1, char const s2);
void		process_cmd(char *line, t_environment *env);
void		handle_command(t_environment *env, const char *cmd);
char		*ft_strnjoin(char const *s1, char const *s2, size_t n);
int			is_word(char *str, t_lexer *state, t_environment *env,
				int var_flag);
void		dollar_handler(char *str, t_lexer *state, t_environment *env,
				int var_flag);
char		*var_finder(char *str, t_lexer *state, t_environment *env,
				int var_flag);
void		initialize_environment(t_environment *env, char **environ);

#endif