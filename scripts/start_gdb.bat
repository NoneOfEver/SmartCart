@echo off

REM 设置 GDB 路径和 ELF 文件
set "GDB_PATH=D:\SmartCart\Dependency\Toolchain\riscv-none-embed\bin\riscv-none-embed-gdb.exe"
set "ELF_FILE=D:\SmartCart\build\debugch32-ninja.elf"

REM 设置远程目标的 IP 和端口
set "REMOTE_IP=localhost"
set "REMOTE_PORT=3333"

REM 启动 GDB 并执行指令
"%GDB_PATH%" "%ELF_FILE%" --batch --command=commands.gdb
