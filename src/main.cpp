#include "MainFrame.h"
#include "GamePanel.h"


class MyApp : public wxApp {
public:
    virtual bool OnInit() override;
};


bool MyApp::OnInit() {
    srand((unsigned int)time(NULL));
    SetProcessDPIAware();
    MainFrame* frame = new MainFrame("HitOrMiss", wxDefaultPosition, wxSize(825, 1010));
    frame->Show(true);
    return true;
}


wxIMPLEMENT_APP(MyApp);
