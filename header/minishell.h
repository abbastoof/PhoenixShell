/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:39:59 by atoof             #+#    #+#             */
/*   Updated: 2023/07/01 23:38:34 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/syslimits.h>
# include <termios.h>

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

extern char			**environ;

//cmd_trim
typedef struct s_cmdsplit
{
	int				wd_count;
	int				index;
	int				start;
	char			quote;
	int				res;
}					t_cmdsplit;

// typedef struct s_cmd
// {
// 	pid_t	pid;
// 	int		end[2];
// 	int		infile;
// 	int		outfile;
// 	char	*paths;
// 	char	**cmd_paths;
// 	char	**cmd_arguments;
// 	char	*cmd;
// 	char	**args;
// }			t_cmd;

typedef struct s_redir
{
	int				type;
	char			*file_name;
	struct s_redir	*next;
}					t_redir;

typedef struct s_tree
{
	int				type;
	char			*cmd;
	char			**args;
	t_redir			*redir;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_token
{
	int				type;
	char			*value;
}					t_token;

typedef struct s_result
{
	int				token_1;
	int				token_2;
}					t_result;

typedef struct s_lexer
{
	char			*start;
	int				indx;
	int				flag;
	int				i;
	int				inquote;
	int				indquote;
	int				token_indx;
	char			*tmp;
	char			*res;
	char			*var;
	char			*path;
	char			*des;
}					t_lexer;

typedef struct s_environment
{
	char			**env_var;
	int				counter;
}					t_env;

//cmd_trim
t_token				*ft_cmdtrim(char *str, t_token *tokens);
int					check_isquote(char *str, t_cmdsplit *cmd);
void				check_redirectors(char *str, t_cmdsplit *cmd);
void				init_cmdsplit(t_cmdsplit *cmd);
int					redirectors(char *str, int i);
int					words_count(char *str, t_cmdsplit *cmd);

//lexer
void				free_state(t_lexer *state);
void				free_tokens(t_token *tokens);
void				display_token(t_token *tokens);
void				process_cmd(char *line, t_env *env);
int					check_incorrect_quotes(t_token *tokens);
int					expand_var(t_token *token, t_lexer *state, t_env *env,
						int var_flag);
void				check_dollar_sign(char *str, t_lexer *state, t_env *env,
						int var_flag);
char				*var_finder(char *str, t_lexer *state, t_env *env,
						int var_flag);
void				expand_quotes(t_token *tokens, t_env *env, t_lexer *state);
// void				get_command_arguments(t_cmd *lst, t_token *cmd);
int					syntax(t_token *tokens);
// void				free_cmd_struct(t_cmd *cmd);

//built_in
void				pwd(void);
void				echo(char **args);
void				ft_cd(t_env *env, char *args);

// list
void				create_tree(t_token *tokens, t_tree **tree);
void				add_back(t_redir **lst, t_redir *new_node);
int					add_args(t_token **tokens, t_tree *new_node);
void				parse_cmd_node(t_token **tokens, t_tree *node);
void				display_list(t_tree *lst);
// void				free_list(t_lst *lst);
int					redir(int type);
t_redir				*redir_node(t_token **tokens, int type);
//TODO: DELETE OR COMMENT_OUT DISPLAY FUNCTION

//helper
int					ft_isquote(int c);
int					ft_isspace(int c);
void				commands(char *cmd);
void				free_env(t_env *env);
void				init_signals(void);
void				sigint_handler(int signum);
void				ctrl_d_handler(void);
void				disable_enable_ctl(int enable);
char				*find_path(char **envp, char *str);
char				**ft_realloc(char **ptr, size_t size);
void				init_tokens(t_token *tokens, int wd_count);
// void		initialize_minishell(t_minishell *line);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_chrjoin(char const *s1, char const s2);
void				handle_command(t_env *env, t_token *tokens);
void				rl_replace_line(const char *text, int clear_undo);
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);
void				initialize_environment(t_env *env, char **environ);

//pipe

// void				get_command_paths(t_cmd *lst, t_env *env);

#endif