/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** send_map by Lucas Le Ray
*/

#include "server.h"

char *get_items_map(server_t *server, case_t *c)
{
	char		buff[item_list_size_all(c->items) * 11
				+ egg_list_size_all(server->eggs) * 2 + 1];
	char		*tmp = buff;
	item_list_t	*item = c->items;
	egg_list_t	*eggs = server->eggs;

	if (!item->next)
		return (strdup(""));
	while ((eggs = eggs->next))
		print_egg(eggs, c, &tmp);
	while ((item = item->next)) {
		tmp += sprintf(tmp, "%d", (int)item->data);
		if (item->next || player_list_size_all(c->players) > 0)
			tmp += sprintf(tmp, " ");
	}
	return (strdup(buff));
}

char *player_to_str(player_t *player)
{
	char		buff[READ_SIZE + 1];
	char		*tmp = buff;
	dir_e		d = player->direction;
	char		*s = player->command ?
			player->command->cmd : "NONE";

	tmp += sprintf(tmp, "P(%d:%s:%s:%s)",
		player->id,
		player->team->name,
		!strncmp(s, "Incantation", strlen("Incantation")) ?
		"INCANTATION" :
		!strncmp(s, "Take", strlen("Take")) ? "TAKE" :
		player->forward > 0 ? "FORWARD" :
		player->dead ? "DEAD" :
		"NONE",
		d == UP ? "UP" : d == DOWN ? "DOWN" : d == LEFT ?
		"LEFT" : "RIGHT");
	if (player->forward > 0)
		player->forward--;
	return (strdup(buff));
}

char *get_players_map(case_t *c)
{
	char		buff[(READ_SIZE + 1)
				* player_list_size_all(c->players)];
	char		*tmp = buff;
	player_list_t	*player = c->players->next;
	char		*str;

	if (!player)
		return (strdup(""));
	while (player && player->data) {
		str = player_to_str(player->data);
		tmp += sprintf(tmp, "%s", str);
		free(str);
		if (player->next)
			tmp += sprintf(tmp, " ");
		player = player->next;
	}
	return (strdup(buff));
}

void format_case(server_t *server, case_t *c, char **tmp)
{
	char	*items = get_items_map(server, c);
	char	*players = get_players_map(c);

	*tmp += sprintf(*tmp, "%s%s", items, players);
	free(items);
	free(players);
}

void send_map(server_t *server)
{
	char	buff[server->height * server->width * (READ_SIZE + 1)];
	char	*tmp = buff;
	double	cooldown;

	cooldown = (double)((clock() - server->map_send) / CLOCKS_PER_SEC);
	if (cooldown < (double)(COOLDOWN_MAP))
		return;
	server->map_send = clock();
	tmp += sprintf(tmp, "(%d:%d)[", server->width, server->height);
	for (int y = 0; y < server->height; y++) {
		for (int x = 0; x < server->width; x++) {
			format_case(server, server->map[y][x], &tmp);
			tmp += x < server->width - 1
			|| y < server->height - 1 ? sprintf(tmp, ",") : 0;
		}
	}
	tmp += sprintf(tmp, "]");
	if (write(server->network->fd_graphical, buff, strlen(buff)) == -1) {
		server->network->fd_graphical = -1;
	}
}
