# ysf——yearnext software framework

[![GitHub release](https://img.shields.io/badge/version-0.0.3-red.svg)](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-debug)  [![AUR](http://progressed.io/bar/25?title=debug)](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-debug)  [![AUR](https://img.shields.io/badge/license-GPL%20V2-blue.svg)](https://coding.net/u/yearnext/p/ysf/git/blob/ysf-stm32f1xx-debug/LICENSE)  [![AUR](https://img.shields.io/badge/language-c-blue.svg)]()  [![AUR](https://img.shields.io/badge/platform-stm8-green.svg)](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm8-alpha)  [![AUR](https://img.shields.io/badge/platform-stm32-green.svg)](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha)

## 目录
* [框架简介](#1)
* [框架目录](#2)
* [相关文档](#3)
* [例程](#4)

<h2 id="1"> 框架简介 </h2>
ysf是一个基于事件驱动的单片机编程框架。

<h2 id="2"> 目录介绍 </h2>

|目录名称|功能简介|
|:-:|:-:|
|[common](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/common)|公共组件，包含编译器配置、路径配置、基本数据类型定义以及一些使用工具|
|[framework](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/framework)|包含了框架的api以及相关实现|
|[core](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/core)|提供了全部api的接口|
|[demo](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/demo)|用于演示最新的api|
|[doc](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/doc)|包含了编程规范、框架结构、文件模版等|
|[hal](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/hal)|硬件驱动|
|[proj](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/proj)|工程目录|
|[stack](https://coding.net/u/yearnext/p/ysf/git/tree/ysf-stm32f1xx-alpha/stack)|协议栈|

<h2 id="3"> 相关文档 </h2>
1. [框架Logo](https://coding.net/u/yearnext/p/ysf/git/blob/ysf-stm32f1xx-alpha/doc/logo/logo_ver0.0.1.png) 
2. [框架编程规范](https://coding.net/u/yearnext/p/ysf/git/blob/ysf-stm32f1xx-alpha/doc/rules/code_rules.md) 
3. [版本命名规则](https://coding.net/u/yearnext/p/ysf/git/blob/ysf-stm32f1xx-alpha/doc/rules/version_rules.md)
4. [头文件模版](https://coding.net/u/yearnext/p/ysf/git/blob/ysf-stm32f1xx-alpha/doc/template/head_template.h)
5. [源文件模版](https://coding.net/u/yearnext/p/ysf/git/blob/ysf-stm32f1xx-alpha/doc/template/source_template.c)

<h2 id="4"> 例程 </h2>
本例程主要演示单片机GPIO的配置、ysf定时器的使用方式以及ysf事件结构的使用。
	
    /* Includes ------------------------------------------------------------------*/
    #include "fw_core.h"
    
    /* Private define ------------------------------------------------------------*/
	/**
	 *******************************************************************************
	 * @brief      define led port and mode
	 *******************************************************************************
	 */  
	#define LED_PORT MCU_PORT_D
	#define LED_PIN  MCU_PIN_13
	#define LED_MODE GPIO_DIR_OUTPUT

    /* Private typedef -----------------------------------------------------------*/
    /* Private variables ---------------------------------------------------------*/
	/**
	 *******************************************************************************
	 * @brief      define led device
	 *******************************************************************************
	 */  
	static Hal_Device_t Led;

	/**
	 *******************************************************************************
	 * @brief       timer variable define
	 *******************************************************************************
	 */ 
	static struct Fw_Task        LedTask;
	static struct Fw_Timer       LedTimer;
	
	static struct Fw_Timer       PutTimer;
    
    /* Exported variables --------------------------------------------------------*/
    /* Private functions ---------------------------------------------------------*/
    /* Exported functions --------------------------------------------------------*/
	/**
	 *******************************************************************************
	 * @brief       led1 blink function
	 *******************************************************************************
	 */
	void Led_Task_Handle(uint32_t event, void *param);
	
	void App_Led_Init(void)
	{
	    hPortFlag portConfig;
	    portConfig.Port = LED_PORT;
	    portConfig.Pin  = LED_PIN;
	    portConfig.Dir  = LED_DIR;
	        
	    Hal_Device_Open(&Led, HAL_DEVICE_GPIO, "led");
	    Hal_Device_Init(&Led, portConfig.Flag);
	    
	    Fw_Task_Init(&LedTask, "Led Task", 1, (void *)Led_Task_Handle, FW_MESSAGE_HANDLE_TYPE_TASK);
	    
	    Fw_Timer_Init(&LedTimer, "Led Timer");
	    Fw_Timer_SetTaskHandle(&LedTimer, &LedTask, LED_BLINK_EVENT, (void *)&Led);
	    Fw_Timer_Start(&LedTimer, 500, -1);
	}
	
	void Led_Task_Handle(uint32_t event, void *param)
	{
	    Hal_Device_t *drv = (Hal_Device_t *)param;
	    
	    switch(event)
	    {
	        case LED_ON_EVENT:
	            Hal_Device_Control(drv, HAL_GPIO_WRITE_CMD, 0x01, 1);
	            break;
	        case LED_OFF_EVENT:
	            Hal_Device_Control(drv, HAL_GPIO_WRITE_CMD, 0x00, 1);
	            break;
	        case LED_BLINK_EVENT:
	            Hal_Device_Control(drv, HAL_GPIO_TOGGLE_CMD);
	            break;
	        default:
	            break;
	    }
	}

	/**
	 *******************************************************************************
	 * @brief       led1 blink function
	 *******************************************************************************
	 */
	void App_Put_Callback(void *param);
	void App_Put_Init(void)
	{
	    Fw_Timer_Init(&PutTimer, "Put User Message Timer");
	    Fw_Timer_SetCallback(&PutTimer, App_Put_Callback, NULL);
	    Fw_Timer_Start(&PutTimer, 1000, -1);
	}
	
	void App_Put_Callback(void *param)
	{
	    log("Hello World!\r\n");
	}

	/**
	 *******************************************************************************
	 * @brief       user init function
	 *******************************************************************************
	 */
	void App_User_Init(void)
	{
	    App_Led_Init();
	    App_Put_Init();
	}