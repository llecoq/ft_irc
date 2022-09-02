/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:34:23 by llecoq            #+#    #+#             */
/*   Updated: 2022/09/01 17:51:44 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

#define CRLF "\r\n"


// ERROR REPLIES 1459
#define ERR_NOSUCHNICK(nickname)				"401 " + nickname + " :No such nick/channel" + CRLF
#define ERR_UNKNOWNCOMMAND(command)				"421 " + command + " :Unknown command" + CRLF

// ERROR REPLIES 2812
#define ERR_NEEDMOREPARAMS(command)				"461 " + command + " :Not enough parameters" + CRLF
#define ERR_ALREADYREGISTRED					"462 :Unauthorized command (already registered)\r\n"
#define ERR_NOTREGISTERED						"451 :You have not registered\r\n"
#define ERR_NORECIPIENT(command)				"411 :No recipient given " + command + CRLF
#define ERR_CANNOTSENDTOCHAN(channel)			"404 " + channel + " :Cannot send to channel" + CRLF


// COMMAND RESPONSES RFC_2812
#define RPL_WELCOME(nickname)					"001 " + nickname + " :Bijour " + nickname + CRLF

// COMMAND RESPONSES RFC_1459


#endif // NUMERIC_REPLIES_HPP