//
// Created by 30668 on 2023/10/7.
//

#include <stdint.h>
#include <stdio.h>

#include "core.h"
#include "isa.h"
#include "program.h"
#include "ram.h"


//some basic setting about instruction
#define INSTRUCTION_HANDLER  5

static handler_t handler_table[INSTRUCTION_HANDLER] = {
        &mov_handler,
        &push_handler,
        &pop_handler,
        &add_handler,
        &sub_handler,
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
//            printf("%llu\n",*(uint64_t *)core->reg.rsp);
        }
    }
}

static void pop_handler(core_t *core, inst_t *inst){
    if(inst->op == POP){
        if(inst->dst.type == REG){
            uint64_t value = *(uint64_t *)core->reg.rsp;
            *(uint64_t *)inst->dst.reg = value;
            core->reg.rsp += 8;
            printf("%llu",value);
        }
    }
}

static void add_handler(core_t *core, inst_t *inst){
    //calculation
    uint64_t value = *(uint64_t *)inst->dst.reg + *(uint64_t *)inst->ori.reg;

    //check and set flags
    core->flag.CF = 0;
    core->flag.ZF = 0;
    core->flag.SF = 0;
    core->flag.OF = 0;
    uint8_t ori_sign = (*(uint64_t *)inst->ori.reg >> 63) & 0x1;
    uint8_t dst_sign = (*(uint64_t *)inst->dst.reg >> 63) & 0x1;
    uint8_t value_sign = (value >> 63)&0x1;
    core->flag.CF = (value < *(uint64_t *)inst->ori.reg);
    core->flag.ZF = value == 0;
    core->flag.SF = value_sign;
    core->flag.OF = (ori_sign && dst_sign && !value_sign) || (!ori_sign && !dst_sign && value_sign);
    *(uint64_t *)inst->dst.reg = value;
}
static void sub_handler(core_t *core, inst_t *inst){
    //calculation
    uint64_t value = *(uint64_t *)inst->dst.reg - *(uint64_t *)inst->ori.reg;

    //check and set flags
    core->flag.CF = 0;
    core->flag.ZF = 0;
    core->flag.SF = 0;
    core->flag.OF = 0;
    uint8_t ori_sign = (*(uint64_t *)inst->ori.reg >> 63) & 0x1;
    uint8_t dst_sign = (*(uint64_t *)inst->dst.reg >> 63) & 0x1;
    uint8_t value_sign = (value >> 63)&0x1;
    core->flag.CF = (value > *(uint64_t *)inst->ori.reg);
    core->flag.ZF = value == 0;
    core->flag.SF = value_sign;
    core->flag.OF = (ori_sign && !dst_sign && value_sign) || (!ori_sign && dst_sign && !value_sign);
    *(uint64_t *)inst->dst.reg = value;
}


void run_single(core_t *core, inst_t inst){
    handler_t handler = handler_table[inst.op];
    handler(core, &inst);
    core->reg.rip += sizeof(inst_t);
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


