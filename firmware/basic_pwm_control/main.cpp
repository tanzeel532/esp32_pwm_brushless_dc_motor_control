#include <Arduino.h>

#define escpin 4
#define led_builtin 2

const int pwm_freq = 50;
const int pwm_res = 16;        //resolution (0–16 bits)
const int pwm_channel = 0;     //channels (0–15)

const float t_period = 1.0 / pwm_freq;

//duty cycle values for 1ms and 2ms pulses
const uint32_t duty_min = (0.001 / t_period) * ((1 << pwm_res) - 1);
const uint32_t duty_max = (0.002 / t_period) * ((1 << pwm_res) - 1);

uint32_t pwm_duty = duty_min;
unsigned long t_last = 0;

void setup()
{
    pinMode(led_builtin, OUTPUT);

    ledcSetup(pwm_channel, pwm_freq, pwm_res);
    ledcAttachPin(escpin, pwm_channel);

    ledcWrite(pwm_channel, duty_min);

    //led blink at startup
    for(int i = 0; i < 5; i++)
    {
        digitalWrite(led_builtin, HIGH);
        delay(500);
        digitalWrite(led_builtin, LOW);
        delay(500);
    }
}

void loop()
{
    unsigned long t_current = millis();
    unsigned long diff = t_current - t_last;

    if (diff >= 20)
    {
        if (pwm_duty < duty_max)
        {
            pwm_duty++;     //increment by one for smoother control
            ledcWrite(pwm_channel, pwm_duty);
        }
        else if(pwm_duty == duty_max)
        {
            digitalWrite(led_builtin, HIGH);     //led on when max duty reaches
            ledcWrite(pwm_channel, pwm_duty);
        }

        t_last = t_current;
    }
}   
