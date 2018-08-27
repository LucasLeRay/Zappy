/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** init_server by Lucas Le Ray
*/

#include "server.h"

int	get_server_socket(void)
{
	struct protoent		*pe = getprotobyname("TCP");
	int			fd;

	if (!pe)
		return (-1);
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	return (fd);
}

bool	bind_server(int fd, int port)
{
	struct sockaddr_in	s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
		return (false);
	return (true);
}

bool	init_server(server_t *server)
{
	int			fd = get_server_socket();
	network_t		*network = malloc(sizeof(network_t));

	printf("Port : %d\n", server->port);
	if (fd == -1)
		return (error_msg(strerror(errno)));
	if (!bind_server(fd, server->port))
		return (error_msg(strerror(errno)));
	if (listen(fd, MAX_CLIENTS) == -1)
		return (error_msg(strerror(errno)));
	server->id_p = 0;
	network->fd_server = fd;
	network->fd_graphical = -1;
	network->timeout.tv_sec = 0;
	network->timeout.tv_usec = 1 / server->freq;
	server->network = network;
	return (true);
}