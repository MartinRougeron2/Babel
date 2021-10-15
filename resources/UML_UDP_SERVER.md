@startuml





/' Objects '/

class server {
	+server(boost::asio::io_service& io_service, short port)
	-data_ : char
	-sender_endpoint_ : udp::endpoint
	-socket_ : udp::socket
	+handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd) : void
	+handle_send_to(const boost::system::error_code &, size_t) : void
}


enum server::empty {
	max_length
}





/' Inheritance relationships '/




/' Aggregation relationships '/





/' Nested objects '/

.server +-- .server::empty




@enduml
