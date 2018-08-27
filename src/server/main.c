/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** main by Lucas Le Ray
*/

#include "server.h"

void display_usage(char *executable_name)
{
	printf("USAGE:\t%s -p port -x width -y height ", executable_name);
	printf("-n name1 name2 ... -c clientsNb -f freq\n");
	printf("\tport\t\tis the port number\n");
	printf("\twidth\t\tis the width of the world\n");
	printf("\theight\t\tis the height of the world\n");
	printf("\tameX\t\tis the name of the team X\n");
	printf("\tclientsNb\tis the number of authorized clients per team\n");
	printf("\tfreq\t\tis the reciprocal of time unit for execution of ");
	printf("actions\n");
}

int main(int ac, char **av)
{
	server_t	server;

	signal(SIGPIPE, SIG_IGN);
	if (av && av[0] && av[1] && !strcmp("-help", av[1])) {
		display_usage(av[0]);
		return (0);
	} else if (!get_params(&server, ac, av)) {
		free_server(&server);
		return (84);
	} else {
		launch_server(&server);
		free_server(&server);
		return (0);
	}
}