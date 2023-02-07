
Some Notes on [brpc](https://github.com/apache/brpc)
====================================================

This work investigate the [brpc library](https://github.com/apache/brpc) for **Next Generation DingoDB**.

## Overview

As a core part of [braft](https://github.com/baidu/braft), `brpc` provides a high performance framework for inter-nodes communication. It 
wrap many RPC protocols, for example [gRPC](https://github.com/grpc/grpc), RDMA, thrift, and HTTP-RESTful like RPCs. See 
[brpc overview](https://github.com/apache/brpc/blob/master/docs/en/overview.md) for more details.

Project Structure:
```text
tree --charset=ascii -L 1 .

.
|-- README.md
|-- brpc-grpc_c++    # cp brpc-grpc_c++ your_brpc_root_dir/example/grpc_c++
`-- docs
```

## Requirements

For our requirements, we focus on these points for `brpc + gRPC` combination:

- [ ] brpc使用gRPC跨语言交互的验证
- [ ] brpc提供的C++库的梳理
- [ ] brpc支持的编程模型（同步、异步、协程）
- [X] brpc benchmark
- [X] `proto=3`
- [ ] [grpc-java](https://github.com/grpc/grpc-java) vs [brpc-java aka starlight](https://github.com/baidu/starlight)

## Short Reports

### Prepare brpc

Interesting `grpc` tools in golang:
- [evans: cli client](https://github.com/ktr0731/evans)
- [ghz: benchmark](https://github.com/bojand/ghz)
- [buf.build](https://docs.buf.build/introduction)

### brpc and cross language example

See [brpc-cross-lang](./docs/01-cross-lang.md).

### brpc and its depedencies

See [brpc depedencies](./docs/02-depedencies.md).

### brpc programming models

See [brpc programming models](./docs/03-brpc-internals.md).

### brpc benchmarks

See [brpc benchmarks](./docs/04-benchmarks.md).

### brpc/grpc in java

See [brpc java](./docs/05-java.md).

### `proto3`

In the simple `grpc_c++` example, `proto3` works fine.

Difference between `proto2` and `proto3`:

- [proto2 vs proto3](https://www.hackingnote.com/en/versus/proto2-vs-proto3/index.html)

## Reference

- https://github.com/apache/brpc
- https://github.com/apache/brpc/blob/master/docs/
- https://github.com/baidu/braft
- http://jinke.me/2018-09-14-coroutine-context-switch/

