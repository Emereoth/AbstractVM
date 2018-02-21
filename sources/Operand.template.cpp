// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.template.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:34:21 by acottier          #+#    #+#             */
/*   Updated: 2018/02/15 14:17:25 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Operand.class.hpp"

template <typename T>
Operand<T>::Operand(T value, eOperandType type) : _value(value), _type(type) {}

template <typename T>
Operand<T>::~Operand(void) {}

template <typename T>
int					Operand<T>::getPrecision(void) const
{
	return ((int)_type);
}

template <typename T>
eOperandType		Operand<T>::getType(void) const
{
	return (_type);
}

template <typename T>
T					Operand<T>::getValue(void) const
{
	return (_value);
}

template <typename T>
IOperand const *	Operand<T>::createOperand(std::string const & value, eOperandType type) const
{
	IOperand const *	(Operand<T>::*f[5])(std::string const &) = {&Operand<T>::createInt8, &Operand<T>::createInt16, 
							&Operand<T>::createInt32, &Operand<T>::createFloat, &Operand<T>::createDouble};
	
	return (*f(type)(value));
}

template <typename T>
IOperand	const *	Operand<T>::operator+(IOperand const & rhs)
{
	(void)rhs;
	return (*this);
}

template <typename T>
IOperand	const *	Operand<T>::operator-(IOperand const & rhs)
{
	(void)rhs;
	return (*this);
}

template <typename T>
IOperand	const *	Operand<T>::operator*(IOperand const & rhs)
{
	(void)rhs;
	return (*this);
}

template <typename T>
IOperand	  const *	Operand<T>::operator/(IOperand const & rhs)
{
	(void)rhs;
	return (*this);
}

template <typename T>
IOperand	const *	Operand<T>::operator%(IOperand const & rhs)
{
	(void)rhs;
	return (*this);
}

template <typename T>
IOperand	const *	Operand<T>::operator=(IOperand const & rhs)
{
	_type = rhs.getType();
	_value = rhs.getValue();
}

template <typename T>
std::string	const &	Operand<T>::toString(void) const
{
	return (to_string(_value));
}

template <typename T>
Operand<T>::Operand(void) {}

template <typename T>
Operand<T>::Operand(Operand<T> const & src)
{
	(void)src;
}

template <typename T>
IOperand const *	Operand<T>::createInt8(std::string const & value) const
{
	return (new Operand<int8_t>(static_cast<int8_t>(atoi(value.c_str())), eOperandType::Int8));
}

template <typename T>
IOperand const *	Operand<T>::createInt16(std::string const & value) const
{
	return (new Operand<int16_t>(static_cast<int16_t>(atoi(value.c_str())), eOperandType::Int16));
}

template <typename T>
IOperand const *	Operand<T>::createInt32(std::string const & value) const
{
	return (new Operand<int32_t>(static_cast<int32_t>(atoi(value.c_str())), eOperandType::Int32));
}

template <typename T>
IOperand const *	Operand<T>::createFloat(std::string const & value) const
{
	return (new Operand<float>(static_cast<float>(atof(value.c_str())), eOperandType::Float));
}

template <typename T>
IOperand const *	Operand<T>::createDouble(std::string const & value) const
{
	return (new Operand<double>(static_cast<double>(atof(value.c_str())), eOperandType::Double));
}