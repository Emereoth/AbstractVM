/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.template.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:34:21 by acottier          #+#    #+#             */
/*   Updated: 2018/02/10 17:30:02 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Operand.class.hpp"

template <typename T>
Operand::Operand(T const & input, eOperandType type) : _value(input), _type(type) {}

template <typename T>
Operand::~Operand(void) {}

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
IOperand const *	operator+(IOperand const & rhs)
{
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;