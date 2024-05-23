@echo off

REM 设置 OpenOCD 路径和配置文件路径
set "OPENOCD_PATH=D:\SmartCart\Dependency\Toolchain\OpenOCD\bin\openocd.exe"
set "CFG_PATH=D:\SmartCart\Dependency\Toolchain\wch-riscv.cfg"

REM 启动 OpenOCD
"%OPENOCD_PATH%" -f "%CFG_PATH%"
