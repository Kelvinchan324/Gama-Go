#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "1_Global.h"
#include "2_Colors.h"

//----------------------------------------------------------------------
#include <TFT_eWidget.h>               // Widget library

GraphWidget DoseGraph = GraphWidget(&tft);    // Graph widget

// Traces are drawn on tft using graph instance
TraceWidget tr4 = TraceWidget(&DoseGraph);    // Graph trace 3

void drawDoseGraph() 
{

  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  // Graph area is 270 pixels wide, 150 high, dark grey background
  DoseGraph.createGraph(270, 150, tft.color565(5, 5, 5));

  // x scale units is from 0 to 100, y scale units is -50 to 50
  DoseGraph.setGraphScale(0.0, 100.0, 0.0, 2.0); 

  // X grid starts at 0 with lines every 10 x-scale units
  // Y grid starts at 0 with lines every 25 y-scale units
  // blue grid
  DoseGraph.setGraphGrid(0.0, 10.0, 0.0, 1, TFT_BLUE);  
  
  // Draw empty graph, top left corner at 40,10 on TFT
  DoseGraph.drawGraph(originX, originY); 

  // Start a trace with using red and another with green
  tr4.startTrace(TFT_BLUE);

  // Add points on graph to trace 1 using graph scale factors (Buttom Line)
  tr4.addPoint(0.0, 0.0);
  tr4.addPoint(100.0, 0.0);

  // Draw the y axis scale
  tft.setTextDatum(MR_DATUM); // Middle right text datum
  tft.drawNumber(0.0, DoseGraph.getPointX(0.0), DoseGraph.getPointY(0.0));

  tft.drawNumber(1.0, DoseGraph.getPointX(0.0), DoseGraph.getPointY(1.0));
  tft.drawNumber(2.0, DoseGraph.getPointX(0.0), DoseGraph.getPointY(2.0));

  // Restart traces with new colours
  tr4.startTrace(TFT_RED);

}

void plotDoseGraph ()
{
    static uint32_t plotTime = millis();
    static float DoseX = 0.0, DoseY = 0.1;

  // Sample periodically
  if (millis() - plotTime >= 100) {
    plotTime = millis();

    // Add a new point on each trace
    tr4.addPoint(DoseX, DoseY);


    // Create next plot point
    DoseX += 1.0;
    DoseY = MinuteDoseRate;

    // If the end of the graph is reached start 2 new traces
    if (DoseX > 100.0) {
      DoseX = 0.0;

      // Draw empty graph at 40,10 on display
      DoseGraph.drawGraph(originX, originY);
      // Start new trace
      tr4.startTrace(TFT_RED);
    
    }
  }
}
