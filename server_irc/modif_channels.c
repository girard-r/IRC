/*
** modif_channels.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Apr 12 20:03:06 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:03:07 2015 Aurélien GIRARDEAU
*/

#include "channel.h"
#include "msg.h"

int			pop_in_channel(char *name, int fd, t_channel **root)
{
  t_channel		*tmp;

  tmp = (*root)->next;
  while (tmp != (*root))
    {
      if (strcmp(name, tmp->channel_name) == 0)
	{
	  if (is_in_fds(fd, tmp->root) == FALSE)
	    return (-2);
	  pop_fd_list(&(tmp->root), fd);
	  tmp->size -= 1;
	  if (tmp->size == 0)
	    return (delete_channel(tmp));
	  return (0);
	}
      tmp = tmp->next;
    }
  return (-1);
}

int			add_in_channel(char *name, int fd, t_channel **root)
{
  t_channel		*tmp;

  tmp = (*root)->next;
  while (tmp != (*root))
    {
      if (strcmp(tmp->channel_name, name) == 0)
	return (add_in_channel_aux(tmp, fd));
      tmp = tmp->next;
    }
  return (create_channel(root, name, fd));
}
int			add_in_channel_aux(t_channel *elem, int fd)
{
  if (add_fd_list(&(elem->root), fd) == -1)
    return (-1);
  elem->size += 1;
  return (0);
}

int			create_channel(t_channel **root, char *name, int fd)
{
  t_channel		*tmp;

  if ((tmp = malloc(sizeof(t_channel))) == NULL
      || (tmp->root = init_fds()) == NULL
      || add_fd_list(&(tmp->root), fd) == -1)
    return (-1);
  tmp->channel_name = strdup(name);
  tmp->size = 1;
  tmp->next = (*root);
  tmp->prev = (*root)->prev;
  tmp->next->prev = tmp;
  tmp->prev->next = tmp;
  return (0);
}

int			delete_channel(t_channel *tmp)
{
  free(tmp->root);
  free(tmp->channel_name);
  tmp->next->prev = tmp->prev;
  tmp->prev->next = tmp->next;
  free(tmp);
  return (0);
}
