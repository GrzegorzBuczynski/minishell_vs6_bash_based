/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/07 18:46:45 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*get_redir_cmd(char **ps)
{
	t_cmd	*ret_cmd;
	char	*file;
	int		tok;

	tok = get_token(ps);
	ret_cmd = NULL;
	file = NULL;
	file = get_string(ps);
	file = remove_quotes(file);
	if (file == NULL)
		ft_panic("missing file for redirection", 1);
	if (tok == '<')
		ret_cmd = inputcmd(file);
	else if (tok == '>')
		ret_cmd = redircmd(file, O_CREAT | O_WRONLY | O_TRUNC, 1);
	else if (tok == '+')
		ret_cmd = redircmd(file, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (tok == '-')
		ret_cmd = here_doc_cmd(file);
	return (ret_cmd);
}

int	get_token(char **ps)
{
	ft_skip_whitespace(ps);
	if (!ft_strncmp(*ps, "<<", 2))
		return (*ps += 2, '-');
	if (!ft_strncmp(*ps, ">>", 2))
		return (*ps += 2, '+');
	if (!ft_strncmp(*ps, ">", 1))
		return (*ps += 1, '>');
	if (!ft_strncmp(*ps, "<", 1))
		return (*ps += 1, '<');
	if (!ft_strncmp(*ps, "|", 1))
		return (*ps += 1, '|');
	return ('a');
}
