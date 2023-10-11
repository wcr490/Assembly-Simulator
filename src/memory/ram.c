//
// Created by 30668 on 2023/10/10.
//
#include <stdint.h>
#include <stdio.h>

#include "ram.h"

#define STACK_BOTTOM    0x1000


void rsp_init(core_t *core){
    core->reg.rsp = STACK_BOTTOM;
}

void write_stack_64(uint64_t addr, uint64_t data) {
    for (int i = 0; i < 8; i++) {
        *((uint8_t *)(addr + i)) = (data >> (i * 8)) & 0xFF;
    }
}
