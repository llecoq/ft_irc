/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:34:23 by llecoq            #+#    #+#             */
/*   Updated: 2022/08/29 12:07:38 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

#define CRLF "\r\n"

// ERROR REPLIES

#define ERR_NOSUCHNICK(nickname)			"401 " + nickname + " :No such nick/channel" + CRLF
#define ERR_UNKNOWNCOMMAND(command)			"421 " + command + " :Unknown command" + CRLF

// COMMAND RESPONSES
#define RPL_WELCOME(nickname)				"001 " + nickname + " :Bijour " + nickname + CRLF					
#define ERR_UNKNOWNCOMMAND(command)			"421 " + command + " :Unknown command" + CRLF


#endif // NUMERIC_REPLIES_HPP