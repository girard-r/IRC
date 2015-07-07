/*
** server_main.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Thu Apr  9 20:09:15 2015 Aurélien GIRARDEAU
** Last update Thu Apr 16 12:21:59 2015 Aurélien GIRARDEAU
*/

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "e_bool.h"
# include "parsing.h"
# include "channel.h"
# include "user.h"
# include "msg.h"

int			main(int argc, char **argv)
{
  int			port;

  if (argc > 2)
    {
      printf("Usage : ./server [<port>]\n");
      return (1);
    }
  process_signal();
  if (argc == 1)
    port = 6667;
  else
    port = atoi(argv[1]);
  process_signal();
  main_loop(port);
  return (0);
}
