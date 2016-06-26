##
## Makefile for  in /home/noboud_n/PSU_2015_zappy
## 
## Made by Nyrandone Noboud-Inpeng
## Login   <noboud_n@epitech.net>
## 
## Started on  Sun Jun 26 19:32:40 2016 Nyrandone Noboud-Inpeng
## Last update Sun Jun 26 23:42:49 2016 Jérémy Octeau
##

RM	= rm -rf

all:
	$(MAKE) -C server
	$(MAKE) -C Zappy-SDL2

server:
	$(MAKE) -C server

client:
	$(MAKE) -C Zappy-SDL2

clean:
	$(MAKE) clean -C server
	$(MAKE) clean -C Zappy-SDL2

fclean:
	$(RM) zappy_server
	$(RM) zappy-gfx
	$(MAKE) fclean -C server
	$(MAKE) fclean -C Zappy-SDL2

re:
	$(MAKE) re -C server
	$(MAKE) re -C Zappy-SDL2
