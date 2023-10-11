//
// Created by 30668 on 2023/10/7.
//

#ifndef SIMULATOR_ISA_H
#define SIMULATOR_ISA_H
#include <stdint.h>
#include "core.h"

typedef enum OP{
    MOV,          //call mov_handler
    PUSH,         //call push_handler
    POP,          //call pop_handler
}op_t;

typedef enum OD_TYPE{
    IMM,
    REG,
    MEM,
}od_type;

typedef struct OD{
    od_type type;
    uint64_t Imm;     //used in both imm and mem
    uint64_t reg;     //addr,not the real object
    uint64_t reg_second;
    uint64_t scale;
}od_t;

typedef struct INSTRUCTION{
    op_t op;
    od_t ori;
    od_t dst;
}inst_t;

static void mov_handler(core_t *core, inst_t *inst);
static void push_handler(core_t *core, inst_t *inst);
static void pop_handler(core_t *core, inst_t *inst);
typedef void (*handler_t)(core_t *core, inst_t *inst);



void run_single(core_t *core , inst_t inst);
inst_t inst_build(op_t op, od_t ori, od_t dst);
od_t od_build(od_type type, uint64_t Imm, uint64_t reg, uint64_t reg_second, uint64_t scale);

#endif //SIMULATOR_ISA_H
