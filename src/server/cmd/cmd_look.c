/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_look by Lucas Le Ray
*/

#include "server.h"

case_t *check_case_look(server_t *server, int y, int x)
{
	if (y < 0)
		y = server->height + y;
	if (x < 0)
		x = server->height + x;
	return (server->map[y % server->height][x % server->width]);
}

case_t *find_case(server_t *server, player_t *player, int i, int j)
{
	switch (player->direction) {
		case (UP):
			return (check_case_look(server,
				player->y - i, player->x + j));
		case (RIGHT):
			return (check_case_look(server,
				player->y + j, player->x + i));
		case (DOWN):
			return (check_case_look(server,
				player->y + i, player->x - j));
		case (LEFT):
			return (check_case_look(server,
				player->y - j, player->x - i));
		default:
			return (NULL);
	}
}

int find_nb_players(case_t *c)
{
	player_list_t	*tmp = c->players->next;
	int		nb = 0;

	while (tmp) {
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}

char *get_case_content(case_t *c, int nb_players)
{
	char		buff[READ_SIZE];
	char		*tmp = buff;
	int		i;
	char		*item_list;

	for (i = 0; i < nb_players; i++) {
		tmp += sprintf(tmp, "player");
		if (i < nb_players - 1)
			tmp += sprintf(tmp, " ");
	}
	item_list = item_list_to_string(c->items);
	if (nb_players == 0 && !item_list)
		return (strdup(""));
	if (item_list) {
		if (nb_players > 0)
			tmp += sprintf(tmp, " ");
		tmp += sprintf(tmp, "%s", item_list);
		free(item_list);
	}
	return (strdup(buff));
}

void look_around(server_t *server, player_t *player,
		__attribute__((unused))char *cmd)
{
	char	buff[READ_SIZE * 81];
	char	*items = buff;
	case_t	*c;
	int	nb_players;
	char	*case_content;

	if (!check_cmd_param(player, cmd, 1))
		return;
	items += sprintf(items, "[ ");
	for (int i = 0; i <= player->level; i++) {
		for (int j = 0; j < (2 * i) + 1; j++) {
			c = find_case(server, player, i, j - i);
			nb_players = find_nb_players(c);
			case_content = get_case_content(c, nb_players);
			items += sprintf(items, "%s, ", case_content);
			free(case_content);
		}
	}
	items += sprintf(items, "]\n");
	add_msg_send(player, strdup(buff));
}