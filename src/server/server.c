/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server by Lucas Le Ray
*/

#include "server.h"

bool server_loop(server_t *server)
{
	fill_fd_select(server);
	if (!select_fd(server))
		return (false);
	check_fd_select(server);
	handle_cmd(server);
	handle_life(server);
	handle_eggs(server);
	upload_items(server);
	return (true);
}

int launch_server(server_t *server)
{
	srand(time(NULL));
	build_map(server);
	server->players = player_list_new(NULL);
	server->eggs = egg_list_new(NULL);
	if (!init_server(server))
		return (84);
	server->end = NULL;
	while (!server->end) {
		if (!server_loop(server))
			return (84);
	}
	end_graphical(server);
	return (0);
}
