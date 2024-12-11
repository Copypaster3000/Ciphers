# Ciphers

This project implements two cryptographic utilities in C: a **Caesar Cipher** and an **XOR Cipher**. These utilities are designed to showcase the use of UNIX I/O system calls, string manipulation, and command-line option parsing. The project includes a `Makefile` for easy compilation and cleanup.

## Features

### 1. **Caesar Cipher**
- Encrypts or decrypts text using a shift-based substitution cipher.
- Supports all printable ASCII characters.
- Command-line options:
  - `-e`: Encrypt (default).
  - `-d`: Decrypt.
  - `-s [shift]`: Specify the shift value (0–95, default: 3).
- Input is read from `stdin` and output to `stdout`.

### 2. **XOR Cipher**
- Encrypts or decrypts data using a key-based XOR cipher.
- Supports arbitrary text input and binary data.
- Command-line options:
  - `-k [key]`: Specify the encryption/decryption key (default: `Xerographic`).
- Input is read from `stdin` and output to `stdout`.

## Files

- **`caesar.c`**: Implements the Caesar Cipher.
- **`xor.c`**: Implements the XOR Cipher.
- **`Makefile`**: Automates building and cleaning the project.

## Build and Run

### Compilation
To compile the project, run:
```bash
make
```

This will generate two executable files:
- `caesar`
- `xor`

### Usage

#### Caesar Cipher
Encrypt a text file:
```bash
./caesar -e -s 5 < input.txt > encrypted.txt
```

Decrypt a text file:
```bash
./caesar -d -s 5 < encrypted.txt > decrypted.txt
```

Type text directly into the program:
- Run the Caesar Cipher program:
  ./caesar -e -s 5
- Type your text directly into the terminal.
- Press 'Ctrl+D' (EOF in Unix) to signal the end of input. The transformed text will be output
  
#### XOR Cipher
Encrypt a file with a custom key:
```bash
./xor -k "MySecretKey" < input.txt > encrypted.bin
```

Decrypt a file with the same key:
```bash
./xor -k "MySecretKey" < encrypted.bin > decrypted.txt
```

### Clean Up
To remove compiled binaries and intermediate files, run:
```bash
make clean
```

## Notes
- The Caesar Cipher only processes printable ASCII characters; non-printing characters are ignored.
- The XOR Cipher supports both text and binary data.
- Ensure input redirection (`<`) and output redirection (`>`) are used as required.
