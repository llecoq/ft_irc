#include "Execution.hpp"

Execution::Execution() {}

Execution::~Execution() {}

void Execution::user() {}

void Execution::nick() {}

void Execution::join() {}

void Execution::kick() {}

void Execution::topic() {}

void Execution::invite() {}

void Execution::mode() {}

void Execution::privmsg() {}

void Execution::notice() {}

void Execution::run(Client& client) {

	std::string index[NBR_CMDS];
	index[0] = "USER";
	index[1] = "NICK";
	index[2] = "JOIN";
	index[3] = "KICK";
	index[4] = "TOPIC";
	index[5] = "INVITE";
	index[6] = "MODE";
	index[7] = "PRIVMSG";
	index[8] = "NOTICE";

	std::string buffer = client.get_str_buf();
	int i = -1;
	while (i < NBR_CMDS && index[i] != buffer)
		++i;

	// gestion if buff only \n

	if (i == NBR_CMDS) {
		if (buffer.empty()) {
			printf("empty buffer\n"); // havent thought about what I sould do in this case yet
										// maybe run should return a code :
										// 	0 an exec command was run, everything went smoothly
										// 	1 the buffer was empty we have to went fir the next pull
			return ;
		}
		printf("421 %s %s :Unknown command\n", (client.get_nickname().c_str()), (get_first_word(buffer)).c_str());
		exit(-1);
	}

	void (Execution::*_cmd_exec[NBR_CMDS])(void);
	_cmd_exec[0] = &Execution::user;
	_cmd_exec[1] = &Execution::nick;
	_cmd_exec[3] = &Execution::join;
	_cmd_exec[4] = &Execution::kick;
	_cmd_exec[5] = &Execution::topic;
	_cmd_exec[6] = &Execution::invite;
	_cmd_exec[7] = &Execution::privmsg;
	_cmd_exec[8] = &Execution::notice;

	// gestion mutli Execution

	if (i && i < NBR_CMDS)
		(this->*_cmd_exec[i])();
}