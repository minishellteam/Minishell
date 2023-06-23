/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:43:25 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/23 09:00:45 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal, siginfo_t *sa, void *content)
{
	int i;

	(void)content;
	i = sa->si_pid;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		printf("pass\n");
}
