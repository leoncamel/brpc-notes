
Some Notes on [brpc](https://github.com/apache/brpc)
====================================================

This work investigate the [brpc library](https://github.com/apache/brpc) for **Next Generation DingoDB**.

## Overviw

As a core part of [braft](https://github.com/baidu/braft), `brpc` provides a high performance framework for inter-nodes communication. It 
wrap many RPC protocols, for example [gRPC](https://github.com/grpc/grpc), RDMA, thrift, and HTTP-RESTful like RPCs. See 
[brpc overview](https://github.com/apache/brpc/blob/master/docs/en/overview.md) for more details.


## Requirements

For our requirements, we focus on these points for `brpc + gRPC` combination:

- [ ] brpc使用gRPC跨语言交互的验证
- [ ] brpc提供的C++库的梳理
- [ ] brpc支持的编程模型（同步、异步、协程）

## Short Reports

### Prepare brpc

### brpc and cross language example

See [brpc-cross-lang](./docs/01-cross-lang.md).

### brpc and its depedencies

See [brpc depedencies](./docs/02-depedencies.md).

### brcp programming models

See [brpc internals](./docs/03-brpc-internals.md).

## Reference

- https://github.com/apache/brpc
- https://github.com/baidu/braft

