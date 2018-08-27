/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** select by Lucas Le Ray
*/

#include "server.h"

int get_biggest_fd(server_t *server)
{
	player_list_t	*tmp = server->players->next;
	int		fd = server->network->fd_server;

	while (tmp) {
		if (tmp->data->fd > fd)
			fd = tmp->data->fd;
		tmp = tmp->next;
	}
	if (server->network->fd_graphical > fd)
		fd = server->network->fd_graphical;
	return (fd);
}

void fill_fd_select(server_t *server)
{
	player_list_t	*tmp = server->players->next;
	fd_set		*r = &(server->network->read_fds);
	fd_set		*w = &(server->network->write_fds);
	network_t	*net = server->network;

	FD_ZERO(r);
	FD_ZERO(w);
	FD_SET(net->fd_server, r);
	if (net->fd_graphical > -1)
		FD_SET(net->fd_graphical, w);
	while (tmp) {
		FD_SET(tmp->data->fd, r);
		if (rb_size(&(tmp->data->msg_send)) > 0)
			FD_SET(tmp->data->fd, w);
		tmp = tmp->next;
	}
}

bool select_fd(server_t *server)
{
	int		fd_max = get_biggest_fd(server);
	fd_set		*r = &(server->network->read_fds);
	fd_set		*w = &(server->network->write_fds);
	struct timeval	*timeout = &(server->network->timeout);

	if (select(fd_max + 1, r, w, NULL, timeout) == -1)
		return (error_msg(strerror(errno)));
	return (true);
}

void check_fd_select(server_t *server)
{
	network_t	*net = server->network;
	player_list_t	*tmp = server->players->next;

	if (FD_ISSET(net->fd_server, &(net->read_fds))) {
		add_client(server);
	}
	if (net->fd_graphical != -1
		&& FD_ISSET(net->fd_graphical, &(net->write_fds))) {
		send_map(server);
	}
	while (tmp) {
		if (FD_ISSET(tmp->data->fd, &(net->read_fds)))
			add_msg_get(tmp->data);
		if (rb_size(&(tmp->data->msg_send)) > 0
		&& FD_ISSET(tmp->data->fd, &(net->write_fds))) {
			send_message(server, &tmp);
		}
		tmp = tmp->next;
	}
}