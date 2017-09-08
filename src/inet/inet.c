#include "inet.h"
#include <logger/logger.h>

#include <string.h>
#include <stdio.h>


#ifndef _WIN32
#include <errno.h>
#endif

int inetInit ()
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup (MAKEWORD (1,1), &wsa_data);
#else
    return 0;
#endif
}

int inetQuit ()
{
#ifdef _WIN32
    return WSACleanup();
  #else
    return 0;
#endif
}

ssize_t inetReadn (INETsock sock, void* buf, size_t count)
{
    size_t total = 0;

#ifdef _WIN32
    // TODO
#else
    ssize_t num_read;
    char* byte_buf = (char*)buf;

    while (total < count)
    {
        num_read = read (sock, byte_buf, count - total);

        if (num_read == 0)
        {
            return total;
        }
        if (num_read == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }

        total += num_read;
        byte_buf += num_read;
    }
#endif

    return total;
}

ssize_t inetWriten (INETsock sock, void* buf, size_t count)
{
    size_t total = 0;

#ifdef _WIN32
    // TODO
#else
    ssize_t num_write;
    const char* byte_buf = (const char*)buf;

    while (total < count)
    {
        num_write = write (sock, byte_buf, count - total);

        if (num_write <= 0)
        {
            if (num_write == -1 && errno == EINTR)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }

        total += num_write;
        byte_buf += num_write;
    }
#endif

    return total;
}


int inetCloseSock (INETsock sock)
{
  int status = 0;

#ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0)
    {
        status = closesocket(sock);
    }
#else
    status = shutdown (sock, SHUT_RDWR);
    if (status == 0)
    {
        status = close(sock);
    }
#endif

  return status;
}

INETsock inetBind (const char *service, int type)
{
    if (service == NULL)
    {
        /* Bind to empherial port.
         */

        return socket (AF_INET, type, 0);
    }

    /* First initialize hints
     */
    struct addrinfo hints;

    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_socktype = type;
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;

    /* Aquire addrinfo structures
     */
    struct addrinfo* list;
    int s = getaddrinfo (NULL, service, &hints, &list);

    if (s != 0)
    {
        logWarn ("getaddrinfo(%s) failed. More info: %s", service, gai_strerror (s));

        return INET_INVAL_SOCK;
    }

    /* Iterate through list
     */
    INETsock fd = INET_INVAL_SOCK;
    struct addrinfo* ai;
    for (ai = list; ai != NULL; ai = ai->ai_next)
    {
        fd = socket (ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd == INET_INVAL_SOCK)
        {
            /* Continue trying
             */
            continue;
        }

        if (bind (fd, ai->ai_addr, ai->ai_addrlen) == 0)
        {
            /* Success
             */
            break;
        }

        /* Failed to connect to socket. Free file descriptor
         */
        if (inetCloseSock (fd) != 0)
        {
            logWarn ("failed to close socket");
        }
    }

    /* Exited loop. Done with addrinfo structre. Free up.
     */
    freeaddrinfo (list);

    /* NOTE: if failed to connect to a socket, fd would still be -1.
     * So in any scenario, return fd.
     */
    return fd;
}

int inetConnect (INETsock sock, const char* host, const char* service)
{
    struct sockaddr_in addr;
    memset (&addr, 0, sizeof (struct sockaddr_in));

    addr.sin_family = AF_INET;

#if _WIN32
    if (InetPton (AF_INET, host, &addr.sin_addr) != 1)
#else
    if (inet_pton (AF_INET, host, &addr.sin_addr) != 1)
#endif
    {
        return -1;
    }

    /* Consistency is key
     */
    int port_num;
    if (sscanf (service, "%d", &port_num) != 1)
    {
        return -1;
    }

    addr.sin_port = htons (port_num);

    if (connect (sock, (struct sockaddr*)&addr, sizeof (struct sockaddr_in)) != 0)
    {
        return -1;
    }

    return 0;
}

INETsock inetListen (const char* service, int backlog)
{
    INETsock fd = inetBind (service, SOCK_STREAM);
    if (fd == INET_INVAL_SOCK)
    {
        return INET_INVAL_SOCK;
    }

    if (listen (fd, backlog) != 0)
    {
        return INET_INVAL_SOCK;
    }

    return fd;
}

INETsock inetAccept (INETsock lis, unsigned long* addr, unsigned short* port)
{
    struct sockaddr_in sock_addr;
    socklen_t sock_len = sizeof (struct sockaddr_in);

    INETsock fd = accept (lis, (struct sockaddr*)&sock_addr, &sock_len);

    if (fd == INET_INVAL_SOCK)
    {
        logWarn ("accept(2) failed, returning invalid socket");
        return INET_INVAL_SOCK;
    }

    if (addr != NULL)
    {
       *addr = sock_addr.sin_addr.s_addr;
    }
    if (port != NULL)
    {
        *port = sock_addr.sin_port;
    }

    return fd;
}
