#include <Network/Socket.h>
#include <fmt/printf.h>
#include <sys/socket.h>
#include <sys/types.h>
namespace Uriel {
Socket::Socket(int socketfd) : socketfd_(socketfd) {}

Socket::~Socket() {}

const int Socket::GetSocketfd() const {
	return socketfd_;
}
TcpSocket::TcpSocket() : Socket(0) {
	socketfd_ = socket(AF_INET, SOCK_STREAM, 0);
}

TcpSocket::TcpSocket(bool block) : TcpSocket() {
	if (!block) {
		socketfd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	}
}

TcpSocket::~TcpSocket() {}

} // namespace Uriel