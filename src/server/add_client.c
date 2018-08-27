/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** add_client by Lucas Le Ray
*/

#include "server.h"

void delete_player(server_t *server, player_list_t **p)
{
	(*p)->data->team->nb_players--;
	player_list_del_data(&(*p)->data->case_on->players, (*p)->data, false);
	player_list_del_data(&server->players, (*p)->data, true);
	*p = server->players;
}

int accept_client(server_t *server)
{
	struct sockaddr_in	addr_in;
	struct sockaddr		*addr = (struct sockaddr *)&addr_in;
	socklen_t		addr_len = sizeof(addr_in);
	int			fd;

	fd = accept(server->network->fd_server, addr, &addr_len);
	if (fd < 0)
		error_msg(strerror(errno));
	return (fd);
}

void create_new_player(server_t *server, int fd)
{
	player_t	*player = malloc(sizeof(player_t));

	player->id = server->id_p;
	server->id_p++;
	player->case_on = NULL;
	player->team = NULL;
	player->direction = NO_DIR;
	player->level = 1;
	player->inventory = item_list_new(NONE);
	player->fd = fd;
	player->dead = false;
	player->disconnected = false;
	player->command = NULL;
	rb_init(&(player->msg_get), 0);
	rb_init(&(player->msg_send), 0);
	player_list_push(server->players, player);
	add_msg_send(player, MSG_WELCOME);
}

bool add_client(server_t *server)
{
	int	fd_client = accept_client(server);

	if (fd_client == -1)
		return (false);
	if (server->network->fd_graphical == -1) {
		server->network->fd_graphical = fd_client;
	} else {
		create_new_player(server, fd_client);
	}
	return (true);
}
