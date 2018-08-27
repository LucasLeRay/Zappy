/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** free_server by Lucas Le Ray
*/

#include "server.h"

void free_teams(team_t **teams)
{
	int	i;

	if (!teams)
		return;
	for (i = 0; teams[i] ; i++) {
		free(teams[i]->name);
		free(teams[i]);
	}
	free(teams);
}

void free_map(server_t *server)
{
	int	y;
	int	x;

	if (!server->map)
		return;
	for (y = 0; y < server->height; y++) {
		for (x = 0; x < server->width; x++) {
			player_list_clear(server->map[y][x]->players, false);
			item_list_clear(server->map[y][x]->items);
			free(server->map[y][x]->players);
			free(server->map[y][x]->items);
			free(server->map[y][x]);
		}
		free(server->map[y]);
	}
	free(server->map);
}

void free_server(server_t *server)
{
	free_teams(server->teams);
	free_map(server);
	if (server->players) {
		player_list_clear(server->players, true);
		free(server->players);
	}
	if (server->eggs) {
		egg_list_clear(server->eggs, true);
		free(server->eggs);
	}
	if (server->network)
		free(server->network);
}