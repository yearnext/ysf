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
 * @date       2017-08-07                                                      *
 * @brief      mcu gpio application component source files                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup map gpio component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "map_gpio.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
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
#define IS_PORT_NUM_INVAILD(num)                         ((num) >= MCU_PORT_NUM)

#define IS_PIN_NUM_INVAILD(num)                          ((num) >= MCU_PIN_NUM)

#define IS_PIN_MODE_INVAILD(mode)                        ((mode) == 0xFF)                      

#define GPIO_INIT_IS_LOW                                                  (0x40)
#define GPIO_INIT_IS_HIHG                                                 (0x80)

/**
 *******************************************************************************
 * @brief      define mcu address
 *******************************************************************************
 */
#define GPIO_RCC_CONTROL_POS                                                 (2)
#define GPIO_PIN_CONFIG_POS                                                  (1)
#define GPIO_PIN_LOW_VALUE                                                 (0UL)
#define STM32F1XX_GPIO_RORT_OFFSET (GPIOB_BASE - GPIOA_BASE)                               
#define STM32F1XX_PORT_ADDR(port)  ((GPIO_TypeDef *)(GPIOA_BASE + (STM32F1XX_GPIO_RORT_OFFSET * (uint32_t)port))) 

/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
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
    _SET_BIT(RCC->APB2ENR, GPIO_RCC_CONTROL_POS + port);
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
    _SET_BIT(RCC->APB2RSTR, GPIO_RCC_CONTROL_POS + port);
    _CLR_BIT(RCC->APB2RSTR, GPIO_RCC_CONTROL_POS + port);
}

/**
 *******************************************************************************
 * @brief       set gpio mode
 * @param       [in/out]  *reg           gpio port
 * @param       [in/out]  offset         gpio offset
 * @param       [in/out]  mode           set mode
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _mode_set(uint32_t *reg, uint8_t offset, uint8_t mode)
{
    uint8_t i;
    uint8_t temp = mode;
    uint8_t shift = offset;
    
    for(i=0; i<4; i++)
    {
        temp = (mode >> i) & 0x01;
        shift = offset + i;
        
        *reg &= (uint32_t)(~(1 << shift));
        *reg |= (uint32_t)(temp << shift);
    }
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
    GPIO_TypeDef *GPIO = STM32F1XX_PORT_ADDR(port);
    uint32_t regTemp   = 0;
    uint8_t  offset    = (pin % 8)*4;
    
    if(pin >= (MCU_PIN_NUM/2))
    {
        regTemp = GPIO->CRH;
        _mode_set(&regTemp, offset, mode);
        GPIO->CRH = regTemp;
    }
    else
    {
        regTemp = GPIO->CRL;
        _mode_set(&regTemp, offset, mode);
        GPIO->CRL = regTemp;
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
void _set(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F1XX_PORT_ADDR(port);
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
void _clr(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F1XX_PORT_ADDR(port);
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
uint16_t _get_intput(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F1XX_PORT_ADDR(port);

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
uint16_t _get_output(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *GPIO = STM32F1XX_PORT_ADDR(port);
    
    if(_READ_BIT(GPIO->ODR, pin) == GPIO_PIN_LOW_VALUE)
    {
        return 0;
    }    
    
    return 1;
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       enable gpio
 * @param       [in/out]  port                    gpio port
 * @return      [in/out]  HAL_ERR_NONE            enable success
 * @return      [in/out]  HAL_ERR_FAIL            enable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_GPIO_Open(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));

    _close(port);
    _open(port);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable gpio
 * @param       [in/out]  *dev                    gpio block
 * @return      [in/out]  HAL_ERR_NONE            enable success
 * @return      [in/out]  HAL_ERR_FAIL            enable failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Open(struct HalGPIODevice *dev)
{
    return Map_GPIO_Open(dev->Port);
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
hal_err_t Map_GPIO_Close(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    
    _close(port);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disable gpio
 * @param       [in/out]  *dev                    gpio block
 * @return      [in/out]  HAL_ERR_NONE            disable success
 * @return      [in/out]  HAL_ERR_FAIL            disable failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Close(struct HalGPIODevice *dev)
{
    return Map_GPIO_Close(dev->Port);
}

/**
 *******************************************************************************
 * @brief       gpio init
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  io                      config io mode
 * @param       [in/out]  mode                    config gpio mode
 * @return      [in/out]  HAL_ERR_NONE            init success
 * @return      [in/out]  HAL_ERR_FAIL            init failed
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_GPIO_Init(uint8_t port, uint8_t pin, uint8_t io,uint8_t mode)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    hal_assert(IS_PIN_MODE_INVAILD(mode))

	uint8_t setMode = io | setMode;
	
    _config(port, pin, setMode);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       init gpio
 * @param       [in/out]  *dev                    gpio block
 * @return      [in/out]  HAL_ERR_NONE            init success
 * @return      [in/out]  HAL_ERR_FAIL            init failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Init(struct HalGPIODevice *dev)
{
    return Map_GPIO_Init(dev->Port, dev->Pin, dev->IO, dev->Mode);
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
hal_err_t Map_GPIO_Fini(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    _config(port, pin, GPIO_INIT_MODE);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       deinit gpio
 * @param       [in/out]  *dev                    gpio block
 * @return      [in/out]  HAL_ERR_NONE            deinit success
 * @return      [in/out]  HAL_ERR_FAIL            deinit failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Fini(struct HalGPIODevice *dev)
{
    return Map_GPIO_Fini(dev->Port, dev->Pin);
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
hal_err_t Map_GPIO_Set(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    _set(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set gpio pin
 * @param       [in/out]  *dev                    gpio block
 * @return      [in/out]  HAL_ERR_NONE            set success
 * @return      [in/out]  HAL_ERR_FAIL            set failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Set(struct HalGPIODevice *dev)
{
    return Map_GPIO_Set(dev->Port, dev->Pin);
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
hal_err_t Map_GPIO_Clear(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    _clr(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       clear gpio pin
 * @param       [in/out]  *dev                    gpio block
 * @return      [in/out]  HAL_ERR_NONE            clear success
 * @return      [in/out]  HAL_ERR_FAIL            clear failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Clear(struct HalGPIODevice *dev)
{
    return Map_GPIO_Clear(dev->Port, dev->Pin);
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
hal_err_t Map_GPIO_GetIntputStatus(uint8_t port, uint8_t pin, uint16_t *status)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    *status = _get_intput(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio pin intput status
 * @param       [in/out]  *dev                    gpio block
 * @param       [in/out]  *status                 gpio status
 * @return      [in/out]  HAL_ERR_NONE            get success
 * @return      [in/out]  HAL_ERR_FAIL            get failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_GetIntputStatus(struct HalGPIODevice *dev, uint16_t *status)
{
    return Map_GPIO_GetIntputStatus(dev->Port, dev->Pin, status);
}

/**
 *******************************************************************************
 * @brief       get gpio output status
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  *status                 gpio output status
 * @return      [in/out]  HAL_ERR_NONE            get success
 * @return      [in/out]  HAL_ERR_FAIL            get fail
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_GPIO_GetOutputStatus(uint8_t port, uint8_t pin, uint16_t *status)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    *status = _get_output(port, pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get gpio pin output status
 * @param       [in/out]  *dev                    gpio block
 * @param       [in/out]  *status                 gpio status
 * @return      [in/out]  HAL_ERR_NONE            get success
 * @return      [in/out]  HAL_ERR_FAIL            get failed
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_GetOutputStatus(struct HalGPIODevice *dev, uint16_t *status)
{
    return Map_GPIO_GetOutputStatus(dev->Port, dev->Pin, status);
}

/**
 *******************************************************************************
 * @brief       gpio output toggle
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @return      [in/out]  HAL_ERR_NONE            get success
 * @return      [in/out]  HAL_ERR_FAIL            get fail
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_GPIO_Toggle(uint8_t port, uint8_t pin)
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
 * @param       [in/out]  *dev                    gpio block
 * @return      [in/out]  HAL_ERR_NONE            set success
 * @return      [in/out]  HAL_ERR_FAIL            set fail
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Toggle(struct HalGPIODevice *dev)
{
    return Map_GPIO_Toggle(dev->Port, dev->Pin);
}

/**
 *******************************************************************************
 * @brief       write gpio port data
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pos                     gpio pin pos
 * @param       [in/out]  wrData                  write data
 * @param       [in/out]  num                     pos num
 * @return      [in/out]  HAL_ERR_NONE            success
 * @return      [in/out]  HAL_ERR_FAIL            fail
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_GPIO_Write(uint8_t port, uint8_t pos, uint16_t wrData, uint8_t num)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pos+num));
    
    GPIO_TypeDef *GPIO = STM32F1XX_PORT_ADDR(port);
    uint16_t portData = _READ_REG(GPIO->ODR);
    uint8_t i;
    
    //< update cache
    for(i=0; i<num; i++)
    {
        portData &= ~(1 << pos);
        
        if(wrData & 0x01)
        {
            portData |= (1 << pos);
        }
        
        wrData >>= 1 ;
        pos++;
    }
    
    //< update param
    _SET_REG(GPIO->BSRR, portData);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       write gpio port data
 * @param       [in/out]  *dev                    gpio block
 * @param       [in/out]  *param                  set param
 * @return      [in/out]  HAL_ERR_NONE            set success
 * @return      [in/out]  HAL_ERR_FAIL            set fail
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Write(struct HalGPIODevice *dev, struct MspGPIOParam *param)
{
    return Map_GPIO_Write(dev->Port, param->Pos, param->RWData, param->Num);
}

/**
 *******************************************************************************
 * @brief       read gpio port data
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pos                     gpio pin pos
 * @param       [in/out]  *rdData                 read data
 * @param       [in/out]  num                     pos num
 * @return      [in/out]  HAL_ERR_NONE            success
 * @return      [in/out]  HAL_ERR_FAIL            fail
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_GPIO_Read(uint8_t port, uint8_t pos, uint16_t *rdData, uint8_t num)
{
    hal_assert(IS_PTR_NULL(wrData));
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pos+num));
    
    GPIO_TypeDef *GPIO = STM32F1XX_PORT_ADDR(port);
    uint16_t portData = _READ_REG(GPIO->IDR);
    uint16_t tempData;
    uint8_t i;
    
    //< update cache
    for(i=0; i<num; i++)
    {
        tempData = portData & (1 << pos);
        
        if(tempData)
        {
            *rdData |= 1 << pos;
        }
    }

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       read gpio port data
 * @param       [in/out]  *dev                    gpio block
 * @param       [in/out]  *param                  read param
 * @return      [in/out]  HAL_ERR_NONE            read success
 * @return      [in/out]  HAL_ERR_FAIL            read fail
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Read(struct HalGPIODevice *dev, struct MspGPIOParam *param)
{
    return Map_GPIO_Read(dev->Port, param->Pos, &param->RWData, param->Num);
}

/**
 *******************************************************************************
 * @brief       gpio control
 * @param       [in/out]  *dev                    gpio device block
 * @param       [in/out]  cmd                     set gpio cmd
 * @param       [in/out]  *param                  set param
 * @return      [in/out]  HAL_ERR_NONE            set success
 * @return      [in/out]  HAL_ERR_FAIL            set fail
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_GPIO_Control(struct HalGPIODevice *port, uint8_t cmd, void *param)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(param));
    
    switch(cmd)
    {
        case GPIO_CMD_OPEN:
        {
            _close(port->Port);
            _open(port->Port);
            break;
        }
        case GPIO_CMD_CLOSE:
        {
            _close(port->Port);
            break;
        }
        case GPIO_CMD_INIT:
        {
            _config(port->Port, port->Pin, port->Mode);
            break;
        }
        case GPIO_CMD_FINI:
        {
            _config(port->Port, port->Pin, GPIO_INIT_MODE);
            break;
        }
        case GPIO_CMD_SET:
        {
            _set(port->Port, port->Pin);
            break;
        }
        case GPIO_CMD_RESET:
        {
            _clr(port->Port, port->Pin);
            break;
        }
        case GPIO_CMD_GET_INPUT:
        {
            uint16_t *status = (uint16_t *)param;
            *status = _get_intput(port->Port, port->Pin);
            break;
        }
        case GPIO_CMD_GET_OUTPUT:
        {
            uint16_t *status = (uint16_t *)param;
            *status = _get_output(port->Port, port->Pin);
            break;
        }
        case GPIO_CMD_TOGGLE:
        {
            if(_get_output(port->Port, port->Pin))
            {
                _clr(port->Port, port->Pin); 
            }
            else
            {
                _set(port->Port, port->Pin);
            }
            break;
        }
        case GPIO_CMD_WRITE:
        {
            struct MspGPIOParam *WrParam = (struct MspGPIOParam *)param;
            Map_GPIO_Write(port->Port, WrParam->Pos, WrParam->RWData, WrParam->Num);
            break;
        }
        case GPIO_CMD_READ:
        {
            struct MspGPIOParam *RdParam = (struct MspGPIOParam *)param;
            Map_GPIO_Read(port->Port, RdParam->Pos, &RdParam->RWData, RdParam->Num);
            break;
        }
        default:
            break;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       gpio control
 * @param       [in/out]  *dev                    gpio device block
 * @param       [in/out]  cmd                     set gpio cmd
 * @param       [in/out]  *param                  set param
 * @return      [in/out]  HAL_ERR_NONE            set success
 * @return      [in/out]  HAL_ERR_FAIL            set fail
 * @note        This function type is inline
 *******************************************************************************
 */
__INLINE hal_err_t Hal_GPIO_Control(struct HalGPIODevice *dev, uint8_t cmd, void *param)
{
    return Map_GPIO_Control(dev, cmd, param);
}

/** @}*/     /** map gpio component */

/**********************************END OF FILE*********************************/

