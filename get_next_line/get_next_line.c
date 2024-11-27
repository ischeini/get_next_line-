/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:30:56 by ischeini          #+#    #+#             */
/*   Updated: 2024/11/27 18:08:24 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_to_free(char *tof)
{
	free(tof);
	return (NULL);
}

static char	*ft_txt_rest(char *tmp)
{
	char	*text;
	char	*aux;

	aux = ft_strchr(tmp, '\n');
	if (!aux || !aux[1])
		return (ft_to_free(tmp));
	else
		text = ft_strdup(aux + 1);
	free(tmp);
	if (!text)
		return (NULL);
	return (text);
}

static char	*ft_find_line(char *txt)
{
	char	*rest_line;
	int		i;

	i = 0;
	while (txt[i] && txt[i] != '\n')
		i++;
	rest_line = ft_substr(txt, 0, i + 1);
	if (!rest_line)
		return (ft_to_free(txt));
	return (rest_line);
}

static char	*ft_read_txt(int fd, char *txt, char *tmp)
{
	char	*aux;
	int		b_read;

	b_read = 1;
	while (b_read > 0 || !ft_strchr(txt, '\n'))
	{
		b_read = read(fd, tmp, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(tmp);
			return (ft_to_free(txt));
		}
		else if (b_read == 0)
			break ;
		tmp[b_read] = 0;
		if (!txt)
			txt = ft_strdup("");
		aux = txt;
		txt = ft_strjoin(aux, tmp);
		free(aux);
	}
	free(tmp);
	return (txt);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_to_free(txt));
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (ft_to_free(txt));
	tmp = ft_read_txt(fd, txt, tmp);
	if (!tmp && txt)
		tmp = ft_strdup(txt);
	if (!tmp)
		return (ft_to_free(txt));
	line = ft_find_line(tmp);
	if (!line)
	{
		free(tmp);
		return (ft_to_free(txt));
	}
	txt = ft_txt_rest(tmp);
	return (line);
}
