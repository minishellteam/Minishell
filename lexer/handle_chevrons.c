/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chevrons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:32:56 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/20 10:50:07 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	check_multiple_chevrons(void)
// {
// 	if (*(g_sh.line + 2) == '>' || *(g_sh.line + 2) == '<')
// 	{
// 		if (*(g_sh.line + 3) == '>')
// 			get_error_message(">>", 1);
// 		else if (*(g_sh.line + 3) == '<')
// 			get_error_message("<<", 1);
// 		else if (*(g_sh.line + 2) == '<' && *(g_sh.line + 3) != '<')
// 			get_error_message("<", 1);
// 		else if (*(g_sh.line + 2) == '>' && *(g_sh.line + 3) != '>')
// 			get_error_message(">", 1);
// 		return (1);
// 	}
// 	return (0);
// }

char	*check_chevrons(int token_len)
{
	char	*token;

	token = NULL;
	if ((*g_sh.line == '>' && *(g_sh.line + 1) == '>')
		|| (*g_sh.line == '<' && *(g_sh.line + 1) == '<'))
	{
		// if (check_multiple_chevrons())
		// 	return (NULL);
		token = get_double_chevron_token(token_len);
	}
	// else if ((*g_sh.line == '>' && *(g_sh.line + 1) == '<'))
	// {
	// 	get_error_message("<", 1);
	// 	return (NULL);
	// }
	// else if (*g_sh.line == '<' && *(g_sh.line + 1) == '>'
	// 	&& *(g_sh.line + 2) == '>')
	// {
	// 	get_error_message(">", 1);
	// 	return (NULL);
	// }
	return (token);
}

char	*get_double_chevron_token(int token_len)
{
	char	*token;

	token_len = 2;
	token = malloc(sizeof(char) * token_len + 1);
	ft_strlcpy(token, g_sh.line, token_len + 1);
	g_sh.line += 2;
	return (token);
}
