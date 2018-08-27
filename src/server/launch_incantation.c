/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** launch_incantation by Lucas Le Ray
*/

#include "server.h"

static const struct incantation_s INCANTATIONS[] = {
	{ 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 2, 2, 1, 1, 1, 0, 0, 0 },
	{ 3, 2, 2, 0, 1, 0, 2, 0 },
	{ 4, 4, 1, 1, 2, 0, 1, 0 },
	{ 5, 4, 1, 2, 1, 3, 0, 0 },
	{ 6, 6, 1, 2, 3, 0, 1, 0 },
	{ 7, 6, 2, 2, 2, 2, 2, 0 }
};

int check_case_incantation(item_list_t *list, player_t *p)
{
	struct incantation_s	i = INCANTATIONS[p->level - 1];

	if (item_list_size(list, LINEMATE) >= i.linemate * i.nb_players
	&& item_list_size(list, DERAUMERE) >= i.deraumere * i.nb_players
	&& item_list_size(list, SIBUR) >= i.sibur * i.nb_players
	&& item_list_size(list, MENDIANE) >= i.mendiane * i.nb_players
	&& item_list_size(list, PHIRAS) >= i.phiras * i.nb_players
	&& item_list_size(list, THYSTAME) >= i.thystame * i.nb_players)
		return (1);
	return (0);
}

void add_cmd_incantation(player_t *player, bool work)
{
	player->command = malloc(sizeof(command_t));
	if (work) {
		add_msg_send(player, MSG_LAUNCH_INC);
		player->command->cmd = strdup("Incantation");
	} else {
		add_msg_send(player, MSG_KO);
		player->command->cmd = strdup("Fail Incantation");
	}
	player->command->exec = incantation;
	player->command->cycle = 300;
	player->command->start = clock();
}

void delete_items_incantation(player_t *player)
{
	case_t			*c = player->case_on;
	struct incantation_s	i = INCANTATIONS[player->level - 1];

	for (int j = 0; j < i.thystame; j++)
		item_list_del_data(&c->items, THYSTAME);
	for (int j = 0; j < i.phiras; j++)
		item_list_del_data(&c->items, PHIRAS);
	for (int j = 0; j < i.mendiane; j++)
		item_list_del_data(&c->items, MENDIANE);
	for (int j = 0; j < i.sibur; j++)
		item_list_del_data(&c->items, SIBUR);
	for (int j = 0; j < i.deraumere; j++)
		item_list_del_data(&c->items, DERAUMERE);
	for (int j = 0; j < i.linemate; j++)
		item_list_del_data(&c->items, LINEMATE);
}

void choose_incantation(player_t *player)
{
	player_list_t	*p = player->case_on->players;
	int		nb = 0;

	while ((p = p->next))
		if (p->data->team == player->team) {
			add_cmd_incantation(p->data, true);
			nb++;
		}
	p = player->case_on->players;
	while (nb < INCANTATIONS[player->level - 1].nb_players
		&& (p = p->next)) {
		add_cmd_incantation(p->data, true);
		nb++;
	}
	delete_items_incantation(player);
}

void launch_incantation(player_t *player)
{
	player_list_t	*p = player->case_on->players;
	int		tot = 0;

	if (player->level >= 8) {
		add_msg_send(player, MSG_KO);
		return;
	}
	while ((p = p->next))
		if (p->data->level == player->level)
			tot++;
	if (tot >= INCANTATIONS[player->level - 1].nb_players
		&& check_case_incantation(player->case_on->items, player)) {
		choose_incantation(player);
	} else {
		add_cmd_incantation(player, false);
	}
}