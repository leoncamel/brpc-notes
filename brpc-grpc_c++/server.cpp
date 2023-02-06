// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

// A server to receive HelloRequest and send back HelloReply

#include <chrono>
#include <thread>
#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include <brpc/restful.h>
#include "helloworld.pb.h"

#if defined(__GNUC__)
#define BENCHMARK_UNUSED __attribute__((unused))
#define BENCHMARK_ALWAYS_INLINE __attribute__((always_inline))
#define BENCHMARK_NOEXCEPT noexcept
#define BENCHMARK_NOEXCEPT_OP(x) noexcept(x)
#elif defined(_MSC_VER) && !defined(__clang__)
#define BENCHMARK_UNUSED
#define BENCHMARK_ALWAYS_INLINE __forceinline
#if _MSC_VER >= 1900
#define BENCHMARK_NOEXCEPT noexcept
#define BENCHMARK_NOEXCEPT_OP(x) noexcept(x)
#else
#define BENCHMARK_NOEXCEPT
#define BENCHMARK_NOEXCEPT_OP(x)
#endif
#define __func__ __FUNCTION__
#else
#define BENCHMARK_UNUSED
#define BENCHMARK_ALWAYS_INLINE
#define BENCHMARK_NOEXCEPT
#define BENCHMARK_NOEXCEPT_OP(x)
#endif

template <class Tp>
inline BENCHMARK_ALWAYS_INLINE void DoNotOptimize(Tp const& value) {
  asm volatile("" : : "r,m"(value) : "memory");
}

template <class Tp>
inline BENCHMARK_ALWAYS_INLINE void DoNotOptimize(Tp& value) {
#if defined(__clang__)
  asm volatile("" : "+r,m"(value) : : "memory");
#else
  asm volatile("" : "+m,r"(value) : : "memory");
#endif
}

// Force the compiler to flush pending writes to global memory. Acts as an
// effective read/write barrier
inline BENCHMARK_ALWAYS_INLINE void ClobberMemory() {
  asm volatile("" : : : "memory");
}

DEFINE_int32(port, 50051, "TCP Port of this server");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no "
             "read/write operations during the last `idle_timeout_s'");
DEFINE_bool(gzip, false, "compress body using gzip");

void heavy_computation(int n) {
  int running_total = 23;
  for (int i=0; i < n; i++) {
    running_total = 37 * running_total + i;
  }
  DoNotOptimize(running_total);
  ClobberMemory();
}

class GreeterImpl : public helloworld::Greeter {
public:
    GreeterImpl() {}
    virtual ~GreeterImpl() {}
    void SayHello(google::protobuf::RpcController* cntl_base,
                 const helloworld::HelloRequest* req,
                 helloworld::HelloReply* res,
                 google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);
        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
        if (FLAGS_gzip) {
            cntl->set_response_compress_type(brpc::COMPRESS_TYPE_GZIP);
        }

        // Method 1: sleep
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Method 2:
        heavy_computation(10000000);

        res->set_message("Hello " + req->name());
    }
};

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);

    // Generally you only need one Server.
    brpc::Server server;

    GreeterImpl http_svc;

    // Add services into server. Notice the second parameter, because the
    // service is put on stack, we don't want server to delete it, otherwise
    // use brpc::SERVER_OWNS_SERVICE.
    if (server.AddService(&http_svc,
                          brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add http_svc";
        return -1;
    }

    // Start the server.
    brpc::ServerOptions options;
    options.num_threads = 4;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    if (server.Start(FLAGS_port, &options) != 0) {
        LOG(ERROR) << "Fail to start HttpServer";
        return -1;
    }

    // Wait until Ctrl-C is pressed, then Stop() and Join() the server.
    server.RunUntilAskedToQuit();
    return 0;
}
