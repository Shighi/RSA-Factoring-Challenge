# RSA Factoring Challenge

This project contains solutions for factoring numbers and RSA factoring challenges.

## Description

- `factors` - Factorizes numbers into a product of two smaller numbers.
- `rsa` - Finds prime factors of RSA numbers.

## Requirements
- Ubuntu 20.04 LTS
- Python 3

## Usage

### Factoring
```bash
./factors <file>
```
Where `<file>` contains natural numbers to factor (one per line)

Example:
```bash
./factors tests/test00
```

### RSA Factoring
```bash
./rsa <file>
```
Where `<file>` contains a single number to factor into two primes

Example:
```bash
./rsa tests/rsa-1
```

## Author
Daisy Shighi
