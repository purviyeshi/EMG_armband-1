#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_log.h"

static const char *TAG = "RECEIVER";
uint8_t receiverAddress[] = {0xE8, 0x31, 0xCD, 0xC3, 0xB0, 0x00}; // Replace with the MAC address of this ESP   
char receivedMessage[100];
void ondatareceived(const uint8_t *mac_addr, const uint8_t *data, int len) {
    ESP_LOGI(TAG,"Received message: %.*s\n", len, data);
    int data_len = sizeof(receivedMessage) / sizeof(receivedMessage[0]);
    memcpy(receivedMessage,data,data_len);
    receivedMessage[data_len];  
}

void app_main(void) {
   

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
     uint8_t senderMacAddress[] = {0xE8, 0x31, 0xCD, 0xC3, 0xEF, 0x8C};
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

