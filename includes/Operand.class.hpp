/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:15:23 by acottier          #+#    #+#             */
/*   Updated: 2018/04/04 16:32:17 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"
#include "Factory.class.hpp"

enum class opType 
{
	ADD,
	MUL,
	DIV,
	SUB,
	MOD
};

template <typename T>
class Operand : public IOperand
{
	public:
		Operand(T value, eOperandType type);

		~Operand(void);

		int 							getPrecision(void) const;
		eOperandType					getType(void) const;
		T 								getValue(void) const;

		IOperand const *				operator+(IOperand const & rhs) const;				
		IOperand const *				operator-(IOperand const & rhs) const;				
		IOperand const *				operator*(IOperand const & rhs) const;				
		IOperand const *				operator/(IOperand const & rhs) const;				
		IOperand const *				operator%(IOperand const & rhs) const;		

		IOperand &						operator=(IOperand const & rhs);
		std::string const &				toString(void) const;

		
	private:
		Operand(void);
		Operand(Operand const & src);

		eOperandType					opResultType(IOperand const & rhs) const;

		T								_value;
		eOperandType					_type;
		std::string						_string;
};

template <typename T>
Operand<T>::Operand(T value, eOperandType type) : _value(value), _type(type), _string(std::to_string(_value)) {}

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
IOperand	const *	Operand<T>::operator+(IOperand const & rhs) const
{
	eOperandType		retType = this.opResultType(rhs);
	IOperand const *	res = Factory::createInt8(_string);
	return (this);
}

template <typename T>
IOperand	const *	Operand<T>::operator-(IOperand const & rhs) const
{
	eOperandType		retType = this.opResultType(rhs);
	IOperand const *	res = Factory::createInt16(_string);
	return (this);
}

template <typename T>
IOperand	const *	Operand<T>::operator*(IOperand const & rhs) const
{
	eOperandType		retType = this.opResultType(rhs);
	IOperand const *	res = Factory::createInt32(_string);
	return (this);
}

template <typename T>
IOperand	const *	Operand<T>::operator/(IOperand const & rhs) const
{
	eOperandType		retType = this.opResultType(rhs);
	IOperand const *	res = Factory::createFloat(_string);
	return (this);
}

template <typename T>
IOperand	const *	Operand<T>::operator%(IOperand const & rhs) const
{
	eOperandType		retType = this.opResultType(rhs);
	IOperand const *	res = Factory::createDouble(_string);
	return (this);
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
	return (_string);
}

template <typename T>
Operand<T>::Operand(void) {}

template <typename T>
Operand<T>::Operand(Operand<T> const & src)
{
	(void)src;
}

template <typename T>
eOperandType		Operand<T>::opResultType(IOperand const & rhs)
{
	return (_type > rhs.getType() ? _type : rhs.getType() );
}

#endif