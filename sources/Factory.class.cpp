/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:52:52 by acottier          #+#    #+#             */
/*   Updated: 2018/04/24 14:54:47 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Factory.class.hpp"
#include "../includes/Operand.class.hpp"
#include <map>

Factory::Factory(void) {}

Factory::Factory(Factory const & src)
{
	(void)src;
}

Factory::~Factory(void) {}

/*
*	Create operand depending on value data type
*/
IOperand const *	Factory::createOperand(std::string const & value, eOperandType type) const
{
	std::map<eOperandType, IOperand const * (Factory::*) (std::string const &) const>	functionMap = 
	{
		{Int8, &Factory::createInt8},
		{Int16, &Factory::createInt16},
		{Int32, &Factory::createInt32},
		{Float, &Factory::createFloat},
		{Double, &Factory::createDouble}
	};

	return ((this->*(functionMap[type]))(value));
}

 /*
 *	Create operand containing an int8 value
 */
IOperand const *	Factory::createInt8(std::string const & value) const
{
	int8_t				castedValue = static_cast<int8_t>(atoi(value.c_str()));
	IOperand const * 	res = new Operand<int8_t>(castedValue, eOperandType::Int8);

	return (res);
}

 /*
 *	Create operand containing an int816 value
 */
IOperand const *	Factory::createInt16(std::string const & value) const
{
	int16_t				castedValue = static_cast<int16_t>(atoi(value.c_str()));
	IOperand const *	res = new Operand<int16_t>(castedValue, eOperandType::Int16);

	return (res);
}

 /*
 *	Create operand containing an int32 value
 */
IOperand const *	Factory::createInt32(std::string const & value) const
{
	int32_t				castedValue = static_cast<int32_t>(atoi(value.c_str()));
	IOperand const *	res = new Operand<int16_t>(castedValue, eOperandType::Int32);

	return (res);
}

 /*
 *	Create operand containing an float value
 */
IOperand const *	Factory::createFloat(std::string const & value) const
{
	float			castedValue = static_cast<float>(atof(value.c_str()));
	IOperand const *	res = new Operand<float>(castedValue, eOperandType::Float);

	return (res);
}

 /*
 *	Create operand containing a double value
 */
IOperand const *	Factory::createDouble(std::string const & value) const
{
	double			castedValue = static_cast<double>(atof(value.c_str()));
	IOperand const *	res = new Operand<double>(castedValue, eOperandType::Double);

	return (res);
}