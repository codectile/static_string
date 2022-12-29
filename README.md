# static_string
A basic string class focusing on compile-time operations

# Motivation
I was working on something and needed to work with string in compile time. `std::string` was a no go for me as it was allocating data on the heap and my strings were long enough for SSO. The `static_string` class tries to do most operations in compile-time. I have implemented basic functionality such as concatenations, substrings, etc. but it still lacks a fair chunk. I designed the class based on my usage and you can always add more functionality. This class was written out the top my head and I cannot promise the robustness of the functionality that this class provides. Please consider `static_string`s as just a wrapper around null terminated C-Strings and a lot can go wrong if misused. Use at your own risk :)

# Example
```c++
#include <stdio.h>
#include "static_string.hpp"

int main()
{
    constexpr static_string str("hello");
    constexpr static_string str2(" world!");
    constexpr static_string str3 = str + str2;
    printf("New string: %s\n", str3.data());
    return 0;
}
```

## Assembly output of GCC with optimization -O2
```
.LC1:
        .string "New string: %s\n"
main:
        sub     rsp, 520
        xor     eax, eax
        mov     ecx, 64
        mov     rdi, rsp
        mov     rsi, rsp
        rep stosq
        mov     rax, QWORD PTR .LC0[rip]
        mov     edi, OFFSET FLAT:.LC1
        mov     DWORD PTR [rsp+8], 6581362
        mov     QWORD PTR [rsp], rax
        xor     eax, eax
        call    printf
        xor     eax, eax
        add     rsp, 520
        ret
.LC0:
        .byte   104
        .byte   101
        .byte   108
        .byte   108
        .byte   111
        .byte   32
        .byte   119
        .byte   111
```
