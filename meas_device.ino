#include "gui.h"
#include "measurement.h"
#include "data.h"




class Config
{
    public:
      // Sampling in ms.
      static const uint16_t SAMPLING_TIME = 50;
      static const uint16_t FPS = 5;
      static const uint16_t BUTTON_PIN = 9;
};


void setup(void)
{ 
    GUI::init();
    Measurement::init();
    Data::init();

    // Init button inputs.
    pinMode(Config::BUTTON_PIN, INPUT_PULLUP);
}

void loop() 
{
    uint32_t timestamp_gui = 0;
    uint32_t timestamp_sampling = 0;
    uint32_t timestamp_button = 0;


    while(true)
    {
        // Measurement process.
        if(millis() > (timestamp_sampling + Config::SAMPLING_TIME))
        {
            Measurement::run();
            timestamp_sampling = millis();
        }

        // GUI process.
        if(millis() > (timestamp_gui + (1000 / Config::FPS)))
        {
            GUI::run();
            timestamp_gui = millis();
        }
        
        // Check button.
        if(millis() > (timestamp_button + 500))
        {
            if(!digitalRead(Config::BUTTON_PIN))
            {
                Data::reset();
            }
            timestamp_button = millis();
        }        
    }

}






