/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:15:23 by acottier          #+#    #+#             */
/*   Updated: 2018/02/21 15:18:43 by acottier         ###   ########.fr       */
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

		int 					getPrecision(void) const;
		eOperandType			getType(void) const;
		T		 				getValue(void) const;
		IOperand const *		createOperand(std::string const & value, eOperandType type) const;

		virtual IOperand const *		operator+(IOperand const & rhs);				
		virtual IOperand const *		operator-(IOperand const & rhs);				
		virtual IOperand const *		operator*(IOperand const & rhs);				
		virtual IOperand const *		operator/(IOperand const & rhs);				
		virtual IOperand const *		operator%(IOperand const & rhs);		

		IOperand const *		operator=(IOperand const & rhs);
		std::string const &		toString(void) const;

	private:
		Operand(void);
		Operand(Operand const & src);

		IOperand const * 		createInt8( std::string const & value ) const;
		IOperand const * 		createInt16( std::string const & value ) const;
		IOperand const * 		createInt32( std::string const & value ) const;
		IOperand const * 		createFloat( std::string const & value ) const;
		IOperand const * 		createDouble( std::string const & value ) const;

		T						_value;
		eOperandType			_type;
};

#endif