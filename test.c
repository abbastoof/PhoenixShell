#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

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

#define MAX_TOKENS 100

typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct s_lexerstate
{
	char	*current_character;
	char	*start_position;
	int		token_index;
	int		within_single_quote;
	int		within_double_quote;
	t_token	*tokens;
}			t_lexerstate;

void	assign_token_type(char *str, t_token *token, t_lexerstate *state)
{
	if (strcmp(str, "|") == 0)
	{
		token[state->token_index].type = TOKEN_PIPE;
		state->token_index++;
	}
	else if (strcmp(str, "<") == 0)
	{
		token[state->token_index].type = TOKEN_INPUT;
		state->token_index++;
	}
	else if (strcmp(str, ">") == 0)
	{
		token[state->token_index].type = TOKEN_OUTPUT;
		state->token_index++;
	}
	else if (strcmp(str, ">>") == 0)
	{
		token[state->token_index].type = TOKEN_OUTPUT_APPEND;
		state->token_index++;
	}
	else if (strcmp(str, "<<") == 0)
	{
		token[state->token_index].type = TOKEN_HEREDOC;
		state->token_index++;
	}
	else if (str[0] == '$')
	{
		if (strcmp(str, "$?") == 0)
		{
			token[state->token_index].type = TOKEN_EXIT_STATUS;
			state->token_index++;
		}
		else
		{
			token[state->token_index].type = TOKEN_VARIABLE;
			state->token_index++;
		}
	}
	else
	{
		token[state->token_index].type = (token->type == TOKEN_CMD) ? TOKEN_ARG : token->type;
		token->value = strdup(str);
		state->token_index++;
	}
}

void	assign_new_token(t_lexerstate *state, int token_type)
{
	t_token	*token;

	token = &(state->tokens[state->token_index]);
	token->type = token_type;
	token->value = strdup(state->start_position + 1);
	state->token_index++;
}

void	handle_quote(t_lexerstate *state, int token_type)
{
	int	*within_quote;

	if (token_type == TOKEN_QUOTE)
		within_quote = &(state->within_single_quote);
	else
		within_quote = &(state->within_double_quote);
	if (*within_quote == 0)
	{
		*within_quote = 1;
		state->start_position = state->current_character;
	}
	else
	{
		*within_quote = 0;
		*(state->current_character) = '\0';
		assign_new_token(state, token_type);
	}
}

t_token	*tokenize_command(char *command_line)
{
	t_lexerstate	state;

	state.current_character = command_line;
	state.start_position = command_line;
	state.token_index = 0;
	state.within_single_quote = 0;
	state.within_double_quote = 0;
	state.tokens = (t_token *)malloc(MAX_TOKENS * sizeof(t_token));
	while (*(state.current_character))
	{
		if (*(state.current_character) == '\'' && !state.within_double_quote)
		{
			handle_quote(&state, TOKEN_QUOTE);
		}
		else if (*(state.current_character) == '\"'
				&& !state.within_single_quote)
		{
			handle_quote(&state, TOKEN_DQUOTE);
		}
		else if (!state.within_single_quote && !state.within_double_quote
				&& *(state.current_character) == ' ')
		{
			*(state.current_character) = '\0';
			assign_token_type(state.start_position,
					&(state.tokens[state.token_index]), &state);
			state.start_position = state.current_character + 1;
		}
		state.current_character++;
	}
	assign_token_type(state.start_position, &(state.tokens[state.token_index]), &state);
		// Handle last argument
	return (state.tokens);
}

void	process_command(char *cmd)
{
	t_token	*tokens;
	int		i;

	tokens = tokenize_command(cmd);
	i = 0;
	printf("Tokens:\n");
	while (tokens[i].value != NULL)
	{
		printf("Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
		i++;
	}
	// Free tokens
	i = 0;
	while (i < MAX_TOKENS && tokens[i].value != NULL)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

int	main(void)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("Minishell> ");
		add_history(cmd);
		if (!cmd || strcmp(cmd, "exit") == 0)
		{
			if (cmd)
				free(cmd);
			break ;
		}
		process_command(cmd);
		free(cmd);
	}
	return (0);
}
