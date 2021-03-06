/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:40 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:24:08 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char		*get_value(t_shell *sh, int *i)
{
	char	*tmp;
	char	*value;
	int		j;

	j = 0;
	*i += 1;
	while (sh->line[*i + j] && ft_isalnum(sh->line[*i + j]))
		++j;
	tmp = ft_strndup(&sh->line[*i], j);
	value = ft_getenv(tmp, sh->env);
	if (value)
	{
		while (*value != '=')
			++value;
		++value;
	}
	*i += j;
	free(tmp);
	return (value);
}

void			ft_replace_dollar(t_shell *sh, int i)
{
	char	*str1;
	char	*value;
	char	*str2;

	str1 = ft_strndup(sh->line, i);
	value = get_value(sh, &i);
	str2 = ft_strdup(&sh->line[i]);
	free(sh->line);
	sh->line = ft_replace_line(str1, value, str2);
	free(str1);
	free(str2);
}
