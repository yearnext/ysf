/**
 ******************************************************************************
 * @file       ysf_commtools.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��1��10��
 * @brief      ysf ͨ�ù�������ͷ�ļ�
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
 * @defgroup ysf ͨ�ù�������
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_COMMON_TOOLS_H__
#define __YSF_COMMON_TOOLS_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
 * @name ynf Ӧ�ù���
 * @{
 */
/** ������ת���ַ����� */
#define Name2String(name)    (#name)

/** ����������ռ�ڴ���ֽڴ�С */
#define YSF_CalTypeByteSize(type) (sizeof(type) / sizeof(unsigned char))

/** ����������ռ�ڴ��λ����С */
#define YSF_CalTypeBitSize(type)  (YSF_CalTypeByteSize(type) * 8)

/** �������� */
#define YSF_CalRemainder(dividend,divisor) ((dividend)%(divisor))

/** �����Ƿ�������� */
#define YSF_CheckRemainder(dividend,divisor) ((((dividend)%(divisor)) != 0 ) \
                                             ? (1) : (0))
                                             
/**@} */
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ͨ�ù�������  */

/**********************************END OF FILE*********************************/
