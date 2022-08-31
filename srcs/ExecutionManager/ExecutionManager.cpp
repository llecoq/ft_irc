#include "ExecutionManager.hpp"
#include "numeric_replies.hpp"

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
//-------------UTILS
std::string	ExecutionManager::_erase_bn_end(std::string const &buf) {
	std::string copy = buf;

	std::string::iterator ite = --(copy.end());
	if (*ite == '\n')
		copy.erase(ite);
	return copy;
}

std::string	ExecutionManager::_erase_space_begin(std::string const &buf) {
	std::string copy = buf;

	int i = 0;
	std::string::const_iterator it = copy.begin();
	if (*it == ' ') {
		while (*it == ' ') {
			++it;
			++i;
		}
		copy.erase(0, i);
	}
	return copy;
}

std::string	ExecutionManager::_get_first_word(std::string const &buf) {
	std::string copy = _erase_space_begin(buf);
	std::string first_word = copy;
	size_t pos_space = copy.find_first_of(" ");
	if (pos_space != std::string::npos)
		first_word.erase(pos_space, std::string::npos);
	first_word = _erase_bn_end(first_word);
	return first_word;
}

std::vector<std::string>	ExecutionManager::_split(std::string const &buf) {

	std::vector<std::string> vec;
	size_t start;
	size_t end = 0;

	while ((start = buf.find_first_not_of(" ", end)) != std::string::npos) { // size_t npos -> end of string
		end = buf.find(" ", start);
		vec.push_back(buf.substr(start, end - start));
	}
	return vec;
}
//-------------

void	ExecutionManager::init_client(int fd, char* ipstr) {
	Client*	new_client = new Client(fd); // delete afterwards
	
	_client_book.insert(fd_client_pair(fd, new_client));
	new_client->set_ipstr(ipstr);
}

void	ExecutionManager::run(Client* client) {

	std::string buffer = client->get_buf();
	token_vector tokens = _split(buffer);
	std::string cmd = _get_first_word(buffer);
	std::cout << "cmd : " << cmd << std::endl;

	if (buffer.empty())
		return ;

	cmd_iterator it = command_book.begin();
	cmd_iterator ite = command_book.end();
	while (it != ite) {
		if (cmd == it->first) {
			(this->*(it->second))(client, tokens);
			break ;
		}
		++it;
	}
	if (it == ite) {
		std::string msg = ERR_UNKNOWNCOMMAND(client->get_nickname(), cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0 );
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
