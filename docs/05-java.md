
## `grpc` programming models in Java

### Synchronized

```java

  PingResponse rsp = blockingStub
                    .withDeadlineAfter(grpcTimeout, TimeUnit.MILLISECONDS)
                    .ping(builder.build());
  log.info("Got Ping response with uuid={}", rsp.getToken());
  if (rsp.getToken().equals(uuid)) {
    return true;
  }
```

### Future Style

```java
ListenableFuture<PingResponse> pingRsp = futureStub.ping(builder.build());
// ...
pingRsp.get();
```

### Asynchronized

```java
asyncStub.ping(builder.build(), new StreamObserver<PingResponse>() {
    @Override
    public void onNext(PingResponse value) {

    }

    @Override
    public void onError(Throwable t) {

    }

    @Override
    public void onCompleted() {

    }
});
```

## References

- [grpc-java](https://github.com/grpc/grpc-java)

