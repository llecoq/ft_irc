#include "Server.hpp"

void testExecParsing() {

	Server server = Server();

	Client client;

	(void)client;

	server.exec.run(client);
}

int main() {

	testExecParsing();
}