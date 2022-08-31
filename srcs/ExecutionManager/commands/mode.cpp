#include "ExecutionManager.hpp"

//pseudocode below
int ExecutionManager::XXXXX(Client *client, std::vector<std::string>) {
	//check if authentication is complete
	if (client->get_authentification() == 0)
		return 0; // or msg ? ERR_NOTREGISTERED
}

//send msg to the entire channel to let people know what mode has been set
don't forget to write conditions for too many or too few parameters
