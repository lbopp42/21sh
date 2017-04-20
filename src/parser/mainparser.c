/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/20 17:24:10 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	isio_file(tokenx)
{
	if (tokenx == '<' && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == "<&" && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == '>' && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == ">&" && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == ">>" && tokenx + 1 == WORD)
		return (1);
	return (0);
}

int	isio_redirect(tokenx)
{
	if (isio_file(tokenx))
		return (1);
	else if (tokenx == IO_NUMBER && isiofile(tokenx + 1))
		return (1);
	else if (tokenx == "<<" && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == IO_NUMBER && tokenx + 1 == "<<")
		return (1);
	return (0);
}

int	iscmd_prefix(tokenx)
{
	static int i = 0;

	i++;
	if (isio_redirect(tokenx))
		return (1);
	else if (iscmd_prefix(tokenx) && isio_redirect(tokenx + 1) && i < 2)
		return (1);
	return (0);
}

int	iscommand(tokenx)
{
	if (iscmd_prefix(tokenx) && tokenx + 1 == WORD && iscmd_prefix(tokenx + 2))
		return (1);
	else if (iscmd_prefix(tokenx) && tokenx + 1 == WORD)
		return (1);
	else if (iscmd_prefix(tokenx))
		return (1);
	else if (tokenx == WORD && iscmd_prefix(tokenx + 1))
		return (1);
	else if (token == WORD)
		return (1);
	return (0);
}

int	ispipe_sequence(tokenx)
{
	static int i = 0;

	i++;
	if (ispipe_sequence(tokenx) && tokenx + 1 == '|' && ((tokenx + 2 == '\n' && iscommand(tokenx + 3) || iscommand(tokenx + 2)) && i < 4))
		return (1);
	else if (iscommand(tokenx))
		return (1);
	return (0);
}

int	isand_or(tokenx)
{
	static int i = 0;

	i++;
	if (isand_or(tokenx) && tokenx + 1 == "&&" && ((tokenx + 2 == '\n' && ispipe_sequence(tokenx + 3)) || ispipe_sequence(tokenx + 2)) && i < 4)
		return (1);
	else if (isand_or(tokenx) && tokenx + 1 == "||" && ((tokenx + 2 == '\n' && ispipe_sequence(tokenx + 3)) || ispipe_sequence(tokenx + 2)) && i < 4)
		return (1);
	else if (ispipe_sequence(tokenx))
		return (1);
	return (0);
}

int	islist(tokenx)
{
	static int i = 0;

	i++;
	if (islist(tokenx) && isseparator_op(tokenx + 1) && isand_or(tokenx + 2) && i < 3)
		return (1);
	else if (isand_or(tokenx))
		return (1);
	return (0);
}

int	isseparator_op(tokenx)
{
	if (tokenx == ';')
		return (1);
	else if (tokenx == '&')
		return (1);
	return (0);
}

int	iscomplete_command(void)
{
	if (islist(tokenx))
		return (1);
	else if (islist(tokenx) && isseparator_op(tokenx + 1))
		return (1);
	return (0);
}

int main(void)
{
	
}
