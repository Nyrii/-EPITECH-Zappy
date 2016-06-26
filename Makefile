##
## Makefile for  in /home/noboud_n/PSU_2015_zappy
## 
## Made by Nyrandone Noboud-Inpeng
## Login   <noboud_n@epitech.net>
## 
## Started on  Sun Jun 26 19:32:40 2016 Nyrandone Noboud-Inpeng
## Last update Sun Jun 26 19:43:19 2016 Nyrandone Noboud-Inpeng
##

all: server client

server:
	$(MAKE) -C Network

client:
	$(MAKE) -C Graphical

clean:
	$(MAKE) clean -C Network
	$(MAKE) clean -C Graphical

fclean:
	$(MAKE) fclean -C Network
	$(MAKE) fclean -C Graphical

re:
	$(MAKE) re -C Network
	$(MAKE) re -C Graphical
