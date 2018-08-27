/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** get_params by Lucas Le Ray
*/

#include "server.h"

static const server_t TMP_SERVER = { -1, -1, -1, -1, -1, false, -1,
				NULL, NULL, NULL, NULL, NULL,
				(clock_t)0, (clock_t)0 };
static const param_t PARAM_SERVER[] = {
	{ "-p", (add_param)add_param_int, "port",
		"is the port number",
		(int)((char *)&TMP_SERVER.port - (char *)&TMP_SERVER)
	},
	{ "-x", (add_param)add_param_int, "width",
		"is the width of the world",
		(int)((char *)&TMP_SERVER.width - (char *)&TMP_SERVER)
	},
	{ "-y", (add_param)add_param_int, "height",
		"is the height of the world",
		(int)((char *)&TMP_SERVER.height - (char *)&TMP_SERVER)
	},
	{ "-c", (add_param)add_param_int, "clientsNb",
		"is the number of authorized clients per team",
		(int)((char *)&TMP_SERVER.clients_nb - (char *)&TMP_SERVER)
	},
	{ "-f", (add_param)add_param_int, "freq",
		"is the reciprocal of time unit for execution of actions",
		(int)((char *)&TMP_SERVER.freq - (char *)&TMP_SERVER)
	},
	{ "-n", (add_param)add_param_team, "nameX",
		"is the name of the team X",
		(int)((char *)&TMP_SERVER.teams - (char *)&TMP_SERVER)
	}
};

bool add_param_int(int *param, char **av)
{
	if (!av || !av[0])
		return (false);
	*param = atoi(av[0]);
	if (*param <= 0)
		return (false);
	return (true);
}

bool add_param_team(team_t ***param, char **av)
{
	int	i = 0;

	while (av && av[i] && av[i][0] != '-')
		i++;
	if (!i)
		return (false);
	*param = malloc(sizeof(team_t *) * (i + 1));
	i = 0;
	while (av[i] && av[i][0] != '-') {
		(*param)[i] = malloc(sizeof(team_t));
		(*param)[i]->name = strdup(av[i]);
		(*param)[i]->nb_players = 0;
		i++;
	}
	(*param)[i] = NULL;
	return (true);
}

bool add_params_server(server_t *server, char **av, int i)
{
	unsigned	j;

	for (j = 0; j < 6; j++) {
		if (!strcmp(av[i], PARAM_SERVER[j].specifier)
		&& !PARAM_SERVER[j].add_new_param(
		(void *)((char *)server + PARAM_SERVER[j].offset),
		&av[i + 1])) {
			dprintf(2, "Invalid %s\n%s\t%s\n",
			PARAM_SERVER[j].name, PARAM_SERVER[j].name,
				PARAM_SERVER[j].usage);
			return (false);
		}
	}
	return (true);
}

void init_params_server(server_t *server)
{
	server->port = 0;
	server->width = 0;
	server->height = 0;
	server->clients_nb = 0;
	server->freq = 100;
	server->teams = NULL;
	server->map = NULL;
	server->players = NULL;
	server->eggs = NULL;
	server->network = NULL;
	server->item_poping = clock();
	server->map_send = clock();
}

bool get_params(server_t *server, int ac, char **av)
{
	int	i;

	init_params_server(server);
	for (i = 0; i < ac; ++i) {
		if (!add_params_server(server, av, i))
			return (false);
	}
	for (i = 0; server->teams && server->teams[i]; i++)
		server->teams[i]->max_players = server->clients_nb;
	if (!server->port
		|| server->width < 10 || server->width > 30
		|| server->height < 10 || server->height > 30
		|| !server->clients_nb
		|| !server->freq
		|| !server->teams) {
		display_usage(av[0]);
		return (false);
	}
	return (true);
}
