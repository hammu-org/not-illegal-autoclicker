#include <wx/wx.h>
#include "move.hpp"

class MyFrame : public wxFrame
{
public:
  MyFrame() : wxFrame(nullptr, wxID_ANY, "Autoclicker GUI", wxDefaultPosition, wxSize(500, 500))
  {
    auto *panel = new wxPanel(this);
    auto *mainSizer = new wxBoxSizer(wxVERTICAL);

    startXCtrl = new wxTextCtrl(panel, wxID_ANY);
    startYCtrl = new wxTextCtrl(panel, wxID_ANY);
    endXCtrl = new wxTextCtrl(panel, wxID_ANY);
    endYCtrl = new wxTextCtrl(panel, wxID_ANY);
    intervalMinCtrl = new wxTextCtrl(panel, wxID_ANY);
    intervalSecCtrl = new wxTextCtrl(panel, wxID_ANY);
    intervalMsCtrl = new wxTextCtrl(panel, wxID_ANY);

    wxFont fontBold(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    // Group: Mouse Movement (top)
    auto *moveBox = new wxStaticBox(panel, wxID_ANY, "Mouse Movement");
    auto *moveSizer = new wxStaticBoxSizer(moveBox, wxVERTICAL);
    auto *moveGrid = new wxFlexGridSizer(2, 4, 12, 12); // 2 rows, 4 cols, more spacing
    auto *lblStartX = new wxStaticText(panel, wxID_ANY, "Start X:");
    lblStartX->SetFont(fontBold);
    auto *lblStartY = new wxStaticText(panel, wxID_ANY, "Start Y:");
    lblStartY->SetFont(fontBold);
    auto *lblEndX = new wxStaticText(panel, wxID_ANY, "End X:");
    lblEndX->SetFont(fontBold);
    auto *lblEndY = new wxStaticText(panel, wxID_ANY, "End Y:");
    lblEndY->SetFont(fontBold);
    moveGrid->Add(lblStartX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    moveGrid->Add(startXCtrl, 1, wxEXPAND | wxRIGHT, 12);
    moveGrid->Add(lblEndX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    moveGrid->Add(endXCtrl, 1, wxEXPAND);
    moveGrid->Add(lblStartY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    moveGrid->Add(startYCtrl, 1, wxEXPAND | wxRIGHT, 12);
    moveGrid->Add(lblEndY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    moveGrid->Add(endYCtrl, 1, wxEXPAND);
    moveGrid->AddGrowableCol(1);
    moveGrid->AddGrowableCol(3);
    moveSizer->Add(moveGrid, 1, wxALL | wxEXPAND, 12);
    auto *moveBtn = new wxButton(panel, wxID_ANY, "Move Mouse");
    moveBtn->SetMinSize(wxSize(0, 40));
    moveSizer->Add(moveBtn, 0, wxALL | wxEXPAND, 10);
    mainSizer->Add(moveSizer, 0, wxALL | wxEXPAND, 16);

    // Group: Click Interval (bottom)
    auto *intervalBox = new wxStaticBox(panel, wxID_ANY, "Click Interval");
    auto *intervalSizer = new wxStaticBoxSizer(intervalBox, wxVERTICAL);
    auto *intervalGrid = new wxFlexGridSizer(1, 6, 10, 10); // 1 row, 6 cols
    auto *lblMin = new wxStaticText(panel, wxID_ANY, "Min:");
    lblMin->SetFont(fontBold);
    auto *lblSec = new wxStaticText(panel, wxID_ANY, "Sec:");
    lblSec->SetFont(fontBold);
    auto *lblMs = new wxStaticText(panel, wxID_ANY, "Ms:");
    lblMs->SetFont(fontBold);
    intervalGrid->Add(lblMin, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
    intervalGrid->Add(intervalMinCtrl, 1, wxEXPAND | wxRIGHT, 8);
    intervalGrid->Add(lblSec, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
    intervalGrid->Add(intervalSecCtrl, 1, wxEXPAND | wxRIGHT, 8);
    intervalGrid->Add(lblMs, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
    intervalGrid->Add(intervalMsCtrl, 1, wxEXPAND);
    intervalGrid->AddGrowableCol(1, 1);
    intervalGrid->AddGrowableCol(3, 1);
    intervalGrid->AddGrowableCol(5, 1);
    intervalSizer->Add(intervalGrid, 0, wxALL | wxEXPAND, 12);
    auto *clickBtn = new wxButton(panel, wxID_ANY, "Start Clicking");
    clickBtn->SetMinSize(wxSize(0, 40));
    intervalSizer->Add(clickBtn, 0, wxALL | wxEXPAND, 10);
    mainSizer->Add(intervalSizer, 0, wxALL | wxEXPAND, 16);

    panel->SetSizer(mainSizer);

    moveBtn->Bind(wxEVT_BUTTON, &MyFrame::OnMove, this);
    clickBtn->Bind(wxEVT_BUTTON, &MyFrame::OnClick, this);
  }

private:
  wxTextCtrl *startXCtrl, *startYCtrl, *endXCtrl, *endYCtrl;
  wxTextCtrl *intervalMinCtrl, *intervalSecCtrl, *intervalMsCtrl;

  void OnMove(wxCommandEvent &)
  {
    long startX, startY, endX, endY;
    startXCtrl->GetValue().ToLong(&startX);
    startYCtrl->GetValue().ToLong(&startY);
    endXCtrl->GetValue().ToLong(&endX);
    endYCtrl->GetValue().ToLong(&endY);
    moveMouseSmooth(static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(endX), static_cast<int>(endY));
    wxLogMessage("Mouse moved from (%ld, %ld) to (%ld, %ld)", startX, startY, endX, endY);
  }

  void OnClick(wxCommandEvent &)
  {
    long min = 0, sec = 0, ms = 0;
    intervalMinCtrl->GetValue().ToLong(&min);
    intervalSecCtrl->GetValue().ToLong(&sec);
    intervalMsCtrl->GetValue().ToLong(&ms);
    long interval = min * 60000 + sec * 1000 + ms;
    performClickLoop(interval);
  }

  void performClickLoop(long interval)
  {
    // Perform 10 clicks at the current mouse position, with the specified interval
    for (int i = 0; i < 10; ++i)
    {
      leftClick();
      wxMilliSleep(interval);
    }
    wxLogMessage("Clicked 10 times at interval: %ld ms", interval);
  }
};

class MyApp : public wxApp
{
public:
  bool OnInit() override
  {
    auto *frame = new MyFrame();
    frame->Show();
    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
