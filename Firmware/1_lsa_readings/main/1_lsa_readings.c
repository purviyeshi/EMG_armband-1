#include <stdio.h>
#include "esp_err.h"
#include "esp_adc_cal.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define DEFAULT_VREF 1100
#define NUM_SENSORS 5
static const char *TAG = "LSA_READINGS";

void app_main(void)
{
     adc1_config_width(ADC_WIDTH_BIT_12);            //    Configure ADC width to 12 bits

    
   adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);          //       Configure ADC channel attenuation
   adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
   adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
   adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
   adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

     uint16_t adc1_readings[NUM_SENSORS];      //initialise array of adc1 readings.      
    
    
    const adc1_channel_t sensor_channels[NUM_SENSORS] = {ADC1_CHANNEL_0, ADC1_CHANNEL_3,ADC1_CHANNEL_6, ADC1_CHANNEL_7, ADC1_CHANNEL_4};
        //        store raw data from ADC channels       
 
    while (1) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            adc1_readings[i] = adc1_get_raw(sensor_channels[i]);
        }

        // Display raw ADC readings
        
        ESP_LOGI(TAG, "LSA_1: %d \t LSA_2: %d \t LSA_3: %d \t LSA_4: %d \t LSA_5: %d", adc1_readings[0], adc1_readings[1], adc1_readings[2], adc1_readings[3], adc1_readings[4]);
        
        vTaskDelay(10 / portTICK_PERIOD_MS); // Add a time delay 
    }
   
} 
