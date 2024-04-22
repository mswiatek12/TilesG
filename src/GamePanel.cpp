#include "GamePanel.h"
#include "MainFrame.h"
#include "ScoreDialog.h"

wxDEFINE_EVENT(wxEVT_SCORE_UPDATED, wxCommandEvent);

GamePanel::GamePanel(wxWindow* parent, wxPoint pos, wxSize size)
    : wxPanel(parent, wxID_ANY, pos, size), score(0), cell_width(195), cell_height(195),  timeLeft(30), lastHitTime(0){
    target_x1 = rand() % 4 * cell_width;
    target_y1 = rand() % 4 * cell_height;
    target_x2 = rand() % 4 * cell_width;
    target_y2 = rand() % 4 * cell_height;
    Bind(wxEVT_PAINT, &GamePanel::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GamePanel::OnClick, this);
    gameTimer.Bind(wxEVT_TIMER, &GamePanel::OnTimer, this);
    gameTimer.Start(1000);
    srand(time(NULL));
}

void GamePanel::ResetGame() {
    gameTimer.Stop();
    score = 0;
    timeLeft = 30;
    gameTimer.Start(1000);
    Refresh();
}

void GamePanel::OnPaint(wxPaintEvent& e) {
    wxPaintDC dc(this);
    DrawSquares(dc);
    DrawTarget(dc);
}


void GamePanel::DrawSquares(wxPaintDC& dc) {
    dc.SetPen(*wxGREY_PEN);
    dc.SetBrush(*wxWHITE_BRUSH);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dc.DrawRectangle(j * cell_width, i * cell_height, cell_width, cell_height);
        }
    }
}

void GamePanel::DrawTarget(wxPaintDC& dc) {
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawRectangle(target_x1, target_y1, cell_width, cell_height);
    dc.DrawRectangle(target_x2, target_y2, cell_width, cell_height);
}

void GamePanel::OnClick(wxMouseEvent& e) {
    wxPoint pos = e.GetPosition();
    if (pos.x >= target_x1 && pos.x <= target_x1 + cell_width &&
        pos.y >= target_y1 && pos.y <= target_y1 + cell_height) {
        UpdateScore();
        target_x1 = rand() % 4 * cell_width;
        target_y1 = rand() % 4 * cell_height;
    }
    if (target_x2 == target_x1 && target_y2 == target_y1) {
        target_x2 = rand() % 4 * cell_width;
        target_y2 = rand() % 4 * cell_height;
    }
    else if (pos.x >= target_x2 && pos.x <= target_x2 + cell_width &&
        pos.y >= target_y2 && pos.y <= target_y2 + cell_height) {
        UpdateScore();
        target_x2 = rand() % 4 * cell_width;
        target_y2 = rand() % 4 * cell_height;
        if(target_x2 == target_x1 && target_y2 == target_y1) { 
            target_x2 = rand() % 4 * cell_width;
            target_y2 = rand() % 4 * cell_height;
        }
    }
    Refresh();
}


void GamePanel::UpdateScore() {
    int currentTime = std::time(0);
    if (currentTime - lastHitTime <= 0.15) { // 0.15 seconds threshold for multiplier
        score += 2; // Double points for quick successive hits
    }
    else {
        score++;
    }
    lastHitTime = currentTime;
    wxCommandEvent event(wxEVT_SCORE_UPDATED);
    event.SetInt(score);
    wxPostEvent(GetParent(), event);
}

void GamePanel::StartGame() {
    timeLeft = 30;          // game lasts for 30 seconds
    gameTimer.Start(1000); // timer ticks every second
}

void GamePanel::ResetTimer() {
    timeLeft = 30;  // Reset the time left to the initial value.
    gameTimer.Start(1000); // Restart the timer with a standard interval.
}



void GamePanel::OnTimer(wxTimerEvent& event) {
    if (timeLeft > 0) {
        timeLeft--;
    }
    if (timeLeft == 0) {
        gameTimer.Stop();
        ScoreDialog* dialog = new ScoreDialog(GetParent(), score);
        dialog->ShowModal();
        delete dialog;
        ResetTimer();
    }
    else {
        wxCommandEvent timerEvent(wxEVT_TIMER_UPDATE);
        timerEvent.SetInt(timeLeft);
        wxPostEvent(GetParent(), timerEvent); // Post the timer update to the parent.
    }
}