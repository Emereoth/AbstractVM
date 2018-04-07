/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:06:13 by acottier          #+#    #+#             */
/*   Updated: 2018/04/07 13:32:38 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

#include <exception>
#include <string>

class Error : public std::exception
{
	public:
		Error(void);
		Error(Error const & src);
		~Error(void);

		Error const *		operator=(Error const & rhs);

		void				addMsg(std::string const newMsg);
		std::string			getMsg(void) const;
		bool				isEmpty(void) const;
		
	private:
		std::string			_errMsg;
};

#endif