NAME = webserv

REQUEST_PATH = srcs/request
RESPONSE_PATH = srcs/response
UTILS_PATH = srcs/utils

SRCS = srcs/main.cpp \
	$(REQUEST_PATH)/HttpRequest.cpp \
	$(REQUEST_PATH)/RequestMeta.cpp \
	$(REQUEST_PATH)/RequestParse.cpp \
	$(RESPONSE_PATH)/HttpResponse.cpp \
	$(RESPONSE_PATH)/ResponseBuilder.cpp \
	$(UTILS_PATH)/Logger.cpp \
	srcs/WebServer.cpp \
	srcs/ServerSocket.cpp \
	srcs/ClientConnection.cpp \

#OBJS = $(SRCS:.cpp=.o) #it does't compile with OBJS

#add logs folder
#add objs folder

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g

RM = rm -f

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -DDEV=1 -I./includes $(SRCS) -o $(NAME)

all: $(NAME)

#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re