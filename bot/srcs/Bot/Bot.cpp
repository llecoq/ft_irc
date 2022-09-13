#include "Bot.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Bot::Bot()
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Bot::~Bot()
{
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	Bot::process_data()
{
	std::cout << _data.input;
}

void	Bot::init_bot(int fd)
{
	std::string	msg("BOT bot :motdepassecomplique\r\n"); // shouldn't be visible on github

	_fd = fd;
	if (send(_fd, msg.c_str(), msg.size(), 0) == FAILED)
		perror("Bot: send");
}

ssize_t	Bot::read_data()
{
	_data.nbytes = recv(_fd, _data.buf, sizeof _data.buf, 0);
	if (_data.nbytes == FAILED)
		perror("Bot: recv");
	else
	{
		_data.buf[_data.nbytes] = '\0';
		_data.input = _data.buf;
	}
	return _data.nbytes;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */