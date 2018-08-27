##
## EPITECH PROJECT, 2018
## PSU_myirc_2017
## File description:
## Makefile by Lucas Le Ray
##

# SRC

#SRC		=
INC		=	-I include
F		=	-W -Wall -Werror -Wextra
FF		=
#LIB		=

# SERVER

NAME_SERVER	=	zappy_server
MAIN_SERVER	=	src/server/main.c
SRC_SERVER	=	src/server/server.c			\
				src/server/get_params.c		\
				src/server/free_server.c	\
				src/server/build_map.c		\
				src/server/item_list.c		\
				src/server/item_list2.c		\
				src/server/player_list.c	\
				src/server/egg_list.c		\
				src/server/init_server.c	\
				src/server/select.c			\
				src/server/add_client.c		\
				src/server/send_message.c	\
				src/server/str_concat.c		\
				src/server/str_to_tab.c		\
				src/server/add_msg.c		\
				src/server/handle_cmd.c		\
				src/server/get_item.c		\
				src/server/handle_life.c	\
				src/server/send_map.c		\
				src/server/handle_eggs.c	\
				src/server/end_graphical.c	\
				src/server/error.c			\
				src/server/write_egg.c		\
				src/server/check_cmd_param.c	\
				src/server/launch_incantation.c		\
				src/server/ring_buffer/deinit.c		\
				src/server/ring_buffer/init.c		\
				src/server/ring_buffer/rb.c			\
				src/server/ring_buffer/rb_extract.c	\
				src/server/ring_buffer/rb_it.c		\
				src/server/ring_buffer/rb_push.c	\
				src/server/cmd/cmd_join_team.c		\
				src/server/cmd/cmd_turn.c			\
				src/server/cmd/cmd_forward.c		\
				src/server/cmd/cmd_look.c			\
				src/server/cmd/cmd_connect_nbr.c	\
				src/server/cmd/cmd_inventory.c		\
				src/server/cmd/cmd_eject.c			\
				src/server/cmd/cmd_object.c			\
				src/server/cmd/cmd_incantation.c	\
				src/server/cmd/cmd_fork.c			\
				src/server/cmd/cmd_broadcast.c

INC_SERVER	=	-I include -I include/server
F_SERVER	=	$(F)
FF_SERVER	=	$(FF)
#LIB_SERVER	=	$(LIB)

# OTHER
GCC		=	gcc

all:			$(NAME_SERVER)

$(NAME_SERVER):		$(MAIN_SERVER:.c=.o) $(SRC_SERVER:.c=.o)
			$(GCC) -o $@ $^

src/server/%.o:		src/server/%.c
			$(GCC) -o $@ $(F_SERVER) $(FF_SERVER) $(INC_SERVER) -c $<

%.o:			%.c
			$(GCC) -o $@ $(F) $(FF) $(INC) -c $<

clean:
			rm -f $(MAIN_SERVER:.c=.o) $(SRC_SERVER:.c=.o)

fclean:			clean
			rm -f $(NAME_SERVER)

re:			fclean all

.PHONY:		all clean fclean re

