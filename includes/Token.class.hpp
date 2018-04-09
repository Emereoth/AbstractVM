/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:37:26 by acottier          #+#    #+#             */
/*   Updated: 2018/04/09 18:14:00 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_CLASS_HPP
# define TOKEN_CLASS_HPP

#include <string>
#include <vector>
#include <list>

enum Range
{
	INT_8,
	INT_16,
	INT_32,
	FLOAT,
	DOUBLE
};

enum CommandType
{
    INSTRUCTION,
    ARGUMENT
};

class Token
{
    public:
        Token(void);
        Token(int const & line, std::string const & command, int *pos);
        Token(Token const & src);
        Token &operator=(Token const & rhs);
        ~Token(void);

        int							getLine(void) const;
        int							getInputType(void) const;
        std::string					getContent(void) const;
        int							getErrors(void) const;
        void						addError(int const & type);
        void						showContent(void) const;
		std::string					showFullLine(std::list<Token *>::iterator ii, std::list<Token *> list) const;
		void						setRange(int range);

    private:
        int                         _type;
		int							_range;
        int                         _line;
        std::string					_content;
        int							_errors;
};

#endif