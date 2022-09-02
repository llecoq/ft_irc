/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:34:23 by llecoq            #+#    #+#             */
/*   Updated: 2022/09/02 17:34:03 by llecoq           ###   ########.fr       */
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
#define ERR_ALREADYREGISTRED					"462 :Unauthorized command (already registered)"
#define ERR_BADCHANNAME(channel)				"479 " + channel + " :Invalid channel name" + CRLF

// COMMAND RESPONSES RFC_2812
#define RPL_WELCOME(nickname)					"001 " + nickname + " :Bijour " + nickname + CRLF
#define RPL_NOTOPIC(nickname, channel) 			"331 " + nickname + " " + channel + " :No topic is set" + CRLF
#define RPL_TOPIC(nickname, channel, topic) 	"332 " + nickname + " " + channel + " :" + topic + CRLF
#define RPL_NAMREPLY(channel, nickname)			"353 " + nickname + " " + channel + " :" + nickname + CRLF
#define RPL_ENDOFNAMES(channel, nickname)		"366 " + nickname + " " + channel + " :End of /NAMES list" + CRLF

// :ft_irc_server 353 llecoq @ #bibi :@llecoq

// MSG_BUILDER
#define MSG_JOIN(channel, nickname)				":" + nickname + " JOIN " + channel + CRLF
	// msg = ":llecoq JOIN #baba\n";

// COMMAND RESPONSES RFC_1459

#endif // NUMERIC_REPLIES_HPP