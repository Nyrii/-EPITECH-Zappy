##
## Makefile for myirc in /home/wilmot_g/Rendu/PSU_2015_myirc
##
## Made by guillaume wilmot
## Login   <wilmot_g@epitech.net>
##
## Started on  Mon May 16 23:28:34 2016 guillaume wilmot
## Last update Tue Jun  7 11:39:10 2016 Nyrandone Noboud-Inpeng
##

SRCSER	= main.c

OBJS	=  $(addprefix $(OBJSER), $(SRCSER:.c=.o))

RM	= rm -f

CC	= cc

NAMESER	= server

OBJSER	= obj/
SRCSERD	= src/
INCS	= -I inc/

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
