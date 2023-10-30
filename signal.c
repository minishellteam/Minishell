/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:43:25 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/30 14:59:30 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	basic_signal(int signal)
{
	if (signal == SIGINT)
	{
		set_exit_status(128 + 2);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	command_signal(int signal)
{
	if (signal == SIGINT)
	{
		set_exit_status(128 + 2);
		printf("\n");
	}
	if (signal == SIGQUIT)
	{
		set_exit_status(128 + 3);
		printf("Quit (core dumped)\n");
	}
	exit(*get_exit_status());
}

void	here_doc_signal(int signal)
{
	if (signal == SIGINT)
	{
		set_exit_status(128 + 2);
		printf("\n");
	}
}
