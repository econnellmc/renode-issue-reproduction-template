cmake_minimum_required(VERSION 3.8)

# Name of the project
project(smm_mmuart)

# Verilog file containing the top module to be Verilated
set(VTOP
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/smm_mmuart.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/core16550mm.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/input_filter.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/rzi_mod.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/rwcontrol.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/uart_reg.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/intcontrol.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/rzi_demod.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/baudgen.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/rxblock.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/fifoctrl.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/txblock.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/lin_header_detect.v 
        ${SVN_G6_ROOT}/design/source/smm/smm_mmuart/trunk/rtl/uart_fifo.v 
)

# C/C++ source files to be compiled
set(CSOURCES sim_main.cpp)

# Additional compiling, linking or verilating arguments (respectively)
add_compile_definitions(RESET_ACTIVE_LOW)
set(COMP_LIB_ARGS -fPIC)
#set(LINK_EXEC_ARGS ...)
#set(LINK_LIB_ARGS ...)
#set(VERI_EXEC_ARGS --trace)
set(VERI_EXEC_ARGS -Wno-PINMISSING -Wno-MODDUP -Wno-COMBDLY -Wno-CASEINCOMPLETE -Wno-WIDTH -Wno-IMPLICIT)
set(VERI_LIB_ARGS -Wno-PINMISSING -Wno-MODDUP -Wno-COMBDLY -Wno-CASEINCOMPLETE -Wno-WIDTH -Wno-IMPLICIT)

# CMake file doing the hard job
include(../../cmake/configure-and-verilate.cmake)
