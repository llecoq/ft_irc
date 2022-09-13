#ifndef BOTCLIENT_HPP
# define BOTCLIENT_HPP

# include "BotCommons.hpp"
# include "BotExceptions.hpp"
# include "Bot.hpp"

#define NO_TIMEOUT -1

enum	e_events
{
	CONNECTION_LOST,
	DATA_RECEIVED
};

class BotClient
{

	public:

		BotClient(const char *port);
		~BotClient();

		// member functions
		void	init();
		void	run();

		BotClient &		operator=( BotClient const & rhs );

	private:

		BotClient();

		void		_get_address_info();
		void		_get_receiving_socket();
		int			_connect_to_socket(addrinfo *ptr);
		void		_poll_events();
		static void	_signal_handler(int signum);
		int			_find_event();

		const char		*_port;
		struct addrinfo	*_servinfo;
		struct pollfd	*_pollfd;
		int				_receiving_socket;
		Bot				_bot;
};

std::ostream &			operator<<( std::ostream & o, BotClient const & i );

#endif /* ************************************************************* Client_H */