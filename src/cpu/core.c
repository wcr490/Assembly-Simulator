#include <stdint.h>
#include <stdio.h>


#include "core.h"





cpu_t cpu_build(){
    cpu_t cpu;
    core_t core = cpu.core;

    cpu_init(&cpu);
    flag_init(&cpu);
    return cpu;
}

void cpu_init(cpu_t *cpu){
    core_t core;
    cpu->core = core;
}
void flag_init(cpu_t *cpu){
    flag_t flag;
    cpu->core.flag = flag;
    cpu->core.flag.CF = 0;
    cpu->core.flag.ZF = 0;
    cpu->core.flag.SF = 0;
    cpu->core.flag.OF = 0;
}



void core_debug(cpu_t cpu,core_t core){
    printf("------------------------------start\n");
    printf("Register info\n");
    printf("%5p   %10i  <al>\n",(&(core.reg.al)),core.reg.al);
    printf("%5p   %10i  <ah>\n",(&(core.reg.ah)),core.reg.ah);
    printf("%5p   %10i  <ax>\n",(&(core.reg.ax)),core.reg.ax);
    printf("%5p   %10i  <eax>\n",&(core.reg.eax),core.reg.eax);
    printf("%5p   %10llu  <rax>\n",&(core.reg.rax),core.reg.rax);
    printf("%5p   %10llu  <rbx>\n",&(core.reg.rbx),core.reg.rbx);
    printf("%5p   %10llu  <rcx>\n",&(core.reg.rcx),core.reg.rcx);
    printf("%5p   %10llu  <rdx>\n",&(core.reg.rdx),core.reg.rdx);
    printf("%5p   %10llu  <rsi>\n",&(core.reg.rsi),core.reg.rsi);
    printf("%5p   %10llu  <rdi>\n", &(core.reg.rdi), core.reg.rdi);
    printf("%5p   %10d  <rbp>\n", &(core.reg.rbp), core.reg.rbp);
    printf("%5p   %10d  <rsp>\n",&(core.reg.rsp), core.reg.rsp);
    printf("%5p   %10llu  <rip>\n",&(core.reg.rip),core.reg.rip);
    printf("Flag info\n");
    printf("%i  CF\n",core.flag.CF);
    printf("%i  ZF\n",core.flag.ZF);
    printf("%i  SF\n",core.flag.SF);
    printf("%i  OF\n",core.flag.OF);
    printf("--------------------------------end\n");
}
void core_debug_web(cpu_t cpu,core_t core){
    printf("------------------------------start\n");
    printf("<al>   %10llu %p\n",core.reg.al,&(core.reg.al));
    printf("<ah>   %10llu %p\n",core.reg.ah,&(core.reg.ah));
    printf("<ax>   %10llu\n",core.reg.ax);
    printf("<eax>  %10llu\n",core.reg.eax);
    printf("<rax>  %10llu\n",core.reg.rax);
    printf("<rbx>  %10llu\n",core.reg.rbx);
    printf("<rcx>  %10llu\n",core.reg.rcx);
    printf("<rdx>  %10llu\n",core.reg.rdx);
    printf("<rsi>  %10llu\n",core.reg.rsi);
    printf("<rdi>  %10llu\n",core.reg.rdi);
    printf("<rbp>  %10llu\n",core.reg.rbp);
    printf("<rsp>  %10llu\n",core.reg.rsp);
    printf("<rip>  %10llu\n",core.reg.rip);
    printf("--------------------------------end\n");
}


