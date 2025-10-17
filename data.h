#ifndef DATA_H_
#define DATA_H_

#include <stdint.h>












class MeasValue
{
    private:
    public:
      float current;
      float voltage;
      void set_data(float current, float voltage);



};


class Data
{
    private:
        static void shift_values();



    public:
        static void init();
        static const uint16_t NUMBER_MEASUREMENTS = 430;
        static uint16_t number;
        static MeasValue values[NUMBER_MEASUREMENTS + 1];

        static MeasValue max;
        static MeasValue active;

        static void add_value(float current, float voltage);
        static void update_max(float current, float voltage);
        static void reset();
};



#endif