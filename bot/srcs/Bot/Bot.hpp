#ifndef BOT_HPP
# define BOT_HPP

# include "BotCommons.hpp"

#define BUFFER_SIZE 512
#define FAILED -1

struct t_recv_data
{
	t_recv_data(): nbytes(0) {}

	char 		buf[BUFFER_SIZE];
	ssize_t 	nbytes;
	std::string	input;
};

class Bot
{

	public:

		Bot();
		~Bot();

		void	init_bot(int fd);
		ssize_t	read_data();
		void	process_data();

	private:

		t_recv_data	_data;
		int			_fd;

};

#endif /* ************************************************************* BOT_H */