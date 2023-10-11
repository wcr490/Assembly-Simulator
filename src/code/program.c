//
// Created by 30668 on 2023/10/7.
//
#include <stdint.h>

#include "core.h"
#include "isa.h"
#include "program.h"


int CURRENT_LOADING_FLAG = 0;

inst_t inst_buf[INSTRUCTION_MAX_CYCLE];


void rip_init(core_t *core){
    core->reg.rip = (uint64_t)&inst_buf[0];
}

void buf_init(){
    CURRENT_LOADING_FLAG = 0;
}


void load_inst_buf(core_t core, inst_t inst){
    if(CURRENT_LOADING_FLAG > INSTRUCTION_MAX_CYCLE){
        return;
    }
    inst_buf[CURRENT_LOADING_FLAG] = inst;
    CURRENT_LOADING_FLAG++;
    return;
}



void run_inst_buf(core_t *core){
    for(int i = 0; i < CURRENT_LOADING_FLAG; i ++){
        inst_t *current_inst = (inst_t *)(core->reg.rip);
        run_single(core, *current_inst);
        core->reg.rip += sizeof(inst_t);
    }
}



void rip_leap(core_t *core){
    core->reg.rip = core->reg.rip + sizeof(inst_t);
}


int show_buf_size(){
    return CURRENT_LOADING_FLAG;
}
int show_buf_addr(int id){
    return (int)&inst_buf[id];
}



