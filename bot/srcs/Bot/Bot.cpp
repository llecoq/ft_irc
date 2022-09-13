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

bool	Bot::_insult_is_found(std::string msg)
{
	std::ifstream	infile("./assets/dict_insult_fr.txt");
	std::string		word;

	if (!infile)
	{
		std::cout << "MARDE" << std::endl;
		infile.close();
		return false;
	}
	while (infile >> word)
	{
		size_t pos = msg.find(word);
		if (pos != std::string::npos)
			return true;
	}
	infile.close();
	return false;
}

void	Bot::process_data()
{
	token_vector	tokens = _split(_data.input, " ");

	if (tokens.size() == 4 && tokens[1] == "PRIVMSG")
		if (_insult_is_found(tokens[3]))
		{
			std::string	kick_msg("KICK ");

			kick_msg.append(tokens[2]);
			kick_msg.append(" ");
			kick_msg.append(tokens[0]);
			kick_msg.append(" ");
			kick_msg.append("Malotru ! Vous êtes bien malhonnête!\r\n");
			send(_fd, kick_msg.c_str(), kick_msg.size(), 0);
			std::cout << "insult found !!!!!! KICK THE VILAAAAIN OUT" << std::endl;
		}
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
		if (_data.input.empty() == false && _data.input[0] == ':')
			_data.input.erase(0, 1);
	}
	return _data.nbytes;
}

std::vector<std::string>	Bot::_split(std::string const &buf, std::string sep)
{
	size_t colon = 0;
	if (sep == " ") 
		colon = buf.find_first_of(":", 0);

	token_vector vec;
	size_t start = 0;
	size_t end = 0;

	while ((start = buf.find_first_not_of(sep, end)) != std::string::npos)
	{
		end = buf.find(sep, start);
		if (sep == " " && start == colon)
			end = std::string::npos;
		vec.push_back(buf.substr(start, end - start));
	}
	return vec;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */