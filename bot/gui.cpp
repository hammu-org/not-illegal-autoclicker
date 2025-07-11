#include <wx/wx.h>
#include <wx/event.h>
#include <wx/statline.h>
#include "move.hpp"

class MyFrame : public wxFrame
{
public:
  enum
  {
    ID_HOTKEY_F12 = wxID_HIGHEST + 1
  };
  MyFrame();
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnClick(wxCommandEvent &);
  void OnF10Hotkey(wxKeyEvent &);
  void OnClose(wxCloseEvent &event);
  void StartClickLoop();
  void StopClickLoop();

private:
  wxTextCtrl *intervalMinCtrl, *intervalSecCtrl, *intervalMsCtrl;
  wxTextCtrl *originalXCtrl, *originalYCtrl;
  wxTextCtrl *targetXCtrl, *targetYCtrl;
  wxStaticText *clickStatusLabel;
  wxStaticText *offsetLabel;
  wxSlider *offsetSlider;
  wxStaticText *cursorPosLabel; // New label for cursor position
  bool isClicking = false;
  int randomOffsetMs = 200;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Autoclicker GUI", wxDefaultPosition, wxSize(500, 500))
{
  auto *panel = new wxPanel(this);
  auto *mainSizer = new wxBoxSizer(wxVERTICAL);

  // Cursor position display section
  auto *cursorPosBox = new wxStaticBox(panel, wxID_ANY, "Cursor Position (on Click)");
  auto *cursorPosSizer = new wxStaticBoxSizer(cursorPosBox, wxVERTICAL);
  cursorPosLabel = new wxStaticText(panel, wxID_ANY, "X: -  Y: -");
  cursorPosSizer->Add(cursorPosLabel, 0, wxALL | wxEXPAND, 8);
  mainSizer->Add(cursorPosSizer, 0, wxALL | wxEXPAND, 16);

  intervalMinCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalSecCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalMsCtrl = new wxTextCtrl(panel, wxID_ANY, "0");

  wxFont fontBold(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

  // Group: Click Interval
  auto *intervalBox = new wxStaticBox(panel, wxID_ANY, "Click Interval");
  auto *intervalSizer = new wxStaticBoxSizer(intervalBox, wxVERTICAL);

  // Interval controls
  auto *intervalGrid = new wxFlexGridSizer(1, 6, 10, 10);
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
  intervalSizer->Add(intervalGrid, 0, wxALL | wxEXPAND, 8);

  // Divider before original position
  auto *origDivider = new wxStaticLine(panel, wxID_ANY);
  intervalSizer->Add(origDivider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8);

  // Original position controls
  auto *origGrid = new wxFlexGridSizer(1, 4, 10, 10);
  auto *lblOriginalX = new wxStaticText(panel, wxID_ANY, "Original X:");
  lblOriginalX->SetFont(fontBold);
  originalXCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  auto *lblOriginalY = new wxStaticText(panel, wxID_ANY, "Original Y:");
  lblOriginalY->SetFont(fontBold);
  originalYCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  origGrid->Add(lblOriginalX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  origGrid->Add(originalXCtrl, 1, wxEXPAND | wxRIGHT, 8);
  origGrid->Add(lblOriginalY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  origGrid->Add(originalYCtrl, 1, wxEXPAND | wxRIGHT, 8);
  origGrid->AddGrowableCol(1, 1);
  origGrid->AddGrowableCol(3, 1);
  intervalSizer->Add(origGrid, 0, wxALL | wxEXPAND, 8);

  // Divider before target position
  auto *divider = new wxStaticLine(panel, wxID_ANY);
  intervalSizer->Add(divider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8);

  // Target controls
  auto *targetGrid = new wxFlexGridSizer(1, 4, 10, 10);
  auto *lblTargetX = new wxStaticText(panel, wxID_ANY, "Target X:");
  lblTargetX->SetFont(fontBold);
  targetXCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  auto *lblTargetY = new wxStaticText(panel, wxID_ANY, "Target Y:");
  lblTargetY->SetFont(fontBold);
  targetYCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  targetGrid->Add(lblTargetX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  targetGrid->Add(targetXCtrl, 1, wxEXPAND | wxRIGHT, 8);
  targetGrid->Add(lblTargetY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  targetGrid->Add(targetYCtrl, 1, wxEXPAND | wxRIGHT, 8);
  targetGrid->AddGrowableCol(1, 1);
  targetGrid->AddGrowableCol(3, 1);
  intervalSizer->Add(targetGrid, 0, wxALL | wxEXPAND, 8);

  // Add random offset slider and label (ms)
  auto *offsetSizer = new wxBoxSizer(wxHORIZONTAL);
  offsetLabel = new wxStaticText(panel, wxID_ANY, "Random Offset (ms): 200");
  offsetSlider = new wxSlider(panel, wxID_ANY, 200, 0, 2000, wxDefaultPosition, wxSize(160, -1));
  offsetSizer->Add(offsetLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  offsetSizer->Add(offsetSlider, 1, wxALIGN_CENTER_VERTICAL);
  intervalSizer->Add(offsetSizer, 0, wxALL | wxEXPAND, 8);
  offsetSlider->Bind(wxEVT_SLIDER, [this](wxCommandEvent &evt)
                     {
    randomOffsetMs = offsetSlider->GetValue();
    offsetLabel->SetLabel(wxString::Format("Random Offset (ms): %d", randomOffsetMs)); });

  clickStatusLabel = new wxStaticText(panel, wxID_ANY, "Click Status: Idle");
  wxFont clickStatusFont = fontBold;
  clickStatusFont.SetPointSize(11);
  clickStatusLabel->SetFont(clickStatusFont);
  intervalSizer->Add(clickStatusLabel, 0, wxALL | wxEXPAND, 6);
  auto *clickHotkeyLabel = new wxStaticText(panel, wxID_ANY, "Hotkey: F12 to Start/Stop Clicking");
  wxFont clickHotkeyFont = fontBold;
  clickHotkeyFont.SetPointSize(9);
  clickHotkeyLabel->SetFont(clickHotkeyFont);
  intervalSizer->Add(clickHotkeyLabel, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
  mainSizer->Add(intervalSizer, 0, wxALL | wxEXPAND, 16);

  auto *quitBtn = new wxButton(panel, wxID_EXIT, "Quit");
  quitBtn->SetMinSize(wxSize(0, 40));
  mainSizer->Add(quitBtn, 0, wxALL | wxEXPAND, 16);
  quitBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &)
                { Close(true); });

  panel->SetSizer(mainSizer);

  RegisterHotKey(ID_HOTKEY_F12, wxMOD_NONE, WXK_F12);
  Bind(wxEVT_HOTKEY, &MyFrame::OnF10Hotkey, this, ID_HOTKEY_F12);
  Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);

  // Bind mouse left down event to update cursor position label
  panel->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseLeftDown, this);
}

void MyFrame::OnClick(wxCommandEvent &)
{
  // Get and display cursor position on click
  wxPoint pos = wxGetMousePosition();
  cursorPosLabel->SetLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
  StartClickLoop();
}

void MyFrame::OnF10Hotkey(wxKeyEvent &)
{
  // Get and display cursor position on hotkey
  wxPoint pos = wxGetMousePosition();
  cursorPosLabel->SetLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
  if (isClicking)
    StopClickLoop();
  else
    StartClickLoop();
}

void MyFrame::StartClickLoop()
{
  if (!isClicking)
  {
    isClicking = true;
    clickStatusLabel->SetLabel("Click Status: Clicking...");

    // Start click loop in a new thread to avoid blocking UI
    std::thread([this]()
                {
      long min = 0, sec = 0, ms = 0;
      intervalMinCtrl->GetValue().ToLong(&min);
      intervalSecCtrl->GetValue().ToLong(&sec);
      intervalMsCtrl->GetValue().ToLong(&ms);
      long baseInterval = min * 60000 + sec * 1000 + ms;
      if (baseInterval < 1) baseInterval = 1;

      // Setup randomizer for ±user-selected offset in ms
      std::random_device rd;
      std::mt19937 gen(rd());
      int offsetRange = randomOffsetMs;
      std::uniform_int_distribution<int> dist(-offsetRange, offsetRange);

      while (isClicking)
      {
        long origX = 0, origY = 0, targetX = 0, targetY = 0;
        originalXCtrl->GetValue().ToLong(&origX);
        originalYCtrl->GetValue().ToLong(&origY);
        targetXCtrl->GetValue().ToLong(&targetX);
        targetYCtrl->GetValue().ToLong(&targetY);


        // Move from original to target
        moveMouseSmooth(static_cast<int>(origX), static_cast<int>(origY), static_cast<int>(targetX), static_cast<int>(targetY));

        // Wait until the mouse is at (or very near) the target before clicking
        int waitCount = 0;
        const int maxWait = 100; // up to 1 second (10ms * 100)
        while (waitCount < maxWait) {
          wxPoint pos = wxGetMousePosition();
          if (std::abs(pos.x - targetX) <= 2 && std::abs(pos.y - targetY) <= 2) break;
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
          ++waitCount;
        }

        wxTheApp->CallAfter([this, targetX, targetY]() {
          cursorPosLabel->SetLabel(wxString::Format("X: %ld  Y: %ld", targetX, targetY));
        });
        leftClick();

        int randomized = baseInterval + dist(gen);
        if (randomized < 1) randomized = 1;
        wxMilliSleep(randomized);

        // Optionally, move back to original (if you want a round-trip loop)
        // moveMouseSmooth(static_cast<int>(targetX), static_cast<int>(targetY), static_cast<int>(origX), static_cast<int>(origY));
      }
      wxTheApp->CallAfter([this]() {
        isClicking = false;
        clickStatusLabel->SetLabel("Click Status: Idle");
      }); })
        .detach();
  }
}

void MyFrame::StopClickLoop()
{
  isClicking = false;
  clickStatusLabel->SetLabel("Click Status: Idle");
}

void MyFrame::OnClose(wxCloseEvent &event)
{
  UnregisterHotKey(MyFrame::ID_HOTKEY_F12);
  event.Skip();
}

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

void MyFrame::OnMouseLeftDown(wxMouseEvent &event)
{
  wxPoint pos = wxGetMousePosition();
  cursorPosLabel->SetLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
  event.Skip();
}
