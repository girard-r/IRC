/*
** signal.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 19:05:47 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 19:44:29 2015 Aurélien GIRARDEAU
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include "msg.h"
#include "user.h"

void		handle_signal(int sig)
{
  t_user	*tmp;

  (void)sig;
  if (g_sock != -1 && g_root)
    {
      tmp = g_root->next;
      while (tmp != g_root)
	{
	  if (sig == 42)
	    send_response(tmp->fd, "QUIT", ": Connection timed out");
	  else
	    send_response(tmp->fd, "QUIT", ": Ctrl+C caught in the server");
	  close(tmp->fd);
	  tmp = tmp->next;
	}
      usleep(10000);
      close(g_sock);
    }
  exit(EXIT_SUCCESS);
}

int		process_signal()
{
  if (signal(SIGINT, handle_signal) != SIG_ERR
      && signal(SIGQUIT, handle_signal) != SIG_ERR)
    return (1);
  return (0);
}
