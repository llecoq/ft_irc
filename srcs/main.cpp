/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:04:46 by llecoq            #+#    #+#             */
/*   Updated: 2022/08/28 19:42:35 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char *argv[])
{
	(void)argc;
	Server	server(argv[1], argv[2]);

	// mini parsing port // mdp ?
	try
	{
		server.init();
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	
	// try
		// serv.init
			// get address info
			// create listening socket
			// bind to port
			// listen() for incomming connection

		// poll()

		// main loop
			// accept
			// send
			// rec
	// catch
	// exit (EXIT_SUCCESS);
}	