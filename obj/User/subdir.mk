################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/HX77.c \
../User/Key_Get.c \
../User/L610.c \
../User/allshow.c \
../User/ch32v30x_it.c \
../User/dma.c \
../User/lcd.c \
../User/main.c \
../User/pages.c \
../User/sys.c \
../User/system_ch32v30x.c 

OBJS += \
./User/HX77.o \
./User/Key_Get.o \
./User/L610.o \
./User/allshow.o \
./User/ch32v30x_it.o \
./User/dma.o \
./User/lcd.o \
./User/main.o \
./User/pages.o \
./User/sys.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/HX77.d \
./User/Key_Get.d \
./User/L610.d \
./User/allshow.d \
./User/ch32v30x_it.d \
./User/dma.d \
./User/lcd.d \
./User/main.d \
./User/pages.d \
./User/sys.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"D:\SmartCart\Debug" -I"D:\SmartCart\Core" -I"D:\SmartCart\User" -I"D:\SmartCart\Peripheral\inc" -I"D:\SmartCart\Hardware" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

