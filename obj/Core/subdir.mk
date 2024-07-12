################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"D:\SmartCart\Debug" -I"D:\SmartCart\Core" -I"D:\SmartCart\User" -I"D:\SmartCart\Peripheral\inc" -I"D:\SmartCart\Hardware" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

