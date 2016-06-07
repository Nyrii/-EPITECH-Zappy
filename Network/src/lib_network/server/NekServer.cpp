//
// Server.cpp for  in /home/empoci_k/rendu_tek2/cpp_indie_studio/nekfeu/server
//
// Made by Kévin Empociello
// Login   <empoci_k@epitech.net>
//
// Started on  Wed Apr 27 15:16:50 2016 Kévin Empociello
// Last update Sun Jun  5 21:23:29 2016 nekfeu
//

#include "NekServer.hh"

std::string			NekServer::vectorToStr(std::vector<int> map) {
  std::string			tmp;

  for (unsigned int i = 0 ; i < map.size() ; i++) {
    tmp.push_back(map[i] + '0');
  }
  return tmp;
}

std::vector<int>		NekServer::strToVector(std::string str) {
  std::vector<int>		tmp;

  for (unsigned int i = 0; i < str.size() ; i++) {
    tmp.push_back(str[i] - '0');
  }
  return tmp;
}

std::vector<std::string>        NekServer::splitStr(const std::string &str, char sep) {
  std::stringstream             ss(str);
  std::string                   word;
  std::vector<std::string>      words;

  while (std::getline(ss, word, sep))
    words.push_back(word);
  return words;
}

std::string	NekServer::buildGameListString() {
  std::string	build;

  build += "/l";
  for (unsigned int i = 0 ; i < _maps.size() ; i++) {
    build += _maps[i].creator;
    build += ';';
    build += std::to_string(_maps[i].players.size());
    build += ';';
    build += std::to_string(_maps[i].nbMaxPlayers);
    build += ';';
    for (unsigned int j = 0 ; j < _maps[i].map.size() ; j++) {
      build += std::to_string(_maps[i].map[j]);
    }
    if (i + 1 < _maps.size())
      build += '\n';
  }
  if (_maps.size() == 0)
    build += "No games";
  return build;
}

bool		NekServer::checkClientExist(sockaddr_in *csin, std::string name) {
  for (unsigned int i = 0 ; i < _players.size() ; i++) {
    if(_players[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
       && _players[i].sin.sin_port == csin->sin_port)
      return true;
    else if (_players[i].pseudo == name)
      return true;
  }
  return false;
}

void		NekServer::writeToClient(sockaddr_in *sin, const char *buffer) {
  if (sendto(_sock, buffer, strlen(buffer), 0, (sockaddr *) sin, sizeof *sin) < 0) {
    perror("send()");
    exit(errno);
  }
  printf("### [%s] ### sent\n", buffer);
}

void		NekServer::getNewGame(sockaddr_in *sin) {
  // BLOQUER SI USERNAME DEJA CREER UNE GAME
  std::string	newGameStr = std::string(&_buffer[2]);
  std::vector<std::string> body = splitStr(newGameStr, ';');
  std::vector<Client>	init;

  Game newGame = {body[0], std::stoi(body[1]), 1, strToVector(body[2]), "", init};

  /* DEBUG */
  std::cout << "New Game by " << newGame.creator << " - Players :  "<< newGame.nbPlayers << "/" << newGame.nbMaxPlayers << std::endl;
  std::cout << "Map - [";
  for (unsigned int i = 0; i < newGame.map.size() ; i++) {
    std::cout << newGame.map[i];
  }
  std::cout << "]" << std::endl;
  /* DEBUG END */

  Client newCl = { *sin, newGame.creator, 0, 0 };
  newGame.players.push_back(newCl);


  _maps.push_back(newGame);
  std::cout << "Game created" << std::endl;
}

void		NekServer::sendGameList(sockaddr_in *sin) {
  std::string	map;

  map = buildGameListString();
  writeToClient(sin, map.c_str());
}

int		NekServer::readFromClient(sockaddr_in *sin) {
  int		n = 0;
  unsigned int	sinsize = sizeof *sin;

  if ((n = recvfrom(_sock, _buffer, 4096 - 1, 0, (sockaddr *) sin, &sinsize)) < 0) {
    perror("recvfrom()");
    exit(errno);
  }

  _buffer[n] = '\0';
  return n;
}

void				NekServer::notifyAllClients(std::string str, Client newCl, Game game) {
  for (unsigned int i = 0 ; i < game.players.size() ; i++) {
    if (game.players[i].pseudo != newCl.pseudo && game.players[i].pseudo != game.creator)
      writeToClient(&game.players[i].sin, std::string(str + newCl.pseudo + ";" + std::to_string(newCl.x) + ";" + std::to_string(newCl.y)).c_str());
  }
}

void				NekServer::sendPositions(Client newCl, Game game) {
  std::string			tmp = "/p";

  for (unsigned int i = 0 ; i < game.players.size() ; i++) {
    if (game.players[i].pseudo != newCl.pseudo) {
      tmp += game.players[i].pseudo + ";" + std::to_string(game.players[i].x) + ";" + std::to_string(game.players[i].y);
    }
  }
  if (tmp[tmp.size() - 1] == ';')
    tmp.pop_back();
  if (tmp != "/p")
    writeToClient(&newCl.sin, tmp.c_str());
}

void				NekServer::sendPositionsToAll() {
  for (unsigned int i = 0; i < _maps.size() ; i++) {
    for (unsigned int j = 0; j < _maps[i].players.size() ; j++) {
      sendPositions(_maps[i].players[j], _maps[i]);
    }
  }
}

void				NekServer::clientJoinGame(sockaddr_in *sin) {
  std::string			newGameStr = std::string(&_buffer[2]);
  std::vector<std::string>	body = splitStr(newGameStr, ';');
  bool				clientExist = false;

  for (unsigned int i = 0; i < _maps.size() ; i++) {
    if (_maps[i].creator == body[0]) {
      std::cout << "Map trouvée" << std::endl;
      /* il doit join cette map */
      /* on verifie le pseudo */
      for (unsigned int j = 0 ; j < _maps[i].players.size() ; j++) {
	if (_maps[i].players[j].pseudo == body[1]) {
	  // check ip et port ->(_maps[i].players[j].sin.sin_addr.s_addr == sin->sin_addr.s_addr && _maps[i].players[j].sin.sin_port == sin->sin_port) ||
	  clientExist = true;
	  break;
	}
      }
      if (clientExist == false) {
	Client newCl = { *sin, body[1], 0, 0 };
	_maps[i].players.push_back(newCl);
	std::cout << newCl.pseudo << " a rejoint la partie de " << _maps[i].creator << std::endl;

	// ask to creator position.
	// and return to all
	for (unsigned int j = 0 ; j < _maps[i].players.size() ; j++) {
	  if (_maps[i].players[j].pseudo == _maps[i].creator) {
	    writeToClient(&_maps[i].players[j].sin, std::string("/j" + newCl.pseudo + ";" + std::to_string(newCl.x) + ";" + std::to_string(newCl.y)).c_str());
	    sleep(1);
	    readFromClient(&_maps[i].players[j].sin);
	    std::cout << "Join position asked to host" << std::endl;
	    break;
	  }
	}

	//writeToClient(&newCl.sin, std::string("/m" + vectorToStr(_maps[i].map)).c_str());
	std::cout << "Join position given : " << _buffer << std::endl;
	std::vector<std::string> body = splitStr(std::string(&_buffer[2]), ';');

	newCl.x = std::stoi(body[1]);
	newCl.y = std::stoi(body[0]);

	sleep(1);
	writeToClient(&newCl.sin, std::string("/j" + body[1] + ";" + body[0]).c_str());
	// ask position to host
	//	notifyAllClients("/j", newCl, _maps[i]);
	//sendPositions(newCl, _maps[i]);
	/* Envoyer map au nouveau joueur */
	/* Notifier tout les autres clients de la map */
      }
    }
  }
}

void	NekServer::sharePositionToAll(Client cl, Game game, std::string str) {
  str = "/p" + str;
  for (unsigned int i = 0 ; i < game.players.size() ; i++) {
    if (game.players[i].pseudo != cl.pseudo)
      writeToClient(&game.players[i].sin, str.c_str());
  }
}

void	NekServer::getPosition(sockaddr_in *sin) {
  std::string	newGameStr = std::string(&_buffer[2]);
  std::vector<std::string> body = splitStr(newGameStr, ';');

  (void) sin;
  /* parcourir toutes les maps */
  for (unsigned int i = 0; i < _maps.size() ; i++) {
    for (unsigned int j = 0; j < _maps[i].players.size() ; j++) {
      if (_maps[i].players[j].pseudo == body[0]) {
	_maps[i].players[j].x = std::stoi(body[1]);
	_maps[i].players[j].y = std::stoi(body[2]);
	std::cout << "Received position of " << body[0] << "[" << body[1] << ";" << body[2] << "]" << std::endl;
	sharePositionToAll(_maps[i].players[j], _maps[i], newGameStr);
	break;
      }
    }
  }
}


void	NekServer::launch() {
  std::cout << "NekServer launched..." << std::endl;
  while (1) {
    _timeout.tv_sec = 1;
    _timeout.tv_usec = 0;
    /* Vide le set de rdfs */
    FD_ZERO(&_rdfs);
    /* Set file no in rdfs set FD IN VIDE*/
    FD_SET(STDIN_FILENO, &_rdfs);
    /* On lui met la socket maintenant */
    FD_SET(_sock, &_rdfs);

    /* En passant dans le select on remplit le set et si y a quelque chose on le check apres*/
    if (select(_sock + 1, &_rdfs, NULL, NULL, &_timeout) == -1) {
      perror("select()");
      exit(errno);
    }

    if (FD_ISSET(_sock, &_rdfs)) {
      /* nouveau nekclient */
      sockaddr_in csin;

      /* a client is talking */
      readFromClient(&csin);

      if (strlen(_buffer) >= 2) {
	if (_buffer[0] == '/' && _buffer[1] == 'l') {
	  // client want list of games availables
	  std::cout << "A client get games" << std::endl;
	  sendGameList(&csin);
	} else if (_buffer[0] == '/' && _buffer[1] == 'j') {
	  /* client join une game avec le pseudo du creator */
	  std::cout << "A client want to join a game" << std::endl;
	  clientJoinGame(&csin);
	} else if (_buffer[0] == '/' && _buffer[1] == 's') {
	  // client connect with pseudo
	  /* checker si client existe, et nb max de joueurs*/
	  std::string tmpName = std::string(_buffer);
	  if (checkClientExist(&csin, tmpName) == false) {
	    if (_players.size() < 6) {
	      Client newCl;
	      newCl.sin = csin;
	      newCl.pseudo = tmpName;
	      newCl.x = 0;
	      newCl.y = 0;
	      _players.push_back(newCl);
	      std::cout << "Nouveau client : " << newCl.pseudo << std::endl;
	      // send id
	    } else {
	      // send KO
	      std::cout << "Game full 6/6" << std::endl;
	    }
	  } else {
	    std::cout << "Client already exist" << std::endl;
	    // send KO
	  }
	} else if (_buffer[0] == '/' && _buffer[1] == 'c') {
	  // create a game
	  std::cout << "A client create a game" << std::endl;
	  getNewGame(&csin);
	} else if (_buffer[0] == '/' && _buffer[1] == 'p') {
	  // send position
	  getPosition(&csin);
	} else if (_buffer[0] == '/' && _buffer[1] == 'a') {
	  // launch an attack, a bomb
	}
      }
    }
  }
}

void	NekServer::init() {
  _sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (_sock == -1) {
    perror("socket()");
    exit(errno);
  }
  _sin.sin_addr.s_addr = htonl(INADDR_ANY);
  _sin.sin_port = htons(_port);
  _sin.sin_family = AF_INET;
  // if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &t, sizeof(t)) == -1) {
  //   perror("setsockopt()");
  //   exit(errno);
  // }
  if (bind(_sock,(sockaddr *) &_sin, sizeof _sin) == -1) {
    perror("bind()");
    exit(errno);
  }
}

NekServer::NekServer(int port) {
  _port = port;
  _timeout.tv_sec = 1;
  _timeout.tv_usec = 0;
}

NekServer::~NekServer() {
}
