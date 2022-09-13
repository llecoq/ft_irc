/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:51:42 by llecoq            #+#    #+#             */
/*   Updated: 2022/09/13 16:48:06 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BotClient.hpp"
#include "BotCommons.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "USAGE : ./bot <port number>" << std::endl; 
		exit(EXIT_FAILURE);
	}
	BotClient	BotClient(argv[1]);

	// mini parsing port // mdp ?
	try
	{
		BotClient.init();
		BotClient.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}