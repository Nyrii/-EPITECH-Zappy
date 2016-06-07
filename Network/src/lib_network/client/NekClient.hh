//
// Server.hh for  in /home/empoci_k/rendu_tek2/cpp_indie_studio/nekfeu/server
//
// Made by Kévin Empociello
// Login   <empoci_k@epitech.net>
//
// Started on  Wed Apr 27 15:21:29 2016 Kévin Empociello
// Last update Tue Jun  7 15:00:31 2016 nekfeu
//

#ifndef NEKCLIENT_H
#define NEKCLIENT_H

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

class NekClient{
private:
  std::string		_username;
  int			_sock;
  sockaddr_in		_sin;
  struct hostent	*_hostinfo;
  struct timeval	_timeout;
  char			_buffer[4096];
  fd_set		_rdfs;
  int			_port;
  const char	       	*_host;
public:
  void			writeServer(const char *);
  int			readServer();
  void			launch();
  void			init();
  std::string		getIp() const;
  int			getPort() const;
public:
  NekClient(const char *, int);
  ~NekClient();
};

#endif //NEKCLIENT_H
