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

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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
		ft_memcpy(tab++, 0, temp->content, 1);
		temp = temp->next;
	}
	return (oritab);
}

static int	scanbuffer(char *buffer, t_list **tab, char **leftover)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		ft_lstadd_back(tab, ft_lstnew(buffer[i++]));
	if (buffer[i] == '\n')
	{
		ft_lstadd_back(tab, ft_lstnew(buffer[i++]));
		if (buffer[i])
		{
			*leftover = (char *)malloc((ft_strlen(&buffer[i]) + 1) * sizeof(char));
			ft_bzero(*leftover, ft_strlen(&buffer[i]) + 1);
			ft_memcpy(*leftover, &buffer[i], 0, ft_strlen(&buffer[i]));
		}
		return (0);
	}
	if (!buffer[i])
		ft_bzero(buffer, BUFFER_SIZE + 1);
	return (1);
}

static void	loadleftover(char *buffer, char **leftover)
{
	ft_memcpy(buffer, *leftover, 0, ft_strlen(*leftover));
	free(*leftover);
	*leftover = NULL;
}

char	*get_next_line(int fd)
{
	static char	*leftover[OPEN_MAX];
	char		*buffer;
	char		*result;
	t_list		*tab;

	tab = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, &buffer, 0) < 0))
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!ft_bzero(buffer, BUFFER_SIZE + 1))
		return (NULL);
	if (leftover[fd])
		loadleftover(buffer, &leftover[fd]);
	if (!leftover[fd] && scanbuffer(buffer, &tab, &leftover[fd]))
	{
		while (read(fd, buffer, BUFFER_SIZE) > 0)
		{
			if (!scanbuffer(buffer, &tab, &leftover[fd]))
				break ;
		}
	}
	result = ft_combinestring(tab);
	ft_lstclear(&tab);
	free(buffer);
	return (result);
}
