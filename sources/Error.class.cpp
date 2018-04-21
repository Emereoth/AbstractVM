/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:59:05 by acottier          #+#    #+#             */
/*   Updated: 2018/04/19 17:24:18 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Error.class.hpp"

Error::Error(void) : _errMsg("") {}

Error::Error(Error const & src) : _errMsg(src.getMsg()) {}

Error::~Error(void) {}

Error const *			Error::operator=(Error const & rhs)
{
	_errMsg = rhs.getMsg();
	return (this);
}

/*
*	Adds erorr message to instance
*/
void					Error::addMsg(std::string const newMsg)
{
	_errMsg.append(newMsg);
	_errMsg.append("\n");
}

/*
*	Returns all error messages in instance
*/
std::string				Error::getMsg(void) const
{
	return (_errMsg);
}

/*
*	Checks if the instance contains error messages
*/
bool					Error::isEmpty(void) const
{
	if (_errMsg.length() == 0)
		return (true);
	return (false);
}