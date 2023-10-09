//
// Created by 30668 on 2023/10/6.
//
#include <stdint.h>
#include <stdio.h>
#include <emscripten.h>


#include "header/core.h"
#include "header/isa.h"
#include "header/program.h"






int EMSCRIPTEN_KEEPALIVE main(){
    cpu_t active_cpu = cpu_build();


//    instruction chunk
    rip_init(&active_cpu.core);
//  1000 -> rax
    inst_t inst1 = inst_build(0, od_build(0, (uint64_t)1000, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rbx, 0, 0));
//  rax -> rbx
    inst_t inst2 = inst_build(0, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rbx, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0));
//  6 -> (0x1)
    inst_t inst3 = inst_build(0, od_build(0, (uint64_t)6, 0, 0, 0), od_build(2, (uint64_t)0x1, 0, 0, 0));
//  (0x1) -> rax
    inst_t inst4 = inst_build(0, od_build(2, (uint64_t)0x1, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0));
//  rax -> (0x666)
    inst_t inst5 = inst_build(0, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0), od_build(2, (uint64_t)0x666, 0, 0, 0));
//  (0x666) -> rcx
    inst_t inst6 = inst_build(0, od_build(2, (uint64_t)0x666, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rcx, 0, 0));

//    core_debug(active_cpu, active_cpu.core);


    load_inst_buf(active_cpu.core, inst1);
    load_inst_buf(active_cpu.core, inst2);
    load_inst_buf(active_cpu.core, inst3);
    load_inst_buf(active_cpu.core, inst4);
    load_inst_buf(active_cpu.core, inst5);
    load_inst_buf(active_cpu.core, inst6);

    run_inst_buf((core_t*)&active_cpu.core);
    printf("Implement %i instructions\n" , show_buf_size());
    core_debug(active_cpu, active_cpu.core);
    size_t inst_size = sizeof(inst_t);

//    printf("Size of inst_t: %zu bytes\n", inst_size);
//    printf("inst1 is located in %p\n", show_buf_addr(0));
//    printf("inst1 is located in %p\n", show_buf_addr(1));
//    printf("inst3 is located in %p\n", show_buf_addr(2));
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.al- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.ah- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.ax- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.eax- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rax- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rbx- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rcx- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rdx- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rsi- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rdi- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rbp- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rsp- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rip- ADDR_BIAS);
//    printf("%p\n" , (uint64_t)&active_cpu.core.reg.rip + 0x1 - ADDR_BIAS);

    //loop
    while(1){
        return 0;
    }
    return 0;

}

