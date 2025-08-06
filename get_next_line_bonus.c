/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* get_next_line_bonus.c                              :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2024/10/01 21:11:16 by rmarrero          #+#    #+#             */
/* Updated: 2024/10/28 20:58:15 by rmarrero         ###   ########.fr       */
/* */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char    *get_next_line(int fd)
{
    static t_list   *list[4096];
    char            *line;

    if (BUFFER_SIZE < 0 || fd < 0)
        return (NULL);
    create_and_append(&list[fd], fd); // Usamos la función ya ajustada en el util
    line = malloc(get_len(list[fd]) + 1);
    if (!(list[fd]) || !(line))
        return (free(line), NULL);
    get_copy(list[fd], line);
    get_clear_remaining_data(&list[fd]);
    return (line);
}

// Reemplazamos la función get_free_list por ft_lstclear_bonus
// La lógica para liberar la lista completa ahora se maneja con una sola función.
/*
void    get_free_list(t_list **list, t_list *replace, char *buffer)
{
    t_list  *tmp;

    if (NULL == *list)
        return ;
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->data_buffer);
        free(*list);
        *list = tmp;
    }
    *list = NULL;
    if (replace->data_buffer[0])
        *list = replace;
    else
    {
        free(buffer);
        free(replace);
    }
}
*/

// La función para limpiar los datos restantes se simplifica.
// Ahora creamos un nuevo nodo con el resto de la cadena y limpiamos el resto de la lista.
void    get_clear_remaining_data(t_list **list)
{
    t_list  *last;
    t_list  *replace;
    char    *buffer;
    int     i;
    int     j;

    i = 0;
    j = 0;
    // Usamos ft_lstlast para obtener el último nodo, como en el `utils`.
    last = ft_lstlast_bonus(*list);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return;
    // Buscamos el final de la línea
    while (last->content[i] && last->content[i] != '\n')
        ++i;
    // Copiamos el resto de la cadena en el buffer
    while (last->content[i] && last->content[++i])
        buffer[j++] = last->content[i];
    buffer[j] = '\0';
    
    // Usamos ft_lstnew_bonus para crear un nuevo nodo con los datos restantes
    replace = ft_lstnew_bonus(buffer);
    if (!replace)
    {
        free(buffer);
        return;
    }
    
    // Liberamos toda la lista anterior con ft_lstclear_bonus
    // y luego le asignamos el nuevo nodo con los datos restantes.
    ft_lstclear_bonus(list, free);
    *list = replace;
}