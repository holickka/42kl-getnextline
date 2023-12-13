/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:24:53 by hsim              #+#    #+#             */
/*   Updated: 2023/12/13 21:40:54 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_chrdup(char c)
{
	char	*dest;

	if (!c)
		return (NULL);
	dest = (char *)malloc(1 * sizeof(char));
	if (!dest)
		return (NULL);
	dest[0] = c;
	return (dest);
}

static char	*ft_combinestring(t_list *lst)
{
	t_list	*temp;
	char	*tab;
	char	*oritab;
	int		lstsize;

	if (!lst)
		return (NULL);
	temp = lst;
	lstsize = 0;
	while (temp)
	{
		lstsize++;
		temp = temp->next;
	}
	tab = (char *)malloc((lstsize + 1) * sizeof(char));
	ft_bzero(tab, lstsize + 1);
	oritab = tab;
	temp = lst;
	while (temp)
	{
		ft_memcpy(tab++, temp->content, 1);
		temp = temp->next;
	}
	return (oritab);
}

static int	scanbuffer(char *buffer, t_list **tab, char **leftover)
{
	int	i;
	int	wordcount;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		ft_lstadd_back(tab, ft_lstnew(ft_chrdup(buffer[i++])));
	if (buffer[i] == '\n')
	{
		ft_lstadd_back(tab, ft_lstnew(ft_chrdup(buffer[i++])));
		if (buffer[i])
		{
			wordcount = i;
			while (buffer[wordcount])
				wordcount++;
			wordcount -= i;
			*leftover = (char *)malloc((wordcount + 1) * sizeof(char));
			ft_bzero(*leftover, wordcount + 1);
			ft_memcpy(*leftover, &buffer[i], wordcount);
		}
		return (0);
	}
	if (!buffer[i])
		ft_bzero(buffer, BUFFER_SIZE + 1);
	return (1);
}

static void	loadleftover(char *buffer, char **leftover)
{
	int	wordcount;

	wordcount = 0;
	while ((*leftover)[wordcount])
		wordcount++;
	ft_memcpy(buffer, *leftover, wordcount);
	free(*leftover);
	*leftover = NULL;
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buffer;
	char		*result;
	t_list		*tab;

	tab = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!ft_bzero(buffer, BUFFER_SIZE + 1))
		return (NULL);
	if (leftover)
		loadleftover(buffer, &leftover);
	if (!leftover && scanbuffer(buffer, &tab, &leftover))
	{
		while (read(fd, buffer, BUFFER_SIZE) > 0)
		{
			if (!scanbuffer(buffer, &tab, &leftover))
				break ;
		}
	}
	result = ft_combinestring(tab);
	ft_lstclear(&tab);
	free(buffer);
	return (result);
}
