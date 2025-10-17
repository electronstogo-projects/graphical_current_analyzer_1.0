#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_


#include <stdint.h>




class Measurement
{
    private:
        //INA219 ina219;



    public:
        static void init();
        static void run();

};



#endif