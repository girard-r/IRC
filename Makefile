##
## Makefile for myftp in /home/girard_r/rendu/PSU_2014_myftp
## 
## Made by Aurélien GIRARDEAU
## Login   <girard_r@epitech.net>
## 
## Started on  Tue Mar 10 19:19:52 2015 Aurélien GIRARDEAU
## Last update Sun Apr 12 19:11:11 2015 Aurélien GIRARDEAU
##

SERVER		=		server

CLIENT		=		client

CC		=		gcc

GPP		=		g++

RM		=		rm -f

INCL_DIR	=		includes/

SERVER_DIR	=		server_irc

SERVER_BUILTIN	=		$(SERVER_DIR)/builtins

CLIENT_DIR	=		client_irc

CFLAGS		=		-Wall -Wextra -Werror -I./$(INCL_DIR)

CXXFLAGS	=		-Wall -Wextra -Werror -I./$(INCL_DIR)

SRCS_S		=		$(SERVER_DIR)/channel.c \
				$(SERVER_DIR)/select_loop.c \
				$(SERVER_DIR)/user.c \
				$(SERVER_DIR)/fds_list.c \
				$(SERVER_DIR)/modif_channels.c \
				$(SERVER_BUILTIN)/transfert_file.c \
				$(SERVER_BUILTIN)/begin_connection.c \
				$(SERVER_BUILTIN)/join.c \
				$(SERVER_BUILTIN)/list.c \
				$(SERVER_BUILTIN)/msg.c \
				$(SERVER_BUILTIN)/nick.c \
				$(SERVER_BUILTIN)/part.c \
				$(SERVER_BUILTIN)/quit.c \
				$(SERVER_BUILTIN)/names.c \
				$(SERVER_BUILTIN)/channel_msg.c \
				$(SERVER_DIR)/main.c \
				$(SERVER_DIR)/manage_connection.c \
				$(SERVER_DIR)/response.c \
				$(SERVER_DIR)/signal.c \
				$(SERVER_DIR)/user_get.c \
				$(SERVER_DIR)/user_checks.c \
				$(SERVER_DIR)/parsing.c

OBJS_S		=		$(SRCS_S:.c=.o)

SRCS_C		=		$(CLIENT_DIR)/Line.cpp \
				$(CLIENT_DIR)/Client.cpp \
				$(CLIENT_DIR)/main.cpp

OBJS_C		=		$(SRCS_C:.cpp=.o)

all:				$(SERVER) $(CLIENT)

$(SERVER):			$(OBJS_S)
				$(CC) -o $(SERVER) $(OBJS_S)

$(CLIENT):			$(OBJS_C)
				$(GPP) -o $(CLIENT) $(OBJS_C)

clean:
				$(RM) $(OBJS_S) $(OBJS_C)

fclean:				clean
				$(RM) $(SERVER) $(CLIENT)

re:				fclean all

.PHONY:				all clean fclean re
