/**
 ******************************************************************************
 * @file       ysf_memory.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê2ÔÂ20ÈÕ
 * @brief      ysf_memory source file
 * @par        work paltform                                  
 *                 Windows
 * @par        compiler paltform									                         
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf_memory component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_COMPONENT_BUFFER_PATH
#include YSF_TYPE_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if USE_YSF_MEMORY_API
static uint8_t ysfMemory[USE_YSF_MEMORY_SIZE];
static struct ysf_mem_cb_t ysfMemoryCB;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_MEMORY_API
void ysf_memory_init( void )
{
    ysf_memInit(&ysfMemoryCB, ysfMemory, sizeof(ysfMemory));
}

void *ysf_memory_malloc( ysf_mem_size_t size )
{
    return ysf_memMalloc(&ysfMemoryCB, size);
}

void ysf_memory_free( void *mem )
{
    ysf_memFree(&ysfMemoryCB, mem);
}

ysf_mem_size_t ysf_memory_get_len(void)
{
    return ysf_memGetLen(&ysfMemoryCB);
}

ysf_mem_size_t ysf_memory_get_alignment(void)
{
    return ysf_memGetAlignment(&ysfMemoryCB);
}

ysf_mem_size_t ysf_memory_cal_use_rate(void)
{
    return ysf_memUseRateCal(&ysfMemoryCB);
}

bool ysf_memory_is_in(void *mem)
{
    return ysf_memIsIn(&ysfMemoryCB, mem);
}

#endif

/** @}*/     /* ysf_memory component  */

/**********************************END OF FILE*********************************/
