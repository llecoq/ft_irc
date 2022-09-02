#include "ExecutionManager.hpp"

#define RPL(nickname, msg)		"PRIVMSG " + nickname + " :" + msg + CRLF

unsigned int	ExecutionManager::_err_msg(Client *client, token_vector tokens) {

	std::string cmd("PRIVMSG");
	std::string msg;

	if (tokens.size() == 1) {
		msg = ERR_NORECIPIENT(cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 451;
		// Err error;
		// return error.ret(client->get_fd(), ERR_NORECIPIENT(cmd), 451);
	}
	else if (tokens.size() == 2) {
		msg = ERR_NEEDMOREPARAMS(cmd); // or ERR_NOTEXTTOSEND
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 461;
	}
	if (client->get_authentication() == false) {
		msg = ERR_NOTREGISTERED;
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 451;
	}
	return SUCCESS;
}

std::string	ExecutionManager::_assemble_msg(token_vector token_msg) {

	std::string msg;

	for (size_t i = 2; i < token_msg.size(); ++i) {
		msg.append(token_msg[i]);
	}
	return msg;
}

unsigned int	ExecutionManager::_msg_to_nickname(token_vector tokens, int dest_fd) {
	std::string dest = tokens[1];
	std::string text = tokens[2];

	if (tokens.size() > 3) // in case no :
		text = _assemble_msg(tokens);
	std::string msg = RPL(dest, text);
	send(dest_fd, msg.c_str(), msg.size(), 0);
	return SUCCESS;
}

unsigned int	ExecutionManager::_msg_to_channel(Client *client, token_vector tokens, channel_iterator chan_it, int dest_fd) {
	std::string dest = tokens[1];
	Channel* chan = chan_it->second;
	std::string text = tokens[2];

	if (tokens.size() > 3) // in case no :
		text = _assemble_msg(tokens);
	if (chan->members.find(client->get_nickname()) == chan->members.end()) { // check client is member of chan
		std::string msg = ERR_CANNOTSENDTOCHAN(chan_it->first);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 404;
	}
	for (Channel::members_iterator it = chan->members.begin(); it != chan->members.end(); ++it) {
		if (client->get_nickname() == it->first)
			continue ;
		std::string msg = RPL(dest, text);
		send(dest_fd, msg.c_str(), msg.size(), 0);
	}
	return SUCCESS;
}


unsigned int	ExecutionManager::privmsg(Client *client, token_vector tokens) {

	unsigned int ret = _err_msg(client, tokens);
	if (ret != SUCCESS)
		return ret;

	int dest_fd = _find_fd_client_by_name(tokens[1]);
	channel_iterator chan_it = _channel_book.find(tokens[1]);

	if (dest_fd) {
		ret = _msg_to_nickname(tokens, dest_fd);
	}
	else if (chan_it != _channel_book.end()) {
		ret = _msg_to_channel(client, tokens, chan_it, dest_fd);
	}
	else {
		std::string msg = ERR_NOSUCHNICK(tokens[1]);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		ret = 401;
	}
	return ret;
}

// // ----ERR we are doing---
// // 411 ERR_NORECIPIENT ":No recipient given (<commande>)" = pas de destinataire
// // 401 ERR_NOSUCHNICK "<pseudonyme> :No such nick/channel"
// // 404 ERR_CANNOTSENDTOCHAN "<nom de canal> :Cannot send to channel" =
						// Envoyé à un utilisateur qui (a) soit n'est pas dans
						// un canal en mode +n ou (b) n'est pas opérateur (ou mode +v)
						// sur un canal en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.
						// !!! We don't have to do it because we don't do those flags (n, b, m, v)
// //-------------------------


// // ----ERR we are doing ????---
// // 412 ERR_NOTEXTTOSEND ":No text to send" = Pas de texte à envoyer
// 						// -> I could not replicate this err,
// 						// I only get : No enough param.
// //----------------------------


// // ----ERR we are NOT doing---
// // 	RPL_AWAY "<pseudo> :<message d'absence>"
// // 	ERR_NOTOPLEVEL "<masque> :No toplevel domain specified" = Domaine principal non spécifié.
// // 	ERR_WILDTOPLEVEL "<masque> :Wildcard in toplevel domain" = Joker dans le domaine principal
// // 	ERR_TOOMANYTARGETS "<destination> :Duplicate recipients. No message delivered" 
// 						// Renvoyé à un client qui essaie d'envoyer un PRIVMSG/NOTICE
// 						// utilisant le format de destination utilisateur@hôte pour lequel
// 						// utilisateur@hôte a plusieurs occurrences.
// //-------------------------
