/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:34:23 by llecoq            #+#    #+#             */
/*   Updated: 2022/08/28 13:44:47 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

// ERROR REPLIES

#define ERR_NOSUCHNICK(nickname)			"401 " + nickname + " :No such nick/channel"
#define ERR_UNKNOWNCOMMAND(command)			"421 " + command + " :Unknown command"

// COMMAND RESPONSES
#define ERR_UNKNOWNCOMMAND(command)			"421 " + command + " :Unknown command"


#endif // NUMERIC_REPLIES_HPP