/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_inventory by Lucas Le Ray
*/

#include "server.h"

void inventory(__attribute__((unused))server_t *server, player_t *player,
		__attribute__((unused))char *cmd)
{
	item_list_t	*tmp = player->inventory->next;
	int		items[7] = {0};
	char		buff[READ_SIZE + 1];
	char		*tmp_buff = buff;

	if (!check_cmd_param(player, cmd, 1))
		return;
	while (tmp) {
		items[(int)tmp->data]++;
		tmp = tmp->next;
	}
	tmp_buff += sprintf(tmp_buff, "[ ");
	for (int i = 0; i < 7; i++) {
		tmp_buff += sprintf(tmp_buff, "%s %d",
				get_item_name((item_e) i), items[i]);
		if (i < 6)
			tmp_buff += sprintf(tmp_buff, ", ");
	}
	tmp_buff += sprintf(tmp_buff, " ]\n");
	add_msg_send(player, strdup(buff));
}