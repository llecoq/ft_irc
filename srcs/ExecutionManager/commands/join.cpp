#include "ExecutionManager.hpp"

// JOIN <channels>
//also used to re-enter channel that client is already a member off -> BUT US we cannot leave a channel so no need?

//pseudocode below  --> OK
int ExecutionManager::join(Client *client, std::vector<std::string> tokens) {
	//check if authentication is complete
	if (client->get_authentification() == 0)
		return 0; // or msg ? ERR_NOTREGISTERED
	if (tokens.size() < 2)
		return ERR_NEEDMOREPARAMS
	else if (tokens.size() > 2)
		//We need to create an ERR for TOOMANYPARAMS, does not exist yet in RFC
	
	//split tokens[1] == <channels> on ' , ' char AND lowercase each of them (use c++ algorithm)
	//std::vector<std::string> channels;
	//std::vector<std::string>::iterator it_channel_name;

	for (it = channels.begin(), it != channels.end(), it++)
	{
		//if channel has same name as user
			//send made up err and continue
		//if channel does not exist in channel_book
			//if channel.length() is > 50 
				//send Channel_name too long and continue
			//create new_channel -> add to channel_book
			//join channel -> add to client.joined_channel and to channel_book.joined_members but i added it
			//set client as operator
		//else if channel exists
			//if user in channel
				//send ERR_USERONCHANNEL and continue //this err is not in rfc join section
			//if channel._mode == invite_only (i)
				//send ERR_INVITEONLYCHAN and continue
			//join channel -> add to client.member_channel
		//send the user :
			//JOIN msg //!!! might be different when creating a channel
			//RPL_TOPIC
			//the list of the users (must include himself) who are on the channel (RPL_NAMREPLY)
		//send all other channel members
			//JOIN msg

	}
}


/*
Err that apply to us 
		ERR_NEEDMOREPARAMS              
		ERR_INVITEONLYCHAN              
		RPL_TOPIC

do not apply to us
		ERR_BANNEDFROMCHAN no ban on our server
		ERR_TOOMANYCHANNELS if client has joined max number of channel
		ERR_NOSUCHCHANNEL our join creates a channel if it does not exist
		ERR_CHANNELISFULL no limit               
		ERR_TOOMANYTARGETS not for us           
		ERR_BADCHANNELKEY no password for our channel 
		ERR_BADCHANMASK we do not use channel masks
		ERR_UNAVAILRESOURCE
*/don't forget to write conditions for too many or too few parameters
