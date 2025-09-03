#include "../includes/ClientConnection.hpp"

ClientConnection::ClientConnection(int fd) : _fd(fd) {}

ClientConnection::~ClientConnection(void) {}