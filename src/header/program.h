//
// Created by 30668 on 2023/10/7.
//

#ifndef SIMULATOR_PROGRAM_H
#define SIMULATOR_PROGRAM_H

#define INSTRUCTION_MAX_CYCLE 12

#include "core.h"
#include "isa.h"

extern int CURRENT_LOADING_FLAG;


void rip_init(core_t *core);
void buf_init();
void load_inst_buf(core_t core, inst_t inst);
void run_inst_buf(core_t *core);
int show_buf_size();
void rip_leap(core_t *core);
int show_buf_addr(int id);

#endif //SIMULATOR_PROGRAM_H
