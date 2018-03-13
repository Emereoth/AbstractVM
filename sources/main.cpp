/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:14:38 by acottier          #+#    #+#             */
/*   Updated: 2018/03/12 11:47:01 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <sstream>
#include "../includes/Token.class.hpp"
#include "../includes/avm.hpp"

/*
** Display full content of all elements on a certain line
*/

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

int  		   main(int argc, char **argv)
{
    std::list<Token *> 			input;
	std::string					tooManyArgs = "Too many arguments";

	try
	{
		if (argc > 2)
			throw tooManyArgs;
		argc == 2 ? readFile(argv[1], input) : readStdin(input);
		// for (std::list<Token *>::iterator ii = (input.begin()) ; ii != input.end() ; ii++)
			// (*ii)->showContent();
		synCheck(input);
		parse(input);
	}
	catch (std::string const & message)
	{
		std::cout << message;
		return (1);
	}
    return (0);
}