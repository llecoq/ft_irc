#include "Server.hpp"

Server::Server()
		: _pollfd(), _client_book() , _channel_book() {}

Server::~Server() {}

void Server::run() {}

void Server::function_that_adds_client() {}

Client &Server::function_that_does_receive() {return *(_client_book.begin()->second);}
