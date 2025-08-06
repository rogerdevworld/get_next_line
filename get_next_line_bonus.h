/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:05:39 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/08 18:28:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Ya no necesitamos esta estructura, ya que usaremos la de libft
/*
typedef struct s_list
{
    char            *data_buffer;
    struct s_list   *next;
}   t_list;
*/

// Prototipos de las funciones ajustadas
char    *get_next_line(int fd);
void    create_and_append(t_list **list, int fd);
int     get_len(t_list *list);
void    get_copy(t_list *list, char *line);
int     find_new_line(t_list *list);
void    get_clear_remaining_data(t_list **list);

#endif