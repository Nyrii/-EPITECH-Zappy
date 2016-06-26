##
## Makefile for  in /home/noboud_n/PSU_2015_zappy
## 
## Made by Nyrandone Noboud-Inpeng
## Login   <noboud_n@epitech.net>
## 
## Started on  Sun Jun 26 19:32:40 2016 Nyrandone Noboud-Inpeng
## Last update Sun Jun 26 19:50:46 2016 Nyrandone Noboud-Inpeng
##

RM	= rm -rf

all: server client

server:
	$(MAKE) -C Network

client:
	$(MAKE) -C Graphical

clean:
	$(MAKE) clean -C Network
	$(MAKE) clean -C Graphical

fclean:
	$(RM) zappy_server
	$(MAKE) fclean -C Network
	$(MAKE) fclean -C Graphical

# $(RM) zappy_ai

re:
	$(MAKE) re -C Network
	$(MAKE) re -C Graphical
