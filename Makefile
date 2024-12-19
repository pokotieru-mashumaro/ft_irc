NAME		=	ircserv
SRCS		=	$(wildcard ./srcs/*.cpp) $(wildcard ./srcs/command/*.cpp) $(wildcard ./srcs/utils/*.cpp)
INC_DIR     =	./includes
CC          =	c++
CFLAGS      =	-Wall -Wextra -Werror -std=c++98
DEBUG		=	-g -fsanitize=address
RM          =	rm -f
OBJS        =	$(SRCS:.cpp=.o)

%.o: %.cpp
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)

debug: $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUG) $^ -o $(NAME)

fclean: clean
	@$(RM) $(NAME)

clean:
	@$(RM) $(OBJS)

re:    fclean all

.PHONY:    all clean fclean re