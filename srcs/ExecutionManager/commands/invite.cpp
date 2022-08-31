#include "ExecutionManager.hpp"

//pseudocode below
int ExecutionManager::XXXXX(Client *client, std::vector<std::string>) {
	//check if authentication is complete
	if (client->get_authentification() == 0)
		return 0; // or msg ?
	//make sure client IS operator of channel
		//if not -> ERR_CHANOPRIVSNEEDED and return

}don't forget to write conditions for too many or too few parameters
