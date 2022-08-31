#include "ExecutionManager.hpp"

//pseudocode below
int ExecutionManager::XXXXX(Client *client, std::vector<std::string>) {
	//check if authentication is complete
	if (client->get_authentification() == 0)
		return 0; // or msg ?

	//check if client is operator of this channel
		// no -> ERR_CHANOPRIVSNEEDED and return
}

//send msg to the entire channel to let people know who has been kicked
don't forget to write conditions for too many or too few parameters
