#include "ExecutionManager.hpp"

typedef	std::vector<std::string>										token_vector;
typedef	std::map<std::string, std::string (*)(Client*, token_vector)>	cmd_map;

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
ExecutionManager &ExecutionManager::operator=( ExecutionManager const & rhs ) {
	(void)rhs;
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &operator<<( std::ostream & o, ExecutionManager const & i ) {
	(void)i;
	//o << "Value = " << i.getValue();
	return o;
}
//----------------------------------------------------------------------------


//--------------------------------- METHODS ----------------------------------
//-------------UTILS
std::string _erase_space_begin(std::string const &buf) {
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

std::string _get_first_word(std::string const &buf) {
	std::string copy = _erase_space_begin(buf);
	std::string first_word;
	first_word.append(copy, copy.find_first_of(" "));
	return first_word;
}

std::vector<std::string> _split(std::string const &buf) {

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

void ExecutionManager::init_client(int fd, char* ipstr) {
	Client*	new_client = new Client(fd); // MUST DELETE IT 
	
	_client_book.insert(fd_client_pair(fd, new_client));
	new_client->set_ipstr(ipstr);
}

void run(Client* client) {
	
}
//----------------------------------------------------------------------------


//--------------------------------- ACCESSORS --------------------------------
Client* ExecutionManager::get_client(int fd) const {
	return _client_book.find(fd)->second;
}
//----------------------------------------------------------------------------


//-------------------------------- NON MEMBERS -------------------------------
std::ostream &operator<<(std::ostream & o, ExecutionManager const & i);
//----------------------------------------------------------------------------