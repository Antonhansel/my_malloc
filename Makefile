##
## Makefile for header in /home/angeni_r/malloc_jeudi_premier_commit/malloc
## 
## Made by angenieux romain
## Login   <angeni_r@epitech.net>
## 
## Started on  Thu Feb 13 17:15:36 2014 angenieux romain
## Last update Thu Mar 13 17:41:01 2014 ribeaud antonin
##

NAME		=	"libmy_malloc_"$(HOSTTYPE)".so"

NAMELINK	=	"libmy_malloc.so"

SRCS		=	malloc.c\
			realloc.c \
			statics.c \
			show_alloc_mem.c \
			block.c \
			align.c \
			free.c \

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-W -Wall -Wextra -Werror -lpthread -ldl -fPIC

LDFLAGS		=	-shared

all		:	$(NAME) 

$(NAME)		:	$(OBJS)
			gcc $(OBJS) $(LDFLAGS) -o $(NAME)
			ln -s $(NAME) $(NAMELINK)

clean		:
			rm -f $(OBJS)

fclean		:	clean
			rm -f $(NAME)
			rm -f $(NAMELINK)

re		:	fclean all

.PHONY		:	all clean fclean re
