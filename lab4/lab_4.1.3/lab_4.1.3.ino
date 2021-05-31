#include "setup.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include <arduinoFFT.h>

////////////////////////////////////////////////
// APPROVED FOR ECE 474   Spring 2021
//
//  NOTE: modify analogRead() on line 113 according
//   to your setup.
////////////////////////////////////////////////

QueueHandle_t task34Queue;
TaskHandle_t task3Handle;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink
    ,  "Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(TaskTheme, "Theme", 128, NULL, 3, NULL);

  Task34Starter();

  delay(500);

  vTaskStartScheduler();
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  // initialize led pin as an output.
  ledSetup();

  for (;;) // A Task shall never return or exit.
  {
    LED_PORT &= ~LED_BIT; // turn on
    vTaskDelay( pdMS_TO_TICKS(100) ); // wait for one second
    LED_PORT |= LED_BIT; // turn off
    vTaskDelay( pdMS_TO_TICKS(200) ); // wait for one second
  }
}

void TaskTheme(void * pvParameters) {
  speakerSetup();
  // Play the theme NPLAY times
  for (int i = 0; i < NPLAY; i++) {
    for (int j = 0; j < NFREQ; j++) {
      setOC4AFreq(melody[j]);
      vTaskDelay(pdMS_TO_TICKS(PLAY_DURATION)); // wait for play duration ms
    }
    setOC4AFreq(0);

    // add fencepost to waiting
    if (i != 2) vTaskDelay(pdMS_TO_TICKS(1500));
  }
  // delete the task
  vTaskDelete(NULL);
}

void Task34Starter() {
  char arr[NSAMPLES];
  // generate an array of 512 random 16-bit longs
  for (int i = 0; i < NSAMPLES; i++) {
    arr[i] = random(-100, 100);
  }

  // intialize the queue which tasks 3 and 4 will use to communicate
  // FreeRTOS max queue size is only 128 bytes, so we have to split up our queue to send
  // queues of larger sizes (this does assume that we'll send more than 2 values)
  task34Queue = xQueueCreate((unsigned int)NSAMPLES / 4, (unsigned int)sizeof(double));

  xTaskCreate(Task3, "Task3", 128, &arr, 1, &task3Handle);

  xTaskCreate(Task4, "Task4", 4269, &task3Handle, 0, NULL);

}

void Task3(void * pvParameters) {
  double * arr = ((double **) pvParameters)[0];

  TickType_t start;
  for (int i = 0; i < 5; i++) {
    start = xTaskGetTickCount();
    // transfer the entire contents of arr over the task34Queue
    for (int j = 0; j < 4; j++) {
      xQueueSendToBack(task34Queue, &arr[(NSAMPLES / 4) * j], 0);
      xTaskNotifyWait(0x00, 0xffffffff, NULL, portMAX_DELAY);
    }
    xTaskNotifyWait(0x00, 0xffffffff, NULL, portMAX_DELAY);
    Serial.print("Task 3 Measured Time : ");
    Serial.println((xTaskGetTickCount() - start) * portTICK_PERIOD_MS);
  }
  Serial.print("Task 3 HWM:");
  Serial.println(uxTaskGetStackHighWaterMark(NULL));

  vTaskDelete(NULL);
}


void Task4(void * pvParameters) {
  double vReal[NSAMPLES];
  double vImag[NSAMPLES];
  arduinoFFT FFT = arduinoFFT();

  TickType_t start;
  for (int i = 0; i < 5; i++) {
    start = xTaskGetTickCount();
    for (int j = 0; j < NSAMPLES; j++) {
      vImag[j] = 0.0; // reset the imaginary part
    }

    for (int j = 0; j < 4; j++) {
      xQueueReceive(task34Queue, &vReal[(NSAMPLES / 4) * j], portMAX_DELAY);
      xTaskNotify(task3Handle, 0, eNoAction);
    }

    // fft calculations
    FFT.Compute(vReal, vImag, NSAMPLES, FFT_FORWARD);
    Serial.print("Task 4 measured time : ");
    Serial.println((xTaskGetTickCount() - start) * portTICK_PERIOD_MS);
    xTaskNotify(task3Handle, 0, eNoAction);
  }
  Serial.print("Task 4 HWM:");
  Serial.println(uxTaskGetStackHighWaterMark(NULL));

  vTaskDelete(NULL);
}

void ledSetup() {
  LED_DDR |= LED_BIT;
  LED_PORT |= LED_BIT;
}

void speakerSetup() {
  // clear timer settings
  TIMER_REG_A = 0;
  TIMER_REG_B = 0;
  // set our timer to work in CTC mode
  TIMER_REG_A |= (0 << WGM41) | (0 << WGM40);
  TIMER_REG_B |= (0 << WGM43) | (1 << WGM42);

  // set timer to work in toggle mode
  TIMER_REG_A |= (0 << COM4A1) | (1 << COM4A0);

  // disable interrupts on the timer
  TIMSK4 = 0;

  // set the prescaler of the timer,
  // which follows the formula:
  //
  //  f_out = f_i/o / 2 * N * (PRESCALER + 1)
  //
  // because f_i/o = 16Mhz, we'll just set N = 1
  TIMER_REG_B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
  PRESCALER = 0;
  TIMER_COUNTER = 0;

  // OC4A is tied to pin 6, which is controlled by PH3
  // set pin 6 as an output pin
  SPEAKER_DDR |= 1 << 3;
}

// sets the OCR4A to make the clock cycle frequency
// the same as the input freq
void setOC4AFreq(uint32_t freq) {
  PRESCALER = freq == 0 ? 0 : 16000000 / (2 * freq);
  TIMER_COUNTER = 0;
}