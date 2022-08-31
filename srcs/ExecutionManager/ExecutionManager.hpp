#ifndef EXECUTIONMANAGER_HPP
#define EXECUTIONMANAGER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "commons.hpp"

class Client;

class ExecutionManager
{

	public:

		typedef	std::vector<std::string>										token_vector;
		typedef std::string (ExecutionManager::*pf)(Client*, token_vector);
		typedef	std::map<std::string, pf>										cmd_map;
		typedef	cmd_map::iterator												cmd_iterator;
		typedef std::map<int, Client*>											client_map;
		typedef client_map::iterator											client_iterator;
		typedef std::map<std::string, Channel*>									channel_map;
		typedef channel_map::iterator											channel_iterator;
		typedef	std::pair<int, Client*>											fd_client_pair;


		ExecutionManager(std::string password);
		ExecutionManager( ExecutionManager const & src );
		~ExecutionManager();

		ExecutionManager			&operator=( ExecutionManager const & rhs );

		void						init_client(int client_fd, char* ipstr);
		Client*						get_client(int fd) const;
		void						run(Client *client);

		cmd_map						command_book;

	private:

		ExecutionManager();

		client_map					_client_book;
		channel_map					_channel_book;
		std::string					_password;
		std::string					_erase_space_begin(std::string const &buf);
		std::string					_erase_bn_end(std::string const &buf);
		std::string					_get_first_word(std::string const &buf);
		std::vector<std::string>	_split(std::string const &buf);
		cmd_map						_init_command_book();


		std::string					nick(Client *client, token_vector tokens);
		std::string					user(Client *client, token_vector tokens);
		std::string					join(Client *client, token_vector tokens);
		std::string					kick(Client *client, token_vector tokens);
		std::string					invite(Client *client, token_vector tokens);
		std::string					topic(Client *client, token_vector tokens);
		std::string					mode(Client *client, token_vector tokens);
		std::string					privmsg(Client *client, token_vector tokens);
		std::string					notice(Client *client, token_vector tokens);

};

std::ostream						&operator<<(std::ostream & o, ExecutionManager const & i);

#endif
