/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:44:57 by acottier          #+#    #+#             */
/*   Updated: 2018/03/28 15:00:26 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include <list>
#include <vector>
#include <iostream>
#include "Token.class.hpp"
#include "Operand.class.hpp"
#include "Error.class.hpp"

/* MAIN.CPP */

std::string		showFullContent(std::list<Token *> list, int const & line);

/* INPUT.CPP */

void			separate(std::string const & buffer, int const & i, std::list<Token *> & res, int *pos);
void			readFile(char *file, std::list<Token *> & res);
void			readStdin(std::list<Token *> & res);

/* LEXER.CPP */

void			synCheck(std::list<Token *> input, Error & errMsg);

/* PARSER.CPP */

void			parse(std::list<Token *> input, Error & errMsg);

/* ARGUMENTPARSING.CPP */

bool			checkArgRange(Token * src, int range, Error & errMsg, std::list<Token *> input);

/* OPERATIONS.CPP */

template <typename T>
bool			operationParsing(Operand<T> const & lhs, Operand<T> const & rhs, opType type);

#endif