*** Settings ***
Suite Setup     Setup
Suite Teardown  Teardown
Test Teardown   Test Teardown
Resource        ${RENODEKEYWORDS}

*** Variables ***
${UART}                       sysbus.mmuart0


*** Keywords ***
Create Machine
    Execute Command    $GDB_SERVER_PORT=3333
    Execute Command    path add @${CURDIR}
    Execute Command    path add @boards
    Execute Command    i @scripts/polarfire-soc-icicle-board.resc
    Execute Command    sysbus LoadELF @mpfs-mmuart-interrupt.elf

*** Test Cases ***
Should Fail Test Case
    [Timeout]    300
    Create Machine
    Create Terminal Tester    ${UART}
    Execute Command    start
    Wait For Next Line On Uart
