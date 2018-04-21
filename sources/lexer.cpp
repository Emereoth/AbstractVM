/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:05:55 by acottier          #+#    #+#             */
/*   Updated: 2018/04/20 14:07:49 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "../includes/avm.hpp"

/*
** Checks the number of elements on a line; returns an error code if there's more than 2
*/
void		elemsOnLine(int const line, std::list<Token *>	input, Error & errMsg)
{
	int								cmdNb = 0;
	int								argNb = 0;
	std::stringstream				newMsg;
	std::list<Token *>::iterator	ii = input.begin();

	while (ii != input.end() && line != (*ii)->getLine())
		ii++;
	while (ii != input.end() && line == (*ii)->getLine())
	{
		if ((*ii)->getInputType() == INSTRUCTION)
			cmdNb++;
		else if ((*ii)->getInputType() == ARGUMENT)
			argNb++;		
		ii++;
	}
	if (cmdNb > 1)
		errMsg.addMsg(errorFormatter("too many instructions on line", line, input));
	if (argNb > 1)
		errMsg.addMsg(errorFormatter("too many arguments on line", line, input));
}

/*
** Check syntax on all elements in input list
*/
void		synCheck(std::list<Token *> input, Error & errMsg)
{
	std::stringstream	newErr;
	int					currentLine;

	for (std::list<Token *>::iterator ii = input.begin() ; ii != input.end() ; )
	{
		currentLine = (*ii)->getLine();
		elemsOnLine(currentLine, input, errMsg);
		while (ii != input.end() && (*ii)->getLine() == currentLine)
			ii++;
	}
	if (!errMsg.isEmpty())
		throw errMsg;
}