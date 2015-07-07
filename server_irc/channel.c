/*
** channel.c for server in /home/girard_r/rendu/PSU_2014_myirc/server
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Wed Apr  8 17:51:01 2015 Aurélien GIRARDEAU
** Last update Fri Apr 10 16:54:07 2015 Aurélien GIRARDEAU
*/

#include "channel.h"
#include "msg.h"

t_channel		*init_channels()
{
  t_channel		*channel;

  if ((channel = malloc(sizeof(t_channel))) == NULL)
    return (NULL);
  channel->root = NULL;
  channel->size = -1;
  channel->channel_name = NULL;
  channel->prev = channel;
  channel->next = channel;
  return (channel);
}

t_channel		*get_channel(t_channel *root, char *search)
{
  t_channel		*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (!strcmp(search, tmp->channel_name))
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

e_bool			is_in_channel(char *name, int fd, t_channel *root)
{
  t_channel		*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (strcmp(name, tmp->channel_name) == 0)
	return (is_in_fds(fd, tmp->root));
      tmp = tmp->next;
    }
  return (FALSE);
}

e_bool			channel_exists(char *name, t_channel *root)
{
  t_channel		*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (!strcmp(tmp->channel_name, name))
	return (TRUE);
      tmp = tmp->next;
    }
  return (FALSE);
}
