#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float hum;
};

QueueHandle_t my_queue;

void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {

  Serial.begin(9600);

  dht.begin();

  my_queue = xQueueCreate(5, sizeof(struct readings));

  xTaskCreate(
    read_data,
    "Read Sensor",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    display,
    "Display Data",
    128,
    NULL,
    1,
    NULL
  );
}

void loop() {}

void read_data(void *pvParameters)
{
  struct readings data;

  while(1)
  {
    data.temp = dht.readTemperature();
    data.hum = dht.readHumidity();

    if(!isnan(data.temp) && !isnan(data.hum))
    {
      xQueueSend(my_queue, &data, portMAX_DELAY);
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void display(void *pvParameters)
{
  struct readings data;

  while(1)
  {
    if(xQueueReceive(my_queue, &data, portMAX_DELAY) == pdPASS)
    {
      Serial.print("Temperature : ");
      Serial.print(data.temp);
      Serial.println(" C");

      Serial.print("Humidity    : ");
      Serial.print(data.hum);
      Serial.println(" %");

      Serial.println("----------------");
    }
  }
}