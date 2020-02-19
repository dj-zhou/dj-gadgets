# dj-tools
## A. Introduction

This repository contains some small tools from terminal command line to help for daily development. For example, one may want to know each byte of a **float** variable, then he/she can simply run the following command to find it:

```bash
float-to-u8 1.234
```

### B. Installation

```bash
cd path/to/dj-tool
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

### C. Examples

#### C.1. Check each byte of a float number

Run the command:

```bash
float-to-u8 1.234
```

It will output:

```bash
 float: 1.234000 <=> u8: [182, 243, 157, 63] (little endian)
 float: 1.234000 <=> u8: [0xB6, 0xF3, 0x9D, 0x3F] (little endian)
```

#### C.2. Convert uint8_t numbers to a float number

Run either of the following commands:

```bash
u8-to-float 0 0 32 65
u8-to-float 0x00 0x00 0x20 0x41
```

It will output:

```bash
 u8: [0, 0, 32, 65] <=> float: 10.000000 (little endian)
```

#### C.3. dj-file

This is a project I developed a few years ago for creating a template C project, which contains `main.c` and `Makefile`. It is outdated, but it is a convenience tool to use. 

The following commands show how to install it:

```bash
cd path/to/dj-file
./install.sh
```

The following commands show how to use it:

```bash
cd to/any/empty/folder
djfile
```

Then, you will be editing the `main.c` in vim. 