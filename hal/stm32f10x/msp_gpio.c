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
 * @file       map_gpio.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-04                                                      *
 * @brief      map gpio source files                                           *
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
#define MCU_PORT_NUM                                                         (7) 
#define MCU_PIN_NUM                                                         (16)

/**
 *******************************************************************************
 * @brief      define gpio assert function
 *******************************************************************************
 */
#define IS_PORT_NUM_INVAILD(num)                       ( (num) >= MCU_PORT_NUM )

#define IS_PIN_NUM_INVAILD(num)                        ( (num) >= MCU_PIN_NUM  )

#define IS_PIN_MODE_INVAILD(mode)                      ((mode) == 0xFF)                      

#define GPIO_INIT_IS_LOW                                                  (0x40)
#define GPIO_INIT_IS_HIHG                                                 (0x80)

/**
 *******************************************************************************
 * @brief      define mcu address
 *******************************************************************************
 */
#define GPIO_RCC_CONTROL_POS                                                 (4)
#define GPIO_PIN_CONFIG_POS                                                  (1)
#define GPIO_PIN_LOW_VALUE                                                 (0UL)
#define STM32F10X_GPIO_RORT_OFFSET (GPIOB_BASE - GPIOA_BASE)                               
#define STM32F10X_PORT_ADDR(port)  ((GPIO_TypeDef *)(GPIOA_BASE + (STM32F10X_GPIO_RORT_OFFSET * (uint32_t)port)))   

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
void _open(uint8_t port)
{
    RCC->APB2ENR |= GPIO_RCC_CONTROL_POS << port;
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
void _close(uint8_t port)
{
    RCC->APB2RSTR |= GPIO_RCC_CONTROL_POS << port;
    RCC->APB2RSTR &= ~(GPIO_RCC_CONTROL_POS << port);
}

/**
 *******************************************************************************
 * @brief       gpio config
 * @param       [in/out]  port           gpio port
 * @param       [in/out]  pin            gpio pin
 * @param       [in/out]  mode           gpio mode
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _config(uint8_t port, uint8_t pin, uint8_t mode)
{
    GPIO_TypeDef *GPIO = STM32F10X_PORT_ADDR(port);
    uint8_t offset     = pin%8;

    union MCU_GPIO_MODE_REG
    {
//        struct
//        {
//            uint32_t ModeBit0 : 1;
//            uint32_t ModeBit1 : 1;
//            uint32_t ConfBit0 : 1;
//            uint32_t ConfBit1 : 1;
//        }GPIOPinModeBit[8];
        
        struct
        {
            uint32_t GPIOPinMode : 4;
        }GPIOPinModeValue[8];

        uint32_t RegValue;
    }GPIOModeReg;

    if(pin/8)
    {
        GPIOModeReg.RegValue = GPIO->CRH;
        GPIOModeReg.GPIOPinModeValue[offset].GPIOPinMode = mode & 0x0F;
        GPIO->CRH = GPIOModeReg.GPIOPinModeValue[offset].GPIOPinMode;
        
        if(mode & GPIO_INIT_IS_HIHG)
        {
            _SET_BIT(GPIO->ODR, pin);
        }
        else
        {
            _CLR_BIT(GPIO->ODR, pin);
        }
    }
    else
    {
        GPIOModeReg.RegValue = GPIO->CRL;
        GPIOModeReg.GPIOPinModeValue[offset].GPIOPinMode = mode & 0x0F;
        GPIO->CRL = GPIOModeReg.GPIOPinModeValue[offset].GPIOPinMode;
        
        if(mode & GPIO_INIT_IS_HIHG)
        {
            _SET_BIT(GPIO->ODR, pin);
        }      
        else
        {
            _CLR_BIT(GPIO->ODR, pin);
        }
    }
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
void _set( uint8_t port, uint8_t pin )
{
    GPIO_TypeDef *GPIO = STM32F10X_PORT_ADDR(port);
    _SET_BIT(GPIO->BSRR, pin);
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
void _clr( uint8_t port, uint8_t pin )
{
    GPIO_TypeDef *GPIO = STM32F10X_PORT_ADDR(port);
    _SET_BIT(GPIO->BRR, pin);
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
uint8_t _get_input(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F10X_PORT_ADDR(port);

    if(_READ_BIT(GPIO->IDR, pin) == GPIO_PIN_LOW_VALUE)
    {
        return 0;
    }    
    
    return 1;
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
uint8_t _get_output(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F10X_PORT_ADDR(port);
    
    if(_READ_BIT(GPIO->ODR, pin) == GPIO_PIN_LOW_VALUE)
    {
        return 0;
    }    
    
    return 1;
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
hal_err_t MSP_GPIO_Open(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));

    _close(port);
    _open(port);
    
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
hal_err_t MSP_GPIO_Close(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    
    _close(port);
    
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
hal_err_t MSP_GPIO_Init(uint8_t port, uint8_t pin, uint8_t mode)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    hal_assert(IS_PIN_MODE_INVAILD(mode))
    
    _config(port, pin, mode);
    
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
hal_err_t MSP_GPIO_Deinit(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    _config(port, pin, GPIO_INIT_MODE);
    
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
hal_err_t MSP_GPIO_Set(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    _set(port, pin);
    
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
hal_err_t MSP_GPIO_Clr(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    _clr(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio input status
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  *status                 gpio input status
 * @return      [in/out]  HAL_ERR_NONE            success
 * @return      [in/out]  HAL_ERR_FAIL            fail
 * @note        None
 *******************************************************************************
 */
hal_err_t MSP_GPIO_GetInputStatus(uint8_t port, uint8_t pin, uint8_t *status)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    *status = _get_input(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio output status
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  *status                 gpio output status
 * @return      [in/out]  HAL_ERR_NONE            success
 * @return      [in/out]  HAL_ERR_FAIL            fail
 * @note        None
 *******************************************************************************
 */
hal_err_t MSP_GPIO_GetOutputStatus(uint8_t port, uint8_t pin, uint8_t *status)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    *status = _get_output(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       gpio output toggle
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @return      [in/out]  HAL_ERR_NONE            success
 * @return      [in/out]  HAL_ERR_FAIL            fail
 * @note        None
 *******************************************************************************
 */
hal_err_t MSP_GPIO_Toggle(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    if(_get_output(port, pin))
    {
        _clr(port, pin); 
    }
    else
    {
        _set(port, pin);
    }
    
    return HAL_ERR_NONE;
}


/**
 *******************************************************************************
 * @brief       gpio output toggle
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @return      [in/out]  HAL_ERR_NONE            success
 * @return      [in/out]  HAL_ERR_FAIL            fail
 * @note        None
 *******************************************************************************
 */
hal_err_t MSP_GPIO_OutputCmd(uint8_t port, uint8_t pin, uint8_t cmd)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    if(cmd)
    {
        _set(port, pin); 
    }
    else
    {
        _clr(port, pin);
    }
    
    return HAL_ERR_NONE;
}
#endif 

/** @}*/     /** gpio component */

/**********************************END OF FILE*********************************/
