#include <stdint.h>
#include <stdio.h>


#include "core.h"





cpu_t cpu_build(){
    cpu_t cpu;
    core_t core = cpu.core;

    cpu_init(cpu);
    return cpu;
}

void cpu_init(cpu_t cpu){
    core_t core = cpu.core;

}


void core_debug(cpu_t cpu,core_t core){
    printf("------------------------------start\n");
    printf("%5p   %10i  <al>\n",(&(core.reg.al)) + ADDR_BIAS,core.reg.al);
    printf("%5p   %10i  <ah>\n",(&(core.reg.ah)) + ADDR_BIAS,core.reg.ah);
    printf("%5p   %10i  <ax>\n",(&(core.reg.ax)) + ADDR_BIAS,core.reg.ax);
    printf("%5p   %10i  <eax>\n",(&(core.reg.eax)) + ADDR_BIAS,core.reg.eax);
    printf("%5p   %10llu  <rax>\n",(&(core.reg.rax)) + ADDR_BIAS,core.reg.rax);
    printf("%5p   %10llu  <rbx>\n",(&(core.reg.rbx)) + ADDR_BIAS,core.reg.rbx);
    printf("%5p   %10llu  <rcx>\n",(&(core.reg.rcx)) + ADDR_BIAS,core.reg.rcx);
    printf("%5p   %10llu  <rdx>\n",(&(core.reg.rdx)) + ADDR_BIAS,core.reg.rdx);
    printf("%5p   %10llu  <rsi>\n",(&(core.reg.rsi)) + ADDR_BIAS,core.reg.rsi);
    printf("%5p   %10llu  <rdi>\n",(&(core.reg.rdi)) + ADDR_BIAS,core.reg.rdi);
    printf("%5p   %10llu  <rbp>\n",(&(core.reg.rbp)) + ADDR_BIAS,core.reg.rbp);
    printf("%5p   %10llu  <rsp>\n",(&(core.reg.rsp)) + ADDR_BIAS,core.reg.rsp);
    printf("%5p   %10llu  <rip>\n",(&(core.reg.rip)),core.reg.rip);
    printf("%5p   %10llu  <rip + 8>\n",(&(core.reg.rip)+0x1) + ADDR_BIAS,*(uint64_t *)(core.reg.rip+0x1));
    printf("--------------------------------end\n");
}


