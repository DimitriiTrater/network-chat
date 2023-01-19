#include <iostream>
#include <SFML\Network.hpp>
#include <SFML\Window.hpp>

int main(int, char**) 
{   
    char type;

    std::string name;
    std::string message = "";


    sf::TcpSocket tcpSocket;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    

    std::cout << "Enter type of connection: [c] - client, [s] - server" << std::endl;
    std::cin  >> type;

    if (type == 's')
    {
        sf::TcpListener tcpListener;
        tcpListener.listen(2000);

        if (tcpListener.accept(tcpSocket) != sf::Socket::Done)
            std::cerr << "Error!" << std::endl;
    }
    else if (type == 'c')
    {
        if (tcpSocket.connect(ip, 2000) != sf::Socket::Done)
            std::cerr << "Error!" << std::endl;
    }


    std::cout << "Enter your name" << std::endl;
    std::cin  >> name;

    tcpSocket.setBlocking(false);

    sf::Packet tcpPacket;

    while (true)
    {
        std::cin >> message;

        if (message != "")
        {
            tcpPacket.clear();
            tcpPacket << name << message;

            tcpSocket.send(tcpPacket);

            message = "";
        }

        if (tcpSocket.receive(tcpPacket) == sf::Socket::Done)
        {
            std::string nameRec;
            std::string messageRec;

            tcpPacket    >> nameRec >> messageRec;
            std::cout << nameRec << ": " << messageRec << std::endl;
        }
    }

    return 0;
}
