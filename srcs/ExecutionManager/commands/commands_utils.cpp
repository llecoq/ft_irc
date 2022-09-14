#include "ExecutionManager.hpp"

int	ExecutionManager::_send_rpl(Client *client, std::string msg, int numeric)
{
	if (send(client->get_fd(), msg.c_str(), msg.size(), 0) == FAILED){
		perror("ExecutionManager: send");
		return FAILED;
	}
	return numeric;
}

//does not modify original token bc that is what freenode does
Channel::iterator ExecutionManager::_find_chan_in_lowercase(std::string token) {
	std::string chan_name_lowercase;
	for (std::string::size_type i = 0; i < token.length(); i++) // token to lower
		chan_name_lowercase.push_back(std::tolower(token[i]));
	return (_channel_book.find(chan_name_lowercase));
}