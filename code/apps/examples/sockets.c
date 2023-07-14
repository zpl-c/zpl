#define ZPL_IMPL
#define ZPL_NANO
#define ZPL_ENABLE_SOCKET
#include <zpl.h>

int main(void) {
    zpl_socket_init();

    zpl_socket sock = zpl_socket_create(ZPL_SOCKET_UDP, ZPL_SOCKET_BIND, 0, "127.0.0.1", "7800");
    if (sock == -1) {
        zpl_printf_err("Failed to create socket\n");
        return 1;
    }

    zpl_socket connect = zpl_socket_create(ZPL_SOCKET_UDP, ZPL_SOCKET_CONNECT, 0, "127.0.0.1", "7800");
    if (connect == -1) {
        zpl_printf_err("Failed to create socket\n");
        return 1;
    }

    char buffer[64] = {0};
    zpl_snprintf(buffer, zpl_size_of(buffer), "%s", "Hello, World!\n");
    zpl_isize len = zpl_socket_send(connect, buffer, zpl_size_of(buffer));
    zpl_printf("Sent %d bytes\n", len);
    zpl_socket_close(connect);

    zpl_zero_item(buffer);
    len = zpl_socket_receive(sock, buffer, zpl_size_of(buffer));
    zpl_printf("Received %d bytes, data: %s", len, buffer);

    zpl_socket_close(sock);

    zpl_socket_terminate();
    return 0;
}
