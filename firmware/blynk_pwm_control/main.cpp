#define BLYNK_TEMPLATE_ID "template id"
#define BLYNK_TEMPLATE_NAME "bldc"
#define BLYNK_AUTH_TOKEN "auth_token"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const char ssid[] = "your wifi name";
const char pass[] = "wifi password";

#define escpin 4
#define led_builtin 2

const int pwm_freq = 50;
const int pwm_res = 16;    // resolution (0–16 bits)
const int pwm_channel = 0; // channels (0–15)

const float t_period = 1.0 / pwm_freq;

// duty cycle values for 1ms and 2ms pulses
const uint32_t duty_min = (0.001 / t_period) * ((1 << pwm_res) - 1);
const uint32_t duty_max = (0.002 / t_period) * ((1 << pwm_res) - 1);

uint32_t pwm_duty = duty_min;

void setup()
{
    pinMode(led_builtin, OUTPUT);

    ledcSetup(pwm_channel, pwm_freq, pwm_res);
    ledcAttachPin(escpin, pwm_channel);

    ledcWrite(pwm_channel, duty_min);

    // led blink at startup
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(led_builtin, HIGH);
        delay(500);
        digitalWrite(led_builtin, LOW);
        delay(500);
    }

    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_WRITE(V0)
{
    int throttle = param.asInt();
    pwm_duty = map(throttle, 0, 100, duty_min, duty_max);     //takes integer 0-100 from blynk
    ledcWrite(pwm_channel, pwm_duty);

    if (!Blynk.connected())     //prevents motor running if wifi disconnected
    {
        ledcWrite(pwm_channel, duty_min);     
    }
}
void loop()
{
    Blynk.run();
}
