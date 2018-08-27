/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_turn by Lucas Le Ray
*/

#include "server.h"

void turn_right(__attribute__((unused))server_t *server, player_t *player,
		__attribute__((unused))char *cmd)
{
	if (!check_cmd_param(player, cmd, 1))
		return;
	player->direction = (dir_e)((player->direction + 1) % 4);
	add_msg_send(player, MSG_OK);
}

void turn_left(__attribute__((unused))server_t *server, player_t *player,
		__attribute__((unused))char *cmd)
{
	if (!check_cmd_param(player, cmd, 1))
		return;
	player->direction = (dir_e)((player->direction - 1) % 4);
	add_msg_send(player, MSG_OK);
}