//
// main.cpp for  in /home/empoci_k/rendu_tek2/cpp_indie_studio/nekfeu/server
//
// Made by Kévin Empociello
// Login   <empoci_k@epitech.net>
//
// Started on  Wed Apr 27 17:09:05 2016 Kévin Empociello
// Last update Sun Jun  5 12:10:01 2016 nekfeu
//

#include "NekServer.hh"

int	main() {
  NekServer	nek(8889);

  nek.init();
  nek.launch();
  return 0;
}
