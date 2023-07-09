#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address 44:17:93:E1:C2:D4
uint8_t broadcastAddress[] = {0x44, 0x17, 0x93, 0xE1, 0xC2, 0xD4};
esp_err_t txresult;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    char info[32];
    float yaw;
    float pitch;
    float roll;
    int cmd;
} struct_message;

// Create a struct_message called myData
struct_message txData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
bool setupTXRX() {
  // Init Serial Monitor
  //Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing SimSpirit-NOW");
    return false;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  Serial.println("Init ESP-NOW success. Registering for Send CB....");

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  Serial.println("ESP-NOW adding peer....");
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return false;
  }

  Serial.println("ESP_NOW peer added successfully");

  return true;
}

void loopTXRX(float i_yaw, float i_pitch, float i_roll, int i_cmd) {
  // Set values to send
  strcpy(txData.info, "THIS IS SimSpirit HT");
  txData.yaw = i_yaw;
  txData.pitch = i_pitch;
  txData.roll = i_roll;
  txData.cmd = i_cmd;
  
  // Send message via ESP-NOW
  txresult = esp_now_send(broadcastAddress, (uint8_t *) &txData, sizeof(txData));

  if (txresult == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  //delay(2000);
}