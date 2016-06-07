//
// Server.hh for  in /home/empoci_k/rendu_tek2/cpp_indie_studio/nekfeu/server
//
// Made by Kévin Empociello
// Login   <empoci_k@epitech.net>
//
// Started on  Wed Apr 27 15:21:29 2016 Kévin Empociello
// Last update Sun Jun  5 08:51:23 2016 nekfeu
//

#ifndef NEKSERVER_H
#define NEKSERVER_H

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

typedef struct	Client {
  sockaddr_in	sin;
  std::string	pseudo;
  int		x;
  int		y;
} Client;

typedef struct		Game {
  std::string		creator;
  int			nbMaxPlayers;
  int			nbPlayers;
  std::vector<int>	map;
  std::string		mapStr;
  std::vector<Client>	players;
} Game;

class NekServer {
private:
  struct timeval	_timeout;
  int			_sock;
  sockaddr_in		_sin;
  struct hostent	*_hostinfo;
  char			_buffer[4096];
  fd_set		_rdfs;
  int			_port;
private:
  std::vector<Client>	_players;
  std::vector<Game>	_maps;
public:
  void		sharePositionToAll(Client, Game, std::string);
  void		sendPositionsToAll();
  void		sendPositions(Client, Game);
  void		notifyAllClients(std::string, Client, Game);
  void		clientJoinGame(sockaddr_in *);
  void		getPosition(sockaddr_in *);
  void		getNewGame(sockaddr_in *);
  std::string   buildGameListString();
  void		sendGameList(sockaddr_in *);
  bool		checkClientExist(sockaddr_in *, std::string);
  void		writeToClient(sockaddr_in *, const char *);
  int		readFromClient(sockaddr_in *);
  void		launch();
  void		init();
  std::string		vectorToStr(std::vector<int>);
  std::vector<int>	strToVector(std::string);
  std::vector<std::string> splitStr(const std::string &, char);
public:
  NekServer(int);
  ~NekServer();
};

#endif //SERVER_H
