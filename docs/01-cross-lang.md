
## TODOs

- [ ] Explain in protocol(in theory)
- [ ] Capture an example by wireshark(Unary, Stream, Max Streams, Huge message size, etc)
- [ ] Explain in Code(brpc server vs grpc server)

## brpc server

```
$ ./echo_server
I0207 04:06:21.086003 464140 src/brpc/server.cpp:1114] Server[GreeterImpl] is serving on port=50051.
I0207 04:06:21.086241 464140 src/brpc/server.cpp:1117] Check out http://gserver:50051 in web browser.

$ netstat -anlop | grep (pgrep echo_server)
(Not all processes could be identified, non-owned process info
 will not be shown, you would have to be root to see it all.)
tcp        0      0 0.0.0.0:50051           0.0.0.0:*               LISTEN      464140/./echo_serve  off (0.00/0/0)
```

For the port `50051`, brpc handle both protocols:
- [HTTP/2](https://en.wikipedia.org/wiki/HTTP/2)
- HTTP/1.1: brpc related information

## Golang CLI client by `evans`

We can use [evans](https://github.com/ktr0731/evans), which is written in golang, to send request to server:

```
evans --host gserver --port 50051  --proto /home/xiaolin/ghq/github.com/apache/brpc/example/grpc_c++/helloworld.proto

  ______
 |  ____|
 | |__    __   __   __ _   _ __    ___
 |  __|   \ \ / /  / _. | | '_ \  / __|
 | |____   \ V /  | (_| | | | | | \__ \
 |______|   \_/    \__,_| |_| |_| |___/

 more expressive universal gRPC client


helloworld.Greeter@gserver:50051> call SayHello
name (TYPE_STRING) => Xiaolin
{
  "message": "Hello Xiaolin"
}

helloworld.Greeter@gserver:50051>
Good Bye :)
evans: deprecated usage, please use sub-commands. see `evans -h` for more details.
```

## Golang benchmark tools

See [ghz](https://github.com/bojand/ghz)

Benchmark results at [03-brpc-internals.md](./03-brpc-internals.md).

## References

- (grpc PROTOCOL-HTTP2)[https://github.com/grpc/grpc/blob/master/doc/PROTOCOL-HTTP2.md]
- (RFC-7540)[https://www.rfc-editor.org/rfc/rfc7540]

