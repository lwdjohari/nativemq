#include <asio.hpp>
#include <iostream>
#include <memory>

using asio::ip::tcp;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
 public:
  using Pointer = std::shared_ptr<TcpConnection>;
  TcpConnection(tcp::socket socket) : socket_(std::move(socket)) {}

  static Pointer Create(tcp::socket socket) {
    return std::make_shared<TcpConnection>(std::move(socket));
  }

  tcp::socket& Socket() {
    return socket_;
  }

  void Start() {
    DoRead();
  }

 private:

  void DoRead() {
    auto self(shared_from_this());
    socket_.async_read_some(asio::buffer(data_, kMaxLength),
        [this, self](std::error_code ec, std::size_t length) {
          if (!ec) {
            DoWrite(length);
          }
        });
  }

  void DoWrite(std::size_t length) {
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(data_, length),
        [this, self](std::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            DoRead();
          }
        });
  }

  tcp::socket socket_;
  static constexpr std::size_t kMaxLength = 1024;
  char data_[kMaxLength];
};

class TcpServer {
 public:
  TcpServer(asio::io_context& io_context, short port)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    DoAccept();
  }

 private:
  void DoAccept() {
    acceptor_.async_accept(
        [this](std::error_code ec, tcp::socket socket) {
          if (!ec) {
            auto connection = TcpConnection::Create(std::move(socket));
            connection->Start();
          }
          DoAccept();
        });
  }

  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <port>\n";
      return 1;
    }

    asio::io_context io_context;
    TcpServer server(io_context, std::atoi(argv[1]));
    io_context.run();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
