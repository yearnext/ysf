/**
 ******************************************************************************
 * @file       ysf_type.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��1��10��
 * @brief      ysf ��������ͷ�ļ�
 * @par        ����ƽ̨
 *                 Windows
 * @par        ����ƽ̨
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup ysf������������
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TYPE_H__
#define __YSF_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPILER_PATH

/* Exported types ------------------------------------------------------------*/
typedef enum
{
   ysf_disable  = 0,
   ysf_enable = !ysf_disable,
}ysf_status_t;

/**@} */

/**
 * @name ysf �������Ͷ���
 * @{
 */
enum
{
    YSF_ERR_NONE,              /** �޴���     */
    YSF_ERR_FAIL,              /** ʧ�ܴ���   */
    
    YSF_ERR_NOT_READY,         /** δ�������� */
    YSF_ERR_NOT_SUPPORT,       /** ��֧�ִ��� */
    
    YSF_ERR_INVAILD_PTR,       /** ��Чָ����� */
    YSF_ERR_INVAILD_PARAM,     /** ��Ч�������� */

    YSF_ERR_IO,                /** IO����     */
    
    YSF_ERR_BUG,               /** BUG����    */
    YSF_ERR_UNKNOW,            /** δ֪����   */  
};

typedef int16_t ysf_err_t;
/**@} */

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
