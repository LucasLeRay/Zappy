/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_incantation by Lucas Le Ray
*/

#include "server.h"

bool	check_victory(server_t *server, player_t *player)
{
	player_list_t	*players = server->players;
	int		nb = 0;

	while ((players = players->next)) {
		if (players->data->level == 8
		&& players->data->team == player->team)
			nb++;
	}
	if (nb >= 6)
		return (true);
	return (false);
}

void	incantation(__attribute__((unused))server_t *server,
			player_t *player, char *cmd)
{
	char	buff[READ_SIZE + 1];
	char	*tmp = buff;

	if (!check_cmd_param(player, cmd, 1))
		return;
	if (!strcmp(cmd, "Incantation")) {
		player->level++;
		tmp += sprintf(tmp, "Current level: %d", player->level);
		add_msg_send(player, strdup(buff));
	}
	if (check_victory(server, player))
		server->end = player->team->name;
}