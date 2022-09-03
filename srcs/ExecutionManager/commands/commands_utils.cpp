#include "ExecutionManager.hpp"

int	ExecutionManager::_send_rpl(Client *client, std::string msg, int numeric)
{
	send(client->get_fd(), msg.c_str(), msg.size(), 0);
	return numeric;
}