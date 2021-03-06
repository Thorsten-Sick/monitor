Signature::

    * Calling convention: WINAPI
    * Category: socket
    * Library: ws2_32


WSAStartup
==========

Signature::

    * Is success: ret == 0
    * Return value: int

Parameters::

    ** WORD wVersionRequested
    *  LPWSADATA lpWSAData


gethostbyname
=============

Signature::

    * Is success: ret != NULL
    * Return value: struct hostent *

Parameters::

    ** const char *name


socket
======

Signature::

    * Return value: SOCKET

Parameters::

    ** int af
    ** int type
    ** int protocol

Logging::

    i socket ret


connect
=======

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  const struct sockaddr *name
    *  int namelen

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(name, &ip, &port);

Logging::

    s ip_address ip
    i port port


send
====

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  const char *buf
    *  int len
    *  int flags

Logging::

    b buffer len, buf


sendto
======

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  const char *buf
    *  int len
    ** int flags
    *  const struct sockaddr *to
    *  int tolen

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(to, &ip, &port);

Logging::

    s ip_address ip
    i port port
    b buffer ret > 0 ? ret : 0, buf


recv
====

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  char *buf
    *  int len
    *  int flags

Logging::

    b buffer len, buf


recvfrom
========

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  char *buf
    *  int len
    ** int flags
    *  struct sockaddr *from
    *  int *fromlen

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(from, &ip, &port);

Logging::

    s ip_address ip
    i port port


accept
======

Signature::

    * Return value: SOCKET

Parameters::

    ** SOCKET s socket
    *  struct sockaddr *addr
    *  int *addrlen

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(addr, &ip, &port);

Logging::

    s ip_address ip
    i port port


bind
====

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  const struct sockaddr *name
    *  int namelen

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(name, &ip, &port);

Logging::

    s ip_address ip
    i port port


listen
======

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket
    ** int backlog


select
======

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  fd_set *readfds
    *  fd_set *writefds
    *  fd_set *exceptfds
    *  const struct timeval *timeout


setsockopt
==========

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket
    ** int level
    ** int optname
    *  const char *optval
    *  int optlen

Logging::

    b buffer optlen, optval


ioctlsocket
===========

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket
    ** long cmd
    ** u_long *argp


closesocket
===========

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket


shutdown
========

Signature::

    * Is success: ret != SOCKET_ERROR
    * Return value: int

Parameters::

    ** SOCKET s socket
    ** int how


WSAAccept
=========

Signature::

    * Return value: SOCKET

Parameters::

    ** SOCKET s socket
    *  struct sockaddr *addr
    *  LPINT addrlen
    *  LPCONDITIONPROC lpfnCondition
    *  DWORD_PTR dwCallbackData

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(addr, &ip, &port);

Logging::

    s ip_address ip
    i port port


WSARecv
=======

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  LPWSABUF lpBuffers
    *  DWORD dwBufferCount
    *  LPDWORD lpNumberOfBytesRecvd
    *  LPDWORD lpFlags
    *  LPWSAOVERLAPPED lpOverlapped
    *  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine


WSARecvFrom
===========

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  LPWSABUF lpBuffers
    *  DWORD dwBufferCount
    *  LPDWORD lpNumberOfBytesRecvd
    *  LPDWORD lpFlags
    *  struct sockaddr *lpFrom
    *  LPINT lpFromlen
    *  LPWSAOVERLAPPED lpOverlapped
    *  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(lpFrom, &ip, &port);

Logging::

    s ip_address ip
    i port port


WSASend
=======

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  LPWSABUF lpBuffers
    *  DWORD dwBufferCount
    *  LPDWORD lpNumberOfBytesSent
    *  DWORD dwFlags
    *  LPWSAOVERLAPPED lpOverlapped
    *  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine


WSASendTo
=========

Signature::

    * Is success: ret > 0
    * Return value: int

Parameters::

    ** SOCKET s socket
    *  LPWSABUF lpBuffers
    *  DWORD dwBufferCount
    *  LPDWORD lpNumberOfBytesSent
    *  DWORD dwFlags
    *  const struct sockaddr *lpTo
    *  int iToLen
    *  LPWSAOVERLAPPED lpOverlapped
    *  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(lpTo, &ip, &port);

Logging::

    s ip_address ip
    i port port


WSASocketA
==========

Signature::

    * Return value: SOCKET

Parameters::

    ** int af
    ** int type
    ** int protocol
    *  LPWSAPROTOCOL_INFO lpProtocolInfo
    *  GROUP g
    *  DWORD dwFlags

Logging::

    i socket ret


WSASocketW
==========

Signature::

    * Return value: SOCKET

Parameters::

    ** int af
    ** int type
    ** int protocol
    *  LPWSAPROTOCOL_INFO lpProtocolInfo
    *  GROUP g
    *  DWORD dwFlags

Logging::

    i socket ret


ConnectEx
=========

Signature::

    * Return value: BOOL

Parameters::

    ** SOCKET s socket
    *  const struct sockaddr *name
    *  int namelen
    *  PVOID lpSendBuffer
    *  DWORD dwSendDataLength
    *  LPDWORD lpdwBytesSent
    *  LPOVERLAPPED lpOverlapped

Pre::

    const char *ip = NULL; int port = 0;
    get_ip_port(name, &ip, &port);

Logging::

    s ip_address ip
    i port port
    B buffer lpdwBytesSent, lpSendBuffer


TransmitFile
============

Signature::

    * Return value: BOOL

Parameters::

    ** SOCKET hSocket socket
    ** HANDLE hFile file_handle
    ** DWORD nNumberOfBytesToWrite
    ** DWORD nNumberOfBytesPerSend
    *  LPOVERLAPPED lpOverlapped
    *  LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers
    *  DWORD dwFlags
