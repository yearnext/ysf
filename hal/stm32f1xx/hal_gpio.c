/**
 *******************************************************************************
 *                       Copyright (C) 2017  yearnext                          *
 *                                                                             *
 *    This program is free software; you can redistribute it and/or modify     *
 *    it under the terms of the GNU General Public License as published by     *
 *    the Free Software Foundation; either version 2 of the License, or        *
 *    (at your option) any later version.                                      *
 *                                                                             *
 *    This program is distributed in the hope that it will be useful,          *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *    GNU General Public License for more details.                             *
 *                                                                             *
 *    You should have received a copy of the GNU General Public License along  *
 *    with this program; if not, write to the Free Software Foundation, Inc.,  *
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 *******************************************************************************
 * @file       hal_gpio.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-04                                                      *
 * @brief      gpio source files                                               *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/**
 * @defgroup gpio component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _HAL_PATH
#include _HAL_MAL_PATH
#include _HAL_GPIO_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define mcu port num and pin num
 *******************************************************************************
 */
#if defined(STM32F100xB)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F100xE)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101x6)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101xB)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101xE)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101xG)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F102x6)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F102xB)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103x6)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103xB)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103xE)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103xG)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F105xC)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F107xC)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#else
    #define MCU_USE_PORT_NUM (0) 
    #define PORT_USE_PIN_NUM (0)
#endif

/**
 *******************************************************************************
 * @brief      define gpio assert function
 *******************************************************************************
 */
#define IS_PORT_NUM_INVAILD(num)                   ( (num) >= MCU_USE_PORT_NUM )
#define IS_PIN_NUM_INVAILD(num)                    ( (num) >= PORT_USE_PIN_NUM )

/**
 *******************************************************************************
 * @brief      define mcu address
 *******************************************************************************
 */
#define RCC_GPIO_CONFIG_HEAD                              ((uint32_t)0x00000004)
#define GPIO_PIN_CONFIG_HEAD                                  ((uint16_t)0x0001)

//#define DEFINE_GPIO_PORT(name) GPIO_TypeDef *name[] = \
//                               {                      \
//                                   GPIOA,             \
//                                   GPIOB,             \
//                                   GPIOC,             \
//                                   GPIOD,             \
//                                   GPIOE,             \
//                                   GPIOF,             \
//                                   GPIOG,             \
//                               }
//                                   
//#define DEFINE_PIN_MODE(name)  uint8_t name[] =                                            \
//                               {                                                           \
//                                    0x04,                                                  \
//                                    PIN_INPUT_MODE              | PIN_ANALOG_INPUT,        \
//                                    PIN_INPUT_MODE              | PIN_FLOAT_INPUT,         \
//                                    PIN_INPUT_MODE              | PIN_UP_DOWN_INPUT,       \
//                                                                                           \
//                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_PUSH_PULL_OUTPUT,    \
//                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_OPEN_DNAIN_INPUT,    \
//                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,  \
//                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT, \
//                                                                                           \
//                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_PUSH_PULL_OUTPUT,    \
//                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_OPEN_DNAIN_INPUT,    \
//                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_PUSH_PULL_INPUT,  \
//                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_OPEN_DNAIN_INPUT, \
//                                                                                           \
//                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_PUSH_PULL_OUTPUT,    \
//                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_OPEN_DNAIN_INPUT,    \
//                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,  \
//                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT, \
//                               }

#define STM32F1_GPIO_RORT_OFFSET ((uint32_t)(GPIOB_BASE - GPIOA_BASE))                               
#define STM32F1_PORT_ADDR(port)  ((GPIO_TypeDef *)(GPIOA_BASE + (uint32_t)(STM32F1_GPIO_RORT_OFFSET * (uint32_t)port)))   

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       enable gpio
 * @param       [in/out]  port           gpio port
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void gpio_enable(uint8_t port)
{
    RCC->APB2ENR  |= RCC_GPIO_CONFIG_HEAD << port;
}

/**
 *******************************************************************************
 * @brief       disable gpio
 * @param       [in/out]  port           gpio port
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void gpio_disable(uint8_t port)
{
    RCC->APB2RSTR |= RCC_GPIO_CONFIG_HEAD << port;
    RCC->APB2RSTR &= ~(RCC_GPIO_CONFIG_HEAD << port);
}

/**
 *******************************************************************************
 * @brief       gpio mode clear
 * @param       [in/out]  *reg             gpio mode config register address
 * @param       [in/out]  offset           gpio mode offset
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void gpio_mode_clr( uint32_t *reg, uint8_t offset )
{
    uint8_t i;
    uint8_t shift = offset;
    
    for( i=0; i<4; i++ )
    {
        shift = offset + i;
        
        *reg &= (uint32_t)(~(1 << shift));
    }
}

/**
 *******************************************************************************
 * @brief       gpio mode set
 * @param       [in/out]  *reg             gpio mode config register address
 * @param       [in/out]  offset           gpio mode offset
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void gpio_mode_set( uint32_t *reg, uint8_t offset, uint8_t mode )
{
    uint8_t i;
    uint8_t temp = mode;
    uint8_t shift = offset;
    
    for( i=0; i<4; i++ )
    {
        temp = (mode >> i) & 0x01;
        shift = offset + i;
        
        *reg |= (uint32_t)(temp << shift);
    }
}

/**
 *******************************************************************************
 * @brief       gpio mode config
 * @param       [in/out]  port             gpio port
 * @param       [in/out]  pin              gpio pin
 * @param       [in/out]  mode             gpio mode
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void gpio_config(uint8_t port, uint8_t pin, uint8_t mode)
{
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    uint32_t gpio_crl  = GPIO->CRL;
    uint32_t gpio_crh  = GPIO->CRH;
    uint8_t  offset    = (pin % 8)*4;
    
    if( pin >= (PORT_USE_PIN_NUM/2) )
    {
        gpio_mode_clr(&gpio_crh, offset);
        gpio_mode_set(&gpio_crh, offset, mode);
    }
    else
    {
        gpio_mode_clr(&gpio_crl, offset);
        gpio_mode_set(&gpio_crl, offset, mode);
    }
    
    GPIO->CRL = gpio_crl;
    GPIO->CRH = gpio_crh;
}

/**
 *******************************************************************************
 * @brief       set gpio status
 * @param       [in/out]  port             gpio port
 * @param       [in/out]  pin              gpio pin
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void gpio_set( uint8_t port, uint8_t pin )
{
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    GPIO->BSRR |= GPIO_PIN_CONFIG_HEAD << pin;
}

/**
 *******************************************************************************
 * @brief       clear gpio status
 * @param       [in/out]  port             gpio port
 * @param       [in/out]  pin              gpio pin
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void gpio_clr( uint8_t port, uint8_t pin )
{
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    GPIO->BRR |= GPIO_PIN_CONFIG_HEAD << pin;
}

/**
 *******************************************************************************
 * @brief       get gpio input status
 * @param       [in/out]  port             gpio port
 * @param       [in/out]  pin              gpio pin
 * @return      [in/out]  true             pin is high
 * @return      [in/out]  false            pin is low
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
bool gpio_get_input(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    return ((GPIO->IDR & (GPIO_PIN_CONFIG_HEAD << pin)) ? (true) : (false));
}

/**
 *******************************************************************************
 * @brief       get gpio output status
 * @param       [in/out]  port             gpio port
 * @param       [in/out]  pin              gpio pin
 * @return      [in/out]  true             pin is high
 * @return      [in/out]  false            pin is low
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
bool gpio_get_output(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    return ((GPIO->ODR & (GPIO_PIN_CONFIG_HEAD << pin)) ? (true) : (false));
}

/* Exported functions --------------------------------------------------------*/
#if USE_MSP_GPIO_COMPONENT
/**
 *******************************************************************************
 * @brief       enable gpio
 * @param       [in/out]  port                    gpio port
 * @return      [in/out]  HAL_ERR_NONE            enable success
 * @return      [in/out]  HAL_ERR_FAIL            enable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MspEnableGPIO(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));

    gpio_disable(port);
    gpio_enable(port);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disable gpio
 * @param       [in/out]  port                    gpio port
 * @return      [in/out]  HAL_ERR_NONE            disable success
 * @return      [in/out]  HAL_ERR_FAIL            disable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MspDisableGPIO(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    
    gpio_disable(port);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       gpio init
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  mode                    config mode
 * @return      [in/out]  HAL_ERR_NONE            init success
 * @return      [in/out]  HAL_ERR_FAIL            init failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MspInitGPIO(uint8_t port, uint8_t pin, uint8_t mode)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    
    gpio_config(port, pin, mode);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       gpio deinit
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @return      [in/out]  HAL_ERR_NONE            deinit success
 * @return      [in/out]  HAL_ERR_FAIL            deinit failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MspDeinitGPIO(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    gpio_config(port, pin, GPIO_PIN_INIT_MODE);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set gpio
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @return      [in/out]  HAL_ERR_NONE            set success
 * @return      [in/out]  HAL_ERR_FAIL            set failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MspSetGPIO(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    gpio_set(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       clear gpio
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @return      [in/out]  HAL_ERR_NONE            clear success
 * @return      [in/out]  HAL_ERR_FAIL            clear failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MspClrGPIO(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    gpio_clr(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio input status
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  *status                 gpio input status
 * @return      [in/out]  true                    gpio is high
 * @return      [in/out]  false                   gpio is low
 * @note        None
 *******************************************************************************
 */
hal_err_t MspGetGPIOInputStatus(uint8_t port, uint8_t pin, bool *status)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    *status = gpio_get_input(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio output status
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  *status                 gpio output status
 * @return      [in/out]  true                    gpio is high
 * @return      [in/out]  false                   gpio is low
 * @note        None
 *******************************************************************************
 */
hal_err_t MspGetGPIOOutputStatus(uint8_t port, uint8_t pin, bool *status)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    *status = gpio_get_output(port, pin);
    
    return HAL_ERR_NONE;
}
#endif 

#if USE_MAP_GPIO_COMPONENT
/**
 *******************************************************************************
 * @brief       enable gpio
 * @param       [in/out]  *gpio                   gpio block
 * @return      [in/out]  HAL_ERR_NONE            enable success
 * @return      [in/out]  HAL_ERR_FAIL            enable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalEnableGPIO(struct HalGPIOBlock *gpio)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    
    gpio_disable(gpio->Port);
    gpio_enable(gpio->Port);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disable gpio
 * @param       [in/out]  *gpio                   gpio block
 * @return      [in/out]  HAL_ERR_NONE            disable success
 * @return      [in/out]  HAL_ERR_FAIL            disable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalDisableGPIO(struct HalGPIOBlock *gpio)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    
    gpio_disable(gpio->Port);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       gpio init
 * @param       [in/out]  *gpio                   gpio block
 * @return      [in/out]  HAL_ERR_NONE            init success
 * @return      [in/out]  HAL_ERR_FAIL            init failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalInitGPIO(struct HalGPIOBlock *gpio)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    hal_assert(IS_PIN_NUM_INVAILD(gpio->Pin));
    
    gpio_config(gpio->Port, gpio->Pin, gpio->Mode);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       gpio deinit
 * @param       [in/out]  *gpio                   gpio block
 * @return      [in/out]  HAL_ERR_NONE            deinit success
 * @return      [in/out]  HAL_ERR_FAIL            deinit failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalDeinitGPIO(struct HalGPIOBlock *gpio)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    hal_assert(IS_PIN_NUM_INVAILD(gpio->Pin));
    
    gpio_config(gpio->Port, gpio->Pin, GPIO_PIN_INIT_MODE);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set gpio pin
 * @param       [in/out]  *gpio                   gpio block
 * @return      [in/out]  HAL_ERR_NONE            set success
 * @return      [in/out]  HAL_ERR_FAIL            set failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalSetGPIO(struct HalGPIOBlock *gpio)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    hal_assert(IS_PIN_NUM_INVAILD(gpio->Pin));
    
    gpio_set(gpio->Port, gpio->Pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       clear gpio pin
 * @param       [in/out]  *gpio                   gpio block
 * @return      [in/out]  HAL_ERR_NONE            clear success
 * @return      [in/out]  HAL_ERR_FAIL            clear failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalClrGPIO(struct HalGPIOBlock *gpio)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    hal_assert(IS_PIN_NUM_INVAILD(gpio->Pin));
    
    gpio_clr(gpio->Port, gpio->Pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       gpio pin toggle
 * @param       [in/out]  *gpio                   gpio block
 * @return      [in/out]  HAL_ERR_NONE            clear success
 * @return      [in/out]  HAL_ERR_FAIL            clear failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalToggleGPIO(struct HalGPIOBlock *gpio)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    hal_assert(IS_PIN_NUM_INVAILD(gpio->Pin));
    
    if (gpio_get_output(gpio->Port, gpio->Pin) == true)
    {
        gpio_clr(gpio->Port, gpio->Pin);
    }
    else
    {
        gpio_set(gpio->Port, gpio->Pin);
    }

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio input status
 * @param       [in/out]  *gpio            gpio block
 * @param       [in/out]  *status          gpio input status
 * @return      [in/out]  HAL_ERR_NONE     get success
 * @return      [in/out]  HAL_ERR_FAIL     get failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalGetGPIOInputStatus(struct HalGPIOBlock *gpio, bool *status)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    hal_assert(IS_PIN_NUM_INVAILD(gpio->Pin));
    
    *status = gpio_get_input(gpio->Port, gpio->Pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio output status
 * @param       [in/out]  *gpio            gpio block
 * @param       [in/out]  *status          gpio output status
 * @return      [in/out]  HAL_ERR_NONE     get success
 * @return      [in/out]  HAL_ERR_FAIL     get failed
 * @note        None
 *******************************************************************************
 */
hal_err_t HalGetGPIOOutputStatus(struct HalGPIOBlock *gpio, bool *status)
{
    hal_assert(IS_PTR_NULL(gpio));
    hal_assert(IS_PORT_NUM_INVAILD(gpio->Port));
    hal_assert(IS_PIN_NUM_INVAILD(gpio->Pin));
    
    *status = gpio_get_output(gpio->Port, gpio->Pin);
    
    return HAL_ERR_NONE;
}
#endif

/** @}*/     /** gpio component */

/**********************************END OF FILE*********************************/
