/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_fork by Lucas Le Ray
*/

#include "server.h"

void fork_player(server_t *server, player_t *player, char *cmd)
{
	egg_t	*egg;

	if (!check_cmd_param(player, cmd, 1))
		return;
	egg = malloc(sizeof(egg_t));
	egg->team = player->team;
	egg->c = player->case_on;
	egg->incubation = clock();
	egg_list_push(server->eggs, egg);
	add_msg_send(player, MSG_OK);
}