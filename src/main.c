//
// Created by 30668 on 2023/10/6.
//
#include <stdint.h>
#include <stdio.h>
#include <emscripten.h>
#include <string.h>
#include <ctype.h>


#include "header/core.h"
#include "header/isa.h"
#include "header/program.h"
#include "header/ram.h"

#define DEBUG_MODE 1
#define INPUT_MAX  20
/*
 * Currently,the ram system is completely simulated by using the visual memory.So,it is a kinda insecure.
 * TODO:write some necessary tools to deal with the caller and callee in the memory system.
 * TODO:(later!)have a convincingly secure ram system by building a independent visual memory system by an basic array.
 * TODO:the implementation of POP is unrealistic.
 * Warning:check the instruction chunk firstly when you find it broke down because of it's intricate structure.
 * TODO:improve the interface in html file to make the command more visual.
 * TODO:refine more imperative instruction in the isa.
 */
cpu_t active_cpu;


char* registers[REGISTER_QUANTITY] = {
        "rax",
        "rbx",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbp",
        "rsp"
};

uint64_t reflect_register(char reg[INPUT_MAX]) {
    if (strcmp(reg, "rax") == 0) {
        return (uint64_t)&active_cpu.core.reg.rax;
    } else if (strcmp(reg, "rbx") == 0) {
        return (uint64_t)&active_cpu.core.reg.rbx;
    } else if (strcmp(reg, "rcx") == 0) {
        return (uint64_t)&active_cpu.core.reg.rax;
    } else if (strcmp(reg, "rdx") == 0) {
        return (uint64_t)&active_cpu.core.reg.rax;
    } else if (strcmp(reg, "rsi") == 0) {
        return (uint64_t)&active_cpu.core.reg.rsi;
    } else if (strcmp(reg, "rdi") == 0) {
        return (uint64_t)&active_cpu.core.reg.rdi;
    } else if (strcmp(reg, "rbp") == 0) {
        return (uint64_t)&active_cpu.core.reg.rbp;
    } else if (strcmp(reg, "rsp") == 0) {
        return (uint64_t)&active_cpu.core.reg.rsp;
    } else if (strcmp(reg, "rip") == 0) {
        return (uint64_t)&active_cpu.core.reg.rip;
    } else {
        return 0;
    }
}



int EMSCRIPTEN_KEEPALIVE main(){
    active_cpu = cpu_build();
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
        inst_t inst9 = inst_build(1, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rbx, 0, 0), od_build(0, 0, 0, 0, 0));


//POP chunk
//  rcx
        inst_t inst8 = inst_build(2, od_build(0, 0, 0, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rcx, 0, 0));


//ADD
//  rbx -> rcx
        inst_t inst10 = inst_build(3, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rbx, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rcx, 0, 0));

//SUB
//  rbx -> rax
        inst_t inst11 = inst_build(4, od_build(1, 0, (uint64_t)&active_cpu.core.reg.rbx, 0, 0), od_build(1, 0, (uint64_t)&active_cpu.core.reg.rax, 0, 0));

        load_inst_buf(active_cpu.core, inst1);
        load_inst_buf(active_cpu.core, inst2);
        load_inst_buf(active_cpu.core, inst3);
        load_inst_buf(active_cpu.core, inst4);
        load_inst_buf(active_cpu.core, inst5);
        load_inst_buf(active_cpu.core, inst6);
        load_inst_buf(active_cpu.core, inst7);
        load_inst_buf(active_cpu.core, inst8);
        load_inst_buf(active_cpu.core, inst9);
        load_inst_buf(active_cpu.core, inst10);
        load_inst_buf(active_cpu.core, inst11);
        run_inst_buf((core_t*)&active_cpu.core);
        printf("Implement %i instructions\n" , show_buf_size());
        core_debug(active_cpu, active_cpu.core);
//        core_debug_web(active_cpu, active_cpu.core);
        size_t inst_size = sizeof(inst_t);
    }

    return 0;
}

void instruction_listener(int state, char arg1[INPUT_MAX], char arg2[INPUT_MAX]) {
    /*
     * 0 -> Imm
     * 1 -> REG
     * 2 -> MEM
     */
    int arg1_type = 0;
    int arg2_type = 0;
    int val1;
    int val2;

    // check if it is a number
    if (isdigit(arg1[0])) {
        if(arg1[0] == 0){
            arg1_type = 2;
            val1 = strtol(arg1, NULL, 16);
        }
        else{
            arg1_type = 0;
            val1 = strtol(arg1, NULL, 10);
        }
    }
    if (isdigit(arg2[0])) {
        if(arg2[0] == 0){
            arg2_type = 2;
            val2 = strtol(arg2, NULL, 16);
        }
        else{
            arg2_type = 0;
            val2 = strtol(arg2, NULL, 10);
        }
    }

    // check if it is a register
    for (int i = 0; i < REGISTER_QUANTITY; i++) {
        if (strcasecmp(arg1, registers[i]) == 0) {
            arg1_type = 1;
        }
    }
    for (int j = 0; j < REGISTER_QUANTITY; j++) {
        if (strcasecmp(arg2, registers[j]) == 0) {
            arg2_type = 1;
        }
    }

    // MOV
    /*
    Imm -> reg
    Imm -> mem
    reg -> reg
    reg -> mem
    mem -> reg
    */
    //void run_single(core_t *core, inst_t inst)
    if (state == 2) {
        //Imm -> reg
        if(arg1_type == 0&&arg2_type == 1){
            inst_t inst = inst_build(0, od_build(0, (uint64_t)val1, 0, 0, 0), od_build(1, 0, reflect_register(arg2), 0, 0));
            run_single(&active_cpu.core,inst);
        }
        //Imm -> mem
        if(arg1_type == 0&&arg2_type == 2){
            inst_t inst = inst_build(0, od_build(0, (uint64_t)val1, 0, 0, 0), od_build(2, 0, (uint64_t)val2, 0, 0));
            run_single(&active_cpu.core,inst);
        }
        //reg -> reg
        if(arg1_type == 1&&arg2_type == 1){
            inst_t inst = inst_build(0, od_build(1, 0, reflect_register(arg1), 0, 0), od_build(1, 0, reflect_register(arg2), 0, 0));
            run_single(&active_cpu.core,inst);
        }
        //reg -> mem
        if(arg1_type == 1&&arg2_type == 2){
            inst_t inst = inst_build(0, od_build(1, 0, reflect_register(arg1), 0, 0), od_build(2, (uint64_t)val2, 0, 0, 0));
            run_single(&active_cpu.core,inst);
        }
        //mem -> reg
        if(arg1_type == 2&&arg2_type == 1){
            inst_t inst = inst_build(0, od_build(2, (uint64_t)val1, 0, 0, 0), od_build(1, 0, reflect_register(arg2), 0, 0));
            run_single(&active_cpu.core,inst);
        }
    }
    // PUSH
    if (state == 3) {
        if(arg1_type == 1){
            inst_t inst = inst_build(1, od_build(1, 0, reflect_register(arg1), 0, 0), od_build(0, 0, 0, 0, 0));
            run_single(&active_cpu.core,inst);
        }
    }
    // POP
    if (state == 4) {
        if(arg2_type == 1){
            inst_t inst = inst_build(2, od_build(0, 0, 0, 0, 0), od_build(1, 0, reflect_register(arg2), 0, 0));
            run_single(&active_cpu.core,inst);
        }


    }
    else {
        return;
    }
}


void EMSCRIPTEN_KEEPALIVE web_bridge(int state, char arg1[INPUT_MAX], char arg2[INPUT_MAX]) {
    // init
    if (state == 0) {
        rip_init(&active_cpu.core);
        rsp_init(&active_cpu.core);
        buf_init();
    }
        // print
    else if (state == 1) {
        core_debug_web(active_cpu, active_cpu.core);
    }
        // instruction
    else {
        instruction_listener(state, arg1, arg2);
    }
}

