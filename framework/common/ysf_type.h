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
//#include <stdbool.h>
//#include <stdlib.h>
//#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/**
 * @name ysf �����������Ͷ���
 * @{
 */
typedef unsigned char               ysf_uint8_t;
typedef unsigned short              ysf_uint16_t;
typedef unsigned int                ysf_uint32_t;
typedef unsigned long long          ysf_uint64_t;

typedef char                        ysf_int8_t;
typedef short                       ysf_int16_t;
typedef int                         ysf_int32_t;
typedef long long                   ysf_int64_t;

typedef ysf_uint8_t                 ysf_u8_t;
typedef ysf_uint16_t                ysf_u16_t;
typedef ysf_uint32_t                ysf_u32_t;

typedef volatile ysf_uint8_t        ysf_vu8_t;
typedef volatile ysf_uint16_t       ysf_vu16_t;
typedef volatile ysf_uint32_t       ysf_vu32_t;

typedef const ysf_uint8_t           ysf_cu8_t;
typedef const ysf_uint16_t          ysf_cu16_t;
typedef const ysf_uint32_t          ysf_cu32_t;

typedef volatile const ysf_uint8_t  ysf_vcu8_t;
typedef volatile const ysf_uint16_t ysf_vcu16_t;
typedef volatile const ysf_uint32_t ysf_vcu32_t;

typedef ysf_int8_t                  ysf_s8_t;
typedef ysf_int16_t                 ysf_s16_t;
typedef ysf_int32_t                 ysf_s32_t;

typedef volatile ysf_int8_t         ysf_vs8_t;
typedef volatile ysf_int16_t        ysf_vs16_t;
typedef volatile ysf_int32_t        ysf_vs32_t;

typedef const ysf_int8_t            ysf_cs8_t;
typedef const ysf_int16_t           ysf_cs16_t;
typedef const ysf_int32_t           ysf_cs32_t;

typedef volatile const ysf_int8_t   ysf_vcs8_t;
typedef volatile const ysf_int16_t  ysf_vcs16_t;
typedef volatile const ysf_int32_t  ysf_vcs32_t;

/**@} */

/**
 * @name ysf �������Ͷ���
 * @{
 */
#define YSF_FALSE 0
#define YSF_TRUE  1

typedef enum _YSF_BOOL_TYPE_
{
   ysf_false = 0,
   ysf_true = 1,
}ysf_bool_t;

/**@} */

/**
 * @name ysf �������Ͷ���
 * @{
 */
typedef enum _YSF_ERR_TYPE_
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
}ysf_err_t;
/**@} */

/**
 * @name ysf ��ָ�붨��
 * @{
 */
#define YSF_NULL ((void *)0)

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
