/**
 * Copyright (C) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "coines.h"
#include "bmm150_defs.h"

/******************************************************************************/
/*!                Static variable definition                                 */

/*! Variable that holds the I2C device address or SPI chip selection */
static uint8_t dev_addr;

/******************************************************************************/
/*!                User interface functions                                   */

/*!
 * I2C read function map to COINES platform
 */
BMM150_INTF_RET_TYPE bmm150_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
    dev_addr = *(uint8_t*)intf_ptr;

    return coines_read_i2c(dev_addr, reg_addr, reg_data, (uint16_t)length);
}

/*!
 * I2C write function map to COINES platform
 */
BMM150_INTF_RET_TYPE bmm150_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
    dev_addr = *(uint8_t*)intf_ptr;

    return coines_write_i2c(dev_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)length);
}

/*!
 * SPI read function map to COINES platform
 */
BMM150_INTF_RET_TYPE bmm150_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
    dev_addr = *(uint8_t*)intf_ptr;

    return coines_read_spi(dev_addr, reg_addr, reg_data, (uint16_t)length);
}

/*!
 * SPI write function map to COINES platform
 */
BMM150_INTF_RET_TYPE bmm150_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
    dev_addr = *(uint8_t*)intf_ptr;

    return coines_write_spi(dev_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)length);
}

/*!
 * Delay function map to COINES platform
 */
void bmm150_delay_us(uint32_t period, void *intf_ptr)
{
    coines_delay_usec(period);
}

/*!
 *  @brief Prints the execution status of the APIs.
 */
void bmm150_error_codes_print_result(const char api_name[], int8_t rslt)
{
    if (rslt != BMM150_OK)
    {
        printf("%s\t", api_name);

        switch (rslt)
        {
            case BMM150_E_NULL_PTR:
                printf("Error [%d] : Null pointer error.", rslt);
                printf(
                    "It occurs when the user tries to assign value (not address) to a pointer, which has been initialized to NULL.\r\n");
                break;

            case BMM150_E_COM_FAIL:
                printf("Error [%d] : Communication failure error.", rslt);
                printf(
                    "It occurs due to read/write operation failure and also due to power failure during communication\r\n");
                break;

            case BMM150_E_DEV_NOT_FOUND:
                printf("Error [%d] : Device not found error. It occurs when the device chip id is incorrectly read\r\n",
                       rslt);
                break;

            case BMM150_E_INVALID_CONFIG:
                printf("Error [%d] : Invalid sensor configuration.", rslt);
                printf(" It occurs when there is a mismatch in the requested feature with the available one\r\n");
                break;

            default:
                printf("Error [%d] : Unknown error code\r\n", rslt);
                break;
        }
    }
}

/*!
 *  @brief Function to select the interface between SPI and I2C.
 */
int8_t bmm150_interface_selection(struct bmm150_dev *dev, uint8_t intf)
{
    int8_t rslt = BMM150_OK;

    if (dev != NULL)
    {
        int16_t result = coines_open_comm_intf(COINES_COMM_INTF_USB);

        if (result < COINES_SUCCESS)
        {
            printf(
                "\n Unable to connect with Application Board ! \n" " 1. Check if the board is connected and powered on. \n" " 2. Check if Application Board USB driver is installed. \n"
                " 3. Check if board is in use by another application. (Insufficient permissions to access USB) \n");
            exit(result);
        }

        coines_set_shuttleboard_vdd_vddio_config(0, 0);
        coines_delay_msec(100);

        /* Bus configuration : I2C */
        if (intf == BMM150_I2C_INTF)
        {
            printf("I2C Interface\n");

            dev_addr = BMM150_DEFAULT_I2C_ADDRESS;
            dev->read = bmm150_i2c_read;
            dev->write = bmm150_i2c_write;
            dev->intf = BMM150_I2C_INTF;

            /* set the sensor interface as I2C with 100kHz speed */
            coines_config_i2c_bus(COINES_I2C_BUS_0, COINES_I2C_STANDARD_MODE);
            coines_delay_msec(10);

            /* PS pin is made high for selecting I2C protocol*/
            coines_set_pin_config(COINES_SHUTTLE_PIN_9, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_HIGH);
            coines_set_pin_config(COINES_SHUTTLE_PIN_7, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);
        }
        /* Bus configuration : SPI */
        else if (intf == BMM150_SPI_INTF)
        {
            printf("SPI Interface\n");

            dev_addr = COINES_SHUTTLE_PIN_7;
            dev->read = bmm150_spi_read;
            dev->write = bmm150_spi_write;
            dev->intf = BMM150_SPI_INTF;

            /* PS pin is made high for selecting SPI protocol*/
            coines_set_pin_config(COINES_SHUTTLE_PIN_9, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);

            coines_delay_msec(10);
            coines_config_spi_bus(COINES_SPI_BUS_0, COINES_SPI_SPEED_5_MHZ, COINES_SPI_MODE3);
        }

        coines_set_shuttleboard_vdd_vddio_config(3300, 3300);

        /* Holds the I2C device addr or SPI chip selection */
        dev->intf_ptr = &dev_addr;

        /* Configure delay in microseconds */
        dev->delay_us = bmm150_delay_us;
    }
    else
    {
        rslt = BMM150_E_NULL_PTR;
    }

    return rslt;
}

/*!
 *  @brief Function deinitializes coines platform.
 */
void bmm150_coines_deinit(void)
{
    coines_close_comm_intf(COINES_COMM_INTF_USB);
}
