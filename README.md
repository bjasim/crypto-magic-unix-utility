# CryptoMagic

CryptoMagic is a Linux-based encrypting and decrypting utility written in C. It allows you to secure your ASCII files by encrypting them, making their contents unreadable until decrypted by this utility.

## Prerequisites

Before using CryptoMagic, make sure you have the following prerequisites:
- A Linux-based operating system
- Basic knowledge of using the command line

## Installation

1. Clone this repository to your local machine.
2. Compile the utility using the provided makefile:
   make

You're ready to use CryptoMagic!
## Usage
To encrypt a file:
./cryptoMagic -encrypt input.txt

To decrypt a file:
./cryptoMagic -decrypt encrypted.crp

Replace input.txt and encrypted.crp with your file names.

## Examples
Encrypt a file:
./cryptoMagic -encrypt secret.txt

Decrypt a file:
./cryptoMagic -decrypt confidential.crp






