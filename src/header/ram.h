//
// Created by 30668 on 2023/10/10.
//

#ifndef SIMULATOR_RAM_H
#define SIMULATOR_RAM_H

#include <stdint.h>
#include "core.h"




void rsp_init(core_t *core);
void write_stack_64(uint64_t addr, uint64_t data);



#endif //SIMULATOR_RAM_H
