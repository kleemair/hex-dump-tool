# Hex Dump Tool

A simple hex dump tool written in C that reads any file byte-by-byte 
and displays it in the classic offset / hex / ASCII column format, 
similar to tools like `xxd` or `hexdump -C`.

## Example Output

```
Offset          Hexadecimal                                      ASCII
00000000   48 65 6c 6c 6f 2c 20 57 6f 72 6c 64 21 0d 0a 42   |Hello, World!..B|
00000010   6c 61 68 20 62 6c 61 68 20 62 6c 61 68 62 0d 0a   |lah blah blahb..|
```

## Features
- Reads files in binary mode, so it works on any file type (text, images, executables, etc.)
- Displays byte offset, hex representation, and ASCII representation side by side
- Non-printable bytes are shown as `.` in the ASCII column
- Future features to come...

## Build & Run
```bash
gcc hexdumptool.c -o hexdump
./hexdump <filename>
```
## What I learned
Built this to get started in C and practice low-level file managment and pointer/byte manipulation
in C as part of learning C for reverse engineering. Notable bug I ran into and fixed: 
`char` is signed by default, which caused the output to be messed up in the terminal
which I fixed by casting to `unsigned char` before printing.
