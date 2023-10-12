/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:31:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/10 14:48:33 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_shlvl(t_vars *var)
{
	char	*new_value;
	char	*last_value;
	char	*prefix;
	int		value;

	prefix = "SHLVL=";
	last_value = get_env(var, "SHLVL");
	value = ft_atoi(last_value);
	free(last_value);
	value++;
	new_value = ft_itoa(value);
	new_value = ft_strjoin(prefix, new_value, 3);
	printf("new_value = %s\n", new_value);
	export_var(var->sh, new_value);
	free(new_value);
}

void	update_oldpwd(t_data *sh)
{
	char	buffer[BUFF_SIZE];
	char	*old_pwd;

	if (!getcwd(buffer, BUFF_SIZE))
		perror("minishell");
	else
	{
		old_pwd = ft_strjoin("OLDPWD=", buffer, 0);
		export_var(sh, old_pwd);
		free(old_pwd);
	}
}

void	update_pwd(t_data *sh)
{
	char	buffer[BUFF_SIZE];
	char	*pwd;

	if (!getcwd(buffer, BUFF_SIZE))
		perror("minishell");
	else
	{
		pwd = ft_strjoin("PWD=", buffer, 0);
		export_var(sh, pwd);
		free(pwd);
	}
}
