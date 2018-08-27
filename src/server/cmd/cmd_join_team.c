/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_join_team by Lucas Le Ray
*/

#include "server.h"

void complete_player(server_t *server, player_t *player, int i)
{
	char	buff[READ_SIZE];

	server->teams[i]->nb_players++;
	player->team = server->teams[i];
	player->x = rand() % server->width;
	player->y = rand() % server->height;
	player->case_on = server->map[player->y][player->x];
	player_list_push(player->case_on->players, player);
	player->direction = (dir_e)(rand() % 4);
	player->life = clock();
	for (int j = 0; j < 10; j++)
		item_list_push(player->inventory, FOOD);
	memset(buff, 0, READ_SIZE);
	sprintf(buff, "%d\n", server->teams[i]->max_players
			- server->teams[i]->nb_players);
	add_msg_send(player, strdup(buff));
	memset(buff, 0, READ_SIZE);
	sprintf(buff, "%d %d\n", server->width, server->height);
	add_msg_send(player, strdup(buff));
}

void join_team(server_t *server, player_t *player, char *cmd)
{
	int	i;

	for (i = 0; server->teams[i]; i++) {
		if (!strcmp(server->teams[i]->name, cmd)
			&& server->teams[i]->nb_players
			< server->teams[i]->max_players) {
			complete_player(server, player, i);
			player->forward = 0;
			return;
		}
	}
	add_msg_send(player, MSG_KO);
}