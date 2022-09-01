#include "ExecutionManager.hpp"

//-------------------------- CONSTRUCTOR/DESTRUCTOR --------------------------
ExecutionManager::ExecutionManager() 
: command_book(), _client_book(), _channel_book(), _password() {}

ExecutionManager::ExecutionManager(std::string password)
: command_book(), _client_book(), _channel_book(), _password(password) {
	command_book["NICK"] = &ExecutionManager::nick;
	command_book["USER"] = &ExecutionManager::user;
	command_book["JOIN"] = &ExecutionManager::join;
	command_book["KICK"] = &ExecutionManager::kick;
	command_book["INVITE"] = &ExecutionManager::invite;
	command_book["MODE"] = &ExecutionManager::mode;
	command_book["PRIVMSG"] = &ExecutionManager::privmsg;
	command_book["NOTICE"] = &ExecutionManager::notice;
	command_book["PASS"] = &ExecutionManager::pass;
}

ExecutionManager::ExecutionManager(const ExecutionManager & src) {
	(void)src;
}

ExecutionManager::~ExecutionManager() {
	client_iterator	it;

	for (it = _client_book.begin(); it != _client_book.end(); it++)
		delete it->second;	
}
//----------------------------------------------------------------------------


//--------------------------------- OVERLOADS --------------------------------
ExecutionManager	&ExecutionManager::operator=( ExecutionManager const & rhs ) {
	(void)rhs;
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream	&operator<<( std::ostream & o, ExecutionManager const & i ) {
	(void)i;
	//o << "Value = " << i.getValue();
	return o;
}
//----------------------------------------------------------------------------


//--------------------------------- METHODS ----------------------------------
void	ExecutionManager::init_client(int fd, char* ipstr) {

	Client*	new_client = new Client(fd); // delete afterwards
	
	_client_book.insert(fd_client_pair(fd, new_client));
	new_client->set_ipstr(ipstr);
}

void	ExecutionManager::run(Client* client) {

	if (client->get_buf().empty())
		return ;

	//for multiple \n
	std::vector<std::string> multiple_cmds = _split(client->get_buf(), "\n"); // get_buf will change

	for (size_t i = 0; i < multiple_cmds.size(); ++i) { // for each \n
		token_vector tokens = _split(multiple_cmds[i], " ");
		std::string cmd = *(tokens.begin());

		cmd_iterator found = command_book.find(cmd);
		if (found != command_book.end())
				(this->*(found->second))(client, tokens);
		else {
			std::string msg(ERR_UNKNOWNCOMMAND(cmd));
			send(client->get_fd(), msg.c_str(), msg.size(), 0 );
			break ; // if first command line(in case of multiple \n) is wrong, not even launching the next ones
		}
	}

}
//----------------------------------------------------------------------------


//--------------------------------- ACCESSORS --------------------------------
Client*	ExecutionManager::get_client(int fd) const {
	return _client_book.find(fd)->second;
}
//----------------------------------------------------------------------------


//-------------------------------- NON MEMBERS -------------------------------
std::ostream	&operator<<(std::ostream & o, ExecutionManager const & i);
//----------------------------------------------------------------------------

//--------------------------------- PRIVATE ----------------------------------
std::vector<std::string>	ExecutionManager::_split(std::string const &buf, std::string sep) {

	token_vector vec;
	size_t start = 0;
	size_t end = 0;

	while ((start = buf.find_first_not_of(sep, end)) != std::string::npos) { // size_t npos -> end of string
		end = buf.find(sep, start);
		vec.push_back(buf.substr(start, end - start));
	}
	return vec;
}
//----------------------------------------------------------------------------