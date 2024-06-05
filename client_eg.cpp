#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error: Failed to create socket." << std::endl;
        return 1;
    }

    // 设置服务器地址
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1234); // 服务端端口
    //inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // 服务端IP地址
    
    // 将字符串形式的 IP 地址转换成 in_addr_t 类型
    if (inet_pton(AF_INET, "192.168.231.128", &serverAddr.sin_addr) <= 0) {
        std::cerr << "Error: Invalid IP address." << std::endl;
        close(clientSocket);
        return 1;
    }

    // 连接到服务器
    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Connection failed." << std::endl;
        close(clientSocket);
        return 1;
    }

    // 发送数据
    //uint8_t input[15] = {0xaa,0xf7, 0x43, 0xa4, 0x43, 0x5f, 0xc0, 0x01, 0xc0, 0x48, 0x3d,0x4b,0x34,0xaa,0x55};
    uint8_t input[15] = {0xaa,0xf9, 0x39, 0xf7, 0xf4, 0x10, 0x8f, 0xff, 0xea, 0x00, 0x19,0x00,0x1b,0xaa,0x55};
    //{0xAA ,0xF9 ,0x39 ,0xF7 ,0xF4 ,0x10 ,0x8F ,0xFF ,0xEA ,0x00 ,0x19 ,0x00,0x1B };
    //{0xf7, 0x43, 0xa4, 0x43, 0x5f, 0xc0, 0x01, 0xc0, 0x48, 0x3d, 0x4b}
    if (send(clientSocket, input, sizeof(input), 0) == -1) {
        std::cerr << "Error: Failed to send data." << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Data sent successfully." << std::endl;

    // 关闭套接字
    close(clientSocket);

    return 0;
}

