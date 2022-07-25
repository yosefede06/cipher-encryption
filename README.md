# cipher-encryption
**An algorithm for performing encryption or decryption**

The software can perform three actions:

1) _encode_ - encrypt a string from a file provided to it.
2) _decode_ - decode a string from a file provided to it.
3) _check_ - receive two files, a source file and an encrypted file, and check whether the encryption is correct. If so, the program will print the offset parameter (that is, the k.)

If the user chose to encode or decode, the program will receive through the CLI (Command Line Interface) four arguments in the following order:

1.  Command - a string value indicating the requested command. The valid string values ​​would be
 "encode", "decode" only (more on proper tests, below).
 
2. The offset parameter k - indicates the requested number of indents (for encryption/decryption), so that 𝑘 ∈ ℤ.

3. Path to input file - this file will contain the text that the user requests to encrypt or decrypt.

4. Path to the output file - we will write the text to this file after the encryption or decryption is performed.

If the user chooses to check, the program will receive through the CLI (Command Line Interface)
Three arguments in the following order:
  1.  Command - a string value indicating the command you want to execute, that is the string "check."
  
  2. Path to the source file - this file will contain the original text.

  3. Path to the encrypted file - this file will contain encrypted text (which the software will check    if it is properly encrypted, more on so later).
