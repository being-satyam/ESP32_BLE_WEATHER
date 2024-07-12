#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <DHT.h>

DHT dht(4, DHT11);
BLEServer* pServer = NULL;
BLECharacteristic* pTempCharacteristic = NULL;
BLECharacteristic* pHumCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
float temp = 0;
float hum = 0;

#define SERVICE_UUID "00000002-0000-0000-FDFD-FDFDFDFDFDFD"
#define CHARACTERISTIC_TEMPERATURE_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_HUMIDITY_UUID "beb5483e-36e1-4688-b7f5-ea07361b2321"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);

  // Initialize the DHT11 sensor
  dht.begin();

  // Create the BLE Device
  BLEDevice::init("WEATHER");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic for temperature
  pTempCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_TEMPERATURE_UUID,
                          BLECharacteristic::PROPERTY_READ   |
                          BLECharacteristic::PROPERTY_NOTIFY
                        );
  pTempCharacteristic->addDescriptor(new BLE2902());
  BLEDescriptor* tempDescriptor = new BLEDescriptor(BLEUUID((uint16_t)0x2901));
  tempDescriptor->setValue("Temperature in Celsius");
  pTempCharacteristic->addDescriptor(tempDescriptor);

  // Create a BLE Characteristic for humidity
  pHumCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_HUMIDITY_UUID,
                          BLECharacteristic::PROPERTY_READ   |
                          BLECharacteristic::PROPERTY_NOTIFY
                        );
  pHumCharacteristic->addDescriptor(new BLE2902());
  BLEDescriptor* humDescriptor = new BLEDescriptor(BLEUUID((uint16_t)0x2901));
  humDescriptor->setValue("Humidity in Percent");
  pHumCharacteristic->addDescriptor(humDescriptor);

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting for a client connection to notify...");
}

void loop() {
    // Read the temperature and humidity from the DHT11 sensor
    temp = dht.readTemperature();
    hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        if (deviceConnected) {
            // Convert the float temperature to a string with °C
            char tempString[10];
            snprintf(tempString, sizeof(tempString), "%.2fC", temp);
            pTempCharacteristic->setValue(tempString);
            pTempCharacteristic->notify();
            Serial.print("Temperature: ");
            Serial.println(tempString);

            // Convert the float humidity to a string with %
            char humString[10];
            snprintf(humString, sizeof(humString), "%.2f%%", hum);
            pHumCharacteristic->setValue(humString);
            pHumCharacteristic->notify();
            Serial.print("Humidity: ");
            Serial.println(humString);
        }
    }

    delay(5000); 

    
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); 
        pServer->startAdvertising(); // restart advertising
        Serial.println("Started advertising");
        oldDeviceConnected = deviceConnected;
    }

    // Connecting
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
    }
}
