#include "gui.h"
#include "data.h"
#include "SPI.h"
#include "TFT_eSPI.h"


TFT_eSPI display = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&display);





const uint16_t GUI::X[2] = {45, 470};
const uint16_t GUI::Y[2] = {315, 50};
const uint16_t GUI::GRAPH_HEIGHT = Y[0] - Y[1];
const uint16_t GUI::GRAPH_WIDTH = X[1] - X[0];



void GUI::init()
{
      display.begin();
      display.setRotation(3);
      display.fillScreen(TFT_BLACK);
}





void GUI::run()
{
    sprite.setColorDepth(8);
    sprite.createSprite(WIDTH, HEIGHT);
    sprite.fillSprite(TFT_BLACK);

    draw_graph_frame();
    draw_graph_curves();

    draw_text_infos();

    flush();
}




void GUI::flush()
{
    sprite.pushSprite(0, 0);
}



void GUI::draw_graph_frame()
{
    // Y axis.
    sprite.drawLine(X[0], Y[0], X[0], Y[1], TFT_WHITE);
    // X axis.
    sprite.drawLine(X[0], Y[0], X[1], Y[0], TFT_WHITE);


    // Y axis dotted lines.
    uint16_t x = X[0] - 4;
    for(uint16_t i = 0; i < 5; i++)
    {
        uint16_t y = Y[1] + (GRAPH_HEIGHT / 5) * i;
        draw_dotted_hline(x, x + GRAPH_WIDTH, y, 4, 4);        
    }


    // X axis dotted lines.
    uint16_t y = Y[1] - 2;
    for(uint16_t i = 1; i < 6; i++)
    {
        uint16_t x = X[0] + (GRAPH_WIDTH / 5) * i;
        draw_dotted_vline(y, y + GRAPH_HEIGHT, x, 4, 4);        
    }
}



void GUI::draw_graph_curves()
{
    draw_current(Data::max.current);
    draw_voltage(Data::max.voltage);
}



void GUI::draw_current(float max)
{
    uint16_t y = Y[0] - (Data::values[0].current / max) * (float)GRAPH_HEIGHT;
    uint16_t y_old = y;


    for(uint16_t i = 1; i < Data::number; i++)
    {
        y = Y[0] - (Data::values[i].current / max) * (float)GRAPH_HEIGHT;
        sprite.drawLine(X[0] + i, y_old, X[0] + i + 1, y, TFT_RED);
        y_old = y;
    }
}



void GUI::draw_voltage(float max)
{
    uint16_t y = Y[0] - (Data::values[0].voltage / max) * (float)GRAPH_HEIGHT;
    uint16_t y_old = y;

    for(uint16_t i = 1; i < Data::number; i++)
    {
        y = Y[0] - (Data::values[i].voltage / max) * (float)GRAPH_HEIGHT;
        sprite.drawLine(X[0] + i, y_old, X[0] + i + 1, y, TFT_YELLOW);
        y_old = y;
    }
}




void GUI::draw_text_infos()
{
    sprite.setTextColor(TFT_RED);
    String string;

    // Transform text depending on current value.
    if(Data::active.current >= 1000)
    {
        string = String(Data::active.current / 1000.0, 1) + " A";    
    }
    else
    {
        string = String(Data::active.current, 1) + " mA";
    }
    
    sprite.drawRightString(string, 350, 10, 4);


    // Y axis current.
    for(uint16_t i = 0; i < 5; i++)
    {
        if(Data::max.current >= 1000)
        {
            string = String(int16_t(Data::max.current / 5000) * (i + 1));  
        }
        else
        {
            string = String(int16_t(Data::max.current / 5) * (i + 1));
        }
        
        sprite.drawRightString(string, X[0] - 5, Y[0] - (GRAPH_HEIGHT / 5) * (i + 1) - 15, 2);
    }


    sprite.setTextColor(TFT_YELLOW);
    string = String(Data::active.voltage, 1) + " V";
    sprite.drawRightString(string, 200, 10, 4);



    // Y axis voltage.
    for(uint16_t i = 0; i < 5; i++)
    {
        string = String((Data::max.voltage / 5) * (i + 1), 1);
        sprite.drawRightString(string, X[0] - 5, Y[0] - (GRAPH_HEIGHT / 5) * (i + 1), 2);
    }

    sprite.setTextColor(TFT_WHITE);
    
    // // X axis samples.
    // for(uint16_t i = 0; i < 5; i++)
    // {
    //     string = String((GRAPH_WIDTH / 5) * (i + 1));
    //     sprite.drawRightString(string, X[0] + (GRAPH_WIDTH / 5) * (i + 1) + 6, HEIGHT - 15, 2);
    // }


    //sprite.drawRightString("SAMPLE TIME", WIDTH - 2, 2, 2);
    //string = String(System::SAMPLING_TIME) + " ms";
    //sprite.drawRightString(string, WIDTH - 2, 20, 2);
}




void GUI::draw_dotted_hline(uint16_t x1, uint16_t x2, uint16_t y, uint16_t length, uint16_t gap)
{
    uint16_t x = x1;

    while(true)
    {
        sprite.drawLine(x, y, x + length, y, TFT_WHITE);
        x += gap + length;
        if(x > x2){ return; }  
    }
}



void GUI::draw_dotted_vline(uint16_t y1, uint16_t y2, uint16_t x, uint16_t length, uint16_t gap)
{
    uint16_t y = y1;

    while(true)
    {
        sprite.drawLine(x, y, x, y + length, TFT_WHITE);
        y += gap + length;
        if(y > y2){ return; }  
    }
}