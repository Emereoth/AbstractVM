/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:13:14 by acottier          #+#    #+#             */
/*   Updated: 2018/04/10 14:26:43 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <map>
#include "../includes/Token.class.hpp"
#include "../includes/avm.hpp"

/*
** Checks if operation (first word on line) is valid and recognized by AVM syntax
*/
bool		validOpCheck(Token * ii, Error & errMsg, std::list<Token *> input)
{
	std::string			ops[11] = { "pop" , "dump" , "add" , "sub" , "mul" , "div" , "mod" , "print" , "exit", "push", "assert" };
	std::string			operation = ii->getContent();
	std::stringstream	newMsg;

	for (int i = 0 ; i < 11 ; i++)
	{
		if (!operation.compare(ops[i]))
			return (true);
	}
	newMsg << "Error on line " << ii->getLine() << ": \"" << showFullContent(input, ii->getLine())
		<< "\" : unknown operator \"" << operation << "\"" << std::endl;;
	errMsg.addMsg(newMsg.str());
	return (false);
}

/*
** Checks if operation (first word on line) accepts an operand
*/
bool		opTypeCheck(Token * ii, Error & errMsg, std::list<Token *> input, Token * lastOp)
{
	std::string			lastOpStr = lastOp->getContent();
	std::stringstream	newMsg;

	if (!lastOpStr.compare("push") || !lastOpStr.compare("assert"))
		return (true);
	newMsg << "Error on line " << ii->getLine() << ": \"" << showFullContent(input, ii->getLine())
		<< "\" : operation does not take argument" << std::endl;
	errMsg.addMsg(newMsg.str());
	return (false);
}

/*
** Checks if argument (second word on line) is of the right type and follows a operation needing an operand
*/
bool		validArgCheck(Token * ii, Error & errMsg, std::list<Token *> input, Token * lastOp)
{
	std::string					operation = ii->getContent();
	std::stringstream			newMsg;
	std::map<int, std::string>	rangeMap= { {INT_8, "int8("} , {INT_16, "int16("} , {INT_32, "int32("} ,
											{FLOAT, "float("} , {DOUBLE, "double("} }; 

	if (!opTypeCheck(ii, errMsg, input, lastOp))
		return (false);
	if (operation.back() != ')')
	{
		newMsg << "Error on line " << ii->getLine() << ": \"" << showFullContent(input, ii->getLine())
		<< "\" : invalid argument formatting \"" << operation << "\"" << std::endl;;
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	for (int i = 0 ; i < 5 ; i++)
	{
		if (!operation.compare(0, rangeMap[i].length(), rangeMap[i]))
			return (checkArgRange(ii, i, errMsg, input));
	}
	newMsg << "Error on line " << ii->getLine() << ": \"" << showFullContent(input, ii->getLine())
		<< "\" : invalid argument \"" << operation << "\"" << std::endl;
	errMsg.addMsg(newMsg.str());
	return (false);
}

/*
** Check if operation needs argument and if it does, chcks if it has them
*/
bool		opHasArgument(std::list<Token *>::iterator ii, Error & errMsg, std::list<Token *> input, bool validLine)
{
	std::stringstream				newMsg;
	std::list<Token *>::iterator	current;

	if (!validLine)
		return (false);
	if (!(*ii)->getContent().compare("push") || !(*ii)->getContent().compare("assert"))
	{
		current = ii;
		ii++;
		if ((*ii)->getInputType() == 1)
			return (true);
		newMsg << "Error on line " << (*current)->getLine() << ": \"" << showFullContent(input, (*current)->getLine())
		<< "\" : operation needs argument" << std::endl;
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}

/*
** Walks through input list and checks for semantic errors
*/
void		parse(std::list<Token *> input, Error & errMsg)
{
	bool							validLine = true;
	int								lastErrorLine = -1;
	Token *							lastOp = NULL;
	bool							exitStatus = false;

	for (std::list<Token *>::iterator ii = input.begin() ; ii != input.end() && !exitStatus; ii++)
	{
		if ((*ii)->getLine() == lastErrorLine)
			continue;
		else
			validLine = true;
		if ((*ii)->getInputType() == 0)
		{
			lastOp = (*ii);
			validLine = validOpCheck((*ii), errMsg, input);
			validLine = opHasArgument(ii, errMsg, input, validLine);
			lastErrorLine = (validLine ? -1 : (*ii)->getLine());
			if (validLine && !((*ii)->getContent().compare("exit")))
				exitStatus = true;
		}
		else if ((*ii)->getInputType() == 1)
			validLine = validArgCheck((*ii), errMsg, input, lastOp);
	}
	if (!errMsg.isEmpty())
		throw errMsg;
	else if (!exitStatus)
	{
		errMsg.addMsg("Error : no \'exit\' instruction found\n");
		throw errMsg;
	}
}