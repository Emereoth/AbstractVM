/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:15:23 by acottier          #+#    #+#             */
/*   Updated: 2018/02/12 13:36:17 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"

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
		Operand(T const & input, eOperandType type);
		~Operand(void);

		int 			getPrecision(void) const;
		eOperandType	getType(void) const;
		T 				getValue(void) const;

		Operand const *	operator+(Operand const & rhs);				
		Operand const *	operator-(Operand const & rhs);				
		Operand const *	operator*(Operand const & rhs);				
		Operand const *	operator/(Operand const & rhs);				
		Operand const *	operator%(Operand const & rhs);		

		Operand const *	operator=(Operand const & rhs);
		std::string const &	toString(void) const;

	private:
		Operand(void);
		Operand(Operand const & src);

		eOperandType		_type;
		T					_value;
};

#endif