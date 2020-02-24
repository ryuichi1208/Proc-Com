#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cassert>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

int server (const int& client_socket)
{
    while (1) {
        const size_t MAX_SIZE = 128;
        char buffer[MAX_SIZE];
        read(client_socket, buffer, MAX_SIZE);
        const std::string message(buffer);
        if(message.size() == 0) {
            return 0;
        } else {
            std::cout << message << std::endl;
            return 1;
        }
    }

    assert(!"This line must not be executed.");
}

int main()
{
    const std::string socket_name("my_socket");
    int socket_fd;
    sockaddr_un name;
    int client_sent_quit_message;
    /* ソケットを作成 */
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    /* サーバーとして設定 */
    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, socket_name.c_str());
    bind(socket_fd, reinterpret_cast<sockaddr*>(&name), SUN_LEN (&name));
    /* ソケットを開く */
    listen(socket_fd, 5);
    /* 接続されたらメッセージが届くまで待機 */
    do {
        sockaddr_un client_name;
        socklen_t client_name_len;
        int client_socket_fd;
        /* 接続があるまで待機 */
        client_socket_fd = accept(socket_fd, reinterpret_cast<sockaddr*>(&client_name), &client_name_len);
        /* メッソージを受け取る */
        client_sent_quit_message = server(client_socket_fd);
        /* 切断する*/
        close(client_socket_fd);
    } while (!client_sent_quit_message);
    /* ソケットを閉じる */
    close(socket_fd);
    unlink(socket_name.c_str());

    return EXIT_SUCCESS;
}
