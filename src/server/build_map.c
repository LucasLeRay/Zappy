/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** build_map by Lucas Le Ray
*/

#include "server.h"

void pop_item(server_t *server, int y, int x, float item_pop)
{
	if (item_list_size_all(server->map[y][x]->items) > 9)
		return;
	while (item_pop >= 1) {
		item_list_push(server->map[y][x]->items,
			(item_e)rand() % 6 + 1);
		item_pop--;
	}
	if (rand() % 100 < item_pop * 100) {
		item_list_push(server->map[y][x]->items,
			(item_e)rand() % 6 + 1);
	}
}

void pop_food(server_t *server, int y, int x, float food_pop)
{
	if (item_list_size(server->map[y][x]->items, FOOD) > 2)
		return;
	while (food_pop >= 1) {
		item_list_push(server->map[y][x]->items, FOOD);
		food_pop--;
	}
	if (rand() % 100 < food_pop * 100) {
		item_list_push(server->map[y][x]->items, FOOD);
	}
}

void build_case(server_t *server, int y, int x)
{
	float	item_pop = (float)(rand() % ((int)(100 * DENSITY_ITEM)))
				/ 100;
	float	food_pop = (float)(rand() % ((int)(100 * DENSITY_FOOD)))
				/ 100;

	server->map[y][x] = malloc(sizeof(case_t));
	server->map[y][x]->items = item_list_new(NONE);
	server->map[y][x]->players = player_list_new(NULL);
	pop_item(server, y, x, item_pop);
	pop_food(server, y, x, food_pop);
}

void upload_items(server_t *server)
{
	int	y;
	int	x;
	float	item_pop = (float)(rand() % ((int)(100 * ITEM_POPING)))
				/ 100;
	float	food_pop = (float)(rand() % ((int)(100 * FOOD_POPING)))
				/ 100;
	double	cycle = (double) ((clock() - server->item_poping)
					/ CLOCKS_PER_SEC);

	if (cycle < (double)(POPING_CYCLE / server->freq))
		return;
	server->item_poping = clock();
	for (y = 0; y < server->height; y++) {
		for (x = 0; x < server->width; x++) {
			pop_item(server, y, x, item_pop);
			pop_food(server, y, x, food_pop);
		}
	}
}

void build_map(server_t *server)
{
	int	y;
	int	x;

	server->map = malloc(sizeof(case_t *) * (server->height + 1));
	for (y = 0; y < server->height; y++) {
		server->map[y] = malloc(sizeof(case_t) * (server->width + 1));
		for (x = 0; x < server->width; x++)
			build_case(server, y, x);
		server->map[y][server->width] = NULL;
	}
	server->map[server->height] = NULL;
}
