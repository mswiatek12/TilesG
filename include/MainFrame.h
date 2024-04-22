#pragma once
#include "GamePanel.h"
wxDECLARE_EVENT(wxEVT_TIMER_UPDATE, wxCommandEvent);

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void InitializeInterface();
    void UpdateScoreLabel(int newScore);
    void OnScoreUpdated(wxCommandEvent& event);
    void OnExit(wxCloseEvent& e);
    void UpdateTimerDisplay(wxCommandEvent& event);
    void OnRestartGame(wxCommandEvent& event);

private:
    GamePanel* gamePanel;
    wxStaticText* scoreLabel;
    wxStaticText* timerLabel;
};