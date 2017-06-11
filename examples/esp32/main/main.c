#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include <iota/iota.h>

void hello_task(void *pvParameter)
{
    printf("Hello world!\n");
    const char* tr = iota_generateSeed();
    printf("generated seed: %s\n", tr);
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    system_restart();
}

void app_main()
{
    nvs_flash_init();
    system_init();
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, NULL);
}
