/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:31:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/25 17:28:37 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_var_to_update(char **env, char *var)
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
	export_var_to_update(var->sh->myenv, new_value);
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
		export_var_to_update(sh->myenv, old_pwd);
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
		export_var_to_update(sh->myenv, pwd);
		free(pwd);
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
			export_var_to_update(var->sh->myenv, underscore);
			export_var_to_update(var->sh->expenv, underscore);
			free(underscore);
		}
	}
}
