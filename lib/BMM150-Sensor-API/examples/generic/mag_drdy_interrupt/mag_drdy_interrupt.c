/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/******************************************************************************/
/*!                 Header Files                                              */
#include <stdio.h>
#include "bmm150.h"
#include "bmm150_common.h"

/******************************************************************************/
/*!         Static Function Declaration                                       */

/*!
 *  @brief This internal API is used to set configurations powermode, odr and interrupt mapping.
 *
 *  @param[in] dev       : Structure instance of bmm150_dev.
 *
 *  @return Status of execution.
 */
static int8_t set_config(struct bmm150_dev *dev);

/*!
 *  @brief This internal API is used to get gyro data.
 *
 *  @param[in] dev       : Structure instance of bmm150_dev.
 *
 *  @return Status of execution.
 */
static int8_t get_data(struct bmm150_dev *dev);

/******************************************************************************/
/*!            Functions                                        */

/* This function starts the execution of program. */
int main(void)
{
    /* Status of api are returned to this variable */
    int8_t rslt;

    /* Sensor initialization configuration. */
    struct bmm150_dev dev;

    rslt = bmm150_interface_selection(&dev);
    bmm150_error_codes_print_result("bmm150_interface_selection", rslt);

    if (rslt == BMM150_OK)
    {
        rslt = bmm150_init(&dev);
        bmm150_error_codes_print_result("bmm150_init", rslt);

        if (rslt == BMM150_OK)
        {
            rslt = set_config(&dev);
            bmm150_error_codes_print_result("set_config", rslt);

            if (rslt == BMM150_OK)
            {
                rslt = get_data(&dev);
                bmm150_error_codes_print_result("get_data", rslt);
            }
        }
    }

    return rslt;
}

/*!
 *  @brief This internal API is used to set configurations like powermode, odr and interrupt mapping.
 */
static int8_t set_config(struct bmm150_dev *dev)
{
    /* Status of api are returned to this variable. */
    int8_t rslt;

    struct bmm150_settings settings;

    /* Set powermode as normal mode */
    settings.pwr_mode = BMM150_POWERMODE_NORMAL;
    rslt = bmm150_set_op_mode(&settings, dev);
    bmm150_error_codes_print_result("bmm150_set_op_mode", rslt);

    if (rslt == BMM150_OK)
    {
        /* Setting the preset mode as Low power mode
         * i.e. data rate = 10Hz, XY-rep = 1, Z-rep = 2
         */
        settings.preset_mode = BMM150_PRESETMODE_LOWPOWER;
        rslt = bmm150_set_presetmode(&settings, dev);
        bmm150_error_codes_print_result("bmm150_set_presetmode", rslt);

        if (rslt == BMM150_OK)
        {
            /* Map the data interrupt pin */
            settings.int_settings.drdy_pin_en = 0x01;
            rslt = bmm150_set_sensor_settings(BMM150_SEL_DRDY_PIN_EN, &settings, dev);
            bmm150_error_codes_print_result("bmm150_set_sensor_settings", rslt);
        }
    }

    return rslt;
}

/*!
 *  @brief This internal API is used to get gyro data.
 */
static int8_t get_data(struct bmm150_dev *dev)
{
    /* Status of api are returned to this variable. */
    int8_t rslt;

    int8_t idx;

    struct bmm150_mag_data mag_data;

    /* Reading the mag data */
    while (1)
    {
        /* Get the interrupt status */
        rslt = bmm150_get_interrupt_status(dev);

        if (dev->int_status & BMM150_INT_ASSERTED_DRDY)
        {
            printf("Data interrupt occurred\n");

            for (idx = 0; idx < 50; idx++)
            {
                /* Read mag data */
                rslt = bmm150_read_mag_data(&mag_data, dev);
                bmm150_error_codes_print_result("bmm150_read_mag_data", rslt);

                /* Unit for magnetometer data is microtesla(uT) */
                printf("MAG DATA[%d]  X : %d uT   Y : %d uT   Z : %d uT\n", idx, mag_data.x, mag_data.y, mag_data.z);
            }
        }

        break;
    }

    return rslt;
}
