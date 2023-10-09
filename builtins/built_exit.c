/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:27 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/09 14:43:16 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	free_exit(void)
// {
// 	//if (sh->export->env || sh->export->exp)
// 	//	free_tab();
// 	exit(*get_exit_status());
// }

long long	ft_atol(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

static int	check_long(t_data *sh)
{
	int	i;
	int	sign;

	i = -1;
	sign = 1;
	while (sh->cmds[1][++i])
		if (!ft_isdigit(sh->cmds[1][i]) && sh->cmds[1][0] != '-')
			return (1);
	if (sh->cmds[1][0] == '-')
		sign = -1;
	if (ft_strlen(sh->cmds[1]) >= 19)
	{
		if ((sign > 0 && ft_strlen(sh->cmds[1]) == 19 && sh->cmds[1][18] < '8') \
			|| (sign < 0 && ft_strlen(sh->cmds[1]) == 20 \
			&& sh->cmds[1][19] < '9'))
			return (0);
		return (1);
	}
	return (0);
}

static void	arg_error(t_data *sh)
{
	long long	new_nb;

	if (check_long(sh) == 1)
	{
		get_error_message(sh->cmds[1], 5);
		return ;
	}
	if (ft_atol(sh->cmds[1]) >= 0)
		set_exit_status(ft_atol(sh->cmds[1]) % 256);
	else
	{
		new_nb = ft_atol(sh->cmds[1]) * -1;
		new_nb %= 256;
		set_exit_status(256 - new_nb);
	}
}

void	built_exit(t_data *sh)
{
	printf("exit\n");
	// if (array_size(sh->cmds) <= 3)
	// 	free_exit();
	// if (array_size(sh->cmds) == 2)
	// 	exit(*get_exit_status());
	if (array_size(sh->cmds) == 3)
		arg_error(sh);
	else if (array_size(sh->cmds) > 3)
	{
		get_error_message(NULL, 6);
		return ;
	}
	//system("leaks minishell");
	exit(*get_exit_status());
}
