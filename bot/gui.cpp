#include <wx/wx.h>
#include "move.hpp"

class MyFrame : public wxFrame
{
public:
  MyFrame() : wxFrame(nullptr, wxID_ANY, "Autoclicker GUI", wxDefaultPosition, wxSize(300, 500))
  {
    auto *panel = new wxPanel(this);
    auto *sizer = new wxBoxSizer(wxVERTICAL);

    startXCtrl = new wxTextCtrl(panel, wxID_ANY);
    startYCtrl = new wxTextCtrl(panel, wxID_ANY);
    endXCtrl = new wxTextCtrl(panel, wxID_ANY);
    endYCtrl = new wxTextCtrl(panel, wxID_ANY);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Start X:"), 0, wxALL, 5);
    sizer->Add(startXCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Start Y:"), 0, wxALL, 5);
    sizer->Add(startYCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "End X:"), 0, wxALL, 5);
    sizer->Add(endXCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "End Y:"), 0, wxALL, 5);
    sizer->Add(endYCtrl, 0, wxALL | wxEXPAND, 5);

    auto *startBtn = new wxButton(panel, wxID_ANY, "Start");
    sizer->Add(startBtn, 0, wxALL | wxCENTER, 10);

    panel->SetSizer(sizer);

    startBtn->Bind(wxEVT_BUTTON, &MyFrame::OnStart, this);
  }

private:
  wxTextCtrl *startXCtrl, *startYCtrl, *endXCtrl, *endYCtrl;

  void OnStart(wxCommandEvent &)
  {
    long startX, startY, endX, endY;
    startXCtrl->GetValue().ToLong(&startX);
    startYCtrl->GetValue().ToLong(&startY);
    endXCtrl->GetValue().ToLong(&endX);
    endYCtrl->GetValue().ToLong(&endY);

    moveMouseSmooth(static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(endX), static_cast<int>(endY));
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
