# ysf——yearnext software framework
## 介绍
### 框架简介
ysf是一个基于事件机制的单片机编程框架。

### 目录介绍
|目录名称|功能简介|
|:-:|:-:|
|common|公共组件，包含编译器配置、路径配置、基本数据类型定义以及一些使用工具|
|Framework|包含了框架的api以及相关实现|
|core|提供了全部api的接口|
|demo|用于演示最新的api|
|doc|包含了编程规范、框架结构、文件模版等|
|hal|硬件驱动|
|proj|工程目录|
|stack|协议栈|

## 例程
本例程主要演示单片机GPIO的配置、ysf定时器的使用方式以及ysf事件结构的使用。
	
    /* Includes ------------------------------------------------------------------*/
    #include "fw_interface.h"
    
    /* Private define ------------------------------------------------------------*/
    /* Private typedef -----------------------------------------------------------*/
    /* Private variables ---------------------------------------------------------*/
    /**
     *******************************************************************************
     * @brief   device port define
     *******************************************************************************
     */  
	static struct Hal_GPIO_Block Led1 = 
	{
	    .Port = MCU_PORT_D,
	    .Pin  = MCU_PIN_13,
	    .Mode = GPIO_MODE_PARAM(GPIO_LOW_SPEED_OUTPUT, GPIO_OUT_PUSH_PULL_MODE),
	};
	
	static struct Hal_GPIO_Block Led2 = 
	{
	    .Port = MCU_PORT_G,
	    .Pin  = MCU_PIN_14,
	    .Mode = GPIO_MODE_PARAM(GPIO_LOW_SPEED_OUTPUT, GPIO_OUT_PUSH_PULL_MODE),
	};
	
	static struct Hal_GPIO_Block Key1 = 
	{
	    .Port = MCU_PORT_E,
	    .Pin  = MCU_PIN_0,
	    .Mode = GPIO_MODE_PARAM(GPIO_INPUT, GPIO_IN_PULL_UP_MODE),
	};
	
	static struct Hal_GPIO_Block Key2 = 
	{
	    .Port = MCU_PORT_C,
	    .Pin  = MCU_PIN_13,
	    .Mode = GPIO_MODE_PARAM(GPIO_INPUT, GPIO_IN_PULL_UP_MODE),
	};
    
    /**
     *******************************************************************************
     * @brief   timer variable define
     *******************************************************************************
     */ 
	static struct TimerBlock   led1Timer;
	static struct ProtoThreads Led2Threads;
    
    /**
     *******************************************************************************
     * @brief   signal variable define
     *******************************************************************************
     */
    static struct SignalBlock KeySignal1;
    static struct SignalBlock KeySignal2;
    
    /* Exported variables --------------------------------------------------------*/
    /* Private functions ---------------------------------------------------------*/
    /* Exported functions --------------------------------------------------------*/
    /**
     *******************************************************************************
     * @brief   led1 blink function
     *******************************************************************************
     */
    static fw_err_t led1_blink_handler( void *param )
    {   
		Hal.GPIO.Output.Toggle(Led1.Port, Led1.Mode);

	    return FW_ERR_NONE;
    }
    
    /**
     *******************************************************************************
     * @brief   led2 blink function
     *******************************************************************************
     */
	static _PT_THREAD(bsp_led2_blink)
	{
		fw_pt_begin();
		
		while(1)
		{
			Hal.GPIO.Output.Toggle(Led2.Port, Led2.Pin);
			
			fw_pt_delay(250); 
		}
		
		fw_pt_end();
	}
    
    /**
     *******************************************************************************
     * @brief   led application function
     *******************************************************************************
     */
    static void app_led1_init(void)
    {
	    Framework.Timer.Init.Simple(&led1Timer, led1_blink_handler);
	    Framework.Timer.Start(&led1Timer, CAL_SET_TIME(1000), TIMER_CYCLE_MODE);
    }
    
	static void app_led1_deinit(void)
	{
		Framework.Timer.Stop(&led1Timer);
		Hal.GPIO.Output.Clr(Led1.Port, Led1.Pin);
	}
    
    static void app_led2_init(void)
    {
		fw_pt_init(&Led2Threads, bsp_led2_blink);
		fw_pt_arm(NULL, &Led2Threads);
    }
    
    static void app_led2_deinit(void)
    {
    	fw_pt_disarm(&Led2Threads);
		Hal.GPIO.Output.Clr(Led2.Port, Led2.Pin);
    }
    
    /**
     *******************************************************************************
     * @brief   key1 scan function
     *******************************************************************************
     */
    static bool key1_scan(void)
    {
	    bool status = false;
	    
	    Hal.GPIO.Input.Get(Key1.Port, Key1.Pin, &status);
	    
	    return status;
    }
    
    /**
     *******************************************************************************
     * @brief   key2 scan function
     *******************************************************************************
     */
    static bool key2_scan(void)
    {
	    bool status = false;
	    
	    Hal.GPIO.Input.Get(Key2.Port, Key2.Pin, &status);
	    
	    return status;
    }
    
    /**
     *******************************************************************************
     * @brief   key1 handler function
     *******************************************************************************
     */
		static fw_err_t key1_handler(uint16_t status)
		{
			switch(status)
			{
				case SIGNAL_STATUS_PRESS_EDGE:
					app_led1_deinit();
					app_led2_deinit();
					break;
				case SIGNAL_STATUS_PRESS:
					Hal.GPIO.Output.Clr(Led1.Port, Led1.Pin);
					Hal.GPIO.Output.Clr(Led2.Port, Led2.Pin);
					break;
				case SIGNAL_STATUS_RELEASE_EDGE:
					app_led1_init();
					app_led2_init();
					break;
				default:
					break;
			}
			
			return FW_ERR_NONE;
		}
    
    /**
     *******************************************************************************
     * @brief   key2 handler function
     *******************************************************************************
     */
	static fw_err_t key2_handler(uint16_t status)
	{
		switch(status)
		{
			case SIGNAL_STATUS_PRESS_EDGE:
				app_led1_deinit();
				app_led2_deinit();
				break;
			case SIGNAL_STATUS_PRESS:
				Hal.GPIO.Output.Set(Led1.Port, Led1.Pin);
				Hal.GPIO.Output.Set(Led2.Port, Led2.Pin);
				break;
			case SIGNAL_STATUS_RELEASE_EDGE:
				app_led1_init();
				app_led2_init();
				break;
			default:
				break;
		}
		
		return FW_ERR_NONE;
	}
    
    /**
     *******************************************************************************
     * @brief   device led init function
     *******************************************************************************
     */
    static void bsp_led_init( void )
    {
	    Hal.GPIO.Open(Led1.Port);
	    Hal.GPIO.Init(Led1.Port, Led1.Pin, Led1.Mode);
	
	    Hal.GPIO.Open(Led2.Port);
	    Hal.GPIO.Init(Led2.Port, Led2.Pin, Led2.Mode);
    }
    
    /**
     *******************************************************************************
     * @brief   device key init function
     *******************************************************************************
     */
    static void bsp_key_init(void)
    {
	    Hal.GPIO.Open(Key1.Port);
	    Hal.GPIO.Init(Key1.Port, Key1.Pin, Key1.Mode);
	    Framework.Signal.Start(&KeySignal1, key1_scan, key1_handler);
	    
	    Hal.GPIO.Open(Key2.Port);
	    Hal.GPIO.Init(Key2.Port, Key2.Pin, Key2.Mode);
	    Framework.Signal.Start(&KeySignal2, key2_scan, key2_handler);
    }
    
    /**
     *******************************************************************************
     * @brief   user init function
     *******************************************************************************
     */
    static fw_err_t user_init( void )
    {
	    bsp_led_init();
	    bsp_key_init();
	    
	    app_led1_init();
	    app_led2_init();
	    
	    return FW_ERR_NONE;
    }
    
    /**
     *******************************************************************************
     * @brief   main function
     *******************************************************************************
     */
    int main( void )
    {   
	    fw_core_init();
	    
	    user_init();
	    
	    fw_core_start();
	    
	    return 0;
    }
