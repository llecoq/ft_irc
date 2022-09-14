#include "ExecutionManager.hpp"

//-------------------------- CONSTRUCTOR/DESTRUCTOR --------------------------
ExecutionManager::ExecutionManager() 
: _command_book(), _client_book(), _channel_book(), _password(), _bot_fd(0) {}

ExecutionManager::ExecutionManager(std::string password)
: _command_book(), _client_book(), _channel_book(), _password(password), _bot_fd(0) {
	_command_book["NICK"] = &ExecutionManager::nick;
	_command_book["USER"] = &ExecutionManager::user;
	_command_book["JOIN"] = &ExecutionManager::join;
	_command_book["KICK"] = &ExecutionManager::kick;
	_command_book["INVITE"] = &ExecutionManager::invite;
	_command_book["MODE"] = &ExecutionManager::mode;
	_command_book["PRIVMSG"] = &ExecutionManager::privmsg;
	_command_book["NOTICE"] = &ExecutionManager::notice;
	_command_book["PASS"] = &ExecutionManager::pass;
	_command_book["CAP"] = &ExecutionManager::cap;
	_command_book["PART"] = &ExecutionManager::part;
	_command_book["PING"] = &ExecutionManager::ping;
	_command_book["TOPIC"] = &ExecutionManager::topic;
	_command_book["QUIT"] = &ExecutionManager::quit;
	_command_book["BOT"] = &ExecutionManager::bot;
}

ExecutionManager::ExecutionManager(const ExecutionManager & src) {
	(void)src;
}

ExecutionManager::~ExecutionManager() {
	Client::iterator	client_it;
	Channel::iterator	chan_it;

	for (client_it = _client_book.begin(); client_it != _client_book.end(); client_it++)
		delete client_it->second;	
	for (chan_it = _channel_book.begin(); chan_it != _channel_book.end(); chan_it++)
		delete chan_it->second;
}
//----------------------------------------------------------------------------


//--------------------------------- OVERLOADS --------------------------------
ExecutionManager	&ExecutionManager::operator=( ExecutionManager const & rhs ) {
	(void)rhs;
	return *this;
}

std::ostream	&operator<<( std::ostream & o, ExecutionManager const & i ) {
	(void)i;
	return o;
}
//----------------------------------------------------------------------------


//--------------------------------- METHODS ----------------------------------
void	ExecutionManager::init_client(int fd, const char	*ipstr) {

	Client*	new_client = new Client(fd); // delete afterwards
	
	_client_book.insert(Client::pair(fd, new_client));
	new_client->set_ipstr(ipstr);
}

int	ExecutionManager::run(Client* client) {

	int ret = 0;

	if (client->get_input().empty())
		return ret;

	std::vector<std::string> multiple_cmds = _split(client->get_input(), "\n");
	//for multiple \n
	client->clear_recv_data();

	for (size_t i = 0; i < multiple_cmds.size(); ++i) { // for each \n
		token_vector tokens = _split(multiple_cmds[i], " ");
		std::string cmd = tokens[0];
		cmd_iterator found = _command_book.find(cmd);

		//===========================
		//FOR DEBUGG ONLY
		// for (token_iterator it = tokens.begin(); it != tokens.end(); it++)
			// std::cout << *it << " ";
		// std::cout << std::endl;
		//===========================
		
		if (found == _command_book.end()) {
			ret = 421;
			std::string msg(ERR_UNKNOWNCOMMAND(cmd));
			send(client->get_fd(), msg.c_str(), msg.size(), 0 );
			break ; // if first command line(in case of multiple \n) is wrong, not even launching the next ones
		}
		ret = (this->*(found->second))(client, tokens);
	}
	return ret;
}
//----------------------------------------------------------------------------


//--------------------------------- ACCESSORS --------------------------------
Client*	ExecutionManager::get_client(int fd) const {
	Client::const_iterator	it = _client_book.find(fd);

	if (it == _client_book.end())
		return NULL;
	return it->second;
}
//----------------------------------------------------------------------------


//-------------------------------- NON MEMBERS -------------------------------
std::ostream	&operator<<(std::ostream & o, ExecutionManager const & i);
//----------------------------------------------------------------------------

//--------------------------------- PRIVATE ----------------------------------
std::vector<std::string>	ExecutionManager::_split(std::string const &buf, std::string sep) {

	size_t colon = 0;
	if (sep == " ")
		colon = buf.find_first_of(":", 0);

	token_vector vec;
	size_t start = 0;
	size_t end = 0;

	while ((start = buf.find_first_not_of(sep, end)) != std::string::npos) { // size_t npos -> end of string
		end = buf.find(sep, start);
		if (sep == " " && start == colon) {	// gerer les : only when we are seperating the parameters.
			end = std::string::npos;
		}
		vec.push_back(buf.substr(start, end - start));
	}
	return vec;
}

int	ExecutionManager::_find_fd_client_by_name(std::string nickname) {

	int ret = 0;
	for (Client::iterator it = _client_book.begin(); it != _client_book.end(); ++it) {
		if (it->second->get_nickname() == nickname)
			return it->second->get_fd();
	}
	return ret;
}

void	ExecutionManager::_remove_empty_channel(Channel::iterator chan_it) {
	Channel	*channel = chan_it->second;

	if (channel->empty() == true) {
		_channel_book.erase(chan_it);
		delete channel;
	}
}

Client *ExecutionManager::_get_client_by_name(std::string client_name) {
	for (Client::iterator it = _client_book.begin(); it != _client_book.end(); it++)
		if (it->second->get_nickname() == client_name)
			return it->second;
	return NULL;
}

int	ExecutionManager::_send_rpl(Client *client, std::string msg, int numeric) {
	if (send(client->get_fd(), msg.c_str(), msg.size(), 0) == FAILED){
		perror("ExecutionManager: send");
		return FAILED;
	}
	return numeric;
}

//does not modify original token bc that is what freenode does
Channel::iterator ExecutionManager::_find_chan_in_lowercase(std::string token) {
	std::string chan_name_lowercase;
	for (std::string::size_type i = 0; i < token.length(); i++) // token to lower
		chan_name_lowercase.push_back(std::tolower(token[i]));
	return (_channel_book.find(chan_name_lowercase));
}

//----------------------------------------------------------------------------