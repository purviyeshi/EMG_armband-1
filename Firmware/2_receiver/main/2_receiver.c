#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_log.h"
#include "nvs_flash.h"

static const char *TAG = "RECEIVER";
uint8_t receiverAddress[] = {0xC4, 0xDD, 0x57, 0x5B, 0xF8, 0x54}; // Replace with the MAC address of this ESP   
char receivedMessage[100];
void ondatareceived(const uint8_t *mac_addr, const uint8_t *data, int len) {
    ESP_LOGI(TAG,"Received message: %.*s\n", len, data);
    //int data_len = sizeof(receivedMessage) / sizeof(receivedMessage[0]);
    //memcpy(receivedMessage,data,data_len);
    //receivedMessage[data_len];  
}

void app_main(void) {

//initialize nvs_flash
    esp_err_t cpy = nvs_flash_init();
    if (cpy == ESP_ERR_NVS_NO_FREE_PAGES || cpy == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        cpy = nvs_flash_init();
    }
    ESP_ERROR_CHECK(cpy);
   

    // Initialize WiFi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    // Initialize ESP-NOW
     esp_err_t result;
    result = esp_now_init();
    if (result != ESP_OK) {
        printf("ESP-NOW initialization failed\n");
        return;
    }
    
    //Add senders that you expect to receive data from 
     esp_now_peer_info_t peerInfo;
     uint8_t senderMacAddress[] = {0xC4, 0xDD, 0x57, 0xC9, 0x8D, 0x30};       //  Transmitter MAC Address: C4:DD:57:C9:8D:30
    memset(&peerInfo, 0, sizeof(esp_now_peer_info_t));
    memcpy(peerInfo.peer_addr, senderMacAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    ESP_ERROR_CHECK(esp_now_add_peer(&peerInfo));

    // Register callback for receiving data
    esp_now_register_recv_cb(ondatareceived);
    
      

     while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "WAITING");
        }
}

