
## Async client

```
$ delta asynchronous_echo_c++/client.cpp echo_c++/client.cpp

│ 78 │        // Since we are sending asynchronous RPC (`done' is not NULL),                        │    │
│ 79 │        // these objects MUST remain valid until `done' is called.                            │    │
│ 80 │        // As a result, we allocate these objects on heap                                     │    │
│ 81 │        example::EchoResponse* response = new example::EchoResponse();                        │    │
│ 82 │        brpc::Controller* cntl = new brpc::Controller();                                      │    │
│ 83 │                                                                                              │    │
│ 84 │        // Notice that you don't have to new request, which can be modified                   │    │
│ 85 │        // or destroyed just after stub.Echo is called.                                       │    │
│    │                                                                                              │ 61 │        // We will receive response synchronously, safe to put variables
│    │                                                                                              │ 62 │        // on stack.
│ 86 │        example::EchoRequest request;                                                         │ 63 │        example::EchoRequest request;
│ 87 │        request.set_message("hello world");                                                   │    │
│    │                                                                                              │ 64 │        example::EchoResponse response;
│    │                                                                                              │ 65 │        brpc::Controller cntl;
│ 88 │                                                                                              │ 66 │
│ 89 │        cntl->set_log_id(log_id ++);  // set by user                                          │    │
│ 90 │        if (FLAGS_send_attachment) {                                                          │    │
│ 91 │            // Set attachment which is wired to network directly instead of                   │    │
│ 92 │            // being serialized into protobuf messages.                                       │    │
│ 93 │            cntl->request_attachment().append("foo");                                         │    │
│ 94 │        }                                                                                     │    │
│    │                                                                                              │ 67 │        request.set_message("hello world");
│ 95 │                                                                                              │ 68 │
│ 96 │        // We use protobuf utility `NewCallback' to create a closure object                   │    │
│ 97 │        // that will call our callback `HandleEchoResponse'. This closure                     │    │
│ 98 │        // will automatically delete itself after being called once                           │    │
│ 99 │        google::protobuf::Closure* done = brpc::NewCallback(                                  │    │
│ 100│            &HandleEchoResponse, cntl, response);                                             │    │
│ 101│        stub.Echo(cntl, &request, response, done);                                            │    │
│    │                                                                                              │ 69 │        cntl.set_log_id(log_id ++);  // set by user
│    │                                                                                              │ 70 │        // Set attachment which is wired to network directly instead of
│    │                                                                                              │ 71 │        // being serialized into protobuf messages.
│    │                                                                                              │ 72 │        cntl.request_attachment().append(FLAGS_attachment);
│ 102│                                                                                              │ 73 │
│ 103│        // This is an asynchronous RPC, so we can only fetch the result                       │    │
│ 104│        // inside the callback                                                                │    │
│ 105│        sleep(1);                                                                             │    │
│    │                                                                                              │ 74 │        // Because `done'(last parameter) is NULL, this function waits until
│    │                                                                                              │ 75 │        // the response comes back or error occurs(including timedout).
│    │                                                                                              │ 76 │        stub.Echo(&cntl, &request, &response, NULL);
│    │                                                                                              │ 77 │        if (!cntl.Failed()) {
│    │                                                                                              │ 78 │            LOG(INFO) << "Received response from " << cntl.remote_side()
│    │                                                                                              │ 79 │                << " to " << cntl.local_side()
│    │                                                                                              │ 80 │                << ": " << response.message() << " (attached="
│    │                                                                                              │ 81 │                << cntl.response_attachment() << ")"
│    │                                                                                              │ 82 │                << " latency=" << cntl.latency_us() << "us";
│    │                                                                                              │ 83 │        } else {
│    │                                                                                              │ 84 │            LOG(WARNING) << cntl.ErrorText();
│    │                                                                                              │ 85 │        }
│    │                                                                                              │ 86 │        usleep(FLAGS_interval_ms * 1000L);
```


