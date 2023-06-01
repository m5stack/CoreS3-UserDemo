/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#ifndef _COMMON_H
#define _COMMON_H

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "bmm150.h"

/***************************************************************************/

/*!                 User function prototypes
 ****************************************************************************/

/*!
 *  @brief Function for reading the sensor's registers through SPI bus.
 *
 *  @param[in] cs         : Chip select to enable the sensor.
 *  @param[in] reg_addr   : Register address.
 *  @param[out] reg_data  : Pointer to the data buffer to store the read data.
 *  @param[in] length     : No of bytes to read.
 *  @param[in] intf_ptr   : Interface pointer
 *
 *  @return Status of execution
 *
 *  @retval BMM150_INTF_RET_SUCCESS -> Success.
 *  @retval != BMM150_INTF_RET_SUCCESS -> Failure.
 *
 */
BMM150_INTF_RET_TYPE bmm150_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr   : Sensor I2C address.
 *  @param[in] reg_addr   : Register address.
 *  @param[out] reg_data  : Pointer to the data buffer to store the read data.
 *  @param[in] length     : No of bytes to read.
 *  @param[in] intf_ptr   : Interface pointer
 *
 *  @return Status of execution
 *
 *  @retval BMM150_INTF_RET_SUCCESS -> Success.
 *  @retval != BMM150_INTF_RET_SUCCESS -> Failure.
 *
 */
BMM150_INTF_RET_TYPE bmm150_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 *  @brief Function for writing the sensor's registers through SPI bus.
 *
 *  @param[in] cs         : Chip select to enable the sensor.
 *  @param[in] reg_addr   : Register address.
 *  @param[in] reg_data   : Pointer to the data buffer whose data has to be written.
 *  @param[in] length     : No of bytes to write.
 *  @param[in] intf_ptr   : Interface pointer
 *
 *  @return Status of execution
 *
 *  @retval BMM150_INTF_RET_SUCCESS -> Success.
 *  @retval  != BMM150_INTF_RET_SUCCESS -> Failure.
 *
 */
BMM150_INTF_RET_TYPE bmm150_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : Sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose value is to be written.
 *  @param[in] length   : No of bytes to write.
 *  @param[in] intf_ptr : Interface pointer
 *
 *  @return Status of execution
 *
 *  @retval BMM150_INTF_RET_SUCCESS -> Success.
 *  @retval != BMM150_INTF_RET_SUCCESS -> Failure.
 *
 */
BMM150_INTF_RET_TYPE bmm150_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 *  @brief This function provides the delay for required time (Microsecond) as per the input provided in some of the
 *  APIs.
 *
 *  @param[in] period_us  : The required wait time in microsecond.
 *  @param[in] intf_ptr   : Interface pointer
 *
 *  @return void.
 */
void bmm150_delay_us(uint32_t period_us, void *intf_ptr);

/*!
 *  @brief This function is to select the interface between SPI and I2C.
 *
 *  @param[in] dev    : Structure instance of bmm150_dev
 *  @param[in] intf   : Interface selection parameter
 *                          For I2C : BMM150_I2C_INTF
 *                          For SPI : BMM150_SPI_INTF
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval < 0 -> Failure
 */
int8_t bmm150_interface_selection(struct bmm150_dev *dev, uint8_t intf);

/*!
 *  @brief This API is used to print the execution status.
 *
 *  @param[in] api_name : Name of the API whose execution status has to be printed.
 *  @param[in] rslt     : Error code returned by the API whose execution status has to be printed.
 *
 *  @return void.
 */
void bmm150_error_codes_print_result(const char api_name[], int8_t rslt);

/*!
 * @brief This function deinitializes coines platform
 *
 *  @return void.
 *
 */
void bmm150_coines_deinit(void);

#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif /* _COMMON_H */
