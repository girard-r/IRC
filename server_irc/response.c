/*
** response.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc/server_irc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Thu Apr  9 18:25:54 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:16:26 2015 Aurélien GIRARDEAU
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

int		crlf_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\r' && str[i + 1] != '\n')
    i += 1;
  return (i + 2);
}

char		*concat_str(char *s1, char *s2, char *s3)
{
  char		*s4;

  if ((s4 = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 2)) == NULL)
    return (NULL);
  strcpy(s4, s1);
  s4[strlen(s1)] = 0;
  strcat(s4, s2);
  strcat(s4, s3);
  s4[strlen(s4) + 1] = '\n';
  s4[strlen(s4)] = '\r';
  return (s4);
}

int		send_response(int fd, char *code, char *msg)
{
  char		*response;

  usleep(1);
  if (strlen(code))
    response = concat_str(code, " ", msg);
  else
    response = concat_str(code, "", msg);
  if (!response
      || send(fd, response, crlf_strlen(response), 0) == -1)
    {
      if (response)
	free(response);
      return (-1);
    }
  free(response);
  return (0);
}
