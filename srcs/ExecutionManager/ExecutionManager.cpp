#include "ExecutionManager.hpp"

//-------------------------- CONSTRUCTOR/DESTRUCTOR --------------------------
ExecutionManager::ExecutionManager(std::string password) : _password(password) {
	// _intit_command_map() remplir la map de commande
}

ExecutionManager::ExecutionManager( const ExecutionManager & src ) {
	(void)src;
}

ExecutionManager::~ExecutionManager() {
	client_iterator	it;

	for (it = _client_book.begin(); it != _client_book.end(); it++)
		delete it->second;	
}
//----------------------------------------------------------------------------


//--------------------------------- OVERLOAD ---------------------------------
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
std::string erase_space_begin(std::string const &buf) {
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

std::string get_first_word(std::string const &buf) {
	std::string copy = erase_space_begin(buf);
	std::string first_word;
	first_word.append(copy, copy.find_first_of(" "));
	return first_word;
}

std::vector<std::string> split(std::string const &buf) {

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
	Client*	new_client = new Client(fd); // MUST DELETE IT 
	
	_client_book.insert(fd_client_pair(fd, new_client));
	new_client->set_ipstr(ipstr);
}
//----------------------------------------------------------------------------


//--------------------------------- ACCESSORS --------------------------------
Client*	ExecutionManager::get_client(int fd) const {
	return _client_book.find(fd)->second;
}
//----------------------------------------------------------------------------