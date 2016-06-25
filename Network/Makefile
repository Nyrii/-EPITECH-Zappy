##
## Makefile for myirc in /home/wilmot_g/Rendu/PSU_2015_myirc
##
## Made by guillaume wilmot
## Login   <wilmot_g@epitech.net>
##
## Started on  Mon May 16 23:28:34 2016 guillaume wilmot
## Last update Fri Jun 24 16:14:27 2016 Nyrandone Noboud-Inpeng
##

SRCSER	= bct.c				\
	broadcast_ia.c			\
	broadcast_init.c		\
	buffer_manager_push.c		\
	check_and_action.c		\
	circular_buffer.c		\
	close_all_clients.c		\
	connect_nbr_ia.c		\
	create_buffer_manager.c		\
	dead.c				\
	disconnect.c			\
	drop_ia.c			\
	ebo.c				\
	egg.c				\
	eht.c				\
	elevation.c			\
	enw.c				\
	epur.c				\
	expulse_ia.c			\
	fork_ia.c			\
	forward_ia.c			\
	free.c				\
	free_all.c			\
	generate_map.c			\
	generic_list.c			\
	generic_list_del.c		\
	get_angle.c			\
	get_egg.c			\
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
	life.c				\
	loop.c				\
	main.c				\
	mct.c				\
	msz.c				\
	new_player.c			\
	parse.c				\
	pbc.c				\
	pdi.c				\
	pdr.c				\
	pex.c				\
	pfk.c				\
	pgt.c				\
	pic.c				\
	pie.c				\
	pin.c				\
	plv.c				\
	pnw.c				\
	ppo.c				\
	process.c			\
	remove.c			\
	replace_eol.c			\
	right_ia.c			\
	save_server.c			\
	sbp.c				\
	see_ia.c			\
	see_ia_calculs.c		\
	see_ia_resources.c		\
	seg.c				\
	send.c				\
	server_lib.c			\
	sgt.c				\
	socket.c			\
	sst.c				\
	store_answer.c			\
	store_port.c			\
	store_socks.c			\
	suc.c				\
	take_ia.c			\
	task.c				\
	timer.c				\
	tna.c				\
	victory.c			\
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
