#ifndef _INET_H
#define _INET_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Doxygen documentation
 ****************************************************************************/

/*! @file inet.h
 *  @brief Header file for the inet API.
 *
 *  The aim of the inet library is to create a sufficient and easy
 *  to use API for networking. WinSock and UNIX sockets both
 *  originate from BSD and share the same syntax. So inet is a nice
 *  wrap around both APIs, making it crossplatform and intuitive.
 *
 *  DISCLAIMER: Most of the source code and concepts are copied over
 *  from The Linux Programming Interface by Michael Kerrisk.
 */

/* If we are we on Windows, we want a single define for it.
 */
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
  #define _WIN32
#endif

#ifdef _WIN32
  #ifndef WINVER
    #define WINVER 0x0600
  #endif
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0600
  #endif
  #ifndef NTDDI_VERSION
    #define NTDDI_VERSION 0x06000000
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
#else
  #define _DEFAULT_SOURCE
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netinet/in.h>
  #include <netdb.h>
  #include <unistd.h>
#endif


/*****************************************************************************
 * inet API
 ****************************************************************************/

/*! @def Special value of an invalid socket
 *
 *  Every function in the inet API that is socket related will return a file
 *  descriptor referring to that socket. In case the function failed, the
 *  special value INET_INVALID_SOCKET will be returned. Its primary use is
 *  error detection.
 */

#ifdef _WIN32
  #define INET_INVAL_SOCK INVALID_SOCKET
#else
  #define INET_INVAL_SOCK -1
#endif

/*! @typedef Socket type
 *
 *  Socket type
 */

#ifdef _WIN32
  typedef unsigned INETsock;
#else
  typedef int INETsock;
#endif

/*! @brief Initialize inet library
 *
 *  Call this function before any other inet calls.
 *
 *  @return 0 on success or any other value on failure
 */

int inetInit ();

/*! @brief Perform deinitialization
 *
 *  Call this whenever you are done using inet. It MAY perform some form
 *  of cleaning up
 *
 *  @return 0 on success or any other value on failure
 */

int inetQuit ();

/*! @brief Read data from socket
 *
 *  Attempts to read exactly @ref count bytes of data. It either
 *  succeeds, sees end-of-file and returns the amount of bytes
 *  read before reading enf-of-file, or fails.
 *
 *  @param sock Socket to read from
 *  @param buf Buffer to store information to
 *  @param count Number of bytes to read
 *  @return Number of bytes read or -1 on failure
 *
 *  @remark On UNIX systems, calling this function as opposed to
 *  read(2) has two advantages. First, it is signal-safe, and second,
 *  it will always attempt to read the specified amount of bytes.
 */

ssize_t inetReadn (INETsock sock, void* buf, size_t count);

/*! @brief Write data to socket
 *
 *  Attempts to write exactly @ref count number of bytes. It either
 *  returns @ref count, indication success, or -1 in case of an
 *  error.
 *
 *  @param sock Socket to read from
 *  @param buf Buffer to draw information from
 *  @param count Number of bytes to write
 *  @return @ref count or -1 on failure
 *
 *  @remark Just like @ref inetReadn, @ref inetWriten also has the
 *  advantage of being signal-safe and will always attempt to reach
 *  the @ref count mark, unless some error has arisen.
 */

ssize_t inetWriten (INETsock sock, void* buf, size_t count);

/*! @brief Close an open socket
 *
 *  Use this function only after finishing what you need to do. It is
 *  implementaion defined that will happen if you try to read or write
 *  to the target socket. Note that peer will receive end-of-file.
 *
 *  @param sock Socket to close
 *  @return 0 on success, any other value on failure
 */

int inetCloseSock (INETsock sock);

/*! @brief Create and bind a socket
 *
 *  This function is used for creating a socket. Later, it can be connect
 *  via @ref inetConnect or used with any UNIX socket API. It will be
 *  boind to either the wildcard IP address, in case @ref service is non-NULL
 *  or to an emphemeral port.
 *
 *  @param service Port number
 *  @param type Either SOCK_STREAM or SOCK_DGRAM
 *  @return File desciptor with which to communicate
 */

INETsock inetBind (const char* service, int type);

/*! @brief Establish a connection
 *
 *  Establish a connection.
 *
 *  @param sock A socket returned from @ref inetBind
 *  @param host Ipv4 address of host
 *  @param service Service to which to connect (on host)
 *  @return 0 on success, any other value on failure
 */

int inetConnect (INETsock sock, const char* host, const char* service);

/*! @brief Listen on incoming connections
 *
 *  Creates a socket with the wildcard IP address and specified service.
 *  The type of the socket is SOCK_STREAM, which means that this function
 *  is best suited for a TCP/IP server.
 *
 *  @param service Port on which to listen
 *  @param backlog Same as listen(2)
 *  @return File desciptor with which to communicate
 */

int inetListen (const char* service, int backlog);

/*! @brief Aceept any incomming connection
 *
 *  Accept any incomming connection on socket returned
 *  from @ref inetListen.
 *
 *  @param sock Socket marked as listening
 *  @param addr IPv4 network byte order address of peer
 *  @param port Port number in netowkr byte order of peer
 *  @return File descriptor with which to communicate
 *
 *  @remark You can pass NULL to @ref addr or @port or both
 *  if not interested in the address.
 */

INETsock inetAccept (INETsock lis, unsigned long* addr, unsigned short* port);


#ifdef __cplusplus
}
#endif

#endif /* _INET_H */
