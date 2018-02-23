/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:15:23 by acottier          #+#    #+#             */
/*   Updated: 2018/02/23 13:34:49 by acottier         ###   ########.fr       */
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
		IOperand const *				createOperand(std::string const & value, eOperandType type) const;

		virtual Operand<T> const *		operator+(Operand<T> const & rhs);				
		virtual Operand<T> const *		operator-(Operand<T> const & rhs);				
		virtual Operand<T> const *		operator*(Operand<T> const & rhs);				
		virtual Operand<T> const *		operator/(Operand<T> const & rhs);				
		virtual Operand<T> const *		operator%(Operand<T> const & rhs);		

		Operand<T> const *				operator=(Operand<T> const & rhs);
		std::string const &				toString(void) const;

		T								value;
		
	private:
		Operand(void);
		Operand(Operand const & src);

		IOperand const * 				createInt8( std::string const & value ) const;
		IOperand const * 				createInt16( std::string const & value ) const;
		IOperand const * 				createInt32( std::string const & value ) const;
		IOperand const * 				createFloat( std::string const & value ) const;
		IOperand const * 				createDouble( std::string const & value ) const;

		eOperandType					_type;
};

#endif