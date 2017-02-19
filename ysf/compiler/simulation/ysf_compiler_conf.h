/**
 ******************************************************************************
 * @file       ysf_simulation_compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��1��10��
 * @brief      ���������� ͷ�ļ�
 * @par        ����ƽ̨
 *                 Windows
 * @par        ����ƽ̨
 *                 NONE
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup ynf����
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_SIMULATION_COMPILER_H__
#define __YSF_SIMULATION_COMPILER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 * @name ���������
 * @{
 */
#define __FUNCNAME__           
#define __YSF_FUNCNAME__       

#define PRAGMA(pragma)         

#if !defined(__CORTEX_M)
#define __ASM                   
#define __INLINE                
#define __STATIC_INLINE         static
#endif

#define YSF_ASM                 
#define YSF_INLINE              
#define YSF_STATIC_INLINE       static

#define YSF_SECTION(x)         
#define YSF_UNUSED
#define YSF_USED
#define YSF_WEAK                
#define YSF_IMPORT_API         
#define YSF_EXPORT_API          

/**
 * @name �����������С��ģʽ���
 * @{
 */
#if 0
    #define COMPILER_USE_BIG_ENDIAN
//    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
//    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name ����������ֽڶ�������
 * @{
 */
#define PACKED_HEAD(n)          
#define PACKED_TAIL(n)
#define PACKED(type)            type;
#define ALIGNMENT(n,type)       type;

#define YSF_PACKED_HEAD(n)      
#define YSF_PACKED_TAIL(n)
#define YSF_PACKED(type)        type;
#define YSF_ALIGNMENT(n,type)   type;
/**@} */

/**
 * @name ����������������Ͷ���
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

#if 0
typedef ysf_uint32_t                ysf_addr_t;
#else
typedef ysf_uint64_t                ysf_addr_t;
#endif
/**@} */

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
