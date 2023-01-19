#include <iostream>
#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>


int main(int, char**) 
{
    char type;
	char mode = ' ';

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

	sf::TcpSocket socket;

	sf::Packet packet;	
	

    std::string message = "";
	 
    
    std::cout << "Type of connect:  [c] - client, [s] - server" << std::endl;
    std::cin >> type;
    
    if(type == 's')
    {
    	std::cout << "[info] server ip: " << ip << std::endl;
        sf::TcpListener listener;
        listener.listen(2000);
        if (listener.accept(socket) != sf::Socket::Done)    //который будет содержать новое соединение
            std::cerr << "[error] server side" << std::endl;
    } 
    else if (type == 'c')
    {
        if(socket.connect(ip, 2000) != sf::Socket::Done)
            std::cerr << "[error] client side" << std::endl; //ip и Порт
    } 
 
    socket.setBlocking(false);
 
 
	while(true)
    {
        if(type == 's')
        {
            if(socket.receive(packet) == sf::Socket::Done)
            {				                    //Команда которая ожидает данных в виде пакета от клиентской части
                packet >> message;				//вытаскиваем значение из пакета 
                std::cout << "[message] " << message << std::endl;
                message = "";    
            } 	
        }
    
        if(type == 'c')
        {
            std::getline(std::cin, message);
            if (message != "")
            {    
                packet.clear();	
                packet << message;		//Пакуем значения
                socket.send(packet);	//Отправка данных
                message = "";
            }
        }
	}
 
	return 0;
}
