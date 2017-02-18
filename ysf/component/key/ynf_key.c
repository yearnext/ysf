/**
  ******************************************************************************
  * @file       ysf_key.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017��1��15��
  * @brief      ynf_key Դ�ļ�
  * @par        ����ƽ̨                                  
  *                 Windows
  * @par        ����ƽ̨									                         
  * 				GCC
  ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
  ******************************************************************************
  */

/**
 * @defgroup ynf_key����
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ynf_key.h"
#include "ynf.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       �����ؼ���ʼ������
 * @param       [in/out]  ynfKey_t*         �����ؼ�
 * @param       [in/out]  ynfKeyConfig_t*   �������ò���
 * @return      [in/out]  YNF_SUCCESS       ��ʼ���ɹ�
 * @return      [in/out]  YNF_FAILED        ��ʼ��ʧ��
 * @note        None
 *******************************************************************************
 */
ynfStatus_t YNF_keyInit( ynfKey_t *key, ynfKeyConfig_t *config )
{
#if USE_YNF_KEY_DEBUG
    if (key == NULL)
    {
        YNF_FuncParamErrorLog(key);
        return YNF_FAILED;
    }

    if (config == NULL)
    {
        YNF_FuncParamErrorLog(config);
        return YNF_FAILED;
    }

    if( config->func.detect == NULL )
    {
        YNF_FuncParamErrorLog(config->func.detect);
        return YNF_FAILED;
    }

    if( config->func.handler == NULL )
    {
        YNF_FuncParamErrorLog(config->func.handler);
        return YNF_FAILED;
    }

    if( config->func.handler == NULL )
    {
        YNF_FuncParamErrorLog(config->func.handler);
        return YNF_FAILED;
    }

#endif

    key->func.detect = config->func.detect;
    key->func.handler = config->func.handler;

    key->set.flag = config->flag;
    key->set.time.longPress = config->time.longPress;
    key->set.time.multiPress = config->time.multiPress;

    key->status.key = KEY_STATUS_RELEASE;
    key->status.scan = KEY_SCAN_DETECT;
    return YNF_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       ���ð����ؼ�����
 * @param       [in/out]  ynfKey_t*         �����ؼ�
 * @param       [in/out]  ynfKeyConfig_t*   �������ò���
 * @return      [in/out]  YNF_SUCCESS       ��ʼ���ɹ�
 * @return      [in/out]  YNF_FAILED        ��ʼ��ʧ��
 * @note        None
 *******************************************************************************
 */
ynfStatus_t YNF_keyDeInit( ynfKey_t *key )
{
#if USE_YNF_KEY_DEBUG
    if (key == NULL)
    {
        YNF_FuncParamErrorLog(key);
        return YNF_FAILED;
    }

    if( key->set.flag == KEY_CONFIG_DISABLE_PRESS )
    {
        YNF_FuncParamErrorLog(key->set.flag.enable);
        return YNF_FAILED;
    }
#endif

    memset(key, 0, sizeof(ynfKey_t));

    return YNF_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       ����ɨ�躯��
 * @param       [in/out]  ynfKey_t*         �����ؼ�
 * @return      [in/out]  YNF_SUCCESS       ɨ��ɹ�
 * @return      [in/out]  YNF_FAILED        ɨ��ʧ��
 * @note        None
 *******************************************************************************
 */
ynfStatus_t YNF_keyDetect( ynfKey_t *key )
{
#if USE_YNF_KEY_DEBUG
    if (key == NULL)
    {
        YNF_FuncParamErrorLog(key);
        return YNF_FAILED;
    }

    if( key->set.flag == KEY_CONFIG_DISABLE_PRESS )
    {
        YNF_FuncParamErrorLog(key->set.flag.enable);
        return YNF_FAILED;
    }
#endif
    bool keyStatus = key->func.detect();

    switch(key->status.scan)
    {
        case KEY_SCAN_DETECT:
            if( keyStatus == true )
            {
                key->status.scan = KEY_SCAN_DOWN_FILTER;
            }
            else
            {
                key->status.scan = KEY_SCAN_UP_FILTER;
            }
            break;
        case KEY_SCAN_UP_FILTER:
            if( keyStatus == false )
            {
                key->status.scan = KEY_SCAN_UP_HANDLE;
            }
            else
            {
                key->status.scan = KEY_SCAN_DETECT;
            }
            break;
        case KEY_SCAN_UP_HANDLE:
            if( keyStatus == false )
            {
                /** send message! */
            }
            else
            {
                key->status.scan = KEY_SCAN_DETECT;
            }
            break;
        case KEY_SCAN_DOWN_FILTER:
            if( keyStatus == true )
            {
                key->status.scan = KEY_SCAN_DOWN_HANDLE;
            }
            else
            {
                key->status.scan = KEY_SCAN_DETECT;
            }
            break;
        case KEY_SCAN_DOWN_HANDLE:
            if( keyStatus == true )
            {
                /** send message! */
            }
            else
            {
                key->status.scan = KEY_SCAN_DETECT;
            }
            break;
        default:
            return YNF_FAILED;
            break;
    }

    return YNF_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       ����ɨ�躯��
 * @param       [in/out]  ynfKey_t*         �����ؼ�
 * @return      [in/out]  YNF_SUCCESS       ɨ��ɹ�
 * @return      [in/out]  YNF_FAILED        ɨ��ʧ��
 * @note        None
 *******************************************************************************
 */
ynfStatus_t YNF_keyJudge( ynfKey_t *key )
{
#if USE_YNF_KEY_DEBUG
    if (key == NULL)
    {
        YNF_FuncParamErrorLog(key);
        return YNF_FAILED;
    }

    if( key->set.flag == KEY_CONFIG_DISABLE_PRESS )
    {
        YNF_FuncParamErrorLog(key->set.flag.enable);
        return YNF_FAILED;
    }
#endif

    switch(key->status.key)
    {
        case KEY_STATUS_RELEASE:
            if( key->status.scan == KEY_SCAN_DOWN_HANDLE )
            {
                key->status.key = KEY_STATUS_PRESS_EDGE;
                /** send message! */
            }
            break;
        case KEY_STATUS_PRESS_EDGE:
            if( key->status.scan == KEY_SCAN_DOWN_HANDLE )
            {
                key->status.key = KEY_STATUS_PRESS;
                /** send message! */
            }
            else
            {
                key->status.key = KEY_STATUS_RELEASE_EDGE;
            }
            break;
        case KEY_STATUS_PRESS:
            if( key->status.scan == KEY_SCAN_DOWN_HANDLE )
            {
                if( key->set.flag == KEY_CONFIG_ENABLE_LONGPRESS )
                {
                    key->status.key = KEY_STATUS_LONG_PRESS;
                    /** start key long press timer! */
                    break;
                }

                if( key->set.flag == KEY_CONFIG_ENABLE_MULTIPRESS )
                {
                    key->status.key = KEY_STATUS_MULTI_PRESS;
                    /** start key long press timer! */
                    break;
                }
            }
            else
            {
                key->status.key = KEY_STATUS_RELEASE_EDGE;
            }
            break;
        case KEY_STATUS_LONG_PRESS:
            if( key->status.scan == KEY_SCAN_UP_HANDLE )
            {
                key->status.key = KEY_STATUS_RELEASE_EDGE;
                /** send message! */
            }
            break;
        case KEY_STATUS_MULTI_PRESS:
            if( key->status.scan == KEY_SCAN_UP_HANDLE )
            {
                key->status.key = KEY_STATUS_RELEASE_EDGE;
                /** send message! */
            }
            break;
        case KEY_STATUS_RELEASE_EDGE:
                key->status.key = KEY_STATUS_RELEASE;
            break;
        default:
            return YNF_FAILED;
            break;
    }

    return YNF_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       ����������
 * @param       [in/out]  ynfKey_t*         �����ؼ�
 * @return      [in/out]  YNF_SUCCESS       ����ɹ�
 * @return      [in/out]  YNF_FAILED        ����ʧ��
 * @note        None
 *******************************************************************************
 */
ynfStatus_t YNF_keyHandler( ynfKey_t *key )
{
#if USE_YNF_KEY_DEBUG
    if (key == NULL)
    {
        YNF_FuncParamErrorLog(key);
        return YNF_FAILED;
    }

    if( key->set.flag == KEY_CONFIG_ENABLE_LONGPRESS )
    {
        YNF_FuncParamErrorLog(key->set.flag.enable);
        return YNF_FAILED;
    }
#endif

    key->func.handler(key->status.key);

    return YNF_SUCCESS;
}

/** @}*/     /* ynf_key ����  */

/**********************************END OF FILE*********************************/
