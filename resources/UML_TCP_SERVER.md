@startuml





/' Objects '/

class TcpServer {
	+TcpServer(boost::asio::io_service &, short)
	-voiceServer : UdpServer*
	-ios : boost::asio::io_service&
	-mtx : std::mutex
	-acceptor : tcp::acceptor
	+handle_accept(std::shared_ptr<TcpSession>, const boost::system::error_code &) : void
}


class TcpSession {
	+TcpSession(boost::asio::io_service &, UdpServer* copy, std::mutex* copyMtx)
	-database : Asqlite3
	+C_command_to_commands(C_Commands) : Commands
	-recvCommands : Commands
	-recv : Protocol*
	+decode(std::string) : S_Protocol
	-voiceServer : UdpServer*
	+C_user_to_user(C_User) : UserApp
	-recvUser : UserApp
	+accept(std::string, struct UserApp) : bool
	+add(std::string, struct UserApp) : bool
	+call(std::string, struct UserApp) : bool
	+check_linked(std::string, struct UserApp) : bool
	+check_user(std::string, struct UserApp) : bool
	+close_server(std::string, struct UserApp) : bool
	+hangup(std::string, struct UserApp) : bool
	+join(std::string, struct UserApp) : bool
	+login(std::string, struct UserApp) : bool
	+logout(std::string, struct UserApp) : bool
	+ping(std::string, struct UserApp) : bool
	+refuse(std::string, struct UserApp) : bool
	+remove(std::string, struct UserApp) : bool
	+send(char*) : bool
	+set_string(char const*) : char*
	-buffer : std::array<std::vector<std::bitset<16>, max_length>
	-mtx : std::mutex*
	+decoder(std::vector<std::bitset<16>>) : std::string
	+encoder(std::string) : std::vector<std::bitset<16>>
	-users : std::vector<std::string>
	-socket : tcp::socket
	+getSocket() : tcp::socket&
	-close_socket() : void
	+display(UserApp) : void
	+handleRead(std::shared_ptr<TcpSession> &, const boost::system::error_code &, std::size_t) : void
	+start() : void
}


enum TcpSession::empty {
	max_length
}





/' Inheritance relationships '/




/' Aggregation relationships '/





/' Nested objects '/

.TcpSession +-- .TcpSession::empty




@enduml
