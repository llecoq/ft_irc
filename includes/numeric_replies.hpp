/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:34:23 by llecoq            #+#    #+#             */
/*   Updated: 2022/09/09 14:42:36 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

#define CRLF "\r\n"

// ERROR REPLIES 1459
#define RPL_CHANNELMODEIS(nickname, channel, mode, mode_params)	"324 " + nickname + " " + channel + " :" + mode + mode_params + CRLF
#define ERR_NOSUCHNICK(nickname)						"401 " + nickname + " :No such nick/channel" + CRLF
#define ERR_NOSUCHCHANNEL(channel)						"403 " + channel + " :No such channel" + CRLF
#define ERR_UNKNOWNCOMMAND(command)						"421 " + command + " :Unknown command" + CRLF
#define ERR_NOTONCHANNEL(channel)						"442 " + channel + " :You're not on that channel" + CRLF
#define ERR_UNKNOWNMODE(char)							"472 " + char + " :is unknown mode char to me" + CRLF
#define ERR_CHANOPRIVSNEEDED(channel)					"482 " + channel + " :You're not channel operator" + CRLF

// ERROR REPLIES 2812
#define ERR_NOSUCHCHANNEL(channel)						"403 " + channel + " :No such channel" + CRLF
#define ERR_CANNOTSENDTOCHAN(channel)					"404 " + channel + " :Cannot send to channel" + CRLF
#define ERR_NORECIPIENT(command)						"411 :No recipient given " + command + CRLF
#define ERR_USERNOTINCHANNEL(nickname, channel)			"441 " + nickname + " " + channel + " :They aren't on that channel" + CRLF
#define ERR_NOTONCHANNEL(channel)						"442 " + channel + " :You're not on that channel" + CRLF
#define ERR_USERONCHANNEL(nickname, channel)			"443 " + nickname + " " + channel + " :is already on channel" + CRLF
#define ERR_NOTREGISTERED								"451 :You have not registrered\r\n"
#define ERR_NEEDMOREPARAMS(command)						"461 " + command + " :Not enough parameters" + CRLF
#define ERR_ALREADYREGISTRED							"462 :Unauthorized command (already registered)\r\n"
#define ERR_INVITEONLYCHAN(channel)						"473 " + channel + " :Cannot join channel (+i)" + CRLF
#define ERR_BADCHANNAME(channel)						"479 " + channel + " :Invalid channel name" + CRLF

// COMMAND RESPONSES RFC_2812
#define RPL_WELCOME(nickname)							"001 " + nickname + " :Bijour " + nickname + CRLF
#define RPL_NOTOPIC(nickname, channel) 					"331 " + nickname + " " + channel + " :No topic is set" + CRLF
#define RPL_TOPIC(nickname, channel, topic) 			"332 " + nickname + " " + channel + " :" + topic + CRLF
#define RPL_NAMREPLY(channel, nickname, members)		"353 " + nickname + " " + channel + " :" + members + CRLF
#define RPL_ENDOFNAMES(channel, nickname)				"366 " + nickname + " " + channel + " :End of /NAMES list" + CRLF

// MSG_BUILDER
#define MSG_JOIN(channel, nickname)						":" + nickname + " JOIN " + channel + CRLF
#define MSG_PART(channel, nickname, part_msg)			":" + nickname + " PART " + channel +  " " + part_msg + CRLF
#define MSG_KICK(channel, nickname, kick_msg)			":" + nickname + " KICK " + channel +  " " + kick_msg + CRLF
//change to :WiZ KICK #Finnish John

// COMMAND RESPONSES RFC_1459


#endif // NUMERIC_REPLIES_HPP