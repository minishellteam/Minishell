/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:03:10 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/08 16:10:54 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void add_line_to_history(const char* line, char** history, int* history_size, int max_history_size)
{
	int	i;

	i = 0;
	if (*history_size >= max_history_size) 
	{
		free(history[0]);
		while(++i < max_history_size) 
		history[i - 1] = history[i];
		--(*history_size);
    }
	history[*history_size] = strdup(line);
	++(*history_size);
}

