#include "ExecutionManager.hpp"

//NICK USER ET PASS all have variables in client --> _nickname / _username / _password that are std::strings and then we have a flag _authentication
//so we need to check in all of those functions, at the end if the other ones have been filled and if that's the case, do _authentication == 1

//pseudocode below
int ExecutionManager::XXXXX(Client *client, std::vector<std::string>) {
	
	//if pass and nick already in client -> client._authentication == 1
	if (_nickname.empty() && _username.empty() && _password.empty() == 0)
		_authentication == 1;
}
//don't forget to write conditions for too many or too few parameters
