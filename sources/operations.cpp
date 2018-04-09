/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:40:24 by acottier          #+#    #+#             */
/*   Updated: 2018/04/09 15:41:35 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "../includes/avm.hpp"
#include "../includes/Operand.class.hpp"

bool			checkStack(Error & errMsg)
{
	std::stringstream	newMsg;

	if (0) // EMPTY_STACK
	{
		newMsg << "Error at line " << /*LINE_HERE*/"-1" << ": stack is empty" << std::endl;
		errMsg.addMsg(newMsg.str());
		return (false);
	} 
	else if (1) // LOW STACK
	{
		newMsg << "Error at line " << /*LINE_HERE*/"-1" << ": stack only contains 1 value" << std::endl;
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}