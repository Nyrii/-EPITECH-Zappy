/*
** test_time.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Tue Jun 14 22:01:25 2016 Kevin Empociello
** Last update Tue Jun 14 22:23:24 2016 Kevin Empociello
*/

#include <sys/timeb.h>

double elapse(struct timeb *before, struct timeb *after)
{
  double t;
  t =   (after->time*1000 + after->millitm)
      - (before->time*1000 + before->millitm);
  t /= 1000;
  return t;
}

int main()
{
  /* Declare timing variables to record time */
  struct timeb before, after;
  double t;

  /* Variables for testing */
  int i, count = 0, n = 1000000000;

  /* Timing start */
  ftime(&before);

  double tmp = (before.time*1000 + before.millitm) / 1000;
  printf("Current second in stuct timeb : %lf\n", tmp);


  /* Run your program here */
  /* The following is a test program that counts the number of
     multiples of 3 between 1 and n */
  for (i = 1; i <= n; i++)
    if (i % 3 == 0)
      count++;
  /* Timing ends */
  ftime(&after);

      double tmp2 = (after.time*1000 + after.millitm) / 1000;
  printf("Current second in stuct timeb : %lf\n", tmp2);
  /* Get the elapse time between before and after */
  t = elapse(&before, &after);

  /* Print the number of seconds between before and after */
  printf("The elapse time is: %lf seconds\n", t);

  return 0;
}
