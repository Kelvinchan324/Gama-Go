#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "2_Colors.h"

//----------------------------------------------------------------------
#include <TFT_eWidget.h>               // Widget library

GraphWidget gr = GraphWidget(&tft);    // Graph widget

// Traces are drawn on tft using graph instance
TraceWidget tr1 = TraceWidget(&gr);    // Graph trace 1
TraceWidget tr2 = TraceWidget(&gr);    // Graph trace 2

int originX = 30;
int originY = 140;

void drawDHTgraph() 
{

  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  // Graph area is 270 pixels wide, 150 high, dark grey background
  gr.createGraph(270, 150, tft.color565(5, 5, 5));

  // x scale units is from 0 to 100, y scale units is -50 to 50
  gr.setGraphScale(0.0, 100.0, 0.0, 100.0); 

  // X grid starts at 0 with lines every 10 x-scale units
  // Y grid starts at 0 with lines every 25 y-scale units
  // blue grid
  gr.setGraphGrid(0.0, 5.0, 0.0, 10.0, TFT_BLUE);  
  
  // Draw empty graph, top left corner at 40,10 on TFT
  gr.drawGraph(originX, originY); 

  // Start a trace with using red and another with green
  tr1.startTrace(TFT_BLUE);

  // Add points on graph to trace 1 using graph scale factors (Buttom Line)
  tr1.addPoint(0.0, 0.0);
  tr1.addPoint(100.0, 0.0);

  // Draw the y axis scale
  tft.setTextDatum(MR_DATUM); // Middle right text datum
  tft.drawNumber(0, gr.getPointX(0.0), gr.getPointY(0.0));
  tft.drawNumber(25, gr.getPointX(0.0), gr.getPointY(25.0));
  tft.drawNumber(50, gr.getPointX(0.0), gr.getPointY(50.0));
  tft.drawNumber(75, gr.getPointX(0.0), gr.getPointY(75.0));
  tft.drawNumber(100, gr.getPointX(0.0), gr.getPointY(100.0));

  // Restart traces with new colours
  tr1.startTrace(TFT_RED);
  tr2.startTrace(TFT_SKYBLUE);
}

void plotDHTgraph ()
{
    static uint32_t plotTime = millis();
    static float TempX = 0.0, TempY = 0.0;
    static float RHx = 0.0, RHy = 0.0;

  // Sample periodically
  if (millis() - plotTime >= 100) {
    plotTime = millis();

    // Add a new point on each trace
    tr1.addPoint(TempX, TempY);
    tr2.addPoint(RHx, RHy); 

    // Create next plot point
    TempX += 1.0;
    TempY = DHTtemp;

    RHx += 1.0;
    RHy = DHThum;

    // If the end of the graph is reached start 2 new traces
    if (TempX > 100.0) {
      TempX = 0.0;
      //TempY = 0.0;

      RHx = 0.0;
      //RHy = 0.0;

      // Draw empty graph at 40,10 on display
      gr.drawGraph(originX, originY);
      // Start new trace
      tr1.startTrace(TFT_RED);
      tr2.startTrace(TFT_SKYBLUE);
    }
  }
}
