#include <Network/AsyncIO/Acceptor.h>
#include <Network/NetWorkConfig.hpp>
#include <fmt/printf.h>
#include <string.h>
namespace Uriel {
Acceptor::Acceptor() : isRunning_(false) {
	memset(&sockAddr_, 0, sizeof(sockAddr_));
	sockAddr_.sin_port = htons(NetWorkConfig::Instance().port_);
	sockAddr_.sin_family = AF_INET;
	sockAddr_.sin_addr.s_addr =
		inet_addr(NetWorkConfig::Instance().ip_.c_str());
	if (Bind() == -1) {
		fmt::print("Failed to Bind\n");
		return;
	}
	if (Listen() == -1) {
		fmt::print("Failed to Listen\n");
	}
}

int Acceptor::Bind() {
	return bind(socket_.GetSocketfd(), (sockaddr *)&sockAddr_,
				sizeof(sockAddr_));
}

int Acceptor::Listen() {
	return listen(socket_.GetSocketfd(), 5);
}

int Acceptor::Accept() {
	return accept(socket_.GetSocketfd(), nullptr, nullptr);
}

int Acceptor::Send(int clientId, std::string msg) {
	return send(clientId, msg.c_str(), msg.size(), 0);
}

String Acceptor::Recv(int clientId) {
	String readString;
	while (1) {
		int n = recv(clientId, readBuffer_, 127, MSG_DONTWAIT);
		if (n <= 0) {
			if (n == 0)

				readString.errorNo_ = LOST_CONNECTION;
			else {
				if (errno == EAGAIN)
					readString.errorNo_ = TRY_AGAIN;
				else
					readString.errorNo_ = ERROR;
			}
			break;
		} else
			readString += std::string(readBuffer_, readBuffer_ + n);
		/* code */
	}
	return readString;
}

} // namespace Uriel