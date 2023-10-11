//
// Created by 30668 on 2023/10/6.
//
#include <stdint.h>
#include <stdio.h>
#include <emscripten.h>


#include "header/core.h"
#include "header/isa.h"
#include "header/program.h"
#include "header/ram.h"

#define DEBUG_MODE 1
/*
 * Currently,the ram system is completely simulated by using the visual memory.So,it is a kinda insecure.
 * TODO:write some necessary tools to deal with the caller and callee in the memory system.
 * TODO:(later!)have a convincingly secure ram system by building a independent visual memory system by an basic array.
 * TODO:the implementation of POP is unrealistic.
 * Warning:check the instruction chunk firstly when you find it broke down because of it's intricate structure.
 */

void instruction_listener();


int EMSCRIPTEN_KEEPALIVE main(){
    cpu_t active_cpu = cpu_build();


//initial operation
    rip_init(&active_cpu.core);
    rsp_init(&active_cpu.core);
    buf_init();

//  instructions chunk
    if(DEBUG_MODE){
        //MOV chunk
//  1000 -> rax
        inst_t inst1 = inst_build(0, od_build(0, (uint64_t)1000, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rbx, 0, 0));
//  rax -> rbx
        inst_t inst2 = inst_build(0, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rbx, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0));
//  0xFFF -> (0x1)
        inst_t inst3 = inst_build(0, od_build(0, (uint64_t)0xFFF, 0, 0, 0), od_build(2, (uint64_t)0x1, 0, 0, 0));
//  (0x1) -> rax
        inst_t inst4 = inst_build(0, od_build(2, (uint64_t)0x1, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0));
//  rax -> (0x666)
        inst_t inst5 = inst_build(0, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0), od_build(2, (uint64_t)0x666, 0, 0, 0));
//  (0x666) -> rcx
        inst_t inst6 = inst_build(0, od_build(2, (uint64_t)0x666, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rcx, 0, 0));

//    core_debug(active_cpu, active_cpu.core);


//PUSH chunk
//  rax
        inst_t inst7 = inst_build(1, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0), od_build(0, 0, 0, 0, 0));


//POP chunk
//  rcx
        inst_t inst8 = inst_build(2, od_build(0, 0, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rcx, 0, 0));

        load_inst_buf(active_cpu.core, inst1);
        load_inst_buf(active_cpu.core, inst2);
        load_inst_buf(active_cpu.core, inst3);
        load_inst_buf(active_cpu.core, inst4);
        load_inst_buf(active_cpu.core, inst5);
        load_inst_buf(active_cpu.core, inst6);
        load_inst_buf(active_cpu.core, inst7);
        load_inst_buf(active_cpu.core, inst8);

        run_inst_buf((core_t*)&active_cpu.core);

//    printf("%llu\n", (uint64_t)*(uint64_t *)(active_cpu.core.reg.rsp +8));
//    printf("%llu\n", (uint64_t)*(uint64_t *)(active_cpu.core.reg.rsp));
//    printf("%llu\n", (uint64_t)*(uint64_t *)(active_cpu.core.reg.rsp -8));

        printf("Implement %i instructions\n" , show_buf_size());
        core_debug(active_cpu, active_cpu.core);
        size_t inst_size = sizeof(inst_t);
    }

    return 0;
}

void instruction_listener(core_t *core){
}

void EMSCRIPTEN_KEEPALIVE web_bridge(int state){
    //init

}

