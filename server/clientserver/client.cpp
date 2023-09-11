#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main() {
    // ������� ������ io_service ��� ���������� ������������ ���������� �����-������
    io_service io;

    // ������� ����� ��� �������
    ip::tcp::socket socket(io);

    try {
        // ������������ � �������, ������� ������� �� IP-������ 127.0.0.1 � ����� 12345
        socket.connect(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 12345));

        // ������� ����� ��� ������ ������
        char data[1024];
        boost::system::error_code error;

        // ������ ������ �� �������
        size_t len = socket.read_some(buffer(data), error);

        // ��������� ������ � ������� ������
        if (error == error::eof) {
            std::cout << "������ ������ ����������." << std::endl;
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