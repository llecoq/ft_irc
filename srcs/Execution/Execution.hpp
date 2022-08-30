#ifndef EXECUTION_HPP
#define EXECUTION_HPP

#include "Commons.hpp"
#include "Client.hpp"
#include "utilsExecution.hpp"

#define NBR_CMDS 9

class Execution {

	public :
		Execution();
		//canonical form
		~Execution();

		void user();
		void nick();
		void join();
		void kick();
		void topic();
		void invite();
		void mode();
		void privmsg();
		void notice();

		void run(Client& client);

};

#endif