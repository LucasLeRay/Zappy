/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** connect_nbr
*/

#include "server.h"

void connect_nbr(__attribute__((unused))server_t *server, player_t *player,
		__attribute__((unused))char *cmd)
{
	char buff[READ_SIZE];

	if (!check_cmd_param(player, cmd, 1))
		return;
	sprintf(buff, "%d\n",
		player->team->max_players - player->team->nb_players);
	add_msg_send(player, strdup(buff));
}
