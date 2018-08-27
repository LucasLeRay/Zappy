/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_eject by Lucas Le Ray
*/

#include "server.h"

void send_eject_msg(player_t *player, int direction_from)
{
	char	buff[READ_SIZE];

	sprintf(buff, "eject: %d\n", direction_from);
	add_msg_send(player, strdup(buff));
}

void eject_msg(player_t *player, dir_e dir)
{
	switch (player->direction) {
		case (UP):
			send_eject_msg(player, dir == UP ? 5 : dir == DOWN ?
				1 : dir == RIGHT ? 3 : dir == LEFT ? 7 : 0);
			break;
		case (DOWN):
			send_eject_msg(player, dir == UP ? 1 : dir == DOWN ?
				5 : dir == RIGHT ? 7 : dir == LEFT ? 3 : 0);
			break;
		case (LEFT):
			send_eject_msg(player, dir == UP ? 3 : dir == DOWN ?
				7 : dir == RIGHT ? 5 : dir == LEFT ? 1 : 0);
			break;
		case (RIGHT):
			send_eject_msg(player, dir == UP ? 7 : dir == DOWN ?
				3 : dir == RIGHT ? 1 : dir == LEFT ? 5 : 0);
			break;
		default:
			return;
	}
}

void eject_player(server_t *server, player_t *player,
		__attribute__((unused))char *cmd)
{
	player_list_t	*tmp = player->case_on->players->next;
	dir_e		dir = player->direction;

	if (!check_cmd_param(player, cmd, 1))
		return;
	while (tmp) {
		if (tmp->data != player) {
			eject_msg(tmp->data, dir);
			move_player(server, tmp->data,
			dir == UP ? -1 : dir == DOWN ? 1 : 0,
			dir == LEFT ? -1 : dir == RIGHT ? 1 : 0);
			tmp = player->case_on->players->next;
		} else {
			tmp = tmp->next;
		}
	}
	add_msg_send(player, MSG_OK);
}