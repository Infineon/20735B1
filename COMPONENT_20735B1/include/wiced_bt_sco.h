/*
 * Copyright 2016-2021, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 *
 * Bluetooth Synchronous Connection Oriented Channel Application Programming Interface
 *
 */
#pragma once

#include "wiced.h"
/**
 *  @addtogroup  sco_api_functions       Synchronous Connection Oriented (SCO) Channel
 *  @ingroup     wicedbt_av
 *
 *  SCO Definitions and Functions
 *
 *  SCO logical transport, is a symmetric, point-to-point transport between
 *  the master and a specific slave. The SCO logical transport reserves slots
 *  and can therefore be considered as a circuit-switched connection between
 *  the master and the slave. The master may support up to three SCO links to
 *  the same slave or to different slaves. A slave may support up to three SCO
 *  links from the same master, or two SCO links if the links originate from
 *  different masters. SCO packets are never retransmitted.
 *
 *  @{
 */

/******************************************************
 *              Constants
 ******************************************************/

enum wiced_bt_sco_route_path_e{
    WICED_BT_SCO_OVER_UART = 0, /* PCM routing config for routing to UART */
    WICED_BT_SCO_OVER_PCM,      /* PCM routing config for routing to PCM */
    WICED_BT_SCO_OVER_I2S       /* PCM routing config for routing to I2S */
};
typedef uint8_t wiced_bt_sco_route_path_t;

enum wiced_bt_pcm_data_order_e{
    WICED_BT_PCM_MSB_FIRST = 0, /* PCM data format config for MSB first out */
    WICED_BT_PCM_LSB_FIRST,     /* PCM data format config for LSB first out */
};
typedef uint8_t wiced_bt_pcm_data_order_t;

enum wiced_bt_i2spcm_role_e{
    WICED_BT_I2SPCM_SLAVE = 0, /* PCM/I2S role type(slave) */
    WICED_BT_I2SPCM_MASTER,    /* PCM/I2S role type(master) */
};
typedef uint8_t wiced_bt_i2spcm_role_t;


enum wiced_bt_pcm_sync_type_e{
    WICED_BT_PCM_FRAME_TYPE_SHORT = 0, /* PCM data format config for short frame sync */
    WICED_BT_PCM_FRAME_TYPE_LONG,      /* PCM data format config for long frame sync */
};
typedef uint8_t wiced_bt_pcm_sync_type_t;

enum wiced_bt_pcm_right_justify_e{
    WICED_BT_PCM_DISABLE_RIGHT_JUSTIFY = 0, /* Used default data justify*/
    WICED_BT_PCM_ENABLE_RIGHT_JUSTIFY,      /* Used right justify to sync data */
};
typedef uint8_t wiced_bt_pcm_right_justify_t;

enum wiced_bt_pcm_fill_data_e{
    WICED_BT_PCM_FILL_0S = 0,
    WICED_BT_PCM_FILL_1S,
    WICED_BT_PCM_FILL_SIGNED,
    WICED_BT_PCM_FILL_PROG
};
typedef uint8_t wiced_bt_pcm_fill_data_t;

/******************************************************
 *              Type Definitions
 ******************************************************/

#define  WICED_BT_SCO_DATA_CB_GET_LENGTH(ltch_len)   ((ltch_len>>8)&0xff)

//Call back function for pcm data transfer, ltch_len = (length)<<8|(sco_channel)
typedef void (wiced_bt_sco_data_cb_t) (uint32_t ltch_len, uint8_t *p_data);

/* Subset for the enhanced setup/accept synchronous connection paramters
 * See BT 4.1 or later HCI spec for details */
typedef struct
{
    uint16_t max_latency;                   /**< Maximum latency (0x4-0xFFFE in msecs) */
    uint16_t packet_types;                  /**< Packet Types */
    uint8_t retrans_effort;                 /**< 0x00-0x02, 0xFF don't care */
    wiced_bool_t use_wbs;                   /**< True to use wide band, False to use narrow band */
} wiced_bt_sco_params_t;

typedef struct
{
    wiced_bt_i2spcm_role_t     mode;            /* pcm interface mode: 0: slave; 1: master */
    wiced_bt_pcm_sync_type_t   frame_type;      /* frame type: 0: short; 1: long */
    wiced_bt_pcm_data_order_t  lsbFirst;        /* pcm packet format 0:MSB_FIRST 1:LSB_FIRST */
    uint8_t                    fillNum;         /* pcm fill number */
    wiced_bt_pcm_fill_data_t   fillData;        /* pcm fill data 0:FILL_0S 1:FILL_1S 2:FILL_SIGNED */
    uint8_t                    fillBits;        /* pcm fill bits */
    wiced_bt_pcm_right_justify_t   rightJustify;/* 0:no ; 1:yes  pcm only */
}wiced_bt_pcm_param_t;

typedef struct
{
    wiced_bt_i2spcm_role_t   mode; /* I2S interface mode: 0: slave; 1: master */
}wiced_bt_i2s_param_t;

typedef struct
{
    wiced_bt_sco_data_cb_t   *p_sco_data_cb; /* callback function for transfer pcm data */
}wiced_bt_uart_param_t;


typedef union{
    wiced_bt_pcm_param_t  pcm_param;
    wiced_bt_i2s_param_t  i2s_param;
    wiced_bt_uart_param_t uart_param;
}wiced_bt_trans_config_t;

typedef struct
{
    wiced_bt_sco_route_path_t    path;    /* sco routing path  0:pcm; 1:uart 2:i2s */
    wiced_bt_trans_config_t      trans_param; /* i2s/pcm/uart configuration */
}wiced_bt_voice_path_setup_t;

/******************************************************
 *              Function Declarations
 ******************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Function         wiced_bt_sco_create_as_initiator
 *
 *                  The wiced_sco_lib.a was required to included before we link this function.
 *                  Creates a synchronous connection oriented connection as initiator.
 *
 *  @param[in]  bd_addr                 : Peer bd_addr
 *  @param[in]  p_params                : Pointer to the SCO parameter structure
 *  @param[out] p_sco_index             : SCO index returned
 *
 *  @return     <b> WICED_BT_UNKNOWN_ADDR </b>      : Create connection failed, ACL connection is not up
 *              <b> WICED_BT_BUSY </b>              : Create connection failed, another SCO is being
 *                                                    conncted to the same BD address
 *              <b> WICED_BT_WRONG_MODE </b>        : Create connection failed, wrong mode
 *              <b> WICED_BT_NO_RESOURCES </b>      : Create connection failed, max SCO limit has been
 *                                                    reached
 *              <b> WICED_BT_PENDING </b>            : Create connection successfully, "p_sco_index" is returned
 */
wiced_bt_dev_status_t wiced_bt_sco_create_as_initiator (wiced_bt_device_address_t bd_addr,
                                                        uint16_t *p_sco_index,
                                                        wiced_bt_sco_params_t *p_params);

/**
 * Function         wiced_bt_sco_create_as_acceptor
 *
 *                  Creates a synchronous connection oriented connection as acceptor.
 *
 *  @param[out] p_sco_index             : SCO index returned
 *
 *  @return     <b> WICED_BT_UNKNOWN_ADDR </b>      : Create connection failed, ACL connection is not up or
 *                                                    address is invalid
 *              <b> WICED_BT_BUSY </b>              : Create connection failed, a SCO connection is already
 *                                                    conncted to the same BD address
 *              <b> WICED_BT_WRONG_MODE </b>        : Create connection failed, link in park mode or
 *                                                    automatic un-park is not supported
 *              <b> WICED_BT_NO_RESOURCES </b>      : Create connection failed, max SCO limit has been
 *                                                    reached
 *              <b> WICED_BT_PENDING </b>            : Create connection successfully, "p_sco_index" is returned
 */
wiced_bt_dev_status_t wiced_bt_sco_create_as_acceptor (uint16_t *p_sco_index);

/**
 * Function         wiced_bt_sco_remove
 *
 *                  Removes a specific synchronous connection oriented connection.
 *
 *  @param[in]  sco_index           : SCO index to remove
 *
 *  @return     <b> WICED_BT_UNKNOWN_ADDR </b>      : Remove connection failed, invalid SCO index
 *              <b> WICED_BT_NO_RESOURCES </b>      : Remove connection failed, no resource
 *              <b> WICED_BT_SUCCESS </b>           : Remove connection successfully, device is still
 *                                                    listening for incoming connection
 *              <b> WICED_BT_PENDING </b>            : Remove connection successfully
 */
wiced_bt_dev_status_t wiced_bt_sco_remove (uint16_t sco_index);

/**
 * Function         wiced_bt_sco_accept_connection
 *
 *                  The wiced_sco_lib.a was required to be included before we link this function.
 *                  Called to handle (e)SCO connection request event (wiced_bt_sco_connect_request_event).
 *
 *
 *  @param[in]  sco_index           : SCO index
 *
 *  @param[in]  HCI status code     : WICED_BT_SCO_CONNECTION_ACCEPT              0x00
 *                                    WICED_BT_SCO_CONNECTION_REJECT_RESOURCES    0x0D
 *                                    WICED_BT_SCO_CONNECTION_REJECT_SECURITY     0x0E
 *                                    WICED_BT_SCO_CONNECTION_REJECT_DEVICE       0x0F
 *  @param[in]  p_params            : Pointer to the SCO parameter structure
 *
 */
void wiced_bt_sco_accept_connection (uint16_t sco_index, uint8_t hci_status,
                                     wiced_bt_sco_params_t *p_params);


/**
 * Function         wiced_bt_sco_setup_voice_path
 *
 *                  The wiced_sco_lib.a was required to include before we link this function.
 *                  Configure the SCO routing path.
 *
 *  @param[in]  pData                 : To setup SCO routing path
 *
 * @return
 *              WICED_BT_SUCCESS    : Config success.
 *              WICED_BT_PENDING    : Command sent. Waiting for command complete event.
 *              WICED_BT_BUSY       : Command not sent. Waiting for command complete event for prior command.
 */
wiced_bt_dev_status_t wiced_bt_setup_voice_path(wiced_bt_voice_path_setup_t *pData);



/**
 * Function         wiced_bt_sco_output_stream
 *
 *                  The wiced_sco_lib.a was required to include before we link this function.
 *                  Send pcm data to internal audio pipe.
 *
 *
 *  @param[in]  sco_index     : SCO index to send the stream
 *  @param[in]  p_pcmsrc        : Audio stream source.
 *  @param[in]  len             : Length of stream.
 *
 *  @return                     : Return the legth of non transmited stream.
 */
uint16_t wiced_bt_sco_output_stream( uint16_t sco_index, uint8_t* p_pcmsrc,uint16_t len );

#ifdef __cplusplus
}
#endif
/** @} wicedbt_sco */
