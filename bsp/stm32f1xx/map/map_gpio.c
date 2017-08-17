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
#include "stm32f1xx.h"
#include "map_gpio.h"

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
#if USE_GPIO_COMPONENT
static const struct Map_GPIO_Opera _gpio_ops = 
{
    .Open = Map_GPIO_Open,
    .Close = Map_GPIO_Close, 
    
    .Init = Map_GPIO_Init,
    .Fini = Map_GPIO_Fini,
    
    .Write = Map_GPIO_Write,
    .Read = Map_GPIO_Read,
};
#endif

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define uart register
 *******************************************************************************
 */ 
static GPIO_TypeDef * const GPIO[] = 
{
#ifdef GPIOA
    GPIOA,
#endif
    
#ifdef GPIOB
    GPIOB,
#endif
    
#ifdef GPIOC
    GPIOC,
#endif
    
#ifdef GPIOD
    GPIOD,
#endif
    
#ifdef GPIOE
    GPIOE,
#endif
    
#ifdef GPIOF
    GPIOF,
#endif
    
#ifdef GPIOG
    GPIOG,
#endif
};

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define mcu port num and pin num
 *******************************************************************************
 */
#define MCU_PORT_NUM                                              (_dimof(GPIO)) 
#define MCU_PIN_NUM                                                         (16)

/**
 *******************************************************************************
 * @brief      define gpio assert function
 *******************************************************************************
 */
#define IS_PORT_NUM_INVAILD(num)                         ((num) >= MCU_PORT_NUM)

#define IS_PIN_NUM_INVAILD(num)                           ((num) >= MCU_PIN_NUM)                 

/**
 *******************************************************************************
 * @brief      define mcu address
 *******************************************************************************
 */
#define GPIO_RCC_CONTROL_POS                                                 (2)
#define GPIO_PIN_CONFIG_POS                                                  (1)
#define GPIO_PIN_LOW_VALUE                                                 (0UL)

/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_GPIO_COMPONENT
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
    GPIO_TypeDef *gpio = GPIO[port];
    uint32_t regTemp   = 0;
    uint8_t  offset    = (pin % 8)*4;
    
    if(pin >= (MCU_PIN_NUM/2))
    {
        regTemp = gpio->CRH;
        _mode_set(&regTemp, offset, mode);
        gpio->CRH = regTemp;
    }
    else
    {
        regTemp = gpio->CRL;
        _mode_set(&regTemp, offset, mode);
        gpio->CRL = regTemp;
    }
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       enable gpio
 * @param       [in/out]  port                    gpio port
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_GPIO_Open(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));

    _open(port);
}

/**
 *******************************************************************************
 * @brief       disable gpio
 * @param       [in/out]  port                    gpio port
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_GPIO_Close(uint8_t port)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    
    _close(port);
}

/**
 *******************************************************************************
 * @brief       gpio init
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @param       [in/out]  io                      config io mode
 * @param       [in/out]  mode                    config gpio mode
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_GPIO_Init(uint8_t port, uint8_t pin, uint8_t dir, uint8_t mode)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));

	uint8_t setMode = 0x00;
    
    //< set gpio dir param
    if(dir == GPIO_DIR_LS_OUTPUT)
    {
        setMode = 0x01;
    }
    else if(dir == GPIO_DIR_MS_OUTPUT)
    {
        setMode = 0x02;
    }
    else if(dir == GPIO_DIR_HS_OUTPUT)
    {
        setMode = 0x03;
    }
    else
    {
        //<  do nothing!
    }
    
    //< set gpio mode
    if(dir == GPIO_ANALOG_MODE)
    {
        setMode |= 0x00;
    }
    else if(dir == GPIO_FLOAT_MODE)
    {
        setMode |= 0x04;
    }
    else if(dir == GPIO_PULL_UP_DOWN_MODE)
    {
        setMode |= 0x08;
    }
    else if(dir == GPIO_PUSH_PULL_MODE)
    {
        setMode |= 0x00;
    }
    else if(dir == GPIO_OPEN_DRAIN_MODE)
    {
        setMode |= 0x04;
    }
    else if(dir == GPIO_AF_PUSH_PULL_MODE)
    {
        setMode |= 0x08;
    }
    else if(dir == GPIO_AF_OPEN_DRAIN_MODE)
    {
        setMode |= 0x0C;
    }
    else
    {
        //< do nothing!
    }
    
    //< init port
    _config(port, pin, setMode);
}

/**
 *******************************************************************************
 * @brief       gpio deinit
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pin                     gpio pin
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_GPIO_Fini(uint8_t port, uint8_t pin)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pin));
    
    _config(port, pin, GPIO_INIT_MODE);
}

/**
 *******************************************************************************
 * @brief       write gpio port data
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  pos                     gpio pin pos
 * @param       [in/out]  wrData                  write data
 * @param       [in/out]  num                     pos num
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_GPIO_Write(uint8_t port, uint8_t pos, uint16_t wrData, uint8_t num)
{
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pos+num));
    
    GPIO_TypeDef *gpio = GPIO[port];
    uint16_t portData = _READ_REG(gpio->ODR);

    //< update cache
    for(; num--; pos++)
    {
        if(wrData & (1 << pos))
        {
            portData |= (1 << pos);
        }
        else
        {
            portData &= ~(1 << pos);
        }
    }
    
    //< update param
    _SET_REG(gpio->BSRR, portData);
}

/**
 *******************************************************************************
 * @brief       read gpio port data
 * @param       [in/out]  port                    gpio port
 * @param       [in/out]  dir                     get intput or output data
 * @param       [in/out]  pos                     gpio pin pos
 * @param       [in/out]  *rdData                 read data
 * @param       [in/out]  num                     pos num
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_GPIO_Read(uint8_t port, uint8_t dir, uint8_t pos, uint16_t *rdData, uint8_t num)
{
    hal_assert(IS_PTR_NULL(wrData));
    hal_assert(IS_PORT_NUM_INVAILD(port));
    hal_assert(IS_PIN_NUM_INVAILD(pos+num));
    
    GPIO_TypeDef *gpio = GPIO[port];
    uint16_t portData;
    
    //< get register data
    (dir == GPIO_DIR_INTPUT) ? (portData = _READ_REG(gpio->ODR)) \
                             : (portData = _READ_REG(gpio->IDR));
                             
    //< update register data
    for(; num--; pos++)
    {
        if (portData & (1 << pos))
        {
            *rdData |= 1 << pos;
        }
    }
}

/**
 *******************************************************************************
 * @brief       register gpio opara
 * @param       [in/out]  **ops                   gpio opera
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_GPIO_API_Register(void **ops)
{
    hal_assert(IS_PTR_NULL(ops));
    
    *ops = (void *)&_gpio_ops;
}

#endif

/** @}*/     /** map gpio component */

/**********************************END OF FILE*********************************/

