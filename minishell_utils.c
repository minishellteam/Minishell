/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/14 12:20:08 by ykifadji         ###   ########.fr       */
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

void	free_tab(char	**tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}
