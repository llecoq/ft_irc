#ifndef EXECUTIONMANAGER_HPP
# define EXECUTIONMANAGER_HPP

#include "Client.hpp"

# include <iostream>
# include <string>
# include <map>
# include <vector>

class Client;

class ExecutionManager
{

	public:

		typedef	std::vector<std::string>										token_vector;
		typedef	std::map<std::string, std::string (*)(Client*, token_vector)>	cmd_map;
		typedef std::map<int, Client*>											client_map;
		// typedef std::map<std::string, Channel*>									channel_map;
		// typedef channel_map::iterator											channel_iterator;
		typedef client_map::iterator											client_iterator;
		typedef	std::pair<int, Client*>				fd_client_pair;




		ExecutionManager(std::string password);
		ExecutionManager( ExecutionManager const & src );
		~ExecutionManager();

		ExecutionManager &		operator=( ExecutionManager const & rhs );


		void				init_client(int client_fd, char* ipstr);

		Client*				get_client(int fd) const;


	private:

		cmd_map			_command_book;
		client_map		_client_book;
		// channel_map		_channel_book;
		std::string		_password;


		// _split_cmd_into_tokens()


};

std::ostream &			operator<<( std::ostream & o, ExecutionManager const & i );

#endif /* ************************************************* ExecutionManager_H */
