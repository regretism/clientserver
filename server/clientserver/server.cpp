//Приложение создано с использованием библиотеки boost::asio для реализации асинхронной работы с сокетами
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main() {
    // Создаем объект io_service для управления асинхронными операциями ввода-вывода
    io_service io;

    // Создаем объект acceptor для прослушивания подключений на порту 12345
    ip::tcp::acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 12345));

    while (true) {
        // Создаем сокет для каждого клиента, который подключается
        ip::tcp::socket socket(io);

        // Принимаем подключение клиента
        acceptor.accept(socket);

        // Отправляем клиенту приветственное сообщение
        std::string message = "Hello,client!";
        boost::system::error_code ignored_error;
        write(socket, buffer(message), ignored_error);
    }
    //Сервер продолжает принимать подключения от других клиентов, отправляя каждому из них такое же приветственное сообщение.
    return 0;
}