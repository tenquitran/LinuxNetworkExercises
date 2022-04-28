# Client executables naming scheme

```
1st character: c (client)
2nd character: t (time client) or e (echo client)
3rd character: s (synchronous) or a (asynchronous)
4th character: t (TCP) or u (UDP)
5th character: a (Boost.Asio) or s (Linux sockets)
6th character: 4 for IPv4, 6 for IPv6
```

Server applications reside in subdirectories and therefore don't need to follow these name conventions.

