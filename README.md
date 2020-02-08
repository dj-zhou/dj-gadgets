# dj-tools
## Introduction

This repo contains some small tools from terminal command line to help for daily development. For example, one may want to know each byte of a **float** variable, then he/she can simply run the following command to find it:

```bash
float-to-u8 1.234
```

### Installation

```bash
cd /path/to/dj-tool
make
sudo make install
```

The installed files will be in folder **/usr/local/bin**. They are

```bash
double-to-u8
float-to-u8
u8-to-double
u8-to-float
```

The above files (commands) can be run from any path, if no argument was attached, it will show help information like this:

```bash
usage: 
    u8-to-float <u8> <u8> <u8> <u8> l/b
    u8-to-float <u8> <u8> <u8> <u8> little/big
```

### Examples

#### Check Float Number

Run the command:

```bash
float-to-u8 1.234
```

It will output:

```bash
 float: 1.234000 <=> u8: [182, 243, 157, 63] (little endian)
 float: 1.234000 <=> u8: [0xB6, 0xF3, 0x9D, 0x3F] (little endian)
```

#### Convert u8 (uint8_t) numbers to Float Number

Run either of the following commands:

```bash
u8-to-float 0 0 32 65
u8-to-float 0x00 0x00 0x20 0x41
```

It will output:

```bash
 u8: [0, 0, 32, 65] <=> float: 10.000000 (little endian)
```
