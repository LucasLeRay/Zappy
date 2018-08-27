/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_forward by Lucas Le Ray
*/

#include "server.h"

void move_player(server_t *server, player_t *player, int y, int x)
{
	player->y = (player->y + y) % server->height;
	player->x = (player->x + x) % server->width;
	if (player->y < 0)
		player->y = server->height + player->y;
	if (player->x < 0)
		player->x = server->width + player->x;
	player->forward++;
	player_list_del_data(&player->case_on->players, player, false);
	player->case_on = server->map[player->y][player->x];
	player_list_push(player->case_on->players, player);
}

void move_forward(server_t *server, player_t *player,
		__attribute__((unused))char *cmd)
{
	if (!check_cmd_param(player, cmd, 1))
		return;
	switch (player->direction) {
		case (UP):
			move_player(server, player, -1, 0);
			break;
		case (RIGHT):
			move_player(server, player, 0, 1);
			break;
		case (DOWN):
			move_player(server, player, 1, 0);
			break;
		case (LEFT):
			move_player(server, player, 0, -1);
			break;
		default:
			add_msg_send(player, MSG_KO);
			return;
	}
	add_msg_send(player, MSG_OK);
}