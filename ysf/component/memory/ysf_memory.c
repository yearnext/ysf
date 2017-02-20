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
#include "../ysf/component/memory/ysf_memory.h"
#include "../ysf/component/buffer/ysf_buffer.h"
#include "../ysf/common/ysf_type.h"
#include "../ysf/compiler/ysf_compiler.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static ysf_u8_t ysfMemory[USE_YSF_MEMORY_SIZE];
static ysf_mem_cb_t ysfMemoryCB;

/* Exported variables --------------------------------------------------------*/
const struct _YSF_MEMORY_API_ ysf_memory =
{
    .init   = ysf_memory_init,
    .malloc = ysf_malloc,
    .free   = ysf_free,
};

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void ysf_memory_init( void )
{
    ysf_memInit(&ysfMemoryCB, ysfMemory, sizeof(ysfMemory));
}

void *ysf_malloc( ysf_memSize_t size )
{
    return ysf_memMalloc(&ysfMemoryCB, size);
}

void ysf_free( void *mem )
{
    ysf_memFree(&ysfMemoryCB, mem);
}

/** @}*/     /* ysf_memory component  */

/**********************************END OF FILE*********************************/
