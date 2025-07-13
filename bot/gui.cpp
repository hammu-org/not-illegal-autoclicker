#include "gui.hpp"
#include "emergency_stop_panel.hpp"
#include "interval_panel.hpp"

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Not Illegal Autoclicker", wxDefaultPosition, wxSize(400, 600))
{
  SetMinSize(wxSize(400, 600));
  auto *panel = new wxPanel(this);
  auto *mainSizer = new wxBoxSizer(wxVERTICAL);

  wxFont fontBold(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

  // Emergency Stop Panel
  emergencyStopPanel = new EmergencyStopPanel(panel);
  mainSizer->Add(emergencyStopPanel, 0, wxALL | wxEXPAND, 16);

  // Interval Panel
  intervalPanel = new IntervalPanel(panel);
  mainSizer->Add(intervalPanel, 0, wxALL | wxEXPAND, 16);

  auto *quitBtn = new wxButton(panel, wxID_EXIT, "Quit");
  quitBtn->SetMinSize(wxSize(0, 40));
  mainSizer->Add(quitBtn, 0, wxALL | wxEXPAND, 16);
  quitBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &)
                { Close(true); });
  // --- Add Debug Button ---
  auto *debugBtn = new wxButton(panel, wxID_ANY, "System Info");
  debugBtn->SetMinSize(wxSize(0, 40));
  mainSizer->Add(debugBtn, 0, wxALL | wxEXPAND, 8);
  debugBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &)
                 {
    wxString info;
    info << "wxWidgets version: " << wxVERSION_STRING << "\n";
    info << "Build: " << wxGetOsDescription() << "\n";
    info << "Build date: " << __DATE__ << " " << __TIME__ << "\n";
    info << "Working dir: " << wxGetCwd() << "\n";
    info << "User: " << wxGetUserName() << "\n";
    info << "Computer: " << wxGetHostName() << "\n";
    // Add your own screen bounds info
    ScreenRect bounds = getScreenBounds();
    info << wxString::Format("Screen bounds: left=%d top=%d right=%d bottom=%d\n", bounds.left, bounds.top, bounds.right, bounds.bottom);
    wxMessageBox(info, "System Info", wxOK | wxICON_INFORMATION, this); });

  /// Set the main sizer for the panel
  panel->SetSizer(mainSizer);

  // Register F13 on Windows, F12 on Mac/others for start/stop clicking
#ifdef __WXMSW__
  // On Windows, use VK_F13 (0x7C) and MOD_NOREPEAT
  RegisterHotKey(ID_HOTKEY_F12, MOD_NOREPEAT, 0x7C);
#else
  // On Mac and others, use WXK_F12 and no modifier
  RegisterHotKey(ID_HOTKEY_F12, wxMOD_NONE, WXK_F12);
#endif
  Bind(wxEVT_HOTKEY, &MyFrame::OnHotkey, this, ID_HOTKEY_F12);
  Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);

  // Bind mouse left down event to update cursor position label
  panel->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseLeftDown, this);
}

void MyFrame::OnClick(wxCommandEvent &)
{
  // Get and display cursor position on click
  wxPoint pos = wxGetMousePosition();
  intervalPanel->SetCursorPosLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
  StartClickLoop();
}

void MyFrame::OnHotkey(wxKeyEvent &)
{
  // Get and display cursor position on hotkey
  wxPoint pos = wxGetMousePosition();
  intervalPanel->SetCursorPosLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
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
    intervalPanel->SetClickStatusLabel("Click Status: Clicking...");

    // Start click loop in a new thread to avoid blocking UI
    std::thread([this]()
                {
      long baseInterval = intervalPanel->GetTotalMilliseconds();
      if (baseInterval < 1) baseInterval = 1;

      // Emergency stop duration
      long stopDuration = emergencyStopPanel->GetTotalMilliseconds();
      if (stopDuration < 1) stopDuration = 120000; // fallback to 2 min
      auto startTime = std::chrono::steady_clock::now();

      // Setup randomizer for 7user-selected offset in ms
      std::random_device rd;
      std::mt19937 gen(rd());
      int offsetRange = intervalPanel->GetRandomOffsetMs();
      std::uniform_int_distribution<int> dist(-offsetRange, offsetRange);

      while (isClicking)
      {
        // Emergency stop check
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
        if (elapsed >= stopDuration) {
          isClicking = false;
          break;
        }
        long targetX = 0, targetY = 0;
        intervalPanel->GetTarget(targetX, targetY);

        // Get current mouse position
        MyPoint current = getCurrentMousePos();
        int origX = current.x;
        int origY = current.y;
        // int origX = randomOffset(current.x, 5);
        // int origY = randomOffset(current.y, 10);
        // Clamp to screen
        clampToScreen(origX, origY);

        // Move from original to target, aborts if isClicking is set false
        moveMouseSmooth(static_cast<int>(origX), static_cast<int>(origY), static_cast<int>(targetX), static_cast<int>(targetY), &isClicking);

        // Ensure mouse is at target before clicking
        wxTheApp->CallAfter([this, targetX, targetY]() {
          intervalPanel->SetCursorPosLabel(wxString::Format("X: %ld  Y: %ld", targetX, targetY));
        });
        wxMilliSleep(15);
        leftClick();

        moveMouseSmoothReturn(static_cast<int>(targetX), static_cast<int>(targetY), static_cast<int>(origX), static_cast<int>(origY), &isClicking);
        if (intervalPanel->IsReturnClickEnabled()) {
          wxMilliSleep(15);
          leftClick();
        }
        int randomized = baseInterval + dist(gen);
        if (randomized < 1) randomized = 1;
        wxMilliSleep(randomized);


        // Optionally, move back to original (if you want a round-trip loop)
        // moveMouseSmooth(static_cast<int>(targetX), static_cast<int>(targetY), static_cast<int>(origX), static_cast<int>(origY), &isClicking);
      }
      wxTheApp->CallAfter([this]() {
        isClicking = false;
        intervalPanel->SetClickStatusLabel("Click Status: Idle");
      }); })
        .detach();
  }
}

void MyFrame::StopClickLoop()
{
  isClicking = false;
  intervalPanel->SetClickStatusLabel("Click Status: Idle");
}

void MyFrame::OnClose(wxCloseEvent &event)
{
  UnregisterHotKey(MyFrame::ID_HOTKEY_F12);
  event.Skip();
}

void MyFrame::OnMouseLeftDown(wxMouseEvent &event)
{
  wxPoint pos = wxGetMousePosition();
  intervalPanel->SetCursorPosLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
  event.Skip();
}
