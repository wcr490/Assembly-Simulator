//
// Created by 30668 on 2023/10/7.
//

#include <stdint.h>

#include "core.h"
#include "isa.h"
#include "program.h"
#include "ram.h"


//some basic setting about instruction
#define INSTRUCTION_HANDLER  3

static handler_t handler_table[INSTRUCTION_HANDLER] = {
        &mov_handler,
        &push_handler,
        &pop_handler,
};

//implement single example

/*
mov
 Imm -> reg
 Imm -> mem
 reg -> reg
 reg -> mem
 mem -> reg
*/
static void mov_handler(core_t *core, inst_t *inst){
    if(inst->op == MOV){
        if(inst->ori.type == IMM){
            if(inst->dst.type == REG){
                *(uint64_t *)inst->dst.reg = inst->ori.Imm;
            }
            else if(inst->dst.type == MEM){
                *(uint64_t *)(inst->dst.Imm) = (uint64_t)inst->ori.Imm;
            }
        }
        else if(inst->ori.type == REG){
            uint64_t *temp;
            temp = (uint64_t *)inst->ori.reg;
            if(inst->dst.type == REG){
                *(uint64_t *)inst->dst.reg = *temp;
            }
            else if(inst->dst.type == MEM){
                *(uint64_t *)inst->dst.Imm = *temp;
            }
        }
        else if(inst->ori.type == MEM){
            *(uint64_t *)inst->dst.reg = (uint64_t)*(uint64_t *)inst->ori.Imm;
        }
    }
}

static void push_handler(core_t *core, inst_t *inst){
    if(inst->op == PUSH){
        if(inst->ori.type == REG){
            uint64_t value = (uint64_t)*(uint64_t *)inst->ori.reg;
            core->reg.rsp -= 8;
            write_stack_64(core->reg.rsp, value);
        }
    }
}

static void pop_handler(core_t *core, inst_t *inst){
    if(inst->op == POP){
        if(inst->dst.type == REG){
            uint64_t value = *(uint64_t *)core->reg.rsp;
            *(uint64_t *)inst->dst.reg = value;
            core->reg.rsp += 8;
        }
    }
}



void run_single(core_t *core, inst_t inst){
    handler_t handler = handler_table[inst.op];
    handler(core, &inst);
}

inst_t inst_build(op_t op, od_t ori, od_t dst){
    inst_t inst;
    inst.op = op;
    inst.ori = ori;
    inst.dst = dst;
    return inst;
}

od_t od_build(od_type type, uint64_t Imm, uint64_t reg, uint64_t reg_second, uint64_t scale){
    od_t od;
    od.type = type;
    od.Imm = Imm;        //addr or number
    od.reg = reg;        //addr
    od.reg_second = reg_second;
    od.scale = scale;
    return od;
}


