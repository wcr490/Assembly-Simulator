//
// Created by 30668 on 2023/10/6.
//

#ifndef SIMULATOR_CORE_H
#define SIMULATOR_CORE_H


#include <stdint.h>
//#include "program.h"
//#include <emscripten.h>

#define REGISTER_QUANTITY  20

typedef struct FLAG_STRUCT{
    uint16_t CF;  //carry
    uint16_t ZF;  //zero
    uint16_t SF;  //negative
    uint16_t OF;  //overflow

}flag_t;

typedef struct REG_STRUCT
{
    union
    {
        struct
        {
            uint8_t al;
            uint8_t ah;
        };
        uint16_t ax;
        uint32_t eax;
        uint64_t rax;
    };
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;         //stack pointer

    uint64_t rip;         //program procedure pointer
} reg_t;

typedef struct CORE{
    reg_t reg;
    flag_t flag;
}core_t;

typedef struct CPU{
    core_t core;
}cpu_t;




cpu_t cpu_build();
void cpu_init(cpu_t *cpu);
void flag_init(cpu_t *cpu);
void core_debug(cpu_t cpu,core_t core);
void core_debug_web(cpu_t cpu,core_t core);
void rip_init(core_t *core);

#endif
