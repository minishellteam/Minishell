/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/02 22:17:00 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *message, int x)
{
	if (x == 1)
		perror(message);
	else if (x == 0)
		ft_putstr_fd(message, 2);
	free(message);
}

void	print_tab(char **tab)
{
	int	y;

	y = -1;
	while (tab[++y])
		printf("%s\n", tab[y]);
	printf("\n");
}

void	free_tab(char	**tab, int i)
{
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	init_data(t_vars *var)
{
	int	i;

	i = -1;
	while (++i < var->pipe_nb + 1)
		var->data[i] = NULL;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
