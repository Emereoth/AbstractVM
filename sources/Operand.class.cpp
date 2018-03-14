// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.cpp                                  :+:      :+:    :+:   */
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
IOperand	const *	Operand<T>::operator/(IOperand const & rhs)
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
IOperand	&		Operand<T>::operator=(IOperand const & rhs)
{
	_type = rhs.getType();
	_value = static_cast<Operand<T> *>(rhs)->_value;
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