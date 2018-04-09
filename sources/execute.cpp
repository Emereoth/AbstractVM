/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:01:18 by acottier          #+#    #+#             */
/*   Updated: 2018/04/09 19:10:18 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "../includes/Error.class.hpp"
#include "../includes/Token.class.hpp"
#include "../includes/Error.class.hpp"

void			opPush(int const & line, std::string const & content, Error & errMsg)
{
	// INIT STACK
}

void			execute(std::string const & cmd, int const & line, std::list<Token *>::iterator ii), Error & errMsg
{
	std::map<std::string const &, void (*) (int, std::string const &, Error &)> functionMap = 
	{
		{"push", &opPush},
		{"pop", &opPop},
		{"dump", &opDump},
		{"assert", &opAssert},
		{"add", &opAdd},
		{"sub", &opSub},
		{"mul", &opMul},
		{"div", &opDiv},
		{"mod", &opMod},
		{"print", &opPrint},
		{"exit", &opExit}
	};

	functionMap[cmd](line, (*ii)->getContent(), errMsg);
}

void			walkthrough(std::list<Token *> input, Error & errMsg)
{
	std::string		cmd;

	for (std::list<Token *>::iterator ii = input.begin() ; ii != input.end() ; ii++ )
	{
		if ((*ii)->getInputType() == INSTRUCTION)
		{
			cmd = (*ii)->getContent();
			if (cmd.compare("push") || cmd.compare("assert"))
				execute(cmd, (*ii)->getLine(), ii++, errMsg);
			else
				execute(cmd, (*ii)->getLine(), ii, errMsg);
		}
	}
}