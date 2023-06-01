/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/******************************************************************************/
/*!                 Header Files                                              */
#include <stdio.h>
#include "bmm150.h"
#include "common.h"

/******************************************************************************/
/*!         Static Function Declaration                                       */

/*!
 *  @brief This internal API is used to set configurations like threshold and interrupt mapping.
 *
 *  @param[in] dev       : Structure instance of bmm150_dev.
 *
 *  @return Status of execution.
 */
static int8_t set_config(struct bmm150_dev *dev);

/******************************************************************************/
/*!            Functions                                        */

/* This function starts the execution of program. */
int main(void)
{
    /* Status of api are returned to this variable */
    int8_t rslt;

    /* Sensor initialization configuration. */
    struct bmm150_dev dev;

    /* Interface selection is to be updated as parameter
     * For I2C :  BMM150_I2C_INTF
     * For SPI :  BMM150_SPI_INTF
     */
    rslt = bmm150_interface_selection(&dev, BMM150_I2C_INTF);
    bmm150_error_codes_print_result("bmm150_interface_selection", rslt);

    if (rslt == BMM150_OK)
    {
        rslt = bmm150_init(&dev);
        bmm150_error_codes_print_result("bmm150_init", rslt);

        if (rslt == BMM150_OK)
        {
            rslt = set_config(&dev);
            bmm150_error_codes_print_result("set_config", rslt);
        }

        while (1)
        {
            /* Get the interrupt status */
            rslt = bmm150_get_interrupt_status(&dev);

            if (dev.int_status & BMM150_INT_ASSERTED_LOW_THRES)
            {
                printf("Low threshold interrupt occured");
                break;
            }
        }
    }

    bmm150_coines_deinit();

    return rslt;
}

/*!
 *  @brief This internal API is used to set configurations like threshold and interrupt mapping.
 */
static int8_t set_config(struct bmm150_dev *dev)
{
    /* Status of api are returned to this variable. */
    int8_t rslt;

    struct bmm150_settings settings;

    /* Read the default configuration from the sensor */
    settings.pwr_mode = BMM150_POWERMODE_NORMAL;
    rslt = bmm150_set_op_mode(&settings, dev);
    bmm150_error_codes_print_result("bmm150_set_op_mode", rslt);

    if (rslt == BMM150_OK)
    {
        /* Set any threshold level below which low threshold interrupt occurs */
        settings.int_settings.low_threshold = 0x0A;
        rslt = bmm150_set_sensor_settings(BMM150_SEL_LOW_THRESHOLD_SETTING, &settings, dev);
        bmm150_error_codes_print_result("bmm150_set_sensor_settings_1", rslt);

        if (rslt == BMM150_OK)
        {
            rslt = bmm150_get_sensor_settings(&settings, dev);
            bmm150_error_codes_print_result("bmm150_get_sensor_settings", rslt);
            printf("Low threshold: %d \n", settings.int_settings.low_threshold);
        }

        if (rslt == BMM150_OK)
        {
            /* Low interrupt pins are active low as per datasheet */
            settings.int_settings.low_int_en = 0x00;
            rslt = bmm150_set_sensor_settings(BMM150_SEL_LOW_THRESHOLD_INT, &settings, dev);
            bmm150_error_codes_print_result("bmm150_set_sensor_settings_2", rslt);

            if (rslt == BMM150_OK)
            {
                settings.int_settings.int_pin_en = 0x01;
                rslt = bmm150_set_sensor_settings(BMM150_SEL_INT_PIN_EN, &settings, dev);
                bmm150_error_codes_print_result("bmm150_set_sensor_settings_3", rslt);
            }
        }
    }

    return rslt;
}
