NAME = webserv

SRCS = srcs/main.cpp srcs/HttpRequest.cpp

#OBJS = $(SRCS:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

RM = rm -f

$(NAME): $(SRCS)
		$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

#%.o: %.cpp
#		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re