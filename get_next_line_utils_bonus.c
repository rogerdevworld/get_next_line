/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: rmarrero <rmarrero@student.42barcelon>     +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2024/09/27 23:07:54 by rmarrero          #+#    #+#             */
/* Updated: 2024/10/12 23:10:36 by rmarrero         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "get_next_line.h"

// Reemplazamos la lógica manual por la de Libft.
// En lugar de una función, ahora se usarán las funciones de Libft directamente.
// Si necesitas encontrar el último nodo, usa ft_lstlast.

/*
t_list	*get_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
*/

int	get_len(t_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i]) // Usamos list->content en lugar de list->data_buffer
		{
			if (list->content[i] == '\n')
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
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i]) // Usamos list->content en lugar de list->data_buffer
		{
			if (list->content[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return ;
			}
			line[j++] = list->content[i++];
		}
		list = list->next;
	}
	line[j] = '\0';
}

int	find_new_line(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE) // Usamos list->content
		{
			if (list->content[i] == '\n')
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
		// Usamos la función ft_lstnew_bonus para crear un nuevo nodo
		// y ft_lstadd_back_bonus para agregarlo al final.
		// Esto simplifica enormemente la lógica de manejo de la lista.
		ft_lstadd_back_bonus(list, ft_lstnew_bonus(buffer));
	}
}

// Nota: No te olvides de incluir los archivos de cabecera de las listas de Libft.
// Por ejemplo:
// #include "libft_modules/ft_printf/ft_printf_bonus.h"