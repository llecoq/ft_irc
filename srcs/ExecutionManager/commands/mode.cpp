#include "ExecutionManager.hpp"

int	ExecutionManager::_err_mode_handling(Client *client, token_vector tokens) {
	std::string cmd = "MODE";

	if (tokens.size() < 2)
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);

	Channel::iterator chan_it = _channel_book.find(tokens[1]);
	Channel* chan = chan_it->second;

	if (chan_it == _channel_book.end())
		return _send_rpl(client, ERR_NOSUCHCHANNEL(tokens[1]), 403);
	else if (chan->user_is_in_channel(client) == false)
		return _send_rpl(client, ERR_NOTONCHANNEL(tokens[1]), 403);
	else if (client != chan->get_operator())
		return _send_rpl(client, ERR_CHANOPRIVSNEEDED(tokens[1]), 482);
	return SUCCESS;
}


int	ExecutionManager::mode(Client *client, token_vector tokens) {

	int ret = _err_mode_handling(client, tokens);
	if (ret != SUCCESS)
		return ret;

	// check and store correctly the flags

	return ret;
}

// // RFC 1459
// ------ USER MODES <nickname> {+/- o|i|w|s}
//		-o = operator flag
//		-i = marks a users as invisible
//		-w = user recevives wallops. Wallopas
//				are messages that can broadcast
//				network information and its
//				status to its users.
//		-s = marks a user as invisible
// //----------------------------

// ------ CHANNEL MODES <channel> {+/- o|p|s|i|t|n||m|l|b|v|k} [limit] [user] [ban mask]
//		-o = give/take channel operator privileges
//		-p = private channel flag
//		-s = secret channel flag
//		-i = invite-only channel flag								V
//		-t = topic settable by channel operator only flag			V
//		-n = no messages to channel from clients on the outside
//		-m = moderated channel
//		-l = set the user limit to channel
//		-b = set a ban mask to keep users out
//		-v = give/take the ability to speak on a moderated channel
//		-k = set a channel key (password)
// //--------------------------------------------------------



// // ERR
// // ----ERR we are doing---
//		461 ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
//		403 ERR_NOSUCHCHANNEL "<channel name> :No such channel"
//		442 ERR_NOTONCHANNEL "<channel> :You're not on that channel"
//		482 ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
//		472 ERR_UNKNOWNMODE "<char> :is unknown mode char to me"
// //----------------------------

// // ----ERR we are doing ????---
//	ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag" =
//							Returned by the server to indicate
//							that a MODE message was sent with a
//							nickname parameter and that the a
//							mode flag sent was not recognized.
// //----------------------------

// // ----ERR we are NOT doing---
//	ERR_USERSDONTMATCH ":Cant change mode for other users" =
//						Error sent to any user trying to view
//						or change the user mode for a user other
//						than themselves.
//	ERR_KEYSET "<channel> :Channel key already set"
//	ERR_NOSUCHNICK "<nickname> :No such nick/channel"
// //--------------------------------------------------------



// // RPL
// // ----RPL we are doing---
//	324 RPL_CHANNELMODEIS "<channel> <mode> <mode params>"
// //----------------------------

// // ----RPL we are doing ????---
//	221 RPL_UMODEIS "<user mode string>"
// //----------------------------

// // ----RPL we are NOT doing---
//	RPL_BANLIST "<channel> <banid>"
//	RPL_ENDOFBANLIST "<channel> :End of channel ban list"
// //--------------------------------------------------------