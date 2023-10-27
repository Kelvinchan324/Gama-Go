#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "1_Global.h"
#include "2_Colors.h"

//----------------------------------------------------------------------
#include <TFT_eWidget.h>               // Widget library

GraphWidget BMPgraph = GraphWidget(&tft);    // Graph widget

// Traces are drawn on tft using graph instance
TraceWidget tr3 = TraceWidget(&BMPgraph);    // Graph trace 3

void drawBMPgraph() 
{

  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  // Graph area is 217 pixels wide, 110 high, dark grey background
  BMPgraph.createGraph(217, 110, tft.color565(5, 5, 5));

  // x scale units is from 0 to 100, y scale units is -50 to 50
  BMPgraph.setGraphScale(0.0, 100.0, 900.0, 1025.0); 

  // X grid starts at 0 with lines every 10 x-scale units
  // Y grid starts at 0 with lines every 25 y-scale units
  // blue grid
  BMPgraph.setGraphGrid(0.0, 5.0, 900.0, 10.0, TFT_BLUE);  
  
  // Draw empty graph, top left corner at 40,10 on TFT
  BMPgraph.drawGraph(originX, originY); 

  // Start a trace with using red and another with green
  tr3.startTrace(TFT_BLUE);

  // Add points on graph to trace 1 using graph scale factors (Buttom Line)
  tr3.addPoint(0.0, 0.0);
  tr3.addPoint(100.0, 0.0);

  // Draw the y axis scale
  tft.setTextDatum(MR_DATUM); // Middle right text datum
  tft.drawNumber(900, BMPgraph.getPointX(0.0), BMPgraph.getPointY(900.0));
  tft.drawNumber(925, BMPgraph.getPointX(0.0), BMPgraph.getPointY(925.0));
  tft.drawNumber(950, BMPgraph.getPointX(0.0), BMPgraph.getPointY(950.0));
  tft.drawNumber(975, BMPgraph.getPointX(0.0), BMPgraph.getPointY(975.0));
  tft.drawNumber(1000, BMPgraph.getPointX(0.0), BMPgraph.getPointY(1000.0));
  tft.drawNumber(1025, BMPgraph.getPointX(0.0), BMPgraph.getPointY(1025.0));

  // Restart traces with new colours
  tr3.startTrace(TFT_RED);

}

void plotBMPgraph ()
{
    static uint32_t plotTime = millis();
    static float BMPx = 0.0, BMPy = 1000.0;

  // Sample periodically
  if (millis() - plotTime >= 100) {
    plotTime = millis();

    // Add a new point on each trace
    tr3.addPoint(BMPx, BMPy);


    // Create next plot point
    BMPx += 1.0;
    BMPy = BMPpressure;

    // If the end of the graph is reached start 2 new traces
    if (BMPx > 100.0) {
      BMPx = 0.0;

      // Draw empty graph at 40,10 on display
      BMPgraph.drawGraph(originX, originY);
      // Start new trace
      tr3.startTrace(TFT_RED);
    
    }
  }
}
