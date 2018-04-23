/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argumentParsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:30:33 by acottier          #+#    #+#             */
/*   Updated: 2018/04/23 11:08:29 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <float.h>
#include <sstream>
#include <map>
#include <limits.h>
#include "../includes/avm.hpp"
#include "../includes/Operand.class.hpp"

/*
*	Takes a 'push' or 'assert' argument as input, returns the value between the parenthesis
*/
std::string	extractValue(std::string const & src)
{
	int			startLen = src.find('(');
	int			endLen = src.find(')');

	return (src.substr(startLen + 1, endLen - startLen - 1));
}

/*
*	Checks if given value falls into int8 range
*/
bool		argRangeInt8(std::string const & content, int const line, Error & errMsg, std::list<Token *> input)
{
	int					res;
	bool				outOfBounds = false;

	try {
		res = stoi(extractValue(content));
	}
	catch (std::out_of_range e){
		outOfBounds = true;
	}
	if (res > std::numeric_limits<int8_t>::max() || res < std::numeric_limits<int8_t>::lowest() || outOfBounds)
	{
		errMsg.addMsg(errorFormatter("integer overflow (-128 < int_8 < 127)", line, input));
		return (false);
	}
	return (true);
}

/*
*	Checks if given value falls into int16 range
*/
bool		argRangeInt16(std::string const & content, int const line, Error & errMsg, std::list<Token *> input)
{
	int					res;
	bool				outOfBounds = false;

	try {
		res = stoi(extractValue(content));
	}
	catch (std::out_of_range e) {
		outOfBounds = true;
	}
	if (res > std::numeric_limits<int16_t>::max() || res < std::numeric_limits<int16_t>::lowest() || outOfBounds)
	{
		errMsg.addMsg(errorFormatter("integer overflow (-32768 < int_16 < 32767)", line, input));
		return (false);
	}
	return (true);
}

/*
*	Checks if given value falls into int32 range
*/
bool		argRangeInt32(std::string const & content, int const line, Error & errMsg, std::list<Token *> input)
{
	int					res;
	bool				outOfBounds = false;

	try {
		res = stoi(extractValue(content));
	}
	catch (std::out_of_range e) {
		outOfBounds = true;
	}
	if (res > std::numeric_limits<int32_t>::max() || res < std::numeric_limits<int32_t>::lowest() || outOfBounds)
	{
		errMsg.addMsg(errorFormatter("integer overflow (-2147483648 < int_32 < 2147483647)", line, input));
		return (false);
	}
	return (true);
}

/*
*	Checks if given value falls into float range
*/
bool		argRangeFloat(std::string const & content, int const line, Error & errMsg, std::list<Token *> input)
{
	float				res;
	bool				outOfBounds = false;

	try {
		res = stof(extractValue(content));
	}
	catch (std::out_of_range e) {
		outOfBounds = true;
	}
	if (res > std::numeric_limits<float>::max() || res < std::numeric_limits<float>::lowest() || outOfBounds)
	{
		errMsg.addMsg(errorFormatter("float overflow (1.8E-38 < float < 3.4E+38)", line, input));
		return (false);
	}
	return (true);
}

/*
*	Checks if given value falls into double range
*/
bool		argRangeDouble(std::string const & content, int const line, Error & errMsg, std::list<Token *> input)
{
	double				res;
	bool				outOfBounds = false;

	try {
		res = stod(extractValue(content));
	}
	catch (std::out_of_range e) {
		outOfBounds = true;
	}
	if (res > std::numeric_limits<double>::max() || res < std::numeric_limits<double>::lowest() || outOfBounds)
	{
		errMsg.addMsg(errorFormatter("double overflow (2.2E-308 < double < 1.8E+308)", line, input));
		return (false);
	}
	return (true);
}

/*
*	Calls overflow and type verification function for all data types
*/
bool		checkArgRange(Token * src, int range, Error & errMsg, std::list<Token *> input)
{
	if (range < FLOAT && extractValue(src->getContent()).find('.') != std::string::npos)
	{
		errMsg.addMsg(errorFormatter("decimal value in integer type", src->getLine(), input));
		return (false);
	}
	switch (range)
	{
		case INT_8:
			return (argRangeInt8(src->getContent(), src->getLine(), errMsg, input));
		case INT_16:
			return (argRangeInt16(src->getContent(), src->getLine(), errMsg, input));
		case INT_32:
			return (argRangeInt32(src->getContent(), src->getLine(), errMsg, input));
		case FLOAT:
			return (argRangeFloat(src->getContent(), src->getLine(), errMsg, input));
		case DOUBLE:
			return (argRangeDouble(src->getContent(), src->getLine(), errMsg, input));
	}
	errMsg.addMsg("Unexpected error. This shouldn't happen, like, ever.");
	throw errMsg;
	return (false);
}

/*
*	Is called from checkOpRange(), checks if operation result fits in expected result type
*/
void		checkResLimits(double const res, eOperandType type, Error * errMsg)
{
	double		max;
	double		min;

	switch (type)
	{
		case Int8:
		{
			max = static_cast<double>(std::numeric_limits<int8_t>::max());
			min = static_cast<double>(std::numeric_limits<int8_t>::lowest());
			break ;
		}
		case Int16:
		{
			max = static_cast<double>(std::numeric_limits<int16_t>::max());
			min = static_cast<double>(std::numeric_limits<int16_t>::lowest());
			break ;
		}
		case Int32:
		{
			max = static_cast<double>(std::numeric_limits<int32_t>::max());
			min = static_cast<double>(std::numeric_limits<int32_t>::lowest());
			break ;
		}
		case Float:
		{
			max = static_cast<double>(std::numeric_limits<float>::max());
			min = static_cast<double>(std::numeric_limits<float>::lowest());
			break ;
		}
		case Double:
		{
			max = static_cast<double>(std::numeric_limits<double>::max());
			min = static_cast<double>(std::numeric_limits<double>::lowest());
			break ;
		}
	}
	if (res > max || res < min)
		(*errMsg).addMsg("Operation overflow");
}

/*
*	Is called right before an operation. Computes operation result in double and checks if result is compatible with result type
*/
void		checkOpRange(eOperandType type, std::string const & v1, std::string const & v2, opType op)
{
	Error		errMsg;
	double		res = 0;
	int			intRes = -1;

	try {
		double op1 = stod(extractValue(v1));
		double op2 = stod(extractValue(v2));
		switch (op)
		{
			case opType::ADD:
			{
				res = op1 + op2;
				break;
			}
			case opType::MUL:
			{
				res = op1 * op2;
				break;
			}
			case opType::DIV:
			{
				res = op1 / op2;
				break;
			}
			case opType::SUB:
			{
				res = op1 - op2;
				break;
			}
			case opType::MOD:
			{
				intRes = static_cast<int>(op1) % static_cast<int>(op2);
				break;
			}
		}
		checkResLimits((intRes != -1 ? intRes : res), type, &errMsg);
		if (!errMsg.isEmpty())
			throw errMsg;
	}
	catch (std::out_of_range e)
	{
		errMsg.addMsg("Operation overflow.");
		throw errMsg;
	}
}