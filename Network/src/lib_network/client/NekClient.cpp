//
// Server.cpp for  in /home/empoci_k/rendu_tek2/cpp_indie_studio/nekfeu/server
//
// Made by Kévin Empociello
// Login   <empoci_k@epitech.net>
//
// Started on  Wed Apr 27 15:16:50 2016 Kévin Empociello
// Last update Tue Jun  7 14:57:17 2016 nekfeu
//

#include "NekClient.hh"

std::string NekClient::getIp() const {
  return std::string(_host);
}

int	NekClient::getPort() const {
  return _port;
}

void NekClient::writeServer(const char *buffer) {
  printf("## [%s] sent ##\n", buffer);
  if (sendto(_sock, buffer, strlen(buffer), 0, (sockaddr *) &_sin, sizeof _sin) < 0) {
    perror("sendto()");
    exit(errno);
  }
}

int NekClient::readServer() {
  int n = 0;
  unsigned int sinsize = sizeof _sin;

  if((n = recvfrom(_sock, _buffer, 4096 - 1, 0, (sockaddr *) &_sin, &sinsize)) < 0)
    {
      perror("recvfrom()");
      exit(errno);
    }
  _buffer[n] = 0;
  return n;
}

void	NekClient::launch() {
  std::cout << "Client listening..." << std::endl;
  while (1) {
    _timeout.tv_sec = 1;
    _timeout.tv_usec = 0;
    FD_ZERO(&_rdfs);
    FD_SET(_sock, &_rdfs);
    if (select(_sock + 1, &_rdfs, NULL, NULL, &_timeout) == -1) {
      perror("select()");
      exit(errno);
    }
    if (FD_ISSET(_sock, &_rdfs)) {
      if (readServer() == 0) {
        /* server down */
        printf("Server disconnected !\n");
        break;
      }
      /* Buffer non circulaire */
      puts(_buffer);
    }
  }
}

void	NekClient::init() {
  _sock = socket(AF_INET, SOCK_STREAM, 0);
  if (_sock == -1) {
    perror("socket()");
    exit(errno);
  }
  if ((_hostinfo = gethostbyname(_host)) == NULL) {
    fprintf (stderr, "Unknown host %s.\n", _host);
    exit(EXIT_FAILURE);
  }
  _sin.sin_addr = *(in_addr *) _hostinfo->h_addr;
  _sin.sin_port = htons(_port);
  _sin.sin_family = AF_INET;
  _timeout.tv_sec = 1;
  _timeout.tv_usec = 0;
  if ((connect(_sock, (struct sockaddr *) &_sin, sizeof(struct sockaddr))) == -1)
    exit(errno);
  printf("Client connected\n");
}

NekClient::NekClient(const char *host, int port) {
  _port = port;
  _host = host;
  _x = 0;
  _y = 0;
}

NekClient::~NekClient() {
}
