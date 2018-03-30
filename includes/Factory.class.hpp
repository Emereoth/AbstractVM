/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:48:31 by acottier          #+#    #+#             */
/*   Updated: 2018/03/20 12:26:38 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "Operand.class.hpp"

class Factory
{
	public:
		Factory(void);
		~Factory(void);
		IOperand const *			createOperand(std::string const & value, eOperandType type) const;

	private:
		Factory(Factory const & src);

		Factory const *				operator=(Factory const & rhs);

		IOperand const * 			createInt8( std::string const & value ) const;
		IOperand const * 			createInt16( std::string const & value ) const;
		IOperand const * 			createInt32( std::string const & value ) const;
		IOperand const * 			createFloat( std::string const & value ) const;
		IOperand const * 			createDouble( std::string const & value ) const;
};

#endif