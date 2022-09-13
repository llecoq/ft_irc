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
	_fd = fd;
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