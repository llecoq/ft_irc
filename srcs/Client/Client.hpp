#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "exceptions.hpp"
// # include "Common.hpp"
# include <unistd.h>
# include <sys/socket.h>
# include <string>
# include <iostream>
# include <errno.h>
# include <map>
# include <cstdio>

# define BUFFER_SIZE 512
# define FAILED 	-1

struct t_recv_data
{
	char 	buf[BUFFER_SIZE]; //BUFFER_SIZE ? Check if msg is >BUFFER_SIZE what to do since buffer will already be full
	ssize_t nbytes;
};

class Client
{

	public:

		Client();
		Client( int fd );
		Client( Client const & src );
		~Client();

		Client &		operator=( Client const & rhs );
		// send_priv_msg(); //??

		// methods
		ssize_t				read_data();

		// accessor
		void				set_fd(int fd);
		void				set_authentification(std::string server_pass, std::string client_pass);
		void				set_username(std::string username);
		void				set_realname(std::string realname);
		void				set_nickname(std::string nickname);
		void				set_ipstr(std::string ipstr);
		int					get_fd() const;
		bool				get_authentification() const;
		std::string			get_username() const;
		std::string			get_realname() const;
		std::string			get_nickname() const;
		std::string			get_ipstr() const;

		// debug
		void				display_recv_data() const;

	private:

		int				_fd;
		bool			_authentification;
		std::string 	_username;
		std::string 	_realname;
		std::string 	_nickname;
		std::string		_ipstr;
		t_recv_data 	_recv_data;


		// std::deque<std::string pending_msg> _pending_priv_msg; //pending_msg must contain the sender's username //deque or other ? must be FIFO

		// std::map<std::string channel_name, Channel *> _joined_channels;
};

std::ostream &			operator<<( std::ostream & o, Client const & i );

#endif /* ********************************************************** CLIENT_H */
