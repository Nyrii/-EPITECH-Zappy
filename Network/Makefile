##
## Makefile for myirc in /home/wilmot_g/Rendu/PSU_2015_myirc
##
## Made by guillaume wilmot
## Login   <wilmot_g@epitech.net>
##
## Started on  Mon May 16 23:28:34 2016 guillaume wilmot
## Last update Sat Jun 18 15:01:09 2016 Nyrandone Noboud-Inpeng
##

SRCSER	= bct.c				\
	broadcast_ia.c			\
	broadcast_init.c		\
	close_all_clients.c		\
	connect_nbr_ia.c		\
	drop_ia.c			\
	elevation.c			\
	expulse_ia.c			\
	epur.c				\
	fork_ia.c			\
	forward_ia.c			\
	free.c				\
	free_all.c			\
	generate_map.c			\
	generic_list.c			\
	generic_list_del.c		\
	get_angle.c			\
	get_opt.c			\
	get_opt_set_delay.c		\
	get_player.c			\
	get_team.c			\
	incantation_ia.c		\
	init.c				\
	init_teams_max_players.c	\
	init_nb_players.c		\
	init_percentages.c		\
	init_perimeter.c		\
	init_resources.c		\
	init_strings_resources.c	\
	inventory_ia.c			\
	left_ia.c			\
	loop.c				\
	main.c				\
	mct.c				\
	msz.c				\
	new_player.c			\
	parse.c				\
	pin.c				\
	plv.c				\
	ppo.c				\
	process.c			\
	remove.c			\
	right_ia.c			\
	save_server.c			\
	see_ia.c			\
	see_ia_calculs.c		\
	see_ia_resources.c		\
	send.c				\
	server_lib.c			\
	sgt.c				\
	socket.c			\
	take_ia.c			\
	tna.c				\
	welcome.c

OBJS	=  $(addprefix $(OBJSER), $(SRCSER:.c=.o))

RM	= rm -f

CC	= cc -g

NAMESER	= zappy_server

OBJSER	= obj/
SRCSERD	= src/
INCS	= -I includes/

CFLAGS	= -W -Wall -Wextra -Werror

$(OBJSER)%.o: $(SRCSERD)%.c
	@mkdir -p $(OBJSER)
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

all:
	@make --no-print-directory $(NAMESER)

$(NAMESER): $(OBJS)
	$(CC) -o $(NAMESER) $(OBJS) -lm

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAMESER)

re: fclean all
