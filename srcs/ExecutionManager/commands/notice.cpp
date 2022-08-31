#include "ExecutionManager.hpp"

//pseudocode below -> OK
int ExecutionManager::notice(Client *client, std::vector<std::string>) {
	//check if authentication is complete
	if (client->get_authentification() == 0)
		return 0; // or msg ? ERR_NOTREGISTERED
	if (tokens.size() == 1)
		return ERR_NORECIPIENT 
	if (tokens.size() == 2)
		return ERR_NOTEXTTOSEND
	if (tokens.size() > 3)
		//We need to create an ERR for TOOMANYPARAMS, does not exist yet in RFC

	//if tokens[1] == user in client_book
	{
		//send msg to recipient, with added :sender_name as prefix
		//return
	}
	//else if tokens[1] == channel_name 
	{
		//if user is not already in channel
			return ERR_CANNOTSENDTOCHAN
		//else 
			//send message to the ENTIRE channel (broadcast)
			//return
	}
	// return ERR_NOSUCHNICK
}
