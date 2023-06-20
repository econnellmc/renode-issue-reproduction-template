*** Settings ***
Suite Setup                   Setup
Suite Teardown                Teardown
Test Setup                    Reset Emulation
Test Teardown                 Test Teardown
Resource                      ${RENODEKEYWORDS}

*** Variables ***
${SCRIPT}                     ${CURDIR}/test.resc
${UART}                       sysbus.mmuart1


*** Keywords ***
Load Script
    Execute Script            ${SCRIPT}
    Create Terminal Tester    sysbus.mmuart1

*** Test Cases ***
Should Run Test Case
    Load Script
    Start Emulation
    Wait For Line On Uart  **** PolarFire SoC MSS MMUART example ****
