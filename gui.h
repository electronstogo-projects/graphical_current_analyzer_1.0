#ifndef GUI_H_
#define GUI_H_



#include <stdint.h>





class GUI
{
    private:
        static const uint16_t WIDTH = 480;
        static const uint16_t HEIGHT = 320;

        static const uint16_t X[2];
        static const uint16_t Y[2];
        static const uint16_t GRAPH_HEIGHT;
        static const uint16_t GRAPH_WIDTH;

        static void flush();
        static void draw_graph_frame();
        static void draw_graph_curves();
        static void draw_current(float max);
        static void draw_voltage(float max);
        static void draw_text_infos();
        static void draw_dotted_hline(uint16_t x1, uint16_t x2, uint16_t y, uint16_t length, uint16_t gap);
        static void draw_dotted_vline(uint16_t y1, uint16_t y2, uint16_t x, uint16_t length, uint16_t gap);


    public:
        static void init();
        static void run();
};





#endif