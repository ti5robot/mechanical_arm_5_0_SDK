#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#define BUFFER_SIZE 13
int main() {
    int fd, bytes_written;
   //unsigned char data[] = {0xAA, 0xC2, 0x97, 0xC3, 0x22, 0x43, 0xDE, 0x3E, 0x8B, 0xC0, 0x16, 0x3F, 0x42};
    // unsigned char data[] = {0xAA ,0xC0 ,0xE0 ,0x43 ,0x9B ,0x40 ,0x25 ,0xC0 ,0x01 ,0xC0 ,0x47 ,0x3D };
    unsigned char data[] = {0xAA ,0xF9 ,0x39 ,0xF7 ,0xF4 ,0x10 ,0x8F ,0xFF ,0xEA ,0x00 ,0x19 ,0x00,0x1B };
	// unsigned char data[] = {0xAA ,0xF9 ,0x39 ,0xF7 ,0xF4 ,0x10 ,0x8F ,0xFF ,0xEA ,0x00 ,0x19 ,0x00 };
	
    //unsigned char data[]={0xAA ,0xC0 ,0xF7 ,0x43 ,0xA4 ,0x43 ,0x5F ,0xC0 ,0x01 ,0xC0 ,0x48 ,0x3D ,0x4B};
	// unsigned char data[] = {0xBB, 0x55, 0x97, 0xC3, 0x22, 0x43, 0xDE, 0x3E, 0x8B, 0xC0, 0x16, 0x3F, 0x42};

    // 打开串口设备
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("Error opening serial port");
        return -1;
    }

    // 配置串口参数
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error getting serial port attributes");
        return -1;
    }
    cfsetospeed(&tty, B9600);  // 设置波特率为9600
    tty.c_cflag &= ~PARENB;  // 无奇偶校验
    tty.c_cflag &= ~CSTOPB;  // 1个停止位
    tty.c_cflag &= ~CSIZE;  // 8位数据位
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;  // 禁用硬件流控制
    tty.c_cflag |= CREAD | CLOCAL;  // 使能读取和本地连接
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // 禁用软件流控制
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // 禁用规范模式和回显
    tty.c_oflag &= ~OPOST;  // 原始输出模式

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        return -1;
    }

    // 发送数据
    bytes_written = write(fd, data, sizeof(data));
    if (bytes_written < 0) {
        perror("Error writing to serial port");
        return -1;
    }

    // 关闭串口
    close(fd);

    return 0;
}



/*int main() {
    int fd, bytes_written;
    unsigned char buffer[BUFFER_SIZE];

    // 打开串口设备
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("Error opening serial port");
        return -1;
    }

    // 配置串口参数
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error getting serial port attributes");
        return -1;
    }
    cfsetospeed(&tty, B9600);  // 设置波特率为9600
    tty.c_cflag &= ~PARENB;  // 无奇偶校验
    tty.c_cflag &= ~CSTOPB;  // 1个停止位
    tty.c_cflag &= ~CSIZE;  // 8位数据位
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;  // 禁用硬件流控制
    tty.c_cflag |= CREAD | CLOCAL;  // 使能读取和本地连接
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // 禁用软件流控制
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // 禁用规范模式和回显
    tty.c_oflag &= ~OPOST;  // 原始输出模式

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        return -1;
    }

    // 准备发送的数据
    // unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    unsigned char data[] = {0xC2, 0x97, 0xC3, 0x22, 0x43, 0xDE, 0x3E, 0x8B, 0xC0, 0x16, 0x3F, 0x42};
    int data_len = sizeof(data) / sizeof(data[0]);

    // 添加帧头并发送数据
    unsigned char send_buffer[BUFFER_SIZE + 1];
    send_buffer[0] = 0xAA;  // 帧头
    memcpy(send_buffer + 1, data, data_len);
    bytes_written = write(fd, send_buffer, data_len + 1);
    if (bytes_written < 0) {
        perror("Error writing to serial port");
        return -1;
    }

    // 关闭串口
    close(fd);

    return 0;
}
*/
