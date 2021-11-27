/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "detection_responder.h"
#include <esp_heap_caps.h>
#include "esp_system.h"
#include "driver/gpio.h"
#include "flash_led.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// This dummy implementation writes person and no person scores to the error
// console. Real applications will want to take some custom action instead, and
// should implement their own versions of this function.
void RespondToDetection(tflite::ErrorReporter* error_reporter,
                        int8_t person_score, int8_t no_person_score) {
    TF_LITE_REPORT_ERROR(error_reporter, "score: %d ** %d",
                       person_score, no_person_score);

    // int valueChangeRate = 200;
    if (person_score > 50) {
        TF_LITE_REPORT_ERROR(error_reporter, "BOTTLE! BOTTLE!! BOTTLE!!!!!!");
        // gpio_set_level(GPIO_NUM_4, 1);
        // ledc_set_duty(FLASH_LEDC_SPEED_MODE, FLASH_LEDC_CHANNEL, 255);
        // ledc_update_duty(FLASH_LEDC_SPEED_MODE, FLASH_LEDC_CHANNEL);
        // int duty  = (1<<15) * 500 / 20000 ;//1638
        // ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, duty);
        // ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
        // vTaskDelay(valueChangeRate/portTICK_PERIOD_MS);
    } else {
        TF_LITE_REPORT_ERROR(error_reporter, "... ... ...");
        // gpio_set_level(GPIO_NUM_4, 0);
        // ledc_set_duty(FLASH_LEDC_SPEED_MODE, FLASH_LEDC_CHANNEL, 0);
        // ledc_update_duty(FLASH_LEDC_SPEED_MODE, FLASH_LEDC_CHANNEL);
        // int duty  = (1<<15) * 700 / 20000 ;//1638
        // ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, duty);
        // ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
        // vTaskDelay(valueChangeRate/portTICK_PERIOD_MS);
    }
}
