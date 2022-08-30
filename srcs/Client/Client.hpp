#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Commons.hpp"
// #include "Channel.hpp"

struct s_recv_data {
	char _buf[512]; //512 ? Check if msg is >512 what to do since buffer will already be full
					// const buf non ?
	ssize_t _nbytes;
};

class Client {

	public :
		Client();
		//canonical form
		~Client();
		// send_priv_msg(); //??

	private :
		int _client_fd;
		std::deque<std::string> _pending_priv_msg; // string pending_msg must contain the sender's username //deque or other ? must be FIFO

		// std::map<std::string, Channel*> _joined_channels; // std::string channel_name, Channel* channel
		std::string _username;
		std::string _realname;
		std::string _nickname;
		// Parser *_parser;
		s_recv_data _recv_data;

	
	public:
		// getters
		std::string get_str_buf();
		char* get_buf();
		std::string get_nickname();

};

#endif