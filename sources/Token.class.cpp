/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:55:02 by acottier          #+#    #+#             */
/*   Updated: 2018/04/13 14:07:48 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Token.class.hpp"
#include <iostream>
#include <vector>
#include <list>

Token::Token(void) {}

Token::Token(int const & line, std::string const & command, int *pos) : _line(line), _errors(-1)
{
	std::string		tmp = command.substr(0, command.find(';'));
	
	_type = (*pos == 0 ? INSTRUCTION : ARGUMENT);
	(*pos)++;
	_content = command;
}

Token::Token(Token const & src)
{
	(void)src;
}

Token &				Token::operator=(Token const & src)
{
	(void)src;
	return (*this);
}

Token::~Token(void) {}

int					Token::getLine(void) const
{
	return (_line);
}

int					Token::getInputType(void) const
{
	return (_type);
}

std::string			Token::getContent(void) const
{
	return (_content);
}

int					Token::getErrors(void) const
{
	return (_errors);
}

void				Token::addError(int const & type)
{
	_errors = type;
}

void				Token::showContent(void) const
{
	std::cout << _content << " : " << _type << std::endl;
}

void				Token::setRange(int range)
{
	_range = range;
}