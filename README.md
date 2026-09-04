# Hex Dump Tool

A simple hex dump tool written in C that reads any file byte-by-byte 
and displays it in the classic offset / hex / ASCII column format, 
similar to tools like `xxd` or `hexdump -C`.

## Example Output

```
Offset     Hexadecimal                                      ASCII
00000000   48 65 6c 6c 6f 2c 20 57 6f 72 6c 64 21 0d 0a 62 |Hello, World!..b|
00000010   6c 61 68 20 62 6c 61 68 20 62 6c 61 68 0d 0a 62 |lah blah blah..b|
00000020   6c 61 68 20 62 6c 61 68 20 62 6c 61 68 20 57 6f |lah blah blah Wo|
00000030   72 6c 64 61 73 64 0d 0a                         |rldasd..|

Found "World" 2 times:
Number 1 found at offset: 00000000
Number 2 found at offset: 00000020
```

## Features
- Reads files in binary mode, so it works on any file type (text, images, executables, etc.)
- Displays byte offset, hex representation, and ASCII representation side by side
- Non-printable bytes are shown as `.` in the ASCII column
- Search for a text pattern across the entire file, reporting every offset
where it occurs called with ```--search "<text>"```

## Build & Run
```
gcc hexdumptool.c -o hexdump
hexdump.exe <filename>
```
## What I learned
Built this to get started in C and practice low-level file management and pointer/byte manipulation
in C as part of learning C for reverse engineering. Notable bugs I ran into and fixed: 
- `char` is signed by default, which caused the output to be messed up in the terminal
which I fixed by casting to `unsigned char` before printing.
- When I started to make the search function I only thought about textfiles and decided to choose ```'\0'``` as
factor to decide when the file ended but the problem here is that other file types like for example png frequently
use ```'\0'``` in the middle of the file. So I had to stop using ```strstr``` to look for the searched text and completly change everything
to work with ```memcmp```.
