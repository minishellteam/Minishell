/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:43:25 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/16 15:01:46 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal, siginfo_t *sa, void *content)
{
	int i;
	char	*line;

	(void)content;
	i = sa->si_pid;
	if (signal == SIGINT)
	{
		line = readline("minishell$ ");
	}
	if (signal == SIGQUIT)
		printf("pass\n");
}
