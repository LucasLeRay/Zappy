/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server by Lucas Le Ray
*/

#ifndef ZAPPY_SERVER_H
# define ZAPPY_SERVER_H

# include "zappy.h"
# include "ring_buffer.h"

# define MAX_CLIENTS	4096
# define READ_SIZE	4095
# define CYCLE_LIFE	126
# define CYCLE_INCUB	600

# define DENSITY_ITEM	5.0
# define DENSITY_FOOD	1.0
# define ITEM_POPING	0.1
# define FOOD_POPING	0.05

# define POPING_CYCLE	40

# define COOLDOWN_MAP	1

# define ABS(x)		(x < 0 ? -x : x)

# define MSG_WELCOME	strdup("WELCOME\n")
# define MSG_KO		strdup("ko\n")
# define MSG_OK		strdup("ok\n")
# define MSG_DEAD	strdup("dead\n")
# define MSG_LAUNCH_INC	strdup("Elevation underway\n")

typedef struct server_s server_t;
typedef struct network_s network_t;
typedef enum dir_e dir_e;
typedef enum item_e item_e;
typedef enum param_e param_e;
typedef struct case_s case_t;
typedef struct team_s team_t;
typedef struct player_s player_t;
typedef struct item_list_s item_list_t;
typedef struct player_list_s player_list_t;
typedef struct param_s param_t;
typedef struct command_s command_t;
typedef struct incantantion_s incantation_t;
typedef struct egg_s egg_t;
typedef struct egg_list_s egg_list_t;
typedef struct vector_s vector_t;
typedef struct orientation_s orientation_t;
typedef bool (*add_param)(void *param, char **av);
typedef void (*exec_cmd)(server_t *server, player_t *player, char *cmd);
typedef void (*check_cmd)(server_t *server, player_t *player, char *cmd);

enum item_e {
	FOOD,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	EGG,
	NONE
};

enum dir_e {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NO_DIR
};

struct orientation_s {
	dir_e	dir;
	int	up_left;
	int	up_center;
	int	up_right;
	int	down_left;
	int	down_center;
	int 	down_right;
	int	center_left;
	int	center_right;
};

struct vector_s {
	int	x;
	int	y;
};

struct egg_list_s {
	egg_t		*data;
	egg_list_t	*next;
};

struct egg_s {
	clock_t		incubation;
	team_t		*team;
	case_t		*c;
};

struct incantation_s {
	int		level;
	int		nb_players;
	int		linemate;
	int		deraumere;
	int		sibur;
	int		mendiane;
	int		phiras;
	int		thystame;
};

struct command_s {
	char		*cmd;
	exec_cmd	exec;
	int		cycle;
	clock_t		start;
};

struct param_s {
	char		*specifier;
	add_param	add_new_param;
	char		*name;
	char		*usage;
	int		offset;
};

struct item_list_s {
	item_list_t	*next;
	item_e		data;
};

struct player_list_s {
	player_list_t	*next;
	player_t	*data;
};

struct team_s {
	char		*name;
	int		max_players;
	int		nb_players;
};

struct case_s {
	player_list_t	*players;
	item_list_t	*items;
};

struct player_s {
	int		id;
	case_t		*case_on;
	team_t		*team;
	dir_e		direction;
	int		level;
	item_list_t	*inventory;
	int		fd;
	rb_t		msg_send;
	rb_t		msg_get;
	bool		dead;
	command_t	*command;
	int		x;
	int		y;
	bool		disconnected;
	clock_t		life;
	int		forward;
};

struct network_s {
	int		fd_server;
	int		fd_graphical;
	fd_set		read_fds;
	fd_set		write_fds;
	struct timeval	timeout;
};

struct server_s {
	int		port;
	int		freq;
	int		clients_nb;
	int		height;
	int		width;
	char 		*end;
	int		id_p;
	network_t	*network;
	team_t		**teams;
	case_t		***map;
	player_list_t	*players;
	egg_list_t	*eggs;
	clock_t		item_poping;
	clock_t		map_send;
};

/*	main.c		*/
void	display_usage(char *executable_name);

/*	server.c	*/
int	launch_server(server_t *server);

/*	get_params.c	*/
bool	get_params(server_t *server, int ac, char **av);
bool	add_param_int(int *param, char **av);
bool	add_param_team(team_t ***param, char **av);

/*	free_server.c	*/
void	free_server(server_t *server);

/*	build_map.c	*/
void	upload_items(server_t *server);
void	build_map(server_t *server);

/*	player_list.c	*/
player_list_t	*player_list_new(player_t *data);
void		player_list_push(player_list_t *player_list,
			player_t *data);
void		player_list_clear(player_list_t *player_list, bool free_p);
void		player_list_del_data(player_list_t **player_list,
			player_t *data, bool free_p);
int		player_list_size_all(player_list_t *player_list);

/*	egg_list.c	*/
egg_list_t	*egg_list_new(egg_t *data);
void		egg_list_push(egg_list_t *egg_list, egg_t *data);
void		egg_list_clear(egg_list_t *egg_list, bool free_p);
void		egg_list_del_data(egg_list_t **egg_list,
					egg_t *data, bool free_p);
int		egg_list_size_all(egg_list_t *egg_list);

/*	item_list.c	*/
item_list_t	*item_list_new(item_e data);
void		item_list_push(item_list_t *item_list, item_e data);
void		item_list_clear(item_list_t *item_list);
void		item_list_del_data(item_list_t **item_list, item_e data);

/*	item_list2.c	*/
int		item_list_size(item_list_t *item_list, item_e data);
int		item_list_size_all(item_list_t *item_list);

/*	init_server.c	*/
bool	init_server(server_t *server);

/*	select.c	*/
void	fill_fd_select(server_t *server);
bool	select_fd(server_t *server);
void	check_fd_select(server_t *server);

/*	error.c		*/
bool	error_msg(char *message);

/*	add_client.c	*/
bool	add_client(server_t *server);
void	delete_player(server_t *server, player_list_t **p);

/*	send_message.c	*/
void	send_message(server_t *server, player_list_t **p);

/*	str_concat.c	*/
char	*str_sconcat(const char *a, const char *b, size_t sa, size_t sb);
char	*str_concat_free(char *a, char *b);

/*	add_msg.c	*/
void	add_msg_get(player_t *player);
void	add_msg_send(player_t *player, char *msg);

/*	str_to_tab.c	*/
char	**str_to_tab(char *str, char *delims);
void	free_tab(char **tab);

/*	handle_cmd.c	*/
void	handle_cmd(server_t *server);

/*	get_item.c	*/
char	*get_item_name(item_e item);
char	*item_list_to_string(item_list_t *list);

/*	handle_life.c	*/
void	handle_life(server_t *server);

/*	send_map.c	*/
void	send_map(server_t *server);

/*	launch_incantation	*/
void	launch_incantation(player_t *player);

/*	handle_eggs.c		*/
void	handle_eggs(server_t *server);

/*	end_graphical.c		*/
void	end_graphical(server_t *server);

/*	check_cmd_param.c	*/
bool	check_cmd_param(player_t *player, char *cmd, int nb);

/*	write_egg.c		*/
void	print_egg(egg_list_t *eggs, case_t *c, char **tmp);

/*	cmd/cmd_join_team.c	*/
void	join_team(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_turn.c	*/
void	turn_right(server_t *server, player_t *player, char *cmd);
void	turn_left(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_forward.c	*/
void	move_player(server_t *server, player_t *player, int y, int x);
void	move_forward(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_look.c	*/
void	look_around(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_connect_nbr.c */
void	connect_nbr(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_inventory.c	*/
void	inventory(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_eject.c		*/
void	eject_player(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_object.c	*/
void	take_object(server_t *server, player_t *player, char *cmd);
void	set_object(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_incantation.c	*/
void	incantation(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_fork.c		*/
void	fork_player(server_t *server, player_t *player, char *cmd);

/*	cmd/cmd_broadcast.c	*/
void	broadcast_message(server_t *server, player_t *from, char *cmd);

#endif //ZAPPY_SERVER_H
