#include "MainFrame.h"

wxDEFINE_EVENT(wxEVT_TIMER_UPDATE, wxCommandEvent);

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
    SetTitle(_("TilesG"));
    this->SetBackgroundColour(wxColour(1, 50, 32));
    SetIcon(wxNullIcon);
    SetMinSize(size);
    SetMaxSize(size);
    InitializeInterface();
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnExit, this);
    Bind(wxEVT_SCORE_UPDATED, &MainFrame::OnScoreUpdated, this);
    Bind(wxEVT_TIMER_UPDATE, &MainFrame::UpdateTimerDisplay, this);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnRestartGame, this);
}

void MainFrame::InitializeInterface() {

    scoreLabel = new wxStaticText(this, wxID_ANY, "Score: 0", wxPoint(300, 60), wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    wxFont font = scoreLabel->GetFont();
    font.SetPointSize(30);
    scoreLabel->SetFont(font);
    scoreLabel->SetForegroundColour(wxColour(*wxWHITE));


    gamePanel = new GamePanel(this, wxPoint(12, 178), wxSize(780, 780));


    timerLabel = new wxStaticText(this, wxID_ANY, "Time: 30", wxPoint(15, 30), wxDefaultSize, wxALIGN_LEFT);
    wxFont timerFont = timerLabel->GetFont();
    timerFont.SetPointSize(14);
    timerLabel->SetFont(timerFont);
    timerLabel->SetForegroundColour(wxColour(*wxWHITE));
}

void MainFrame::UpdateScoreLabel(int newScore) {
    wxString scoreText = wxString::Format("Score: %d", newScore);
    scoreLabel->SetLabel(scoreText);
}

void MainFrame::OnScoreUpdated(wxCommandEvent& event) {
    int newScore = event.GetInt();
    UpdateScoreLabel(newScore);
}

void MainFrame::UpdateTimerDisplay(wxCommandEvent& event) {
    int secondsLeft = event.GetInt();
    timerLabel->SetLabel(wxString::Format("Time: %d", secondsLeft));
}

void MainFrame::OnRestartGame(wxCommandEvent& event) {
    gamePanel->ResetGame();
    Refresh();
}

void MainFrame::OnExit(wxCloseEvent& e) {
    if (wxMessageDialog(this, "Do you want to exit?", "Confirm", wxOK | wxCANCEL).ShowModal() == wxID_OK) {
        Destroy();
    }
    else {
        e.Veto();
    }
}