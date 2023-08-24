/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:37:30 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/24 16:46:48 by mtoof            ###   ########.fr       */
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

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}					t_args;

typedef struct s_tree
{
	char			*tmp_file;
	int				type;
	char			*cmd;
	char			**args;
	t_args			*args_ptr;
	int				size_args;
	char			*paths;
	char			**cmd_paths;
	int				fd_in;
	int				fd_out;
	t_redir			*redir;
	struct s_tree	*left;
	struct s_tree	*right;
	int				standard_input;
	int				standard_output;
}					t_tree;

int					g_exit_status;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
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
	int				condition_result;
	char			*tmp;
	char			*res;
	char			*var;
	char			*path;
	char			*des;
}					t_lexer;

typedef struct s_exitlist
{
	int				size;
	int				index;
	pid_t			*pid;
}					t_exitlist;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// cmd_trim
t_token				*new_token(void);
int					redirectors(char *str, int i);
void				init_cmdsplit(t_cmdsplit *cmd);
int					ft_cmdtrim(char *str, t_token **tokens);
int					ft_token_add_back(t_token **tokens, t_token *new);

// lexer
int					syntax(t_token **tokens);
void				free_state(t_lexer *state);
void				free_tokens(t_token **tokens);
int					tokens_list_size(t_token **tokens);
void				process_cmd(char *line, t_env **env);
int					check_quotes_syntax(t_token **tokens);
void				checkquote(char *str, t_lexer *state);
void				checkdquote(char *str, t_lexer *state);
int					dollar_with_character(char *str, t_lexer *state);
int					check_consecutive_redirs(t_result res, t_token *tmp);
int					expansion(t_token **tokens, t_lexer *state, t_env **env);
int					split_quote(char *str, t_cmdsplit *cmd, t_token **tokens);
void				expand_quotes(t_token **tokens, t_env **env,
						t_lexer *state);
int					expand_var(t_token *token, t_lexer *state, t_env **env,
						int var_flag);
int					check_dollar_sign(char *str, t_lexer *state, t_env **env,
						int var_flag);
char				*var_finder(char *str, t_lexer *state, t_env **env,
						int var_flag);
int					join_char(char *str, t_lexer *state, t_env **env,
						int var_flag);
void				word_contain_quote_2(char *str, t_cmdsplit *cmd);

// built_in
int					pwd(void);
int					ft_env(t_env **env);
void				free_path(char *path);
int					ft_echo(t_tree *tree);
int					ft_cd(t_env **env, t_tree *tree);
int					empty_key_with_equal(t_env **tmp);
int					ft_unset(t_tree *tree, t_env **env);
int					ft_export(t_env **env, t_tree *tree);
int					find_key_in_env(t_env **env, char *key, char *value);
int					ft_exit(t_tree *tree, t_env **env, pid_t parent_flag);
int					free_env_assign_new_var(char **new_env, t_env **env,
						char *var);
int					need_add_back(t_env **env, char *var, char **split);

// tree
int					redir(int type);
t_tree				*new_tree_node(void);
void				free_tree(t_tree **tree);
t_args				*new_args_node(char *str);
int					add_args_list(t_tree *node);
void				free_double_ptr(char **args);
int					args_add_back(t_args **args, t_args *new);
int					add_back(t_redir **lst, t_redir *new_node);
void				free_args_list(t_args **args, t_tree *node);
int					add_args(t_token **tokens, t_tree *new_node);
int					create_tree(t_token **tokens, t_tree **tree);
int					parse_cmd_node(t_token **tokens, t_tree *node);
int					parse_redir(t_token **tokens, t_tree *new_node);
t_redir				*new_redir_node(t_token **tokens, int type, char *index);
// TODO: DELETE OR COMMENT_OUT DISPLAY FUNCTION

// helper
int					ft_isquote(int c);
int					ft_isspace(int c);
void				child_signal(void);
void				ctrl_d_handler(void);
void				free_env(t_env **env);
long long			ft_atoll(const char *str);
void				init_signals(int state);
void				echoing_control_chars(int enable);
char				*find_path(t_env **env, char *str);
char				**ft_realloc(char **ptr, size_t size);
void				init_tokens(t_token *tokens, int wd_count);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_chrjoin(char const *s1, char const s2);
void				rl_replace_line(const char *text, int clear_undo);
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);

// env_init
int					ft_listsize(t_env **env);
t_env				*new_env_node(char *line);
char				*shelvl_value(char *value);
void				init_env(t_env **env, char **envp);
int					add_back_env(t_env **env, t_env *new_node);
char				**env_char_ptr(t_env **env, char **env_ptr);
// exec
pid_t				child_process(void);
void				heredoc_signals(void);
void				exit_status_chk(int exit_sig);
void				check_for_last(t_redir *redir);
char				*get_cmd(char **paths, char *cmd);
int					contains_heredoc(t_redir *redir_list);
void				error_access_filename(char *file_name);
void				create_pipe(t_tree **tree, t_env **env);
void				replace_cmd_absolute_path(t_tree *tree);
void				run_cmd_token(t_tree *tree, t_env **env);
void				run_heredoc(t_redir *redir, t_tree *tree);
void				run_cmd_in_child(t_tree *tree, char **env);
void				open_input_file(t_redir *redir, t_tree *tree);
void				open_output_file(t_redir *redir, t_tree *tree);
void				exec_cmd(t_tree **tree, t_env **env, pid_t parent_flag);
int					built_in(t_tree **tree, t_env **env, pid_t parent_flag);
void				exec_tree(t_tree **tree, t_env **env, pid_t parent_flag);
int					exec_cmd_redir(t_redir *redir, t_tree **tree, t_env **env,
						pid_t parent_flag);
int					handle_only_heredoc_logic(t_redir *redir_list, \
						t_tree *cmd_node);
int					check_for_heredoc(t_tree **tree);

#endif
