/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:43:48 by atoof             #+#    #+#             */
/*   Updated: 2023/05/22 13:22:47 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	ft_strjoin_inplace(char *dest, const char *s1, const char *s2)
{
	while (*s1)
		*dest++ = *s1++;
	*dest++ = '=';
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
}

void	set_environment_variable(const char *name, const char *value)
{
	int		i;
	char	*new_value;
	char	**new_environ;

	i = 0;
	while (environ[i] && (ft_strncmp(environ[i], name, ft_strlen(name)) != 0
			|| environ[i][ft_strlen(name)] != '='))
		i++;
	new_value = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (new_value == NULL)
	{
		perror("minishell: malloc");
		exit(EXIT_FAILURE);
	}
	ft_strjoin_inplace(new_value, name, value);
	if (environ[i])
	{
		free(environ[i]);
		environ[i] = new_value;
	}
	else
	{
		new_environ = malloc((i + 2) * sizeof(char *));
		if (new_environ == NULL)
		{
			perror("minishell: malloc");
			exit(EXIT_FAILURE);
		}
		ft_memcpy(new_environ, environ, i * sizeof(char *));
		new_environ[i] = new_value;
		new_environ[i + 1] = NULL;
		free(environ);
		environ = new_environ;
	}
}

void	cd(t_environment *env, char *args)
{
	char	*path;
	char	cwd[1024];
	int		i;

	path = args;
	(void)env;
	if (path[0] == '$')
	{
		if ((path + 1) == NULL)
		{
			perror(path);
			return ;
		}
		path = path + 1;
	}
	else if (ft_strcmp((const char *)path, "-\0") == 0)
	{
		i = -1;
		while (ft_strnstr(env->env_var[++i], "OLDPWD", 1) == NULL)
			path = ft_strnstr(env->env_var[i], "OLDPWD", 1);
		printf("%s\n", path);
		if (path == NULL)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
		else
			printf("%s\n", path);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		return ;
	}
	if (chdir(path) < 0)
		perror("minishell: cd");
	else
	{
		set_environment_variable("OLDPWD", cwd);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("minishell: getcwd");
		else
			set_environment_variable("PWD", cwd);
	}
}