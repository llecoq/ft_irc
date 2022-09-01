#ifndef EXECUTIONMANAGER_HPP
#define EXECUTIONMANAGER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "commons.hpp"
#include "numeric_replies.hpp"

#include <algorithm>

#define	SUCCESS 0 // msg return for commands

class Client;

class ExecutionManager
{

	public:

		typedef	std::vector<std::string>										token_vector;
		typedef	token_vector::iterator											token_iterator;
		typedef unsigned int (ExecutionManager::*pf)(Client*, token_vector);
		typedef	std::map<std::string, pf>										cmd_map;
		typedef	cmd_map::iterator												cmd_iterator;
		typedef std::map<int, Client*>											client_map;
		typedef client_map::iterator											client_iterator;
		typedef std::map<std::string, Channel*>									channel_map;
		typedef channel_map::iterator											channel_iterator;
		typedef	std::pair<int, Client*>											fd_client_pair;


		ExecutionManager(std::string password);
		ExecutionManager(ExecutionManager const & src);
		~ExecutionManager();

		ExecutionManager			&operator=( ExecutionManager const & rhs );

		cmd_map						command_book;

//--------------------------------- ACCESSORS --------------------------------

		Client*						get_client(int fd) const;
	
//--------------------------------- METHODS ----------------------------------
		void						init_client(int client_fd, char* ipstr);
		unsigned int				run(Client *client);

	private:

		ExecutionManager();

		client_map					_client_book;
		channel_map					_channel_book;
		std::string					_password;
		token_vector				_split(std::string const &buf, std::string sep);

		unsigned int				nick(Client *client, token_vector tokens);
		unsigned int				user(Client *client, token_vector tokens);
		unsigned int				join(Client *client, token_vector tokens);
		unsigned int				kick(Client *client, token_vector tokens);
		unsigned int				invite(Client *client, token_vector tokens);
		unsigned int				topic(Client *client, token_vector tokens);
		unsigned int				mode(Client *client, token_vector tokens);
		unsigned int				privmsg(Client *client, token_vector tokens);
		unsigned int				notice(Client *client, token_vector tokens);
		unsigned int				pass(Client *client, token_vector tokens);

};

std::ostream						&operator<<(std::ostream & o, ExecutionManager const & i);

#endif
