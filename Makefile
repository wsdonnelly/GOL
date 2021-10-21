CC = gcc
NAME = gol
SOURCES = srcs/*.c
OBJECTS = *.o
HEADERS = hdrs

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

#$(NAME): $(SOURCES)
#	$(CC) $(CFLAGS) $(SOURCES) -I $(HEADERS) -o $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES) -I $(HEADERS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re