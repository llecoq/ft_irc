#ifndef EXECUTIONMANAGER_HPP
#define EXECUTIONMANAGER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "commons.hpp"
#include "numeric_replies.hpp"


#define SUCCESS 0 // msg return for commands

class Client;

class ExecutionManager
{

public:
	typedef std::vector<std::string>										token_vector;
	typedef token_vector::iterator											token_iterator;
	typedef int (ExecutionManager::*pf)(Client *, token_vector);
	typedef std::map<std::string, pf>										cmd_map;
	typedef cmd_map::iterator												cmd_iterator;

	ExecutionManager(std::string password);
	ExecutionManager(ExecutionManager const &src);
	~ExecutionManager();

	ExecutionManager			&operator=(ExecutionManager const &rhs);

	//--------------------------------- ACCESSORS --------------------------------

	Client						*get_client(int fd) const;

	//--------------------------------- METHODS ----------------------------------
	void						init_client(int client_fd, char *ipstr);
	int							run(Client *client);

private:
	ExecutionManager();

	cmd_map						_command_book;
	Client::map					_client_book;
	Channel::map				_channel_book;
	std::string					_password;

	token_vector				_split(std::string const &buf, std::string sep);
	int							_find_fd_client_by_name(std::string nickname);
	int							_send_rpl(Client* client, std::string msg, int code);

	// join
	int							_send_channel_infos(std::string channel_name,\
									Client *client, std::string msg);

	// privmsg
	int							_err_privmsg_handling(Client *client, token_vector tokens, std::string rpl);
	std::string					_assemble_msg(token_vector token_msg);
	int							_msg_to_nickname(token_vector tokens, int dest_fd, std::string rpl);
	int							_msg_to_channel(Client *client, token_vector tokens,\
									Channel::iterator chan_it, std::string rpl);

	// mode
	int							_display_infos_mode(Client *client, token_vector tokens, Channel* chan);
	int							_err_mode_handling(Client *client, token_vector tokens, Channel::iterator chan_it, Channel* chan);
	bool						_is_valid_mode_param(char c);
	std::string					_add_flags(Channel* chan, std::string new_flags);
	std::string					_remove_flags(Channel* chan, std::string new_flags);
	bool						_is_add_rmv(char c);


	int							nick(Client *client, token_vector tokens);
	int							user(Client *client, token_vector tokens);
	int							join(Client *client, token_vector tokens);
	int							kick(Client *client, token_vector tokens);
	int							invite(Client *client, token_vector tokens);
	int							topic(Client *client, token_vector tokens);
	int							mode(Client *client, token_vector tokens);
	int							privmsg(Client *client, token_vector tokens);
	int							notice(Client *client, token_vector tokens);
	int							pass(Client *client, token_vector tokens);
};

std::ostream					&operator<<(std::ostream &o, ExecutionManager const &i);

#endif
