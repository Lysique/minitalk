NAME_CLIENT = client
NAME_SERVER = server
FILES_CLIENT = client
FILES_SERVER = server
OBJS_CLIENT =  $(SRCS_CLIENT:.c=.o)
OBJS_SERVER =  $(SRCS_SERVER:.c=.o)
SRCS_DIR = ./
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS_CLIENT = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_CLIENT)))
SRCS_SERVER = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_SERVER)))


.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)
$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)
clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)
fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
re: fclean all

.PHONY: all clean fclean re
