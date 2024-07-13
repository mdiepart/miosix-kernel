
miosix_inc = ['lib/miosix-kernel/miosix',
              'lib/miosix-kernel/miosix/config',
              'lib/miosix-kernel/miosix/arch/common',
              'lib/miosix-kernel/miosix/util']

miosix_src = ['lib/miosix-kernel/miosix/kernel/kernel.cpp',
              'lib/miosix-kernel/miosix/kernel/sync.cpp',
              'lib/miosix-kernel/miosix/kernel/error.cpp',
              'lib/miosix-kernel/miosix/kernel/pthread.cpp',
              'lib/miosix-kernel/miosix/kernel/stage_2_boot.cpp',
              'lib/miosix-kernel/miosix/kernel/timeconversion.cpp',
              'lib/miosix-kernel/miosix/kernel/intrusive.cpp',
              'lib/miosix-kernel/miosix/kernel/scheduler/priority/priority_scheduler.cpp',
              'lib/miosix-kernel/miosix/kernel/error.cpp',
              'lib/miosix-kernel/miosix/filesystem/console/console_device.cpp',
              'lib/miosix-kernel/miosix/filesystem/devfs/devfs.cpp',
              'lib/miosix-kernel/miosix/stdlib_integration/libc_integration.cpp',
              'lib/miosix-kernel/miosix/stdlib_integration/libstdcpp_integration.cpp',
              'lib/miosix-kernel/miosix/util/util.cpp',
              ]

miosix_def = {'COMPILING_MIOSIX'          : '',
              '_POSIX_PRIORITY_SCHEDULING': ''}

##
## ARM Cortex M4
##

##
## STM32F4
##
miosix_stm32f4_inc = miosix_inc + ['lib/miosix-kernel/miosix/arch/common/CMSIS/Device/ST/STM32F4xx/Include',
                                   'lib/miosix-kernel/miosix/arch/common/CMSIS/Include',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/common',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/common/interfaces-impl',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/stm32f405_generic',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/stm32f405_generic/interfaces-impl',
                                   'lib/miosix-kernel/miosix/config/arch/cortexM4_stm32f4/stm32f405_generic']

miosix_stm32f4_src = miosix_src + ['lib/miosix-kernel/miosix/arch/common/core/interrupts_cortexMx.cpp',
                                   'lib/miosix-kernel/miosix/arch/common/core/mpu_cortexMx.cpp',
                                   'lib/miosix-kernel/miosix/arch/common/drivers/serial_stm32.cpp',
                                   'lib/miosix-kernel/miosix/arch/common/drivers/dcc.cpp',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/common/interfaces-impl/portability.cpp',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/common/interfaces-impl/delays.cpp',
                                   'lib/miosix-kernel/miosix/arch/common/drivers/stm32_gpio.cpp',
                                   'lib/miosix-kernel/miosix/arch/common/core/stm32_32bit_os_timer.cpp',
                                   'lib/miosix-kernel/miosix/arch/common/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/stm32f405_generic/interfaces-impl/bsp.cpp',
                                   'lib/miosix-kernel/miosix/arch/cortexM4_stm32f4/stm32f405_generic/core/stage_1_boot.cpp']
                                   
miosix_stm32f4_def = miosix_def + {'STM32F405xx' : '', '_ARCH_CORTEXM4_STM32F4' : ''}

##
## NXP MK22
##
miosix_nxpmk22_inc = miosix_inc + ['lib/miosix-kernel/miosix/arch/common/CMSIS/Device/NXP/MK22FN512xxx12/Include',
                                          'lib/miosix-kernel/miosix/arch/common/CMSIS/Include',
                                          'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/common',
                                          'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/common/interfaces-impl',
                                          'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/nxpmk22f51212_generic',
                                          'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/nxpmk22f51212_generic/interfaces-impl',
                                          'lib/miosix-kernel/miosix/config/arch/cortexM4_nxpmk22/nxpmk22f51212_generic']

miosix_nxpmk22_src = miosix_src + ['lib/miosix-kernel/miosix/arch/common/core/interrupts_cortexMx.cpp',
                               'lib/miosix-kernel/miosix/arch/common/core/mpu_cortexMx.cpp',
#                               'lib/miosix-kernel/miosix/arch/common/drivers/serial_nxpmk22.cpp',
                               'lib/miosix-kernel/miosix/arch/common/drivers/dcc.cpp',
                               'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/common/interfaces-impl/portability.cpp',
                               'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/common/interfaces-impl/delays.cpp',
                               'lib/miosix-kernel/miosix/arch/common/drivers/nxpmk22_gpio.cpp',
                               'lib/miosix-kernel/miosix/arch/common/core/nxpmk22_os_timer.cpp',
                               'lib/miosix-kernel/miosix/arch/common/CMSIS/Device/NXP/MK22FN512xxx12/Source/system_MK22F51212.c',
                               'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/nxpmk22f51212_generic/interfaces-impl/bsp.cpp',
                               'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/common/interfaces-impl/portability.cpp',
                               'lib/miosix-kernel/miosix/arch/cortexM4_nxpmk22/nxpmk22f51212_generic/core/stage_1_boot.cpp']

miosix_nxpmk22_def = miosix_def + {'_ARCH_CORTEXM4_NXPMK22' : '',
								   'CPU_XTAL_CLK_HZ' : '12288000',
                                   'CPU_MK22FN512VLH12' : ''}