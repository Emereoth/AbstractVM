/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:59:51 by acottier          #+#    #+#             */
/*   Updated: 2018/04/19 17:08:58 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include "../includes/avm.hpp"
#include "../includes/Token.class.hpp"

/*
** Tokenize input text: separate based on spaces and newlines, ignore everything after a ';' and before a newline
*/
void	separate(std::string const & buffer, int const & i, std::list<Token *> & res, int *pos)
{
	std::string		word;

	for (size_t length = 0 ; length < buffer.length() ;)
	{
		if (buffer[length] != ' ')
		{
			word = buffer.substr(length, buffer.find(' ', length) - length);
			if (word.find(';', 0) != std::string::npos)
			{
				if (word[0] != ';')
					res.push_back(new Token(i, word.substr(0, word.find(';', 0)), pos));
				length = buffer.length();
			}
			else if (word[0] != ' ')
			{
				res.push_back(new Token(i, word, pos));
				length += word.length();
			}
		}
		else
			length++;
	}
}

/*
** Read text from file
*/
void	readFile(char *file, std::list<Token *> & res)
{
    std::ifstream       ifs;
    std::string         buffer;
	int					pos;
    int                 i = 1;
	Error				errMsg;

	ifs.open(file);
	if (!ifs)
	{
		errMsg.addMsg("Error opening file.");
		throw errMsg;
	}
    while (getline(ifs, buffer))
    {
		pos = 0;
		separate(buffer, i, res, &pos);
        i++;
    }
    ifs.close();
}

/*
** Read text form standard input
*/
void	readStdin(std::list<Token *> & res)
{
    std::string buffer;
    int         i = 1;
	int			pos;

    while (getline(std::cin, buffer))
    {
		pos = 0;
        if (!buffer.compare(";;"))
            return ;
		separate(buffer, i, res, &pos);		
        i++;
    }
}