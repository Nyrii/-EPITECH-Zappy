//
// main.cpp for  in /home/empoci_k/rendu_tek2/cpp_indie_studio/nekfeu/server
//
// Made by Kévin Empociello
// Login   <empoci_k@epitech.net>
//
// Started on  Wed Apr 27 17:09:05 2016 Kévin Empociello
// Last update Tue Jun  7 14:55:34 2016 nekfeu
//

#include "NekClient.hh"

int		main()
{
  NekClient	nek("127.0.0.1", 8889);

  nek.init();
  nek.launch();
  return 0;
}
