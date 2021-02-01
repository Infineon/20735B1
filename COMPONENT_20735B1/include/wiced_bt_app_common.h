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
 * WICED BT App Common Utilities. This file provides the interfaces to the utilities that
 * can be used by the applications
 */
#include "wiced_gki.h"
#include "wiced_timer.h"

#ifndef _WICED_BT_APP_COMMON_H_
#define _WICED_BT_APP_COMMON_H_

/* BLE Advertisement Maximum Length*/
#define ADV_LEN_MAX        31

#ifndef WICED_SDK_MAJOR_VER
#define WICED_SDK_MAJOR_VER    5
#endif
#ifndef WICED_SDK_MINOR_VER
#define WICED_SDK_MINOR_VER    0
#endif
#ifndef WICED_SDK_REV_NUMBER
#define WICED_SDK_REV_NUMBER   0
#endif
#ifndef WICED_SDK_BUILD_NUMBER
#define WICED_SDK_BUILD_NUMBER 0
#endif
#define POWER_CLASS            1

/*****************************************************************************
**                                                  Function Declarations
*****************************************************************************/
/** Wiced Bt App Initialization
 *
 * Initializes Application events serialization. Performs the HAL initialization
 *
  * @return   wiced_result_t
 */
wiced_result_t wiced_bt_app_init( void );

/** Starts the application timers . One is app timer which is a seconds timer, and the other is
 * app fine timerwhich is a milli second timer.This function initializes the timers using the application
 *defined timeouts and also starts the timers. If application does not want to start the timer,
 * timer interval can be passed as 0
 *
 *@param[in]    app_timer_interval       :App timer interval in seconds
 *
 *@param[in]    fine_timer_interval      :App fine timer interval in milliseconds
 *
 *@param[in]    p_app_timer_cb           :Pointer to the application timer callback
 *
 *@param[in]    p_app_fine_timer_cb      :Pointer to the application fine timer callback
 *
 * @return      wiced_result_t
 */
wiced_result_t wiced_bt_app_start_timer ( uint16_t app_timer_interval,
    uint16_t fine_timer_interval, wiced_timer_callback_t p_app_timer_cb,
    wiced_timer_callback_t p_app_fine_timer_cb  );

/** Stops the application timers.
 *
 * @return   None
 */
void wiced_bt_app_stop_timer ( void );

/** Starts the application connection idle timer.This function initialize the timer using the application
 *defined connection idle timeout and also starts the timer
 *
  *@param[in]   con_idle_timeout         :Connection idle timeout in seconds
 *
 *@param[in]    p_app_idle_timer_cb      :Pointer to the application idle timer callback
 *
 * @return      wiced_result_t
 */
wiced_result_t wiced_bt_app_start_conn_idle_timer(
                        UINT8 con_idle_timeout,
                        wiced_timer_callback_t p_app_idle_timer_cb );

/** Stops the application connection idle timer.
 *
 * @return   None
 */
void wiced_bt_app_stop_conn_idle_timer( void );

#endif //_WICED_BT_APP_COMMON_H_
