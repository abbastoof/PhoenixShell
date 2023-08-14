/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:39:59 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 20:57:41 by atoof            ###   ########.fr       */
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
# define TOKEN_BLTIN 12

# define TRUE 1
# define FALSE 0
# define FD_WRITE_END 1
# define FD_READ_END 0

typedef struct s_cmdsplit
{
	int				wd_count;
	int				index;
	int				start;
	char			quote;
	int				res;
}					t_cmdsplit;

typedef struct s_redir
{
	int				type;
	char			*file_name;
	char			*key;
	int				last;
	struct s_redir	*next;
}					t_redir;

typedef struct s_tree
{
	char			*tmp_file;
	int				type;
	char			*cmd;
	char			*paths;
	char			**cmd_paths;
	char			**args;
	int				fd_in;
	int				fd_out;
	t_redir			*redir;
	struct s_tree	*left;
	struct s_tree	*right;
	int				exit_status;
	int				standard_input;
	int				standard_output;
}					t_tree;

t_tree				g_tree;

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

typedef struct s_env
{
	char			**env_var;
	char			*key;
	char			*value;
	int				counter;
	struct s_env	*next;
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
void				process_cmd(char *line, t_env **env);
int					check_quotes_syntax(t_token *tokens);
int					expand_var(t_token *token, t_lexer *state, t_env **env,
						int var_flag);
int					check_dollar_sign(char *str, t_lexer *state, t_env **env,
						int var_flag);
char				*var_finder(char *str, t_lexer *state, t_env **env,
						int var_flag);
void				expand_quotes(t_token *tokens, t_env **env, t_lexer *state);
// void				get_command_arguments(t_cmd *lst, t_token *cmd);
int					syntax(t_token *tokens);
// int					check_for_heredoc(t_tree **tree);

//built_in
int					pwd(void);
int					ft_echo(char **args);
int					ft_env(t_env **env);
int					ft_exit(t_tree *tree, t_env **env, pid_t parent_pid);
int					ft_cd(t_env **env, char **args);
int					empty_key_with_equal(t_env **tmp);
int					ft_unset(char **args, t_env **env);
int					ft_export(t_env **env, char **args);
int					find_key_in_env(t_env **env, char *key, char *value);
int					free_env_assign_new_var(char **new_env, t_env **env,
						char *var);

// tree
int					redir(int type);
t_tree				*new_tree_node(void);
void				free_tree(t_tree **tree);
void				display_list(t_tree **tree);
void				free_double_ptr(char **args);
t_redir				*new_redir_node(t_token **tokens, int type, char *index);
int					add_back(t_redir **lst, t_redir *new_node);
int					add_args(t_token **tokens, t_tree *new_node);
int					create_tree(t_token **tokens, t_tree **tree);
int					parse_cmd_node(t_token **tokens, t_tree *node);
int					parse_redir(t_token **tokens, t_tree *new_node);
//TODO: DELETE OR COMMENT_OUT DISPLAY FUNCTION

//helper
int					ft_isquote(int c);
int					ft_isspace(int c);
void				ctrl_d_handler(void);
void				free_env(t_env **env);
void				init_signals(int state);
int					ft_atol(const char *str);
void				echoing_control_chars(int enable);
char				*find_path(t_env **env, char *str);
char				**ft_realloc(char **ptr, size_t size);
void				init_tokens(t_token *tokens, int wd_count);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_chrjoin(char const *s1, char const s2);
void				rl_replace_line(const char *text, int clear_undo);
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);

//env_init
t_env				*new_env_node(char *line);
char				*shelvl_value(char *value);
void				init_env(t_env **env, char **envp);
int					add_back_env(t_env **env, t_env *new_node);
int					ft_listsize(t_env **env);
char				**env_char_ptr(t_env **env, char **env_ptr);
//exec
pid_t				child_process(void);
void				exit_status_chk(void);
void				heredoc_signals(void);
void				check_for_last(t_redir *redir);
char				*get_cmd(char **paths, char *cmd);
void				error_access_filename(char *file_name);
void				create_pipe(t_tree **tree, t_env **env);
void				replace_cmd_absolute_path(t_tree *tree);
void				run_cmd_token(t_tree *tree, t_env **env);
void				run_heredoc(t_redir *redir, t_tree *tree);
void				run_cmd_in_child(t_tree *tree, char **env);
void				open_input_file(t_redir *redir, t_tree *tree);
void				open_output_file(t_redir *redir, t_tree *tree);
void				exec_cmd(t_tree **tree, t_env **env, pid_t parent_pid);
int					built_in(t_tree **tree, t_env **env, pid_t parent_pid);
void				exec_tree(t_tree **tree, t_env **env, pid_t parent_pid);
int					contains_heredoc(t_redir *redir_list);
int					exec_cmd_redir(t_redir *redir, t_tree **tree, t_env **env, \
					pid_t parent_pid);
int					handle_only_heredoc_logic(t_redir *redir_list, \
					t_tree *cmd_node);
int					check_for_heredoc(t_tree **tree);

#endif