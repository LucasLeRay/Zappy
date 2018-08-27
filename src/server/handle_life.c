/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** handle_life by Lucas Le Ray
*/

#include "server.h"

void eat_food(__attribute__((unused))server_t *server, player_t *player)
{
	if (item_list_size(player->inventory, FOOD) > 0) {
		item_list_del_data(&player->inventory, FOOD);
	} else {
		add_msg_send(player, MSG_DEAD);
		player->dead = true;
	}
}

void handle_life(server_t *server)
{
	player_list_t	*list = server->players->next;
	player_t	*p;
	double		life;

	while (list) {
		p = list->data;
		if (p->team) {
			life = (double)((clock() - p->life) / CLOCKS_PER_SEC);
			if (life >= (double)(CYCLE_LIFE / server->freq)) {
				eat_food(server, p);
				p->life = clock();
			}
		}
		list = list->next;
	}
}