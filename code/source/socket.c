// file: source/socket.c

ZPL_BEGIN_C_DECLS

#if defined(ZPL_SYSTEM_WINDOWS)
#   include <ws2tcpip.h>
#   pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else //unix
#   include <sys/socket.h>
#   include <netdb.h>
#   include <fcntl.h>
#   include <unistd.h>
    #ifndef TCP_NODELAY
#       include <netinet/in.h>
#       include <netinet/tcp.h>
#   endif
#endif

ZPL_DEF zpl_socket zpl_socket_init(void) {
#   if defined(ZPL_SYSTEM_WINDOWS)
    WSADATA winsock_data = {0};
    return WSAStartup(MAKEWORD(2, 2), &winsock_data) != NO_ERROR;
#   endif
    return 0;
}

ZPL_DEF zpl_socket zpl_socket_create(zpl_i32 protocol, zpl_i32 mode, char flags, const char *host, const char *service) {
    struct addrinfo *result, hints = {
        (mode == ZPL_SOCKET_BIND) ? AI_PASSIVE : 0,
        AF_UNSPEC,
        (protocol == ZPL_SOCKET_UDP) ? SOCK_DGRAM : SOCK_STREAM,
        0, 0, 0, 0, 0
    };

    if (getaddrinfo(host, service, &hints, &result) != 0) {
        return -1;
    }
#   if defined(ZPL_SYSTEM_WINDOWS)
    zpl_socket sock = (zpl_socket)socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock == INVALID_SOCKET) {
        freeaddrinfo(result);
        return -1;
    }
    if (sock > INT_MAX) {
        closesocket(sock);
        freeaddrinfo(result);
        return -1;
    }
#   else
    zpl_socket sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock == -1) {
        freeaddrinfo(result);
        return -1;
    }
#   endif
    
    if (result->ai_family == AF_INET6) {
        zpl_i32 no = 0;
        setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&no, sizeof(no));
    }

    if (protocol == ZPL_SOCKET_TCP) {
        int nodelay = (flags & ZPL_SOCKET_NO_DELAY);
        setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof(nodelay));
    }

    if (mode == ZPL_SOCKET_BIND) {
        if (bind(sock, result->ai_addr, (int)result->ai_addrlen) != 0) {
            freeaddrinfo(result);
            return -1;
        }
    }

    if (flags & ZPL_SOCKET_NON_BLOCKING) {
#   if defined(ZPL_SYSTEM_WINDOWS)
        DWORD non_blocking = 1;
        if (ioctlsocket(sock, FIONBIO, &non_blocking)) {
            freeaddrinfo(result);
            return -1;
        }
#   else
        if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1) {
            freeaddrinfo(result);
            return -1;
        }
#   endif
    }

    if (mode == ZPL_SOCKET_CONNECT) {
        if (connect(sock, result->ai_addr, (int)result->ai_addrlen) != 0 && !(flags & ZPL_SOCKET_NON_BLOCKING)) {
            freeaddrinfo(result);
            return -1;
        }
    }

    freeaddrinfo(result);
    return sock;
}

ZPL_DEF void zpl_socket_close(zpl_socket socket) {
#   if defined(ZPL_SYSTEM_WINDOWS)
    closesocket(socket);
#   else
    close(socket);
#   endif
}

ZPL_DEF void zpl_socket_terminate(void) {
#   if defined(ZPL_SYSTEM_WINDOWS)
    WSACleanup();
#   endif
}

ZPL_DEF zpl_i32 zpl_socket_listen(zpl_socket socket, zpl_i32 backlog) {
    return listen(socket, backlog);
}

ZPL_DEF zpl_socket zpl_socket_accept(zpl_socket socket, zpl_socket_addr *addr) {
#   if defined(ZPL_SYSTEM_WINDOWS)
    int len = sizeof(*addr);
    zpl_socket sock = (zpl_socket)accept(socket, (struct sockaddr *)addr, &len);
    if (sock == INVALID_SOCKET) {
        return -1;
    }
    if (sock > INT_MAX) {
        closesocket(sock);
        return -1;
    }
#   else
    socklen_t len = sizeof(*addr);
    zpl_socket sock = accept(socket, (struct sockaddr *)addr, &len);
    if (sock == -1) {
        return -1;
    }
#   endif
    return sock;
}

ZPL_DEF zpl_i32 zpl_socket_get_address(zpl_socket socket, zpl_socket_addr *addr) {
    return getsockname(socket, (struct sockaddr *)addr, (socklen_t *)sizeof(*addr));
}

ZPL_DEF zpl_i32 zpl_socket_get_address_info(zpl_socket_addr *addr, char *host, zpl_i32 host_size, char *service, zpl_i32 service_size) {
    return getnameinfo((struct sockaddr *)addr, (socklen_t)sizeof(*addr), host, host_size, service, service_size, 0);
}

ZPL_DEF zpl_i32 zpl_socket_send(zpl_socket socket, const char *data, zpl_i32 size) {
    return send(socket, data, size, 0);
}

ZPL_DEF zpl_i32 zpl_socket_receive(zpl_socket socket, char *buffer, zpl_i32 size) {
    return recv(socket, buffer, size, 0);
}

ZPL_DEF zpl_i32 zpl_socket_send_to(zpl_socket socket, zpl_socket_addr *addr, const char *data, zpl_i32 size) {
    return sendto(socket, data, size, 0, (struct sockaddr *)addr, (socklen_t)sizeof(*addr));
}

ZPL_DEF zpl_i32 zpl_socket_receive_from(zpl_socket socket, zpl_socket_addr *addr, char *buffer, zpl_i32 size) {
    return recvfrom(socket, buffer, size, 0, (struct sockaddr *)addr, (socklen_t *)sizeof(*addr));
}

ZPL_DEF zpl_i32 zpl_socket_select(zpl_socket socket, zpl_f64 time) {
    fd_set fds;
    struct timeval tv;

    FD_ZERO(&fds);
    if (socket > -1) FD_SET(socket, &fds);

    tv.tv_sec = (long)time;
    tv.tv_usec = (long)((time - tv.tv_sec) * 1000000);

    return select(socket + 1, &fds, 0, 0, &tv);
}

ZPL_DEF zpl_i32 zpl_socket_multi_select(zpl_socket *sockets, zpl_i32 count, zpl_f64 time) {
    fd_set fds;
    struct timeval tv;
    zpl_i32 i, max = -1;

    FD_ZERO(&fds);
    for (i = 0; i < count; ++i) {
        if (sockets[i] > max) max = sockets[i];
        if (sockets[i] > -1) FD_SET(sockets[i], &fds);
    }

    tv.tv_sec = (long)time;
    tv.tv_usec = (long)((time - tv.tv_sec) * 1000000);

    return select(max + 1, &fds, 0, 0, &tv);
}

ZPL_END_C_DECLS

