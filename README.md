# LogansBestFriend

LogansBestFriend is a practical modification of the simple shellcode loader "GregsBestFriend" from WhiteKnightLabs, which uses regex to bypass sandbox detections.

LogansBestFriend's configuration does not pop a debug CMD window and executes as a background process, as well as decrypts stager shellcode in memory.

Stager shellcode in the C format can be encrypted by using:

```
#include <stdio.h>

unsigned char code[] = "\x90\x90\x90"; // Enter shellcode here

int main()
{
    char key = 'K'; // Change XOR key here
    int i = 0;
    for (i; i<sizeof(code); i++)
    {
        printf("\\x%02x",code[i]^key);
    }
}

```