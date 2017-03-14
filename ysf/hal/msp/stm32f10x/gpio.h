/**
 ******************************************************************************
 * @file       gpio.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017年3月4日
 * @brief      gpio head file
 * @par        work paltform		                             
 *                 Windows
 * @par        compiler paltform									                         
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup gpio component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10X_GPIO_H__
#define __STM32F10X_GPIO_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_DIR

/* Exported macro ------------------------------------------------------------*/
#define USE_MSP_GPIO_API (1)
    
enum
{
    MCU_PORT_A = 0,
    MCU_PORT_B = 1,
    MCU_PORT_C = 2,
    MCU_PORT_D = 3,
    MCU_PORT_E = 4,
    MCU_PORT_F = 5,
    MCU_PORT_G = 6,
    
    MCU_PORT_0 = 0,
    MCU_PORT_1 = 1,
    MCU_PORT_2 = 2,
    MCU_PORT_3 = 3,
    MCU_PORT_4 = 4,
    MCU_PORT_5 = 5,
    MCU_PORT_6 = 6,
    
    MCU_PIN_0  = 0,
    MCU_PIN_1  = 1,
    MCU_PIN_2  = 2,
    MCU_PIN_3  = 3,
    MCU_PIN_4  = 4,
    MCU_PIN_5  = 5,
    MCU_PIN_6  = 6,
    MCU_PIN_7  = 7,
    MCU_PIN_8  = 8,
    MCU_PIN_9  = 9,
    MCU_PIN_10 = 10,
    MCU_PIN_11 = 11,
    MCU_PIN_12 = 12,
    MCU_PIN_13 = 13,
    MCU_PIN_14 = 14,
    MCU_PIN_15 = 15,
};
    
#define PIN_INPUT_MODE              (0x00)
                            
#define PIN_ANALOG_INPUT            (0x00)
#define PIN_FLOAT_INPUT             (0x04)
#define PIN_UP_DOWN_INPUT           (0x08)
   
#define PIN_LOW_SPEED_OUTPUT_MODE   (0x02)
#define PIN_MEDIUM_SPEED_INPUT_MODE (0x01)
#define PIN_HIGH_SPEED_INPUT_MODE   (0x03)
                               
#define PIN_PUSH_PULL_OUTPUT        (0x00)
#define PIN_OPEN_DNAIN_INPUT        (0x04)
#define PIN_AF_PUSH_PULL_INPUT      (0x08)         
#define PIN_AF_OPEN_DNAIN_INPUT     (0x0C)  

enum
{
    GPIO_PIN_INIT_MODE       = 0x04,                                                           /** 初始化模式 */
     
    GPIO_PIN_I_A_MODE        = PIN_INPUT_MODE              | PIN_ANALOG_INPUT,                 /** 浮空输入模式 */
    GPIO_PIN_I_F_MODE        = PIN_INPUT_MODE              | PIN_FLOAT_INPUT,                  /** 浮点输入模式 */
    GPIO_PIN_I_UD_MODE       = PIN_INPUT_MODE              | PIN_UP_DOWN_INPUT,                /** 上拉/下拉输入模式 */
 
    GPIO_PIN_O_PP_LS_MODE    = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_PUSH_PULL_OUTPUT,             /** 低速(2 Mhz)推挽输出模式 */
    GPIO_PIN_O_OD_LS_MODE    = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_OPEN_DNAIN_INPUT,             /** 低速(2 Mhz)开漏输出模式 */
    GPIO_PIN_AF_O_PP_LS_MODE = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,           /** 低速(2 Mhz)复用推挽输出模式 */
    GPIO_PIN_AF_O_OD_LS_MODE = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT,          /** 低速(2 Mhz)复用开漏输出模式 */

    GPIO_PIN_O_PP_MS_MODE    = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_PUSH_PULL_OUTPUT,             /** 中速(10 Mhz)推挽输模式 */
    GPIO_PIN_O_OD_MS_MODE    = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_OPEN_DNAIN_INPUT,             /** 中速(10 Mhz)开漏输出模式 */
    GPIO_PIN_AF_O_PP_MS_MODE = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_PUSH_PULL_INPUT,           /** 中速(10 Mhz)复用推挽输出模式 */ 
    GPIO_PIN_AF_O_OD_MS_MODE = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_OPEN_DNAIN_INPUT,          /** 中速(10 Mhz)复用开漏输出模式 */
     
    GPIO_PIN_O_PP_HS_MODE    = PIN_HIGH_SPEED_INPUT_MODE   | PIN_PUSH_PULL_OUTPUT,             /** 高速(50 Mhz)推挽输出模式 */
    GPIO_PIN_O_OD_HS_MODE    = PIN_HIGH_SPEED_INPUT_MODE   | PIN_OPEN_DNAIN_INPUT,             /** 高速(50 Mhz)开漏输出模式 */
    GPIO_PIN_AF_O_PP_HS_MODE = PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,           /** 高速(50 Mhz)复用推挽输出模式 */
    GPIO_PIN_AF_O_OD_HS_MODE = PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT,          /** 高速(50 Mhz)复用开漏输出模式 */
};
    
/* Exported types ------------------------------------------------------------*/
struct ysf_msp_gpio_t
{
    uint8_t port;
    uint8_t pin;
    uint8_t mode;
};
    
struct MSP_GPIO_API
{
    struct
    {
        ysf_err_t (*init)(uint8_t);
        ysf_err_t (*fini)(uint8_t);
        ysf_err_t (*config)(uint8_t,uint8_t,uint8_t);
        ysf_err_t (*set)(uint8_t,uint8_t);
        ysf_err_t (*clr)(uint8_t,uint8_t);
        bool (*get)(uint8_t,uint8_t);
    }msp;
    
    struct
    {
        ysf_err_t (*init)(struct ysf_msp_gpio_t*);
        ysf_err_t (*fini)(struct ysf_msp_gpio_t*);
        ysf_err_t (*config)(struct ysf_msp_gpio_t*);
        ysf_err_t (*set)(struct ysf_msp_gpio_t*);
        ysf_err_t (*clr)(struct ysf_msp_gpio_t*);
        bool (*get)(struct ysf_msp_gpio_t*);
    }map;
};
    
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern ysf_err_t msp_gpio_init(uint8_t);
extern ysf_err_t msp_gpio_fini(uint8_t);
extern ysf_err_t msp_gpio_config(uint8_t,uint8_t,uint8_t);
extern ysf_err_t msp_gpio_set(uint8_t,uint8_t);
extern ysf_err_t msp_gpio_clr(uint8_t,uint8_t);
extern bool msp_gpio_get(uint8_t,uint8_t);

extern ysf_err_t map_gpio_init(struct ysf_msp_gpio_t*);
extern ysf_err_t map_gpio_fini(struct ysf_msp_gpio_t*);
extern ysf_err_t map_gpio_config(struct ysf_msp_gpio_t*);
extern ysf_err_t map_gpio_set(struct ysf_msp_gpio_t*);
extern ysf_err_t map_gpio_clr(struct ysf_msp_gpio_t*);
extern bool map_gpio_get(struct ysf_msp_gpio_t*);

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
