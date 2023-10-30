/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:43:25 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/26 17:23:21 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	basic_sigint(int signal)
{
	(void)signal;
	set_exit_status(130);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	basic_sigquit(int signal)
{
	printf("pass\n");
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}
