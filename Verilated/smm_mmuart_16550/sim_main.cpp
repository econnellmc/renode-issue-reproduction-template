//
// Copyright (c) 2010-2021 Antmicro
//
//  This file is licensed under the MIT License.
//  Full license text is available in 'LICENSE' file.
//
#include <verilated.h>
#include "Vsmm_mmuart.h"
#include <bitset>
#include <stdio.h>
#include <stdlib.h>

#define VM_TRACE 0
#define VM_TRACE_VCD 0

#if VM_TRACE_VCD
# include <verilated_vcd_c.h>
# define VERILATED_DUMP VerilatedVcdC
# define DEF_TRACE_FILEPATH "simx.vcd"
#elif VM_TRACE_FST
# include <verilated_fst_c.h>
# define VERILATED_DUMP VerilatedFstC
# define DEF_TRACE_FILEPATH "simx.fst"
#endif

// uart.h and apb3.h can be found in Renode's VerilatorPlugin
#include "src/peripherals/uart.h"
#include "src/buses/apb3.h"

#define UART_FREQ 150000000
#define BAUDRATE 115200

const int prescaler = UART_FREQ / (BAUDRATE * 8);
UART_16550 *uart;
Vsmm_mmuart *top = new Vsmm_mmuart;
#if VM_TRACE
VERILATED_DUMP  *tfp;
#endif
vluint64_t main_time = 0;
uint8_t one = 1;
uint8_t zero = 0;

void eval() {
#if VM_TRACE
    main_time++;
    tfp->dump(main_time);
    tfp->flush();
#endif
    uart->eval();
    top->eval();
}


RenodeAgent* Init() {
    APB3* bus = new APB3();

    //=================================================
    // Init bus signals
    //=================================================
    bus->pclk = &top->PCLK;
    bus->prst = &top->PRESETN;
    bus->paddr = &top->PADDR;
    bus->psel = &top->PSEL;
    bus->penable = &top->PENABLE;
    bus->pwrite = &top->PWRITE;
    bus->pwdata = (uint32_t *)&top->PWDATA;
    bus->pready = &one; //Tie the ready signal high
    bus->prdata = (uint32_t *)&top->PRDATA;
    bus->pslverr = &zero;

    //=================================================
    // Init eval function
    //=================================================
    bus->evaluateModel = &eval;

    //=================================================
    // Init peripheral
    //=================================================
    const int rx_tx_reg = 0x0000;
    uart = new UART_16550(bus, &top->SOUT, &top->SIN, prescaler, rx_tx_reg, &top->INTR);
    return uart;
}

int main(int argc, char **argv, char **env) {
    if(argc < 3) {
        printf("Usage: %s {receiverPort} {senderPort} [{address}]\n", argv[0]);
        exit(-1);
    }
    const char *address = argc < 4 ? "127.0.0.1" : argv[3];

    Verilated::commandArgs(argc, argv);
#if VM_TRACE
   Verilated::traceEverOn(true);
   tfp = new VERILATED_DUMP;
   top->trace(tfp, 99);
   tfp->open(DEF_TRACE_FILEPATH);
#endif
    Init();
    uart->simulate(atoi(argv[1]), atoi(argv[2]), address);
    top->final();
    exit(0);
}
