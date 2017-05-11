# ysf——yearnext software framework
## 前言
学单片机好几年了，这几年我断断续续的开发了一些项目，虽然项目不大，但是在开发过程中总是免不了执行一些重复的操作，次数多了就想把代码中那些重复的内容抽象出来，封装成一个个模块，以便在未来的开发中加快开发速度，节省调试时间。

随着学习的深入，我开始发现就连程序的运行流程也是可以抽象的，但是原有的模块比较杂散，因此我需要在原有的程序结构中再往上添加一层应用层，并将其以下的模块全部封装起来，用户在开发的时候直接调用应用层的接口，不用再去接触底层的一些接口配置了。

## 我的代码简史
在初学单片机的时候因为一些原因写出来的都是阻塞式运行的程序，就拿多段数码管的动态显示来说，当数码管显示完一段之后开始进行软件延时，延时结束后接着显示另一段数码管，如果此时有别的事件发生，只能等待显示程序执行结束之后再去进行事件的处理，我当时觉得写这样的程序有些不妥，但是又没有什么好的解决方法，再加上单片机运行结果又没有什么不对的地方，于是在很长的一段时间里我写的都是这样的程序在加上所接触到的代码也是这种类型的，这让我坚信单片机程序就是这么写的。
直到在一次偶然间我接触到了多任务思想。

## 介绍
### YSF目录介绍
|目录名称|功能简介|
|:-:|:-:|
|common|YSF通用工具|
|compiler|YSF编译器配置|
|component|YSF通用组件|
|hal|YSF底层硬件驱动|


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
