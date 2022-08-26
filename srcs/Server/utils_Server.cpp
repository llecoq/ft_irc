/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_Server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:57:01 by llecoq            #+#    #+#             */
/*   Updated: 2022/08/26 19:11:59 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <cstring>
# include <errno.h>  

# define BACKLOG 10 

enum	e_errors
{
	FAILED = -1,
	ERR_BIND = -2,
	ERR_SOCKET = -3,
	ERR_SETSOCKOPT = -4
};

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
		throw serverExceptions("getaddrinfo error: ", gai_strerror(status));
}

void	Server::_get_listening_socket()
{
	struct addrinfo*	ptr;

    // loop through all the results and bind to the first we can
    for (ptr = _server_info.servinfo; ptr != NULL; ptr = ptr->ai_next)
	{
		if (_create_and_bind_socket(ptr) > 0)
			break;
	}
	freeaddrinfo(_server_info.servinfo);
	if (ptr == NULL)
	{
		std::cerr << "Couldn't create and bind to a socket. Server shutting down." << std::endl;
		exit(EXIT_FAILURE);
	}
}

int	Server::_create_and_bind_socket(addrinfo* ptr)
{
	int		yes = 0;
	int		socket_fd = 0;

	if ((socket_fd = _create_socket(ptr)) == FAILED)
		return ERR_SOCKET;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == FAILED)
	{
		perror("setsockopt");
		std::cerr << "Trying to bind to the socket anyway..." << std::endl;
	}
	if (bind(socket_fd, ptr->ai_addr, ptr->ai_addrlen) == FAILED)
	{
		close(socket_fd);
		perror("server: bind");
		std::cerr << "Trying to create and bind another socket..." << std::endl;
		return ERR_BIND;
	}
	_server_info.listening_socket = socket_fd;
	return socket_fd;
}

int	Server::_create_socket(struct addrinfo* ptr)
{
	int	sockfd = 0;
	
	sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (sockfd == FAILED)
	{
		perror("server: socket");
		std::cerr << "Trying to create and bind another socket..." << std::endl;
	}
	return sockfd;
}

void	Server::_listen_for_incoming_connections()
{
	if (listen(_server_info.listening_socket, BACKLOG) == -1)
		throw serverExceptions("listen :", strerror(errno));
	std::cout << "server: waiting for connections..." << std::endl;
}