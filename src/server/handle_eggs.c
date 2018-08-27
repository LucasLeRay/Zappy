/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** handle_eggs by Lucas Le Ray
*/

#include "server.h"

void pop_egg(server_t *server, egg_t *egg)
{
	egg->team->nb_players++;
	egg_list_del_data(&server->eggs, egg, true);
}

void handle_eggs(server_t *server)
{
	egg_list_t	*eggs = server->eggs;
	double		incubation;

	while ((eggs = eggs->next)) {
		incubation = (double)(clock() - eggs->data->incubation)
			/ CLOCKS_PER_SEC;
		if (incubation >= (double)(CYCLE_INCUB / server->freq))
			pop_egg(server, eggs->data);
	}
}