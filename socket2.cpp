#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

/* Write TEXT to the socket given by file descriptor SOCKET_FD. */
int write_text(const int& socket_fd, const std::string& message)
{
    /* Write the string. */
    write(socket_fd, message.c_str(), message.size() + 1);
    return 0;
}

int main ()
{
    const std::string socket_name("my_socket");
    const std::string message = "Hello World!!";
    int socket_fd;
    sockaddr_un name;
    /* ソケットを作成する */
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    /* ソケット名を設定 */
    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, socket_name.c_str());
    /* ソケットを接続 */
    connect(socket_fd, reinterpret_cast<sockaddr*>(&name), SUN_LEN (&name));
    /* メッセージを送信 */
    write_text(socket_fd, message);
    close(socket_fd);
    return EXIT_SUCCESS;
}
