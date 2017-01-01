Hexdump
=======
Hexdump is a utility that can display the contents of a file in hexademical, decimal, and octal formats.

Build Instructions
------------------
```
cd hexdump/
cmake .
make
```

Example
-------
```
$ ./hexdump CMakeLists.txt
00000000  63 6d 61 6b 65 5f 6d 69  cmake_mi
00000008  6e 69 6d 75 6d 5f 72 65  nimum_re
00000010  71 75 69 72 65 64 28 56  quired(V
00000018  45 52 53 49 4f 4e 20 33  ERSION 3
00000020  2e 36 29 0a 70 72 6f 6a  .6) proj
00000028  65 63 74 28 68 65 78 64  ect(hexd
00000030  75 6d 70 29 0a 0a 73 65  ump)  se
00000038  74 28 43 4d 41 4b 45 5f  t(CMAKE_
00000040  43 5f 53 54 41 4e 44 41  C_STANDA
00000048  52 44 20 39 39 29 0a 0a  RD 99)
00000050  73 65 74 28 53 4f 55 52  set(SOUR
00000058  43 45 5f 46 49 4c 45 53  CE_FILES
00000060  20 6d 61 69 6e 2e 63 29   main.c)
00000068  0a 61 64 64 5f 65 78 65   add_exe
00000070  63 75 74 61 62 6c 65 28  cutable(
00000078  68 65 78 64 75 6d 70 20  hexdump
00000080  24 7b 53 4f 55 52 43 45  ${SOURCE
00000088  5f 46 49 4c 45 53 7d 29  _FILES})
00000090  0a 0a
```

