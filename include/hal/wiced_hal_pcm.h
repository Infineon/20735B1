/*
 * Cypress Semiconductor Proprietary and Confidential. © 2016 Cypress Semiconductor.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Cypress Semiconductor;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Cypress Semiconductor.
 */

/** @file
 *
 * Defines the utilities for configuring the I2S
 */

#ifndef _WICED_HAL_PCM_H_
#define _WICED_HAL_PCM_H_

/**
 * Function         wiced_hal_pcm_select_pads
 *
 * Selects the PCM clock, sync, data out and data in, LHL pins for the PCM peripheral to use.
 *
 *
 * @param[in]    pcm_clk              : PCM Clock Pin
 * @param[in]    pcm_sync           : PCM Sync Pin
 * @param[in]    pcm_out             : PCM Data Out Pin
 * @param[in]    pcm_in               : PCM Data In Pin
 *
 * @return     : None
 */
void wiced_hal_pcm_select_pads( uint8_t pcm_clk, uint8_t pcm_sync,
                            uint8_t pcm_out, uint8_t pcm_in );

#endif // _WICED_HAL_PCM_H_
