##
## Makefile for myirc in /home/wilmot_g/Rendu/PSU_2015_myirc
##
## Made by guillaume wilmot
## Login   <wilmot_g@epitech.net>
##
## Started on  Mon May 16 23:28:34 2016 guillaume wilmot
## Last update Tue Jun  7 16:18:47 2016 Nyrandone Noboud-Inpeng
##

SRCSER	= avance_ia.c		\
	  broadcast_ia.c	\
	  connect_nbr_ia.c	\
	  droite_ia.c		\
	  expulse_ia.c		\
	  fork_ia.c		\
	  free.c		\
	  gauche_ia.c		\
	  get_opt.c		\
	  incantation_ia.c	\
	  init.c		\
	  inventaire_ia.c	\
	  main.c		\
	  pose_ia.c		\
	  prend_ia.c		\
	  process.c		\
	  voir_ia.c

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
	$(CC) -o $(NAMESER) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAMESER)

re: fclean all
