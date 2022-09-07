#include "ExecutionManager.hpp"

#define CMD	"NOTICE"
#define RPL(rpl, nickname, msg)		rpl + " " + nickname + " :" + msg + CRLF

int	ExecutionManager::notice(Client *client, token_vector tokens) {

	int ret = _err_privmsg_handling(client, tokens, CMD);
	if (ret != SUCCESS)
		return ret;

	int dest_fd = _find_fd_client_by_name(tokens[1]);
	Channel::iterator chan_it = _channel_book.find(tokens[1]);

	if (dest_fd) {
		ret = _msg_to_nickname(tokens, dest_fd, CMD);
	}
	else if (chan_it != _channel_book.end()) {
		ret = _msg_to_channel(client, tokens, chan_it, CMD);
	}
	else
		_send_rpl(client, ERR_NOSUCHNICK(tokens[1]), 401);
	return ret;
}

// // ----ERR we are doing---
// // 411 ERR_NORECIPIENT ":No recipient given (<commande>)" = pas de destinataire
// // 401 ERR_NOSUCHNICK "<pseudonyme> :No such nick/channel"
// // 404 ERR_CANNOTSENDTOCHAN "<nom de canal> :Cannot send to channel" =
// 						Envoyé à un utilisateur qui (a) soit n'est pas dans
// 						un canal en mode +n ou (b) n'est pas opérateur (ou mode +v)
// 						sur un canal en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.
// 						!!! We don't have to do it because we don't do those flags (n, b, m, v)
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
