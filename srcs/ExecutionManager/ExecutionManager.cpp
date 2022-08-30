#include "ExecutionManager.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ExecutionManager::ExecutionManager(std::string password)
:
	_password(password)
{
	// _intit_command_map() remplir la map de commande
}

ExecutionManager::ExecutionManager( const ExecutionManager & src )
{
	(void)src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ExecutionManager::~ExecutionManager()
{
	client_iterator	it;

	for (it = _client_book.begin(); it != _client_book.end(); it++)
		delete it->second;	
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ExecutionManager &				ExecutionManager::operator=( ExecutionManager const & rhs )
{
	(void)rhs;
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, ExecutionManager const & i )
{
	(void)i;
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


void	ExecutionManager::init_client(int fd, char* ipstr)
{
	Client*	new_client = new Client(fd); // MUST DELETE IT 
	
	_client_book.insert(fd_client_pair(fd, new_client));
	new_client->set_ipstr(ipstr);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


Client*	ExecutionManager::get_client(int fd) const
{
	return _client_book.find(fd)->second;
}

/* ************************************************************************** */