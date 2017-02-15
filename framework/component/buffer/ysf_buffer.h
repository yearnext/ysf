/**
 ******************************************************************************
  * @file       ysf_buffer.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-01-06
  * @brief      ysf_buffer head file
  * @par        work platform
  *                 Windows
  * @par        compiler
  *                 GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ynf_ringbuff config file
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_BUFFER_H__
#define __YSF_BUFFER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_type.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf buffer debug switch
 *******************************************************************************
 */
#define USE_YSF_BUFFER_DEBUG    (1)

#define USE_YSF_RING_BUFFER_PTR (0)

/* Exported types ------------------------------------------------------------*/
/**
 * @name ring buffer type
 * @{
 */
typedef ysf_u8_t ysf_buffer_size_t;
typedef ysf_u8_t ysf_buffer_point_t;

typedef struct _YSF_BUFFER_TYPE_
{
    ysf_u8_t          *buffer;
    ysf_buffer_size_t size;
}ysf_buffer_t;

#if USE_YSF_RING_BUFFER_PTR
typedef struct _YSF_RING_BUFF_TYPE_
{
    ysf_buffer_t       buffer;
    ysf_u8_t           *head;
    ysf_u8_t           *tail;
    ysf_buffer_size_t  size;
}ysf_rb_t;

#else
typedef struct _YSF_RING_BUFF_TYPE_
{
    ysf_buffer_t       buffer;
    ysf_buffer_point_t head;
    ysf_buffer_point_t tail;
}ysf_rb_t;
#endif

typedef ysf_rb_t ysf_queue_t;
typedef ysf_rb_t ysf_fifo_t;

/**@} */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern ysf_err_t ysf_rbInit( ysf_rb_t*, ysf_u8_t*, ysf_buffer_size_t);
extern ysf_err_t ysf_rbWrite(ysf_rb_t*, ysf_u8_t*, ysf_buffer_size_t);
extern ysf_err_t ysf_rbRead(ysf_rb_t*,  ysf_u8_t*, ysf_buffer_size_t);

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf_buffer 閰嶇疆  */

/**********************************END OF FILE*********************************/
