#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Channel.hpp"
#include "exceptions.hpp"
#include "commons.hpp"

#include <sys/socket.h>

#define BUFFER_SIZE 512
#define FAILED 	-1

struct t_recv_data
{
	t_recv_data(): buf_len(0), nbytes(0) {}

	char 		buf[BUFFER_SIZE];
	ssize_t		buf_len;
	ssize_t 	nbytes;
	std::string	input;
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
		void				set_authentication(std::string server_pass, std::string client_pass);
		void				set_username(std::string username);
		void				set_password(std::string password);
		void				set_realname(std::string realname);
		void				set_nickname(std::string nickname);
		void				set_ipstr(std::string ipstr);
		int					get_fd() const;
		bool				get_authentication() const;
		std::string			get_password() const;
		std::string			get_username() const;
		std::string			get_nickname() const;
		std::string			get_realname() const;
		std::string			get_ipstr() const;
		std::string			get_buf() const;
		std::string			get_input() const;

		// debug
		void				display_recv_data() const;

	private:

		int				_fd;
		bool			_authentication;
		std::string 	_password;
		std::string 	_nickname;
		std::string 	_username;
		std::string 	_realname;
		std::string		_ipstr;
		t_recv_data 	_recv_data;


		// std::deque<std::string pending_msg> _pending_priv_msg; //pending_msg must contain the sender's username //deque or other ? must be FIFO

		std::map<std::string, Channel *> _joined_channels; // channel name, obj channel
};

std::ostream &			operator<<( std::ostream & o, Client const & i );

#endif /* ********************************************************** CLIENT_H */
