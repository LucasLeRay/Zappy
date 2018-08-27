/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_object by Lucas Le Ray
*/

#include "server.h"

void	take_object(__attribute__((unused))server_t *server,
			player_t *player, char *cmd)
{
	char		**tab = str_to_tab(cmd, " ");
	item_list_t	*items = player->case_on->items->next;
	item_e		data;

	if (!check_cmd_param(player, cmd, 2))
		return;
	while (items) {
		data = items->data;
		if (data < 7 && !strcmp(get_item_name(data), tab[1])) {
			item_list_del_data(&player->case_on->items, data);
			item_list_push(player->inventory, data);
			free_tab(tab);
			add_msg_send(player, MSG_OK);
			return;
		}
		items = items->next;
	}
	add_msg_send(player, MSG_KO);
	free_tab(tab);
}

void	set_object(__attribute__((unused))server_t *server,
			player_t *player, char *cmd)
{
	char		**tab = str_to_tab(cmd, " ");
	item_list_t	*items = player->inventory->next;
	item_e		data;

	if (!check_cmd_param(player, cmd, 2))
		return;
	while (items) {
		data = items->data;
		if (data < 7 && !strcmp(get_item_name(data), tab[1])) {
			item_list_del_data(&player->inventory, data);
			item_list_push(player->case_on->items, data);
			free_tab(tab);
			add_msg_send(player, MSG_OK);
			return;
		}
		items = items->next;
	}
	add_msg_send(player, MSG_KO);
	free_tab(tab);
}