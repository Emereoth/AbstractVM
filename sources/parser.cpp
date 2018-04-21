/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:13:14 by acottier          #+#    #+#             */
/*   Updated: 2018/04/20 14:01:07 by acottier         ###   ########.fr       */
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

	for (int i = 0 ; i < 11 ; i++)
	{
		if (!operation.compare(ops[i]))
			return (true);
	}
	errMsg.addMsg(errorFormatter("unknown operator", ii->getLine(), input));
	return (false);
}

/*
** Checks if operation (first word on line) accepts an operand
*/
bool		opTypeCheck(Token * ii, Error & errMsg, std::list<Token *> input, Token * lastOp)
{
	std::string			lastOpStr = lastOp->getContent();

	if (!lastOpStr.compare("push") || !lastOpStr.compare("assert"))
		return (true);
	errMsg.addMsg(errorFormatter("operation does not take argument", ii->getLine(), input));
	return (false);
}

/*
** Checks if argument (second word on line) is of the right type and follows a operation needing an operand
*/
bool		validArgCheck(Token * ii, Error & errMsg, std::list<Token *> input, Token * lastOp)
{
	std::string					operation = ii->getContent();
	std::map<int, std::string>	rangeMap= { {INT_8, "int8("} , {INT_16, "int16("} , {INT_32, "int32("} ,
											{FLOAT, "float("} , {DOUBLE, "double("} }; 

	if (!opTypeCheck(ii, errMsg, input, lastOp))
		return (false);
	if (operation.back() != ')')
	{
		errMsg.addMsg(errorFormatter("invalid argument formatting", ii->getLine(), input));
		return (false);
	}
	for (int i = 0 ; i < 5 ; i++)
	{
		if (!operation.compare(0, rangeMap[i].length(), rangeMap[i]))
			return (checkArgRange(ii, i, errMsg, input));
	}
	errMsg.addMsg(errorFormatter("invalid argument", ii->getLine(), input));
	return (false);
}

/*
** Check if operation needs argument and if it does, checks if it has them
*/
bool		opHasArgument(int const line, Error & errMsg, std::list<Token *> input, bool validLine)
{
	std::list<Token *>::iterator	current;
	std::list<Token *>::iterator	ii = input.begin();

	if (!validLine)
		return (false);
	while (ii != input.end() && line != (*ii)->getLine())
		ii++;
	if (!(*ii)->getContent().compare("push") || !(*ii)->getContent().compare("assert"))
	{
		current = ii;
		ii++;
		if (ii != input.end() && (*ii)->getInputType() == 1)
			return (true);
		errMsg.addMsg(errorFormatter("operation needs argument", line, input));
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
		validLine = true;
		if ((*ii)->getInputType() == 0)
		{
			lastOp = (*ii);
			validLine = validOpCheck((*ii), errMsg, input);
			validLine = opHasArgument((*ii)->getLine(), errMsg, input, validLine);
			lastErrorLine = (validLine ? -1 : (*ii)->getLine());
			if (validLine && !((*ii)->getContent().compare("exit")))
			{
				exitStatus = true;
				ii++;
				if (ii != input.end() && (*ii)->getContent().compare(";;"))
					std::cout << "Warning: some commands are placed after the \'exit\' instruction and won't be parsed nor executed." << std::endl;
			}
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