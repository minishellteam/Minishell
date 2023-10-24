/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:31:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/24 11:03:53 by mkerkeni         ###   ########.fr       */
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
	export_var(var->sh, new_value, 0);
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
		export_var(sh, old_pwd, 0);
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
		export_var(sh, pwd, 0);
		free(pwd);
	}
}

static void	export_underscore(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "_=", ft_strlen(env[i])))
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			return ;
		}
	}
}

void	update_underscore(t_vars *var, int i)
{
	char	*underscore;
	int		j;

	j = 0;
	if (var->cmd && var->cmd[i].args)
	{
		while (var->cmd[i].args[j])
			j++;
		if (j)
		{
			underscore = ft_strjoin("_=", var->cmd[i].args[j - 1], 0);
			export_underscore(var->sh->expenv, underscore);
			export_underscore(var->sh->myenv, underscore);
			free(underscore);
		}
	}
}

void	update_underscore_env(t_data *sh)
{
	char	*underscore;

	underscore = "_=usr/bin/env";
	export_var(sh, underscore, 0);
}
