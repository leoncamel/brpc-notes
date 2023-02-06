
## Static Linking Dependencies

```text
$ ldd echo_client
        linux-vdso.so.1 (0x00007fff4e372000)
        libssl.so.3 => /lib/x86_64-linux-gnu/libssl.so.3 (0x00007fde04945000)
        libcrypto.so.3 => /lib/x86_64-linux-gnu/libcrypto.so.3 (0x00007fde04503000)
        libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007fde044e7000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fde042bd000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fde041d6000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fde041b4000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fde03f8c000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fde05b4c000) 

$ ldd ./echo_server
        linux-vdso.so.1 (0x00007ffe2cf89000)
        libssl.so.3 => /lib/x86_64-linux-gnu/libssl.so.3 (0x00007f249079f000)
        libcrypto.so.3 => /lib/x86_64-linux-gnu/libcrypto.so.3 (0x00007f249035d000)
        libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007f2490341000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f2490117000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f2490030000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f249000e000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f248fde6000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f24919a6000)
```

