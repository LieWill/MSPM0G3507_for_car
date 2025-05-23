/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gMotorBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_Motor_init();
    SYSCFG_DL_TIMER_init();
    SYSCFG_DL_OLED_init();
    SYSCFG_DL_WIT_init();
    SYSCFG_DL_WIT_uart_init();
    SYSCFG_DL_BLUE_TOOTH_init();
    SYSCFG_DL_SYSCTL_CLK_init();
    /* Ensure backup structures have no valid state */
	gMotorBackup.backupRdy 	= false;



}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(Motor_INST, &gMotorBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(Motor_INST, &gMotorBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(Motor_INST);
    DL_TimerG_reset(TIMER_INST);
    DL_I2C_reset(OLED_INST);
    DL_I2C_reset(WIT_INST);
    DL_UART_Main_reset(WIT_uart_INST);
    DL_UART_Main_reset(BLUE_TOOTH_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(Motor_INST);
    DL_TimerG_enablePower(TIMER_INST);
    DL_I2C_enablePower(OLED_INST);
    DL_I2C_enablePower(WIT_INST);
    DL_UART_Main_enablePower(WIT_uart_INST);
    DL_UART_Main_enablePower(BLUE_TOOTH_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_C0_IOMUX,GPIO_Motor_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_C0_PORT, GPIO_Motor_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_C1_IOMUX,GPIO_Motor_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_C1_PORT, GPIO_Motor_C1_PIN);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_OLED_IOMUX_SDA,
        GPIO_OLED_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_OLED_IOMUX_SCL,
        GPIO_OLED_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_OLED_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_OLED_IOMUX_SCL);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_WIT_IOMUX_SDA,
        GPIO_WIT_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_WIT_IOMUX_SCL,
        GPIO_WIT_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_WIT_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_WIT_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_WIT_uart_IOMUX_TX, GPIO_WIT_uart_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_WIT_uart_IOMUX_RX, GPIO_WIT_uart_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_BLUE_TOOTH_IOMUX_TX, GPIO_BLUE_TOOTH_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_BLUE_TOOTH_IOMUX_RX, GPIO_BLUE_TOOTH_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(buzzer_PIN_12_IOMUX);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_0_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_4_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_5_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_6_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_7_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_8_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_9_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_10_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(RIF_PIN_11_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(MOTOR_AIN1_IOMUX);

    DL_GPIO_initDigitalOutput(MOTOR_AIN2_IOMUX);

    DL_GPIO_initDigitalOutput(MOTOR_BIN1_IOMUX);

    DL_GPIO_initDigitalOutput(MOTOR_BIN2_IOMUX);

    DL_GPIO_initDigitalInput(QEI_EA1_IOMUX);

    DL_GPIO_initDigitalInput(QEI_EA2_IOMUX);

    DL_GPIO_initDigitalInputFeatures(QEI_EB1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(QEI_EB2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Button_P1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Button_P2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Button_P3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_setLowerPinsPolarity(QEI_PORT, DL_GPIO_PIN_1_EDGE_RISE |
		DL_GPIO_PIN_0_EDGE_RISE |
		DL_GPIO_PIN_14_EDGE_RISE |
		DL_GPIO_PIN_15_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(QEI_PORT, QEI_EA1_PIN |
		QEI_EB1_PIN);
    DL_GPIO_enableInterrupt(QEI_PORT, QEI_EA1_PIN |
		QEI_EB1_PIN);
    DL_GPIO_clearPins(GPIOB, buzzer_PIN_12_PIN |
		MOTOR_AIN1_PIN |
		MOTOR_AIN2_PIN |
		MOTOR_BIN1_PIN |
		MOTOR_BIN2_PIN);
    DL_GPIO_enableOutput(GPIOB, buzzer_PIN_12_PIN |
		MOTOR_AIN1_PIN |
		MOTOR_AIN2_PIN |
		MOTOR_BIN1_PIN |
		MOTOR_BIN2_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
	.rDivClk2x              = 1,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_SYSOSC,
	.qDiv                   = 4,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_1
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOA_INT_IRQn, 1);

}
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_CLK_init(void) {
    while ((DL_SYSCTL_getClockStatus() & (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD
		 | DL_SYSCTL_CLK_STATUS_HSCLK_GOOD
		 | DL_SYSCTL_CLK_STATUS_LFOSC_GOOD))
	       != (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD
		 | DL_SYSCTL_CLK_STATUS_HSCLK_GOOD
		 | DL_SYSCTL_CLK_STATUS_LFOSC_GOOD))
	{
		/* Ensure that clocks are in default POR configuration before initialization.
		* Additionally once LFXT is enabled, the internal LFOSC is disabled, and cannot
		* be re-enabled other than by executing a BOOTRST. */
		;
	}
}



/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gMotorClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gMotorConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 1000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_Motor_init(void) {

    DL_TimerA_setClockConfig(
        Motor_INST, (DL_TimerA_ClockConfig *) &gMotorClockConfig);

    DL_TimerA_initPWMMode(
        Motor_INST, (DL_TimerA_PWMConfig *) &gMotorConfig);

    // Set Counter control to the smallest CC index being used
    DL_TimerA_setCounterControl(Motor_INST,DL_TIMER_CZC_CCCTL0_ZCOND,DL_TIMER_CAC_CCCTL0_ACOND,DL_TIMER_CLC_CCCTL0_LCOND);

    DL_TimerA_setCaptureCompareOutCtl(Motor_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(Motor_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerA_enableClock(Motor_INST);


    
    DL_TimerA_setCCPDirection(Motor_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by LFCLK /  (4096 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   4096 Hz = 4096 Hz / (8 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gTIMERClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_LFCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_INST_LOAD_VALUE = (0.01s * 4096 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMERTimerConfig = {
    .period     = TIMER_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_init(void) {

    DL_TimerG_setClockConfig(TIMER_INST,
        (DL_TimerG_ClockConfig *) &gTIMERClockConfig);

    DL_TimerG_initTimerMode(TIMER_INST,
        (DL_TimerG_TimerConfig *) &gTIMERTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_INST , DL_TIMERG_INTERRUPT_LOAD_EVENT);
    DL_TimerG_enableClock(TIMER_INST);





}


static const DL_I2C_ClockConfig gOLEDClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_OLED_init(void) {

    DL_I2C_setClockConfig(OLED_INST,
        (DL_I2C_ClockConfig *) &gOLEDClockConfig);
    DL_I2C_disableAnalogGlitchFilter(OLED_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(OLED_INST);
    /* Set frequency to 400000 Hz*/
    DL_I2C_setTimerPeriod(OLED_INST, 9);
    DL_I2C_setControllerTXFIFOThreshold(OLED_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(OLED_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(OLED_INST);


    /* Enable module */
    DL_I2C_enableController(OLED_INST);


}
static const DL_I2C_ClockConfig gWITClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_WIT_init(void) {

    DL_I2C_setClockConfig(WIT_INST,
        (DL_I2C_ClockConfig *) &gWITClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(WIT_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(WIT_INST);




}


static const DL_UART_Main_ClockConfig gWIT_uartClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gWIT_uartConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_WIT_uart_init(void)
{
    DL_UART_Main_setClockConfig(WIT_uart_INST, (DL_UART_Main_ClockConfig *) &gWIT_uartClockConfig);

    DL_UART_Main_init(WIT_uart_INST, (DL_UART_Main_Config *) &gWIT_uartConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(WIT_uart_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(WIT_uart_INST, WIT_uart_IBRD_40_MHZ_115200_BAUD, WIT_uart_FBRD_40_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(WIT_uart_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(WIT_uart_INST_INT_IRQN, 0);

    /* Configure FIFOs */
    DL_UART_Main_enableFIFOs(WIT_uart_INST);
    DL_UART_Main_setRXFIFOThreshold(WIT_uart_INST, DL_UART_RX_FIFO_LEVEL_3_4_FULL);
    DL_UART_Main_setTXFIFOThreshold(WIT_uart_INST, DL_UART_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Configure analog glitch filter */
    DL_UART_Main_enableAnalogGlitchFilter(WIT_uart_INST);
    DL_UART_Main_setAnalogPulseWidth(WIT_uart_INST, DL_UART_PULSE_WIDTH_50_NS);

    DL_UART_Main_enable(WIT_uart_INST);
}

static const DL_UART_Main_ClockConfig gBLUE_TOOTHClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gBLUE_TOOTHConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_BLUE_TOOTH_init(void)
{
    DL_UART_Main_setClockConfig(BLUE_TOOTH_INST, (DL_UART_Main_ClockConfig *) &gBLUE_TOOTHClockConfig);

    DL_UART_Main_init(BLUE_TOOTH_INST, (DL_UART_Main_Config *) &gBLUE_TOOTHConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(BLUE_TOOTH_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(BLUE_TOOTH_INST, BLUE_TOOTH_IBRD_40_MHZ_115200_BAUD, BLUE_TOOTH_FBRD_40_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(BLUE_TOOTH_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(BLUE_TOOTH_INST_INT_IRQN, 1);

    /* Configure FIFOs */
    DL_UART_Main_enableFIFOs(BLUE_TOOTH_INST);
    DL_UART_Main_setRXFIFOThreshold(BLUE_TOOTH_INST, DL_UART_RX_FIFO_LEVEL_3_4_FULL);
    DL_UART_Main_setTXFIFOThreshold(BLUE_TOOTH_INST, DL_UART_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Configure analog glitch filter */
    DL_UART_Main_enableAnalogGlitchFilter(BLUE_TOOTH_INST);
    DL_UART_Main_setAnalogPulseWidth(BLUE_TOOTH_INST, DL_UART_PULSE_WIDTH_50_NS);

    DL_UART_Main_setRXInterruptTimeout(BLUE_TOOTH_INST, 15);

    DL_UART_Main_enable(BLUE_TOOTH_INST);
}

