/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:07:54 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/08 12:06:41 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

int	get_len(t_list *list)
{
	int		i;
	int		len;
	char	*str_content;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		str_content = (char *)list->content;
		while (str_content[i])
		{
			if (str_content[i] == '\n')
				return (++len);
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	get_copy(t_list *list, char *line)
{
	int		i;
	int		j;
	char	*str_content;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		str_content = (char *)list->content;
		while (str_content[i])
		{
			if (str_content[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return ;
			}
			line[j++] = str_content[i++];
		}
		list = list->next;
	}
	line[j] = '\0';
}

int	find_new_line(t_list *list)
{
	int		i;
	char	*str_content;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		str_content = (char *)list->content;
		while (str_content[i] && i < BUFFER_SIZE)
		{
			if (str_content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	create_and_append(t_list **list, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!find_new_line(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		ft_lstadd_back(list, ft_lstnew(buffer));
	}
}
