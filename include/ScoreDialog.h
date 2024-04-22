#pragma once
#include <wx/wx.h>

class ScoreDialog : public wxDialog {
public:
    ScoreDialog(wxWindow* parent, int score);

private:
    void OnRestartButtonClick(wxCommandEvent& event);
    int finalScore;
};