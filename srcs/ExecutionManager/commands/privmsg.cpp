#include "ExecutionManager.hpp"

unsigned int ExecutionManager::privmsg(Client *client, token_vector tokens) {
	std::string cmd("PRIVMSG");
	std::string msg;

	if (tokens.size() == 1) {
		msg = ERR_NORECIPIENT(cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 451;
		// Err error;
		// return error.ret(client->get_fd(), ERR_NORECIPIENT(cmd), 451);
	}
	if (tokens.size() == 2) {
		msg = ERR_NEEDMOREPARAMS(cmd); // or ERR_NOTEXTTOSEND
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 461;
	}
	if (client->get_authentication() == false) {
		msg = ERR_NOTREGISTERED;
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 451;
	}
	// check if user or channel exists then assamble if no : and then send
	return SUCCESS;
}


























// //pseudocode below based on Weechat doing the work when multiple targgets
// // --> OK
// int ExecutionManager::privmsg(Client *client, std::vector<std::string> tokens) {
// 	//check if authentication is complete
// 	if (client->get_authentification() == false)
// 		return 0; // or msg ? ERR_NOTREGISTERED
// 	if (tokens.size() == 1)
// 		return ERR_NORECIPIENT 
// 	if (tokens.size() == 2)
// 		return ERR_NOTEXTTOSEND
// 	if (tokens.size() > 3)
// 		//We need to create an ERR for TOOMANYPARAMS, does not exist yet in RFC

// 	//if tokens[1] == user in client_book
// 	{
// 		//send msg to recipient, with added :sender_name as prefix
// 		//return
// 	}
// 	//else if tokens[1] == channel_name 
// 	{
// 		//if user is not already in channel
// 			return ERR_CANNOTSENDTOCHAN
// 		//else 
// 			//send message to the ENTIRE channel (broadcast)
// 			//return
// 	}
// 	// return ERR_NOSUCHNICK
// }


// // //don't forget to write conditions for too many or too few parameters


// // /*

// // ----ERR we are doing---
// // 411 ERR_NORECIPIENT ":No recipient given (<commande>)" = pas de destinataire

// // 401 ERR_NOSUCHNICK "<pseudonyme> :No such nick/channel"
// //-------------------------


// // ----ERR we are doing ????---
// // 412 ERR_NOTEXTTOSEND ":No text to send" = Pas de texte à envoyer
// 						// -> I could not replicate this err,
// 						// I only get : No enough param.
// //----------------------------


// // ----ERR we are NOT doing---
// // ERR_CANNOTSENDTOCHAN "<nom de canal> :Cannot send to channel" =
// 						// Envoyé à un utilisateur qui (a) soit n'est pas dans
// 						// un canal en mode +n ou (b) n'est pas opérateur (ou mode +v)
// 						// sur un canal en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.
// 						// !!! We don't have to do it because we don't do those flags (n, b, m, v)

// // 	RPL_AWAY "<pseudo> :<message d'absence>"

// // 	ERR_NOTOPLEVEL "<masque> :No toplevel domain specified" = Domaine principal non spécifié.

// // 	ERR_WILDTOPLEVEL "<masque> :Wildcard in toplevel domain" = Joker dans le domaine principal

// // 	ERR_TOOMANYTARGETS "<destination> :Duplicate recipients. No message delivered" 
// 						// Renvoyé à un client qui essaie d'envoyer un PRIVMSG/NOTICE
// 						// utilisant le format de destination utilisateur@hôte pour lequel
// 						// utilisateur@hôte a plusieurs occurrences.
// //-------------------------
