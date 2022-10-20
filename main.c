#include <ncurses.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "UI.h"
#include "server.h"
#include "player.h"
#define PORT 8080

int main() {

    int server_fd, conn_status;
    struct sockaddr_in address;
    int opt = 1;

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    conn_status = connect(server_fd, (struct sockaddr*)&address, sizeof(address));
    if(conn_status < 0)
    {
        if(setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            perror("setsockopt");
            return -5;
        }

        if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
        {
            perror("bind failed");
            return -10;
        }

        if(listen(server_fd, 4) < 0)
        {
            perror("listen");
            return -10;
        }

        game_server_loop(server_fd);

    }
    else
    {
        player_loop(server_fd);
    }

    close(server_fd);
    return 0;
}
