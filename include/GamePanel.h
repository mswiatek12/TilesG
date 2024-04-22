#pragma once
#include <iostream>
#include <ctime>
#include <wx/timer.h>
#include <wx/wxprec.h>
#include <wx/event.h>

wxDECLARE_EVENT(wxEVT_SCORE_UPDATED, wxCommandEvent);

class GamePanel : public wxPanel {
public:
    GamePanel(wxWindow* parent, wxPoint pos, wxSize size);

    void StartGame();                   //defines what will happen at the start(e.g start of the clock)
    void OnTimer(wxTimerEvent& event);  //applies a timer
    void OnPaint(wxPaintEvent& e);      //applies the following: DrawSquares -&- DrawTarger
    void DrawSquares(wxPaintDC& dc);    //draws the chart
    void DrawTarget(wxPaintDC& dc);     //draws the target square (black one)
    void OnClick(wxMouseEvent& e);      //defines what will happen once we click
    void UpdateScore();                 //simply(not really) updates the clock
    void ResetGame();
    void ResetTimer();

private:
    int score;              //score var
    int cell_width;         //just as name suggests
    int cell_height;        //just as name suggests
    int target_x1;           //just as name suggests
    int target_y1;           //just as name suggests
    int target_x2;           //just as name suggests
    int target_y2;           //just as name suggests
    wxTimer gameTimer;

    int timeLeft;           // in seconds
    int lastHitTime;        // store time of last successful hit
};
