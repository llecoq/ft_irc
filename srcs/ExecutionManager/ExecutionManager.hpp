#ifndef EXECUTIONMANAGER_HPP
#define EXECUTIONMANAGER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "commons.hpp"
#include "numeric_replies.hpp"

class Client;

class ExecutionManager
{

	public:

		typedef	std::vector<std::string>										token_vector;
		typedef	token_vector::iterator											token_iterator;
		typedef void (ExecutionManager::*pf)(Client*, token_vector);
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
		void						run(Client *client);

	private:

		ExecutionManager();

		client_map					_client_book;
		channel_map					_channel_book;
		std::string					_password;
		token_vector				_split(std::string const &buf);

		void						nick(Client *client, token_vector tokens);
		void						user(Client *client, token_vector tokens);
		void						join(Client *client, token_vector tokens);
		void						kick(Client *client, token_vector tokens);
		void						invite(Client *client, token_vector tokens);
		void						topic(Client *client, token_vector tokens);
		void						mode(Client *client, token_vector tokens);
		void						privmsg(Client *client, token_vector tokens);
		void						notice(Client *client, token_vector tokens);
		void						pass(Client *client, token_vector tokens);

};

std::ostream						&operator<<(std::ostream & o, ExecutionManager const & i);

#endif
