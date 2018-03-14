/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:52:52 by acottier          #+#    #+#             */
/*   Updated: 2018/03/14 15:43:04 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Factory.class.hpp"


Factory::Factory(void) {}

Factory::Factory(Factory const & src)
{
	(void)src;
}

Factory::~Factory(void) {}

IOperand const *	Factory::createOperand(std::string const & value, eOperandType type) const
{
	// IOperand const *	(Factory::*f)(std::string const &) = {&Factory::createInt8, &Factory::createInt16, 
	// 						&Factory::createInt32, &Factory::createFloat, &Factory::createDouble};
	
	// return (*f(type)(value));
	(void)type;
	return (Factory::createInt8(value));
}

IOperand const *	Factory::createInt8(std::string const & value) const
{
	int8_t				castedValue = static_cast<int8_t>(atoi(value.c_str()));
	IOperand const * 	res = new Operand<int8_t>(castedValue, eOperandType::Int8);

	return (res);
}

// template <typename T>
// IOperand const *	Factory::createInt16(std::string const & value) const
// {
// 	int16_t				castedValue = static_cast<int16_t>(atoi(value.c_str()));
// 	Operand<int16_t>	res = new Operand<int16_t>(castedValue, eOperandType::Int16);

// 	return (res);
// }

// template <typename T>
// IOperand const *	Factory::createInt32(std::string const & value) const
// {
// 	int32_t				castedValue = static_cast<int32_t>(atoi(value.c_str()));
// 	Operand<int32_t>	res = new Operand<int16_t>(castedValue, eOperandType::Int32);

// 	return (res);
// }

// template <typename T>
// IOperand const *	Factory::createFloat(std::string const & value) const
// {
// 	float			castedValue = static_cast<float>(atof(value.c_str()));
// 	Operand<float>	res = new Operand<float>(castedValue, eOperandType::Float);

// 	return (res);
// }

// template <typename T>
// IOperand const *	Factory::createDouble(std::string const & value) const
// {
// 	double			castedValue = static_cast<double>(atof(value.c_str()));
// 	Operand<double>	res = new Operand<double>(castedValue, eOperandType::Double);

// 	return (res);
// }