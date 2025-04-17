/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     80000000



/* Defines for Motor */
#define Motor_INST                                                         TIMA0
#define Motor_INST_IRQHandler                                   TIMA0_IRQHandler
#define Motor_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define Motor_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 0 */
#define GPIO_Motor_C0_PORT                                                 GPIOA
#define GPIO_Motor_C0_PIN                                         DL_GPIO_PIN_21
#define GPIO_Motor_C0_IOMUX                                      (IOMUX_PINCM46)
#define GPIO_Motor_C0_IOMUX_FUNC                     IOMUX_PINCM46_PF_TIMA0_CCP0
#define GPIO_Motor_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_Motor_C1_PORT                                                 GPIOA
#define GPIO_Motor_C1_PIN                                         DL_GPIO_PIN_22
#define GPIO_Motor_C1_IOMUX                                      (IOMUX_PINCM47)
#define GPIO_Motor_C1_IOMUX_FUNC                     IOMUX_PINCM47_PF_TIMA0_CCP1
#define GPIO_Motor_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER */
#define TIMER_INST                                                       (TIMG0)
#define TIMER_INST_IRQHandler                                   TIMG0_IRQHandler
#define TIMER_INST_INT_IRQN                                     (TIMG0_INT_IRQn)
#define TIMER_INST_LOAD_VALUE                                             (204U)




/* Defines for OLED */
#define OLED_INST                                                           I2C0
#define OLED_INST_IRQHandler                                     I2C0_IRQHandler
#define OLED_INST_INT_IRQN                                         I2C0_INT_IRQn
#define OLED_BUS_SPEED_HZ                                                 400000
#define GPIO_OLED_SDA_PORT                                                 GPIOA
#define GPIO_OLED_SDA_PIN                                         DL_GPIO_PIN_28
#define GPIO_OLED_IOMUX_SDA                                       (IOMUX_PINCM3)
#define GPIO_OLED_IOMUX_SDA_FUNC                        IOMUX_PINCM3_PF_I2C0_SDA
#define GPIO_OLED_SCL_PORT                                                 GPIOA
#define GPIO_OLED_SCL_PIN                                         DL_GPIO_PIN_31
#define GPIO_OLED_IOMUX_SCL                                       (IOMUX_PINCM6)
#define GPIO_OLED_IOMUX_SCL_FUNC                        IOMUX_PINCM6_PF_I2C0_SCL

/* Defines for WIT */
#define WIT_INST                                                            I2C1
#define WIT_INST_IRQHandler                                      I2C1_IRQHandler
#define WIT_INST_INT_IRQN                                          I2C1_INT_IRQn
#define GPIO_WIT_SDA_PORT                                                  GPIOA
#define GPIO_WIT_SDA_PIN                                          DL_GPIO_PIN_16
#define GPIO_WIT_IOMUX_SDA                                       (IOMUX_PINCM38)
#define GPIO_WIT_IOMUX_SDA_FUNC                        IOMUX_PINCM38_PF_I2C1_SDA
#define GPIO_WIT_SCL_PORT                                                  GPIOA
#define GPIO_WIT_SCL_PIN                                          DL_GPIO_PIN_17
#define GPIO_WIT_IOMUX_SCL                                       (IOMUX_PINCM39)
#define GPIO_WIT_IOMUX_SCL_FUNC                        IOMUX_PINCM39_PF_I2C1_SCL


/* Defines for WIT_uart */
#define WIT_uart_INST                                                      UART1
#define WIT_uart_INST_FREQUENCY                                         40000000
#define WIT_uart_INST_IRQHandler                                UART1_IRQHandler
#define WIT_uart_INST_INT_IRQN                                    UART1_INT_IRQn
#define GPIO_WIT_uart_RX_PORT                                              GPIOA
#define GPIO_WIT_uart_TX_PORT                                              GPIOA
#define GPIO_WIT_uart_RX_PIN                                       DL_GPIO_PIN_9
#define GPIO_WIT_uart_TX_PIN                                       DL_GPIO_PIN_8
#define GPIO_WIT_uart_IOMUX_RX                                   (IOMUX_PINCM20)
#define GPIO_WIT_uart_IOMUX_TX                                   (IOMUX_PINCM19)
#define GPIO_WIT_uart_IOMUX_RX_FUNC                    IOMUX_PINCM20_PF_UART1_RX
#define GPIO_WIT_uart_IOMUX_TX_FUNC                    IOMUX_PINCM19_PF_UART1_TX
#define WIT_uart_BAUD_RATE                                                (9600)
#define WIT_uart_IBRD_40_MHZ_9600_BAUD                                     (260)
#define WIT_uart_FBRD_40_MHZ_9600_BAUD                                      (27)
/* Defines for BLUE_TOOTH */
#define BLUE_TOOTH_INST                                                    UART0
#define BLUE_TOOTH_INST_FREQUENCY                                       40000000
#define BLUE_TOOTH_INST_IRQHandler                              UART0_IRQHandler
#define BLUE_TOOTH_INST_INT_IRQN                                  UART0_INT_IRQn
#define GPIO_BLUE_TOOTH_RX_PORT                                            GPIOA
#define GPIO_BLUE_TOOTH_TX_PORT                                            GPIOA
#define GPIO_BLUE_TOOTH_RX_PIN                                    DL_GPIO_PIN_11
#define GPIO_BLUE_TOOTH_TX_PIN                                    DL_GPIO_PIN_10
#define GPIO_BLUE_TOOTH_IOMUX_RX                                 (IOMUX_PINCM22)
#define GPIO_BLUE_TOOTH_IOMUX_TX                                 (IOMUX_PINCM21)
#define GPIO_BLUE_TOOTH_IOMUX_RX_FUNC                  IOMUX_PINCM22_PF_UART0_RX
#define GPIO_BLUE_TOOTH_IOMUX_TX_FUNC                  IOMUX_PINCM21_PF_UART0_TX
#define BLUE_TOOTH_BAUD_RATE                                            (115200)
#define BLUE_TOOTH_IBRD_40_MHZ_115200_BAUD                                  (21)
#define BLUE_TOOTH_FBRD_40_MHZ_115200_BAUD                                  (45)





/* Port definition for Pin Group RIF */
#define RIF_PORT                                                         (GPIOB)

/* Defines for PIN_0: GPIOB.0 with pinCMx 12 on package pin 47 */
#define RIF_PIN_0_PIN                                            (DL_GPIO_PIN_0)
#define RIF_PIN_0_IOMUX                                          (IOMUX_PINCM12)
/* Defines for PIN_1: GPIOB.1 with pinCMx 13 on package pin 48 */
#define RIF_PIN_1_PIN                                            (DL_GPIO_PIN_1)
#define RIF_PIN_1_IOMUX                                          (IOMUX_PINCM13)
/* Defines for PIN_2: GPIOB.2 with pinCMx 15 on package pin 50 */
#define RIF_PIN_2_PIN                                            (DL_GPIO_PIN_2)
#define RIF_PIN_2_IOMUX                                          (IOMUX_PINCM15)
/* Defines for PIN_3: GPIOB.3 with pinCMx 16 on package pin 51 */
#define RIF_PIN_3_PIN                                            (DL_GPIO_PIN_3)
#define RIF_PIN_3_IOMUX                                          (IOMUX_PINCM16)
/* Defines for PIN_4: GPIOB.4 with pinCMx 17 on package pin 52 */
#define RIF_PIN_4_PIN                                            (DL_GPIO_PIN_4)
#define RIF_PIN_4_IOMUX                                          (IOMUX_PINCM17)
/* Defines for PIN_5: GPIOB.5 with pinCMx 18 on package pin 53 */
#define RIF_PIN_5_PIN                                            (DL_GPIO_PIN_5)
#define RIF_PIN_5_IOMUX                                          (IOMUX_PINCM18)
/* Defines for PIN_6: GPIOB.6 with pinCMx 23 on package pin 58 */
#define RIF_PIN_6_PIN                                            (DL_GPIO_PIN_6)
#define RIF_PIN_6_IOMUX                                          (IOMUX_PINCM23)
/* Defines for PIN_7: GPIOB.7 with pinCMx 24 on package pin 59 */
#define RIF_PIN_7_PIN                                            (DL_GPIO_PIN_7)
#define RIF_PIN_7_IOMUX                                          (IOMUX_PINCM24)
/* Defines for PIN_8: GPIOB.8 with pinCMx 25 on package pin 60 */
#define RIF_PIN_8_PIN                                            (DL_GPIO_PIN_8)
#define RIF_PIN_8_IOMUX                                          (IOMUX_PINCM25)
/* Defines for PIN_9: GPIOB.9 with pinCMx 26 on package pin 61 */
#define RIF_PIN_9_PIN                                            (DL_GPIO_PIN_9)
#define RIF_PIN_9_IOMUX                                          (IOMUX_PINCM26)
/* Defines for PIN_10: GPIOB.10 with pinCMx 27 on package pin 62 */
#define RIF_PIN_10_PIN                                          (DL_GPIO_PIN_10)
#define RIF_PIN_10_IOMUX                                         (IOMUX_PINCM27)
/* Defines for PIN_11: GPIOB.11 with pinCMx 28 on package pin 63 */
#define RIF_PIN_11_PIN                                          (DL_GPIO_PIN_11)
#define RIF_PIN_11_IOMUX                                         (IOMUX_PINCM28)
/* Port definition for Pin Group MOTOR */
#define MOTOR_PORT                                                       (GPIOB)

/* Defines for AIN1: GPIOB.13 with pinCMx 30 on package pin 1 */
#define MOTOR_AIN1_PIN                                          (DL_GPIO_PIN_13)
#define MOTOR_AIN1_IOMUX                                         (IOMUX_PINCM30)
/* Defines for AIN2: GPIOB.14 with pinCMx 31 on package pin 2 */
#define MOTOR_AIN2_PIN                                          (DL_GPIO_PIN_14)
#define MOTOR_AIN2_IOMUX                                         (IOMUX_PINCM31)
/* Defines for BIN1: GPIOB.15 with pinCMx 32 on package pin 3 */
#define MOTOR_BIN1_PIN                                          (DL_GPIO_PIN_15)
#define MOTOR_BIN1_IOMUX                                         (IOMUX_PINCM32)
/* Defines for BIN2: GPIOB.16 with pinCMx 33 on package pin 4 */
#define MOTOR_BIN2_PIN                                          (DL_GPIO_PIN_16)
#define MOTOR_BIN2_IOMUX                                         (IOMUX_PINCM33)
/* Port definition for Pin Group QEI */
#define QEI_PORT                                                         (GPIOA)

/* Defines for EA1: GPIOA.1 with pinCMx 2 on package pin 34 */
// pins affected by this interrupt request:["EA1","EA2","EB1","EB2"]
#define QEI_INT_IRQN                                            (GPIOA_INT_IRQn)
#define QEI_INT_IIDX                            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define QEI_EA1_IIDX                                         (DL_GPIO_IIDX_DIO1)
#define QEI_EA1_PIN                                              (DL_GPIO_PIN_1)
#define QEI_EA1_IOMUX                                             (IOMUX_PINCM2)
/* Defines for EA2: GPIOA.0 with pinCMx 1 on package pin 33 */
#define QEI_EA2_IIDX                                         (DL_GPIO_IIDX_DIO0)
#define QEI_EA2_PIN                                              (DL_GPIO_PIN_0)
#define QEI_EA2_IOMUX                                             (IOMUX_PINCM1)
/* Defines for EB1: GPIOA.14 with pinCMx 36 on package pin 7 */
#define QEI_EB1_IIDX                                        (DL_GPIO_IIDX_DIO14)
#define QEI_EB1_PIN                                             (DL_GPIO_PIN_14)
#define QEI_EB1_IOMUX                                            (IOMUX_PINCM36)
/* Defines for EB2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define QEI_EB2_IIDX                                        (DL_GPIO_IIDX_DIO15)
#define QEI_EB2_PIN                                             (DL_GPIO_PIN_15)
#define QEI_EB2_IOMUX                                            (IOMUX_PINCM37)
/* Port definition for Pin Group buzzer */
#define buzzer_PORT                                                      (GPIOB)

/* Defines for PIN_12: GPIOB.17 with pinCMx 43 on package pin 14 */
#define buzzer_PIN_12_PIN                                       (DL_GPIO_PIN_17)
#define buzzer_PIN_12_IOMUX                                      (IOMUX_PINCM43)
/* Port definition for Pin Group Button */
#define Button_PORT                                                      (GPIOB)

/* Defines for P1: GPIOB.18 with pinCMx 44 on package pin 15 */
#define Button_P1_PIN                                           (DL_GPIO_PIN_18)
#define Button_P1_IOMUX                                          (IOMUX_PINCM44)
/* Defines for P2: GPIOB.19 with pinCMx 45 on package pin 16 */
#define Button_P2_PIN                                           (DL_GPIO_PIN_19)
#define Button_P2_IOMUX                                          (IOMUX_PINCM45)
/* Defines for P3: GPIOB.20 with pinCMx 48 on package pin 19 */
#define Button_P3_PIN                                           (DL_GPIO_PIN_20)
#define Button_P3_IOMUX                                          (IOMUX_PINCM48)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_SYSCTL_CLK_init(void);
void SYSCFG_DL_Motor_init(void);
void SYSCFG_DL_TIMER_init(void);
void SYSCFG_DL_OLED_init(void);
void SYSCFG_DL_WIT_init(void);
void SYSCFG_DL_WIT_uart_init(void);
void SYSCFG_DL_BLUE_TOOTH_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
