#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				counter;
	struct s_env	*next;
}					t_env;

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}

// substr

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t				i;
	unsigned int		s_length;
	char				*sub;

	if (!s)
		return (NULL);
	s_length = strlen(s);
	if (start >= s_length)
		len = 0;
	if (strlen(s + start) < len)
		len = strlen(s + start);
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

// ft_strjoin

int	count_str(char const *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static int	ft_words_len(const char *s, char c, int index)
{
	int	len;

	len = 0;
	while (s[index] != c && s[index])
	{
		index++;
		len++;
	}
	return (len);
}

static void	free_memory(char **str, int index)
{
	while (index--)
		free(str[index]);
	free(str);
}

static char	**make_words(char **str, char const *s, char c, int w_count)
{
	int	index;
	int	counter;
	int	w_length;

	counter = 0;
	index = 0;
	while (counter < w_count)
	{
		while (s[index] == c && s[index])
			index++;
		w_length = ft_words_len(s, c, index);
		str[counter] = ft_substr(s, index, w_length);
		if (!str[counter])
		{
			free_memory(str, counter);
			return (NULL);
		}
		counter++;
		index += w_length;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**str;

	if (!s)
		return (NULL);
	count = count_str(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	str = make_words(str, s, c, count);
	str[count] = 0;
	return (str);
}

// env_init

static void	*error_handling(void)
{
	ft_putstr_fd("Malloc\n", 2);
	return (NULL);
}

t_env	*new_node(char *line)
{
	char	**split;
	t_env	*node;

	node = malloc(sizeof(t_env) * 1);
	if (!node)
		return (error_handling());
	split = ft_split(line, '=');
	if (!split)
		return (error_handling());
	node->key = split[0];
	node->value = split[1];
	node->next = NULL;
	return (node);
}

int	add_back(t_env **lst, t_env *new_node)
{
	t_env	*last;

	last = *lst;
	if (!new_node)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new_node;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return (0);
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

static void	free_node(t_env *node, t_env *prev)
{
	prev->next = node->next;
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	node->key = NULL;
	node->value = NULL;
}

void	free_line(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env)
		return ;
	tmp = *env;
	prev = *env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, key, strlen(key)) == 0)
		{
			free_node(tmp, prev);
			break ;
		}
		prev = tmp;
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
}

void	init_env(t_env **env, char **envp)
{
	t_env	*node;
	int		index;


	index = 0;
	// env = malloc(sizeof(t_env));
	while (envp[index] != NULL)
	{
		node = new_node(envp[index]);
		if (!node)
		{
			error_handling();
			exit(1);
		}
		if (add_back(env, node) == -1)
			exit(1);
		if (envp[index] != NULL)
			index++;
	}
}

void	printf_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp != NULL)
	{
		printf("%s = %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		index = 0;

	(void)ac;
	(void)av;
	env = NULL;
	init_env(&env, envp);
	free_line(&env, "PWD");
	free_line(&env, "OLDPWD");
	free_line(&env, "_");
	printf_env(env);
	return (0);
}
