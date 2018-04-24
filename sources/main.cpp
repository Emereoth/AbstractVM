/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:14:38 by acottier          #+#    #+#             */
/*   Updated: 2018/04/24 14:43:54 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <sstream>
#include "../includes/Token.class.hpp"
#include "../includes/avm.hpp"

/*
** Display full content of all elements on a certain line
*/

std::string		errorFormatter(std::string const & message, int const line, std::list<Token *> input)
{
	std::stringstream	msg;

	msg << "Error on line " << line << ": \"" << showFullContent(input, line) << "\" : " << message << std::endl;
	return (msg.str());
}

std::string		showFullContent(std::list<Token *> list, int const & line)
{
	std::list<Token *>::iterator		ii = list.begin();
	std::stringstream					res;

	while (ii != list.end())
	{
		if ((*ii)->getLine() == line)
			res << (*ii)->getContent() << " ";
		ii++;
	}
	return (res.str());
}

/*
*	Free input list
*/
void			freeInput(std::list<Token *> input)
{
	for (std::list<Token *>::iterator ii = input.begin() ; ii != input.end() ; ii++)
		delete (*ii);
}

int  		   main(int argc, char **argv)
{
    std::list<Token *> 			input;
	std::string					tooManyArgs = "Too many arguments";
	Error						errMsg;

	try
	{
		if (argc > 2)
			throw tooManyArgs;
		argc == 2 ? readFile(argv[1], input) : readStdin(input);
		synCheck(input, errMsg);
		parse(input, errMsg);
		walkthrough(input, errMsg);
		freeInput(input);
	}
	catch (Error errMsg)
	{
		std::cout << "\n" << errMsg.getMsg();
		freeInput(input);
		return (1);
	}
    return (0);
}