#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_adc_cal.h"
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define DEFAULT_VREF 1100
#define NUM_SENSORS 5 
static const char *TAG = "transmitter";
uint8_t unicastAddress[] = {0xC4, 0xDD, 0x57, 0x5B, 0xF8, 0x54};
uint8_t receiverAddress[] = {0xC4, 0xDD, 0x57, 0x5B, 0xF8, 0x54}; 
// Callback function to handle ESP-NOW sending status
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if (status == ESP_NOW_SEND_SUCCESS) {
        ESP_LOGI(TAG, "Message sent successfully");
    } else {
        ESP_LOGE(TAG, "Message sending failed");
    }
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    ESP_ERROR_CHECK(ret);

    // Initialize WiFi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    // Initialize ESP-NOW
    ESP_ERROR_CHECK(esp_now_init());
    
    //  callback  funtion...ondatasent 
    esp_now_register_send_cb(OnDataSent);

    // Add the receiver
    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(esp_now_peer_info_t));
    memcpy(peerInfo.peer_addr, receiverAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);

    // The lsa reading data to be sent
   // esp_err_t error; // Declare the error variable at the beginning of the function
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

        char lsareads[100];
        
        int data = sprintf(lsareads, sizeof(lsareads),"LSA_1: %d \t LSA_2: %d \t LSA_3: %d \t LSA_4: %d \t LSA_5: %d", adc1_readings[0], adc1_readings[1], adc1_readings[2], adc1_readings[3], adc1_readings[4]);
        
      // Send the data
    esp_err_t result = esp_now_send(unicastAddress, (uint8_t *)data, strlen(data));
    if (result == ESP_OK) {
        ESP_LOGI(TAG, "data send successful");
    } else {
        ESP_LOGE(TAG, "Message sending failed");
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Add a time delay  
    }
  
}

