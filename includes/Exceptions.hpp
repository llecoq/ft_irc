/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:21:27 by llecoq            #+#    #+#             */
/*   Updated: 2022/08/26 17:40:18 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class serverExceptions : public std::exception
{
    private:
    	std::string	_fonction;
    	std::string	_message;

    public:

		virtual ~serverExceptions() throw() {return ;}

    	serverExceptions(std::string function, std::string message)
		:
			_fonction(function),
			_message(message)
		{}

		virtual const char * what() const throw()
		{
			static std::string	errorMessage = _fonction + _message;
			return errorMessage.c_str();
		}
};


#endif