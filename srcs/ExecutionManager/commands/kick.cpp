#include "ExecutionManager.hpp"

//pseudocode below
int ExecutionManager::kick(Client *client, std::vector<std::string>) {
	//check if authentication is complete
	if (client->get_authentification() == 0)
		return 0; // or msg ?
	if (tokens.size() < 3)
		return ERR_NEEDMOREPARAMS
	else if (tokens.size() > 4)
		//We need to create an ERR for TOOMANYPARAMS, does not exist yet in RFC

	//if channel does not exist
		// send ERR_NOSUCHCHANNEL
	//else get corresponding channel

	//if client is not a member of channel
		// Send ERR_NOTONCHANNEL and return;
	//check if client is operator of this channel
		// no -> ERR_CHANOPRIVSNEEDED and return
	//check if target is on the channel 
		//no -> ERR_USERNOTINCHANNEL and return;
	
	//CLIENT IS in channel and is operator AND target is in the channel so now kick him out
	//Remove target from channel._members
	//Remove channel from client._joined_channels
	//SEND broadcast msg to the entire channel to let them now target has been kicked
	//send msg to target to let him know he has been kicked
}

/*
ERR_CHANOPRIVSNEEDED
ERR_NEEDMOREPARAMS
ERR_NOTONCHANNEL
ERR_USERNOTINCHANNEL          


Not for us :
	ERR_BADCHANMASK
*/