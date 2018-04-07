/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argumentParsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:30:33 by acottier          #+#    #+#             */
/*   Updated: 2018/04/07 13:43:51 by acottier         ###   ########.fr       */
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

	res = stoi(extractValue(src->getContent()));
	if (res > CHAR_MAX)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer overflow (-128 < int_8 < 127)";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	else if (res < CHAR_MIN)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer underflow (-128 < int_8 < 127)";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}

bool		argRangeInt16(Token * src, Error & errMsg, std::list<Token *> input)
{
	int					res;
	std::stringstream	newMsg;

	res = stoi(extractValue(src->getContent()));
	if (res > SHRT_MAX)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer overflow (-32768 < int_16 < 32767)";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	else if (res < SHRT_MIN)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer underflow (-32768 < int_16 < 32767)";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	return (true);
}

bool		argRangeInt32(Token * src, Error & errMsg, std::list<Token *> input)
{
	int64_t				res;
	std::stringstream	newMsg;

	res = stoi(extractValue(src->getContent()));
	if (res > INT_MAX)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer overflow (-2147483648 < int_32 < 2147483647)";
		errMsg.addMsg(newMsg.str());
		return (false);
	}
	else if (res < INT_MIN)
	{
		newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
			<< "\": integer underflow (-2147483648 < int_32 < 2147483647)";
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
	// double				res;
	// std::stringstream	newMsg;

	(void)src;
	(void)errMsg;
	(void)input;
	return (true);
	// res = stod(extractValue(src->getContent()));
	// if (res > DBL_MAX)
	// {
	// 	newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
	// 		<< "\": double overflow (-1.79769e+308 < double < 1.79769e+308)";
	// 	errMsg.addMsg(newMsg.str());
	// 	return (false);
	// }
	// else if (res < -DBL_MAX)
	// {
	// 	newMsg << "Error on line " << src->getLine() << ": \"" << showFullContent(input, src->getLine())
	// 		<< "\": double underflow (-1.79769e+308 < double < 1.79769e+308)";
	// 	errMsg.addMsg(newMsg.str());
	// 	return (false);
	// }
	// return (true);
}

bool		checkArgRange(Token * src, int range, Error & errMsg, std::list<Token *> input)
{
	src->setRange(range);
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