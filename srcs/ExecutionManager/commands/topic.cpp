#include "ExecutionManager.hpp"

//pseudocode below -> DONE
int ExecutionManager::XXXXX(Client *client, std::vector<std::string> tokens) {
	//check if authentication is complete
	if (client->get_authentification() == 0)
		return 0; // or msg ?
	if (tokens.size() == 1)
		//ERR_NEEDMOREPARAMS
	else if (tokens.size > 3)
		//We need to create an ERR for TOOMANYPARAMS, does not exist yet in RFC
	if (tokens.size() == 2) //TOPIC channel sans <topic>
		//if _topic exists
			//send RPL_TOPIC to the client
			//and return
		//if no topic is set
			//send RPL_NOTOPIC to the client
			//and return

	//we have "TOPIC channel topic" so we want to SET the topic
	//NB if topic is an empty string then we remove the topic

	//if not on channel 
		//ERR_NOTONCHANNEL and return
	//if channel mode is -t (topic settable by chan operator only) && client is NOT operator
		//ERR_CHANOPRIVSNEEDED and return
	//set topic : channel._topic = tokens[2]
	//send RPL_TOPIC to the ENTIRE CHANNEL
	//return
}

/*

Yes : 
	ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
	RPL_NOTOPIC                     RPL_TOPIC
	ERR_CHANOPRIVSNEEDED

No : ERR_NOCHANMODES

*/don't forget to write conditions for too many or too few parameters
