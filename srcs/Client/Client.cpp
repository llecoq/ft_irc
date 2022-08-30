#include "Client.hpp"

Client::Client()
		: _client_fd(), _pending_priv_msg(), _username(),
			_realname(), _nickname(), _recv_data() {}

Client::~Client() {}

char* Client::get_buf() {
	return _recv_data._buf;
}

std::string Client::get_str_buf() {
	(void)_client_fd;
	return _recv_data._buf;
}

std::string Client::get_nickname() {
	return _nickname;
}