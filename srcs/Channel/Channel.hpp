//ifndef

//include
class Channel {

		Channel();
		//canonical form
		~Channel();
		// send_priv_msg(); //??
		broadcast();

	private :
		std::string _name;
		std::string _topic;
		Client *_operator_client; //or operator_fd?? or username??
 
		std::map<std::string client_name, Client *> _members; //client_name or fd or username

};