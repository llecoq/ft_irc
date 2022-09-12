/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:37:24 by llecoq            #+#    #+#             */
/*   Updated: 2022/09/12 09:49:55 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client() {}

Client::Client(int fd)
:
	_fd(fd),
	_authentication(false)
{}

Client::Client( const Client & src )
{
	(void)src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Client::~Client(){}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Client &				Client::operator=( Client const & rhs )
{
	(void)rhs;
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Client const & i )
{
	o << "-------------------CLIENT--------------------" << std::endl;
	o << "fd = " << i.get_fd() << std::endl;
	o << "ipstr = " << i.get_ipstr() << std::endl;
	o << "password = " << i.get_password() << std::endl;
	o << "nickname = " << i.get_nickname() << std::endl;
	o << "username = " << i.get_username() << std::endl;
	o << "realname = " << i.get_realname() << std::endl;
	i.display_recv_data();
	o << "---------------------------------------------" << std::endl;
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

ssize_t	Client::read_data()
{
	_recv_data.nbytes = recv(_fd, _recv_data.buf + _recv_data.buf_len, sizeof _recv_data.buf, 0);
	if (_recv_data.nbytes == FAILED)
		perror("Client: recv");
	else if (_recv_data.nbytes > 0)
	{
		_recv_data.buf_len += _recv_data.nbytes;
		_recv_data.buf[_recv_data.buf_len] = '\0';
		// A TESTER SUR MAC
		if (_recv_data.buf[_recv_data.buf_len - 1] == '\n') // if last char is '\n' then input is ready to be processed
		{
			_recv_data.input = _recv_data.buf;
			for (size_t i = 0; i < _recv_data.input.size(); i++)
				if (_recv_data.input[i] == '\r')
					_recv_data.input.erase(i, 1);
		}
	}
	return _recv_data.nbytes;
}

void	Client::join_channel(Channel *channel)
{
	_joined_channels.insert(Channel::pair(channel->get_name(), channel));
	channel->add_member(this);
}

int	Client::leave_joined_channels(std::string part_msg, int cmd, Channel::map &channel_book)
{
	Channel::iterator 	it;
	Channel				*channel;

	for (it = _joined_channels.begin(); it != _joined_channels.end(); it++)
	{
		channel = it->second;
		channel->erase_member(this, part_msg, cmd);
		if (channel->empty() == true)
		{
			channel_book.erase(channel->get_name());
			delete channel;
		}
	}
	return 0;
}

void	Client::leave_channel(std::string channel_name, std::string msg, int cmd)
{
	Channel	*channel = _joined_channels.find(channel_name)->second;

	channel->erase_member(this, msg, cmd);
	_joined_channels.erase(channel_name);
}

void	Client::clear_recv_data()
{
	_recv_data.input.clear();
	_recv_data.buf_len = 0;
	_recv_data.buf[0] = 0;
}

void Client::set_input_to_quit()
{
	_recv_data.input = "QUIT :connection lost\n";
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

// will probably have to delete it, it should be of no use but keeping it for testing in case
void	Client::set_fd(int fd)
{
	_fd = fd;
}

void	Client::set_authentication(std::string server_pass, std::string client_pass)
{
	if (_nickname.empty() == 0
		&& _username.empty() == 0
		&& _password.empty() == 0)
		if (server_pass.compare(client_pass) == 0)
			_authentication = true;
}

void	Client::set_password(std::string password)
{
	_password = password;
}

void	Client::set_nickname(std::string nickname)
{
	_nickname = nickname;
}

void	Client::set_username(std::string username)
{
	_username = username;
}

void	Client::set_realname(std::string realname)
{
	realname.erase(0, 1);
	_realname = realname;
}

void	Client::set_ipstr(std::string ipstr)
{
	_ipstr = ipstr;
}

int	Client::get_fd() const
{
	return _fd;
}

bool	Client::get_authentication() const
{
	return _authentication;
}

std::string	Client::get_password() const
{
	return _password;
}

std::string	Client::get_nickname() const
{
	return _nickname;
}

std::string	Client::get_username() const
{
	return _username;
}

std::string	Client::get_realname() const
{
	return _realname;
}

std::string	Client::get_ipstr() const
{
	return _ipstr;
}

std::string	Client::get_buf() const
{
	return _recv_data.buf;
}

std::string	Client::get_input() const
{
	return _recv_data.input;
}

/*
** ----------------------------------- DEBUG -----------------------------------
*/

void	Client::display_recv_data() const
{
	std::cout << "------------------recv_data------------------" << std::endl;
	std::cout << "nbytes = " << _recv_data.nbytes << std::endl;
	std::cout << "buffer = '" << _recv_data.buf << "'" << std::endl;
	std::cout << "input = " << _recv_data.input << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
}

/* ************************************************************************** */