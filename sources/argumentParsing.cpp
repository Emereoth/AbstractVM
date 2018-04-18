/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argumentParsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:30:33 by acottier          #+#    #+#             */
/*   Updated: 2018/04/18 12:01:58 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <float.h>
#include <sstream>
#include <map>
#include "../includes/avm.hpp"

std::string	extractValue(std::string const & src)
{
	int			startLen = src.find('(');
	int			endLen = src.find(')');

	return (src.substr(startLen + 1, endLen - startLen - 1));
}

bool		argRangeInt8(Token * src, Error & errMsg, std::list<Token *> input)
{
	int					res;
	std::stringstream	newMsg;
	bool				outOfBounds = false;

	newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer overflow (-128 < int_8 < 127)";
	try {
		res = stoi(extractValue(src->getContent()));
	}
	catch (std::out_of_range e){
		outOfBounds = true;
	}
	if (res > CHAR_MAX || res < CHAR_MIN || outOfBounds)
	{
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}

bool		argRangeInt16(Token * src, Error & errMsg, std::list<Token *> input)
{
	double				res;
	std::stringstream	newMsg;
	bool				outOfBounds = false;

	newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer overflow (-32768 < int_16 < 32767)";
	try {
		res = stod(extractValue(src->getContent()));
	}
	catch (std::out_of_range e) {
		outOfBounds = true;
	}
	if (res > SHRT_MAX || res < SHRT_MIN || outOfBounds)
	{
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}

bool		argRangeInt32(Token * src, Error & errMsg, std::list<Token *> input)
{
	double				res;
	std::stringstream	newMsg;
	bool				outOfBounds = false;

	newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer overflow (-2147483648 < int_32 < 2147483647)";
	try {
		res = stod(extractValue(src->getContent()));
	}
	catch (std::out_of_range e) {
		outOfBounds = true;
	}
	if (res > INT_MAX || res < INT_MIN || outOfBounds)
	{
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}

bool		argRangeFloat(Token * src, Error & errMsg, std::list<Token *> input)
{
	double				res;
	std::stringstream	newMsg;

	res = stod(extractValue(src->getContent()));
	if (res > FLT_MAX)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": float overflow (-3.40282e+38 < float < 3.40282e+38)";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	else if (res < -FLT_MAX)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": float underflow (-3.40282e+38 < float < 3.40282e+38)";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}

bool		argRangeDouble(Token * src, Error & errMsg, std::list<Token *> input)
{
	(void)src;
	(void)errMsg;
	(void)input;
	return (true);
}

bool		checkArgRange(Token * src, int range, Error & errMsg, std::list<Token *> input)
{
	std::stringstream		newMsg;

	src->setRange(range);
	if (range < FLOAT && extractValue(src->getContent()).find('.') != std::string::npos)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": decimal value in integer type";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	switch (range)
	{
		case INT_8:
			return (argRangeInt8(src,errMsg, input));
		case INT_16:
			return (argRangeInt16(src,errMsg, input));
		case INT_32:
			return (argRangeInt32(src,errMsg, input));
		case FLOAT:
			return (argRangeFloat(src,errMsg, input));
		case DOUBLE:
			return (argRangeDouble(src,errMsg, input));
	}
	errMsg.addMsg("Unexpected error. This shouldn't happen, like, ever.");
	throw errMsg;
	return (false);
}

void		checkOpRange(eOperandType type, std::string const & v1, std::string const & v2)
{
	Error							err;
	std::map<eOperandType, double> limitMap = 
	{
		{Int8, CHAR_MAX},
		{Int16, SHRT_MAX},
		{Int32, INT_MAX},
		{Float, FLT_MAX}
	};
	bool							isFloating = (type == Float || type == Double ? true : false);
	double							res = (isFloating ? stod(v1) + stod(v2) : std::atoi(v1.c_str()) + std::atoi(v2.c_str()));

	if (res > limitMap[type])
		err.addMsg("Error: Overflow.");
	if (res < -(limitMap[type]))
		err.addMsg("Error: Underflow.");
	if (!err.isEmpty())
		throw err;
}