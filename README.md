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
	#include "ysf.h"
	
	/* Private define ------------------------------------------------------------*/                                                        
	/* Private typedef -----------------------------------------------------------*/
	/* Private variables ---------------------------------------------------------*/
	/**
	 *******************************************************************************
	 * @brief       device port define
	 *******************************************************************************
	 */  
	//static struct map_gpio_t led1 = 
	//{
	//    .port = MCU_PORT_D,
	//    .pin  = MCU_PIN_13,
	//};
	
	static struct map_gpio_t led2 = 
	{
	    .port = MCU_PORT_G,
	    .pin  = MCU_PIN_14,
	};
	
	//static struct map_gpio_t key1 = 
	//{
	//    .port = MCU_PORT_E,
	//    .pin  = MCU_PIN_0,
	//};
	
	static struct map_gpio_t key2 = 
	{
	    .port = MCU_PORT_C,
	    .pin  = MCU_PIN_13,
	};
	
	/**
	 *******************************************************************************
	 * @brief       timer variable define
	 *******************************************************************************
	 */ 
	static struct ysf_timer_t *led1Timer;
	//static struct ysf_task_t  led2Task;
	static struct ysf_pt_t    led2PT;
	
	/**
	 *******************************************************************************
	 * @brief       signal variable define
	 *******************************************************************************
	 */
	static struct ysf_signal_t key1Signal;
	static struct ysf_signal_t key2Signal;
	
	/* Exported variables --------------------------------------------------------*/
	/* Private functions ---------------------------------------------------------*/
	/* Exported functions --------------------------------------------------------*/
	
	/**
	 *******************************************************************************
	 * @brief       led1 blink function
	 *******************************************************************************
	 */
	static ysf_err_t led1_blink_handler( void *param )
	{   
	    if( msp.gpio.output.get(MCU_PORT_D, MCU_PIN_13) == true )
	    {
	        msp.gpio.output.clr(MCU_PORT_D, MCU_PIN_13);
	    }
	    else
	    {
	        msp.gpio.output.set(MCU_PORT_D, MCU_PIN_13);
	    }
	    
	    return YSF_ERR_NONE;
	}
	
	/**
	 *******************************************************************************
	 * @brief       led2 blink function
	 *******************************************************************************
	 */
	static YSF_PT_THREAD(bsp_led2_blink)
	{
	    ysf_pt_begin();
	    
	    while(1)
	    {
	        msp.gpio.output.set(led2.port, led2.pin);
	        
	        ysf_pt_delay(250);            
	
	        msp.gpio.output.clr(led2.port, led2.pin);
	        
	        ysf_pt_delay(250); 
	    }
	    
	    ysf_pt_end();
	}
	
	/**
	 *******************************************************************************
	 * @brief       device led init function
	 *******************************************************************************
	 */
	static void bsp_led_init( void )
	{
	    msp.gpio.enable(MCU_PORT_D);
	    msp.gpio.output.init(MCU_PORT_D, MCU_PIN_13, GPIO_PIN_O_PP_LS_MODE);    
	
	    map.gpio.enable(&led2);
	    map.gpio.output.init(&led2, GPIO_PIN_O_PP_LS_MODE);  
	}
	
	static void app_led1_init(void)
	{
	    led1Timer = ysf.timer.simple.cb_init(led1_blink_handler, NULL);
	    ysf.timer.arm(led1Timer, YSF_TIME_2_TICK(1000), YSF_TIMER_CYCLE_MODE);
	}
	
	static void app_led1_deinit(void)
	{
	    ysf.timer.disarm(led1Timer);
	}
	
	static void app_led2_init(void)
	{
	    ysf.pt.init(&led2PT, bsp_led2_blink);
	    ysf.pt.simple.arm(&led2PT);
	}
	
	static void app_led2_deinit(void)
	{
	    ysf.pt.disarm(&led2PT);
	}
	
	/**
	 *******************************************************************************
	 * @brief       key1 scan function
	 *******************************************************************************
	 */
	static enum ysf_signal_status_t key1_scan( void )
	{
	    return ( msp.gpio.input.get(MCU_PORT_E, MCU_PIN_0) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
	}
	
	/**
	 *******************************************************************************
	 * @brief       key2 scan function
	 *******************************************************************************
	 */
	static enum ysf_signal_status_t key2_scan( void )
	{
	    return ( map.gpio.input.get(&key2) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
	}
	
	/**
	 *******************************************************************************
	 * @brief       key1 handler function
	 *******************************************************************************
	 */
	static ysf_err_t key1_handler(uint16_t status)
	{
	    switch(status)
	    {
	        case SIGNAL_STATUS_PRESS_EDGE:
	            app_led1_deinit();
	            app_led2_deinit();
	            break;
	        case SIGNAL_STATUS_PRESS:
	            msp.gpio.output.clr(MCU_PORT_D, MCU_PIN_13);
	            map.gpio.output.clr(&led2);
	            break;
	        case SIGNAL_STATUS_RELEASE_EDGE:
	            app_led1_init();
	            app_led2_init();
	            break;
	        default:
	            break;
	    }
	    
	    return YSF_ERR_NONE;
	}
	
	/**
	 *******************************************************************************
	 * @brief       key2 handler function
	 *******************************************************************************
	 */
	static ysf_err_t key2_handler(uint16_t status)
	{
	    switch(status)
	    {
	        case SIGNAL_STATUS_PRESS_EDGE:
	            app_led1_deinit();
	            app_led2_deinit();
	            break;
	        case SIGNAL_STATUS_PRESS:
	            msp.gpio.output.set(MCU_PORT_D, MCU_PIN_13);
	            map.gpio.output.set(&led2);
	            break;
	        case SIGNAL_STATUS_RELEASE_EDGE:
	            app_led1_init();
	            app_led2_init();
	            break;
	        default:
	            break;
	    }
	    
	    return YSF_ERR_NONE;
	}
	
	/**
	 *******************************************************************************
	 * @brief       device key init function
	 *******************************************************************************
	 */
	static void bsp_key_init(void)
	{
	    msp.gpio.enable(MCU_PORT_E);
	    msp.gpio.input.init(MCU_PORT_E, MCU_PIN_0, GPIO_PIN_I_UD_MODE);
	    ysf.signal.arm(&key1Signal, key1_scan, key1_handler);
	    
	    map.gpio.enable(&key2);
	    map.gpio.input.init(&key2, GPIO_PIN_I_UD_MODE);
	    ysf.signal.arm(&key2Signal, key2_scan, key2_handler);
	}
	
	/**
	 *******************************************************************************
	 * @brief       user init function
	 *******************************************************************************
	 */
	static ysf_err_t user_init( void )
	{
	    bsp_led_init();
	    app_led1_init();
	    app_led2_init();
	    
	    bsp_key_init();
	
	    return YSF_ERR_NONE;
	}
	
	/**
	 *******************************************************************************
	 * @brief       main function
	 *******************************************************************************
	 */
	int main( void )
	{   
	    ysf.init(user_init);
	    ysf.start();
	}