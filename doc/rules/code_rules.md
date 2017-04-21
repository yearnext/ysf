# 编程规范

## 1.命名规范
编程的命名方式主要有Pascal（每个单词的首字母大写）和Camel两种（首个单词的首字母小写，其余单词的首字母大写）。

### 1.1 局部变量
局部变量命名时，使用**Camel**命名规则。

示例：
    
    uint32_t tempData = 0;

### 1.2 函数参数
函数参数命名时，使用**Camel**命名规则。

示例：
    
    void AtOpera(uint8_t atCmd);

### 1.3 结构体成员
结构体成员命名时，使用**Pascal**命名规则。

示例：
    
    struct _demo
	{
		uint8_t DemoVariable;
	};

### 1.4 枚举
结构体成员命名时，使用**Pascal**命名规则。

示例：
    
    enum
	{
		SYSTEM_START_EVENT,
		SYSTEM_END_EVENT,
	};

### 1.5 常量命名
结构体成员命名时，全部使用大写字母表示,每个单词之间使用下划线分隔。

示例：
    
    #define INCLUDE_PATH            "../include/include.h"

### 1.6 类型命名
使用typedef定义新的类型时，需要在类型后面加上_t后缀。

示例：
    
    typedef unsigned char uint8_t;

## 2.代码规范
### 2.1 变量注释规范
	
	/** core tick variable */
	volatile uint32_t coreTick = CORE_TICK_MIN;

### 2.2 枚举注释规范

	/**
	 *******************************************************************************
	 * @brief        demo
	 *******************************************************************************
	 */
	enum
	{
		/** event max enum */
		EVENT_MIN,

		/** event max enum */
		EVENT_MAX,
	};

### 2.3 结构体、联合注释规范

	/**
	 *******************************************************************************
	 * @brief        demo
	 *******************************************************************************
	 */
	struct _TempStruct
	{
		/** max number */
		uint8_t NumberMax,

		/** min number */
		uint8_t NumberMin,
	};

	/**
	 *******************************************************************************
	 * @brief        demo
	 *******************************************************************************
	 */
	union _TempUnion
	{
		/** max number */
		uint8_t NumberMax;

		/** min number */
		uint8_t NumberMin,
	};

### 2.4 模块、模组注释规范
	/**
	 *******************************************************************************
	 * @brief        define param about tick
	 *******************************************************************************
	 */
	#define CORE_TICK_MAX (10000000UL)
	#define CORE_TICK_MIN (0UL)

	volatile uint32_t coreTick = CORE_TICK_MIN;

### 2.5 函数注释规范

    /**
     *******************************************************************************
     * @brief     push data to fifo
     * @param     [in/out]  pushData        push data
     * @return    [in/out]  ERR_NONE        no error
     * @note      None
     *******************************************************************************
     */
    err_t PushInFifo(uint8_t pushData)
    {
	    return ERR_NONE;
    }