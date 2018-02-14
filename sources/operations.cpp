/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:40:24 by acottier          #+#    #+#             */
/*   Updated: 2018/02/10 17:33:07 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "../includes/avm.hpp"
#include "../includes/Operand.class.hpp"

bool			checkStack(std::string * errMsg)
{
	std::stringstream	newMsg;

	if (0) // EMPTY_STACK
	{
		newMsg << "Error at line " << /*LINE_HERE*/"-1" << ": stack is empty" << std::endl;
		(*errMsg).append(newMsg.str());
		return (false);
	} 
	else if (1) // LOW STACK
	{
		newMsg << "Error at line " << /*LINE_HERE*/"-1" << ": stack only contains 1 value" << std::endl;
		(*errMsg).append(newMsg.str());
		return (false);
	}
	return (true);
}

bool			divByZero(Operand<eOperandType> const & rhs, opType type, std::string * errMsg)
{
	std::stringstream	newMsg;

	if (type == opType::DIV && !rhs.getValue())
	{
		newMsg << "Error at line " << /*LINE_HERE*/"-1" << ": division by zero" << std::endl;
		(*errMsg).append(newMsg.str());
		return (false);	
	}
	return (true);
}

bool			operationParsing(Operand const & lhs, Operand const & rhs, opType type)
{
	std::string			errMsg;

	if (!checkStack(&errMsg) || !divByZero(rhs, type, &errMsg))
		throw errMsg;
	return (true);
}