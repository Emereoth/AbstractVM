/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:05:55 by acottier          #+#    #+#             */
/*   Updated: 2018/03/26 16:07:29 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "../includes/avm.hpp"

/*
** Checks the number of elems on a line; returns an error code if there's more than 2
*/
int			elemsOnLine(std::list<Token *>::iterator ii, std::list<Token *>::iterator end, int const & line)
{
	int				res = 0;
	int				currentType = 0;

	while (ii != end && (*ii)->getLine() == line)
	{
		if (currentType == 1)
			return (-1);
		currentType = (*ii)->getInputType();
		res++;
		ii++;
	}
	return (res);
}

/*
** Check syntax on all elems in input list
*/
void		synCheck(std::list<Token *> input, Error & errMsg)
{
	std::stringstream	newErr;
	int					currentLine;

	for (std::list<Token *>::iterator ii = input.begin() ; ii != input.end() ; )
	{
		currentLine = (*ii)->getLine();
		if (elemsOnLine(ii, input.end(), (*ii)->getLine()) == -1)
		{
			newErr << "Error on line " << (*ii)->getLine() << ": \"" << showFullContent(input, (*ii)->getLine()) << "\" : too many elements (max 2)";
			errMsg.addMsg(newErr.str());
			break;
		}
		while (ii != input.end() && (*ii)->getLine() == currentLine)
			ii++;;
	}
	if (!errMsg.isEmpty())
		throw errMsg;
}