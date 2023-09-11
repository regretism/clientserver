#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main() {
    // Создаем объект io_service для управления асинхронными операциями ввода-вывода
    io_service io;

    // Создаем сокет для клиента
    ip::tcp::socket socket(io);

    try {
        // Подключаемся к серверу, который слушает на IP-адресе 127.0.0.1 и порту 12345
        socket.connect(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 12345));

        // Создаем буфер для чтения данных
        char data[1024];
        boost::system::error_code error;

        // Читаем данные от сервера
        size_t len = socket.read_some(buffer(data), error);

        // Проверяем ошибки и выводим данные
        if (error == error::eof) {
            std::cout << "Сервер закрыл соединение." << std::endl;
        }
        else if (error) {
            throw boost::system::system_error(error);
        }

        std::cout.write(data, len);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}