/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:15:23 by acottier          #+#    #+#             */
/*   Updated: 2018/03/14 15:44:12 by acottier         ###   ########.fr       */
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
		virtual ~Operand(void);

		virtual int 							getPrecision(void) const;
		virtual eOperandType					getType(void) const;
		T 										getValue(void) const;

		virtual IOperand const *				operator+(IOperand const & rhs);				
		virtual IOperand const *				operator-(IOperand const & rhs);				
		virtual IOperand const *				operator*(IOperand const & rhs);				
		virtual IOperand const *				operator/(IOperand const & rhs);				
		virtual IOperand const *				operator%(IOperand const & rhs);		

		IOperand &								operator=(IOperand const & rhs);
		virtual std::string const &				toString(void) const;

		
	private:
		Operand(void);
		Operand(Operand const & src);

		eOperandType					_type;
		T								_value;
};

#endif