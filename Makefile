NAME = webserv

REQUEST_PATH = srcs/request

SRCS = srcs/main.cpp \
	$(REQUEST_PATH)/HttpRequest.cpp \
	$(REQUEST_PATH)/RequestMeta.cpp  \
	$(REQUEST_PATH)/RequestParse.cpp

#OBJS = $(SRCS:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

RM = rm -f

$(NAME): $(SRCS)
		$(CXX) $(CXXFLAGS) -I./includes $(SRCS) -o $(NAME)

all: $(NAME)

#%.o: %.cpp
#		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re