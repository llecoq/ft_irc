#include "BotClient.hpp"

static volatile bool	bot_running = true;

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BotClient::BotClient() {}

BotClient::BotClient(const char* port) : _port(port) {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BotClient::~BotClient()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BotClient &				BotClient::operator=( BotClient const & rhs )
{
	(void)rhs;
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, BotClient const & i )
{
	(void)i;
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	BotClient::init()
{
	_get_address_info();
	_get_receiving_socket();
	_bot.init_bot(_receiving_socket);
}

void	BotClient::run()
{
	std::cout << "Bot is now conneted to server !" << std::endl;
	while (bot_running == true)
	{
		_poll_events();
		switch (_find_event())
		{
		case DATA_RECEIVED:
			std::cout << "DATA RECEIVED" << std::endl;
			_bot.process_data();
			break;
		case CONNECTION_LOST:
			std::cout << "CONNECTION_LOST" << std::endl;
			// _bot.kill_connection();
			break;
		}
	}
}

void	BotClient::_signal_handler(int signum)
{
	if (signum == SIGINT)
		bot_running = false;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */