//ifndef

//include

struct s_recv_data {
	char _buf[512]; //512 ? Check if msg is >512 what to do since buffer will already be full
	ssize_t _nbytes;
} t_recv_data;

class Client {

		Client();
		//canonical form
		~Client();
		// send_priv_msg(); //??

	private :
		int _client_fd;
		std::deque<std::string pending_msg> _pending_priv_msg; //pending_msg must contain the sender's username //deque or other ? must be FIFO

		std::map<std::string channel_name, Channel *> _joined_channels;
		std::string _username;
		std::string _realname;
		std::string _nickname;
		Parser *_parser;
		t_recv_data _recv_data;

};