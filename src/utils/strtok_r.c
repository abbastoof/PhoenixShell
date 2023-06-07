/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:52:50 by atoof             #+#    #+#             */
/*   Updated: 2023/06/07 15:38:05 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	const char	*scanp;

	int c, sc;
	while ((c = *s1++) != 0)
	{
		scanp = s2;
		sc = *scanp;
		while (sc != 0)
		{
			if (sc == c)
				return ((char *)(s1 - 1));
			sc = *++scanp;
		}
	}
	return (NULL);
}

size_t	ft_strspn(const char *s1, const char *s2)
{
	const char	*p;
	const char	*spanp;
	int			found;

	p = s1;
	char c;
	char sc;
	while ((c = *p) != '\0')
	{
		spanp = s2;
		found = 0;
		while ((sc = *spanp++) != '\0')
		{
			if (sc == c)
			{
				found = 1;
				break ;
			}
		}
		if (!found)
			break ;
		p++;
	}
	return (p - s1);
}

char	*ft_strtok_r(char *s, const char *delim, char **save_ptr)
{
	char	*token;

	if (s == NULL)
		s = *save_ptr;
	/* Scan leading delimiters. */
	s += ft_strspn(s, delim);
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	/* Find the end of the token.  */
	token = s;
	s = ft_strpbrk(token, delim);
	if (s == NULL)
		/* This token finishes the string.  */
		*save_ptr = token + strlen(token);
	else
	{
		/* Terminate the token and make *SAVE_PTR point past it.  */
		*s = '\0';
		*save_ptr = s + 1;
	}
	return (token);
}


int main()
{
    char str[] = "Geeks for Geeks";
    char* token;
    char* rest = str;
 
    while ((token = strtok_r(rest, " ", &rest)))
        printf("%s\n", token);
 
    return (0);
}
