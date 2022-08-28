/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_Server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:57:01 by llecoq            #+#    #+#             */
/*   Updated: 2022/08/28 11:31:38 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

# include <sys/types.h>
// # include <sys/socket.h>
# include <netdb.h>
# include <cstring>
// # include <errno.h>  
# include <arpa/inet.h>

# define BACKLOG 	10 
# define NO_TIMEOUT -1
# define UNKNOWN	-1


enum	e_errors
{
	PERROR,
	NO_PERROR,
	ERR_BIND = -2,
	ERR_SOCKET = -3,
	ERR_SETSOCKOPT = -4
};

/*
** ----------------------------------- INIT -----------------------------------
*/

void	Server::_get_address_info()
{
	int					status;
	struct addrinfo 	hints;

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	status = getaddrinfo(NULL, _server_info.port, &hints, &_server_info.servinfo);
	if (status != 0)
	{
		// throw serverExceptions("getaddrinfo error: ", gai_strerror(status));
		_err_log("getaddrinfo error: ");
		gai_strerror(status);
		exit(EXIT_FAILURE);
	}
}

void	Server::_get_listening_socket()
{
	struct addrinfo*	ptr;

    // loop through all the results and bind to the first we can
    for (ptr = _server_info.servinfo; ptr != NULL; ptr = ptr->ai_next)
	{
		if (_create_and_bind_socket(ptr) > 0)
		{
			_add_socket_to_pollfd(_server_info.listening_socket);
			break;
		}
	}
	freeaddrinfo(_server_info.servinfo);
	if (ptr == NULL)
		_error_exit(NO_PERROR, "Couldn't create socket and bind to the port. Server shutting down.");
}

int	Server::_create_and_bind_socket(addrinfo* ptr)
{
	int		opt = true;
	int		socket_fd = 0;

	if ((socket_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == FAILED)
	{
		perror("Server: socket");
		_err_log("Trying to create and bind another socket...");
		return ERR_SOCKET;
	}
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == FAILED)
	{
		perror("setsockopt");
		_err_log("Trying to bind to the socket anyway...");
	}
	if (bind(socket_fd, ptr->ai_addr, ptr->ai_addrlen) == FAILED)
	{
		close(socket_fd);
		perror("Server: bind");
		_err_log("Trying to create and bind another socket...");
		return ERR_BIND;
	}
	_server_info.listening_socket = socket_fd;
	return socket_fd;
}

void	Server::_add_socket_to_pollfd(int socket_fd)
{
	_pollfd.push_back(pollfd());
	_pollfd.back().fd = socket_fd;
	_pollfd.back().events = POLLIN;
	
}

void	Server::_listen_for_incoming_connections()
{
	if (listen(_server_info.listening_socket, BACKLOG) == -1)
		throw serverExceptions("listen :", strerror(errno));
	_log("Server: waiting for connections...");
}

/*
** ----------------------------------- RUN -----------------------------------
*/

void	Server::_poll_events()
{
	int				pfds;

	pfds = poll(_pollfd.data(), _pollfd.size(), NO_TIMEOUT);
	if (pfds == FAILED)
		_error_exit(PERROR, "Server: poll");
}

int	Server::_find_event(struct pollfd current_pollfd)
{
	if (current_pollfd.revents & POLLIN)
	{
		if (current_pollfd.fd == _server_info.listening_socket)
			return PENDING_CONNECTION;
		else
		{
		}
		// else
		// {
		// 	// à faire en boucle jusqu'à ce qu'il n'y est plus de data ?
		// 	_nbytes = recv(current_pollfd.fd, _buff, sizeof _buff, 0);

		// 	if (_nbytes > 0)
		// 		return DATA_RECEIVED;
		// 	else if (_nbytes == 0)
		// 		return CONNECTION_LOST;
		// 	else // nbytes == -1
		// 		return RECV_ERROR;
		// }
	}
	return NO_EVENT;
}

void	Server::_accept_pending_connection()
{
	int						new_fd;
	sockaddr_storage		client_addr;
    socklen_t 				addrlen;
	char* 					ipstr;
    
	addrlen = sizeof client_addr;
	// trying to accept() connection
	new_fd = accept(_server_info.listening_socket, (struct sockaddr *)&client_addr, &addrlen);
	fcntl(new_fd, F_SETFL, O_NONBLOCK); // set fd to non blocking
	if (new_fd > 0)
	{
		_log("New connection accepted !");
		_add_socket_to_pollfd(new_fd);
		ipstr = _sockaddr_to_string(client_addr);
		// _authentify_client(new_fd, ipstr);
		// display bienvenue message to client
		// if (_client_identity(ipstr, client_addr) == UNKNOWN)
			// _add_client_to_book(new_fd, ipstr);
	}
	else
		perror("Server: accept");
}

char*	Server::_sockaddr_to_string(sockaddr_storage client_addr)
{
	static char	ipstr[INET6_ADDRSTRLEN];

	// deal with both IPv4 and IPv6:
	if (client_addr.ss_family == AF_INET)
	{
		struct sockaddr_in *s = (struct sockaddr_in *)&client_addr;
		inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
	}
	else
	{ // AF_INET6
		struct sockaddr_in6 *s = (struct sockaddr_in6 *)&client_addr;
		inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
	}
	return ipstr;
}

void	Server::_authentify_client(int fd, char* ipstr)
{
	Client	new_client(fd);

	new_client.read_data();
	new_client.init_client(ipstr);
	std::cout << new_client << std::endl;
}

// void Server::_add_client_to_book(int client_fd, char* ipstr)
// {
// 	// _client_book.insert(client_pair("test", new Client(client_fd, ipstr))); // leaks
// // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH 
// 	(void)client_fd;
// }

void	Server::_process_data(pollfd_iterator it)
{
	(void)it;
}

void	Server::_close_connection(pollfd_iterator it)
{
	(void)it;
}

/*
** --------------------------------- ERROR / LOG ---------------------------------
*/

void	Server::_error_exit(int error, std::string error_msg)
{
	if (error == PERROR)
		perror(error_msg.c_str());
	else if (error_msg.empty() != 1)
		_err_log(error_msg);
	_close_all_fds();
	// CLOSE ALL FDS AND CLEAN EXIT
	exit(EXIT_FAILURE);
}

void	Server::_log(std::string log_msg)
{
	std::cout << log_msg << std::endl;
}

void	Server::_err_log(std::string err_msg)
{
	std::cerr << err_msg << std::endl;
}

void	Server::_close_all_fds()
{
	pollfd_iterator	it;

	for (it = _pollfd.begin(); it != _pollfd.end(); it++)
		close((*it).fd);	
}