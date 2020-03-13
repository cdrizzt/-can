
#include "delay.h"

// Global
volatile uint32_t _millis = 0;
int microsDivider = 1;

void Delay_Init(void)
{
    // 1ms / interrupt
    SysTick_Config(SystemCoreClock / 1000);
    // reset time
    _millis = 0;
    microsDivider = SystemCoreClock / 1000000;
    // highest priority
    NVIC_SetPriority(SysTick_IRQn, 0);
}

/**
 * @brief
 * @details Rolls over at max of uint32_t or ~71 minutes
 * @return Time elapsed in microseconds since the start of the program
 */
static inline uint32_t micros(void) __attribute__((always_inline, unused));
static inline uint32_t micros(void)
{
    // return _millis * 1000 + TIM_GetCounter(TIMER_MAP[ TIMEBASE_MAP[ SYSCLK_TIMEBASE ].timer ].TIMx);
    // systick is a downcounter
    volatile uint32_t ret = _millis * 1000 + 1000 - SysTick->VAL/microsDivider;
    return ret;
}

/**
 * @brief
 * @details Rolls over at max of uint32_t or ~50 days
 * @return Time elapsed in milliseconds since the start of the program
 */
//static inline uint32_t millis() __attribute__((always_inline, unused));
//static inline uint32_t millis() {
__inline uint32_t millis(void) {
    volatile uint32_t ret = _millis;
    return ret;
}

void delayMicroseconds(uint32_t n)
{
    // fudge for function call overhead
    n--;
    uint32_t start = micros();
    while (micros() - start < n);
}

void delay(uint32_t n)
{
    uint32_t start = millis();
    while (millis() - start < n);
}

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
