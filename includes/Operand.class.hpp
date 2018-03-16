/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:15:23 by acottier          #+#    #+#             */
/*   Updated: 2018/03/16 14:46:57 by acottier         ###   ########.fr       */
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

		eOperandType					_type;
		T								_value;
};

#endif