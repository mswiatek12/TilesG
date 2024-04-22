#include "ScoreDialog.h"

ScoreDialog::ScoreDialog(wxWindow* parent, int score)
    : wxDialog(parent, wxID_ANY, _("Game Over"), wxDefaultPosition, wxSize(250, 150)), finalScore(score) {
    new wxStaticText(this, wxID_ANY, wxString::Format("Final Score: %d", finalScore),
        wxPoint(10, 10), wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

    wxButton* restartButton = new wxButton(this, wxID_ANY, _("Restart"), wxPoint(75, 50));
    Bind(wxEVT_BUTTON, &ScoreDialog::OnRestartButtonClick, this, restartButton->GetId());
}


void ScoreDialog::OnRestartButtonClick(wxCommandEvent& event) {
    Close();
    wxCommandEvent restartEvent(wxEVT_COMMAND_BUTTON_CLICKED);
    wxPostEvent(GetParent(), restartEvent);
}