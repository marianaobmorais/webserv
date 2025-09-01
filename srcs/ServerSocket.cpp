#include "ServerSocket.hpp"

ServerSocket::ServerSocket(void) : _fd(-1) {}

ServerSocket::ServerSocket(int newFD) : _fd(newFD) {}

ServerSocket::~ServerSocket(void) {}