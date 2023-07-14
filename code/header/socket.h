// file: header/socket.h

ZPL_BEGIN_C_DECLS

typedef int zpl_socket;

typedef struct zpl_socket_addr {
    char data[128];
} zpl_socket_addr;

typedef enum zpl_socket_protocol {
    ZPL_SOCKET_TCP = 0,
    ZPL_SOCKET_UDP = 1,
} zpl_socket_protocol;

typedef enum zpl_socket_mode {
    ZPL_SOCKET_BIND = 0,
    ZPL_SOCKET_CONNECT = 1,
} zpl_socket_mode;

typedef enum zpl_socket_flags {
    ZPL_SOCKET_DEFAULT = 0,
    ZPL_SOCKET_NON_BLOCKING = 0x01,
    ZPL_SOCKET_NO_DELAY = 0x02,
} zpl_socket_flags;

/**
 * Initializes socket functionality
 * @return 0 on success
 */
ZPL_DEF zpl_i32 zpl_socket_init(void);

/**
 * Creates a new socket configured according to the given parameters
 * @param protocol Protocol of the socket, either ZPL_SOCKET_TCP or ZPL_SOCKET_UDP for TCP or UDP respectively
 * @param mode Mode of the socket (bind or connect), either ZPL_SOCKET_BIND or ZPL_SOCKET_CONNECT
 * @param flags Configuration flags, either ZPL_SOCKET_DEFAULT or a bitwise combination of flags
 * @param host Host/address as a string, can be IPv4, IPv6, etc...
 * @param service Service/port as a string, e.g. "1728" or "http"
 * @return socket handle, or -1 on failure
 */
ZPL_DEF zpl_socket zpl_socket_create(zpl_i32 protocol, zpl_i32 mode, char flags, const char *host, const char *service);

/**
 * Closes the given socket
 * @param socket Socket handle
 */
ZPL_DEF void zpl_socket_close(zpl_socket socket);

/**
 * Terminates socket functionality
 */
ZPL_DEF void zpl_socket_terminate(void);

/**
 * Configures the given socket (must be ZPL_SOCKET_TCP + ZPL_SOCKET_BIND) to listen for new connections with the given backlog
 * @param socket Socket handle
 * @param backlog Size of the backlog
 * @return 0 on success, non-zero on failure
 */
ZPL_DEF zpl_i32 zpl_socket_listen(zpl_socket socket, zpl_i32 backlog);

/**
 * Uses the given socket (must be zpl_socket_listen) to accept a new incoming connection, optionally returning its address
 * @param socket Socket handle
 * @param addr Pointer to zpl_socket_addr to store the address
 * @return a socket handle for the new connection, or -1 on failure (e.g. if there are no new connections)
 */
ZPL_DEF zpl_socket zpl_socket_accept(zpl_socket socket, zpl_socket_addr *addr);

/**
 * Writes the address the given socket is bound to into the given address pointer, useful when automatically assigning a port
 * @param socket Socket handle
 * @param addr Pointer to zpl_socket_addr to store the address
 * @return 0 on success, non-zero on failure
 */
ZPL_DEF zpl_i32 zpl_socket_get_address(zpl_socket socket, zpl_socket_addr *addr);

/**
 * Writes the host/address and service/port of the given address into given buffers (pointer + size), one buffer may be NULL
 * @param addr Pointer to zpl_socket_addr containing the address
 * @param host Buffer to store the host/address string
 * @param host_size Size of the host buffer
 * @param service Buffer to store the service/port string
 * @param service_size Size of the service buffer
 * @return 0 on success, non-zero on failure
 */
ZPL_DEF zpl_i32 zpl_socket_get_address_info(zpl_socket_addr *addr, char *host, zpl_i32 host_size, char *service, zpl_i32 service_size);

/**
 * Uses the given socket (either ZPL_SOCKET_CONNECT or returned by zpl_socket_accept) to send the given data
 * @param socket Socket handle
 * @param data Pointer to the data to be sent
 * @param size Size of the data
 * @return how much data was actually sent (may be less than data size), or -1 on failure
 */
ZPL_DEF zpl_i32 zpl_socket_send(zpl_socket socket, const char *data, zpl_i32 size);

/**
 * Receives data using the given socket (either ZPL_SOCKET_CONNECT or returned by zpl_socket_accept) into the given buffer
 * @param socket Socket handle
 * @param buffer Pointer to the buffer to receive the data
 * @param size Size of the buffer
 * @return the number of bytes received, 0 on orderly shutdown, or -1 on failure (e.g. no data to receive)
 */
ZPL_DEF zpl_i32 zpl_socket_receive(zpl_socket socket, char *buffer, zpl_i32 size);

/**
 * Uses the given socket to send the given data to the given zpl_socket_addr
 * @param socket Socket handle
 * @param addr Pointer to zpl_socket_addr containing the address to send the data to
 * @param data Pointer to the data to be sent
 * @param size Size of the data
 * @return how much data was actually sent (may be less than data size), or -1 on failure
 */
ZPL_DEF zpl_i32 zpl_socket_send_to(zpl_socket socket, zpl_socket_addr *addr, const char *data, zpl_i32 size);

/**
 * Receives data using the given socket into the given buffer, optionally returning the sender's address
 * @param socket Socket handle
 * @param addr Pointer to zpl_socket_addr to store the sender's address
 * @param buffer Pointer to the buffer to receive the data
 * @param size Size of the buffer
 * @return the number of bytes received, 0 on orderly shutdown, or -1 on failure (e.g. no data to receive)
 */
ZPL_DEF zpl_i32 zpl_socket_receive_from(zpl_socket socket, zpl_socket_addr *addr, char *buffer, zpl_i32 size);

/**
 * Waits either until the given socket has new data to receive or the given time (in seconds) has passed
 * @param socket Socket handle
 * @param time Time to wait in seconds
 * @return 1 if new data is available, 0 if timeout was reached, and -1 on error
 */
ZPL_DEF zpl_i32 zpl_socket_select(zpl_socket socket, zpl_f64 time);

/**
 * Waits either until a socket in the given list has new data to receive or the given time (in seconds) has passed
 * @param sockets Array of socket handles
 * @param count Number of sockets in the array
 * @param time Time to wait in seconds
 * @return 1 or more if new data is available, 0 if timeout was reached, and -1 on error
 */
ZPL_DEF zpl_i32 zpl_socket_multi_select(zpl_socket *sockets, zpl_i32 count, zpl_f64 time);

ZPL_END_C_DECLS

