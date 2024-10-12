////////////////////////////////////////////////
//    Author : AshGrey
//    Time   : 2024.1.27
//    Blog   : https://www.ashgrey-sagiri.top
////////////////////////////////////////////////

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "controlDefine.h"

extern int SPEED;
extern int COUNT;
extern int SCORE;

class TetrisApp : public wxApp {
    public:
        virtual bool OnInit() {
            if (!wxApp::OnInit())
                return false;
            wxInitAllImageHandlers();
            TetrisMainFrame* mainFrame = new TetrisMainFrame(wxT("Tetris"));
            (*mainFrame).Show();
            (*mainFrame).SetWindowStyle(wxDEFAULT_FRAME_STYLE
                                        & ~(wxMAXIMIZE_BOX)
                                        & ~(wxRESIZE_BORDER));
            return true;
        };
        std::string mAppname = "Tetris";
};
wxIMPLEMENT_APP(TetrisApp);
wxDECLARE_APP(TetrisApp);


// -----------------------------------------
//    BlockModule
// -----------------------------------------

BlockModule::BlockModule(const int t) : type(t) {
    x = 5;
    y = 0;
    switch (t) {
        case 1 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = true; isBlock[0][3]  = false;        // ..#.
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = true; isBlock[1][3]  = false;        // ..#.
            isBlock[2][0]  = false; isBlock[2][1]  = false; isBlock[2][2]  = true; isBlock[2][3]  = false;        // ..#.
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = true; isBlock[3][3]  = false;        // ..#.
            break;
        case 2 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = true;  isBlock[1][1]  = true;  isBlock[1][2]  = true;  isBlock[1][3]  = true;         // ####
            isBlock[2][0]  = false; isBlock[2][1]  = false; isBlock[2][2]  = false; isBlock[2][3]  = false;        // ....
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = false; isBlock[3][3]  = false;        // ....
            break;
        case 3 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = true;  isBlock[1][3]  = false;        // .##.
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // .##.
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = false; isBlock[3][3]  = false;        // ....
            break;
        case 4 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = false; isBlock[1][3]  = false;        // ....
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // .##.
            isBlock[3][0]  = true;  isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // ##..
            break;
        case 5 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = false; isBlock[1][3]  = false;        // .#..
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // .##.
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = true;  isBlock[3][3]  = false;        // ..#.
            break;
        case 6 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = false; isBlock[1][3]  = false;        // ....
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = false; isBlock[2][3]  = false;        // ##..
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = true;  isBlock[3][3]  = false;        // .##.
            break;
        case 7 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = true;  isBlock[1][3]  = false;        // ..#.
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // .##.
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // .#..
            break;
        case 8 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = false; isBlock[1][3]  = false;        // ....
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // ###.
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = true;  isBlock[3][3]  = false;        // ..#.
            break;
        case 9 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = true;  isBlock[1][3]  = false;        // .##.
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = false; isBlock[2][3]  = false;        // .#..
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // .#..
            break;
        case 10 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = true;  isBlock[1][1]  = false; isBlock[1][2]  = false; isBlock[1][3]  = false;        // #...
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // ###.
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = false; isBlock[3][3]  = false;        // ....
            break;
        case 11 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = false; isBlock[1][3]  = false;        // .#..
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = false; isBlock[2][3]  = false;        // .#..
            isBlock[3][0]  = true;  isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // ##..
            break;
        case 12 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = false; isBlock[1][3]  = false;        // ....
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // ###.
            isBlock[3][0]  = true;  isBlock[3][1]  = false; isBlock[3][2]  = false; isBlock[3][3]  = false;        // #...
            break;
        case 13 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = false; isBlock[1][3]  = false;        // .#..
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = false; isBlock[2][3]  = false;        // .#..
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = true;  isBlock[3][3]  = false;        // .##.
            break;
        case 14 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = true;  isBlock[1][3]  = false;        // ..#.
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // ###.
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = false; isBlock[3][3]  = false;        // ....
            break;
        case 15 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = true;  isBlock[1][1]  = true;  isBlock[1][2]  = false; isBlock[1][3]  = false;        // ##..
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = false; isBlock[2][3]  = false;        // .#..
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // .#..
            break;
        case 16 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = false; isBlock[1][3]  = false;        // ....
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // ###.
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // .#..
            break;
        case 17 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = false; isBlock[1][3]  = false;        // .#..
            isBlock[2][0]  = false; isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // .##.
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // .#..
            break;
        case 18 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = false; isBlock[1][3]  = false;        // .#..
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = true;  isBlock[2][3]  = false;        // ###.
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = false; isBlock[3][3]  = false;        // ....
            break;
        case 19 :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = true;  isBlock[1][2]  = false; isBlock[1][3]  = false;        // .#..
            isBlock[2][0]  = true;  isBlock[2][1]  = true;  isBlock[2][2]  = false; isBlock[2][3]  = false;        // ##..
            isBlock[3][0]  = false; isBlock[3][1]  = true;  isBlock[3][2]  = false; isBlock[3][3]  = false;        // .#..
            break;
        default :
            isBlock[0][0]  = false; isBlock[0][1]  = false; isBlock[0][2]  = false; isBlock[0][3]  = false;        // ....
            isBlock[1][0]  = false; isBlock[1][1]  = false; isBlock[1][2]  = false; isBlock[1][3]  = false;        // ....
            isBlock[2][0]  = false; isBlock[2][1]  = false; isBlock[2][2]  = false; isBlock[2][3]  = false;        // ....
            isBlock[3][0]  = false; isBlock[3][1]  = false; isBlock[3][2]  = false; isBlock[3][3]  = false;        // ....
            break;
    }
}

BlockModule::BlockModule(const BlockModule& bm) {
    type = bm.type;
    x = bm.x;
    y = bm.y;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++)
            isBlock[i - 1][j - 1] = bm.isBlock[i - 1][j - 1];
    }
}

BlockModule& BlockModule::operator = (const BlockModule& bm) {
    if (this == &bm)
        return *this;
    type = bm.type;
    x = bm.x;
    y = bm.y;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++)
            isBlock[i - 1][j - 1] = bm.isBlock[i - 1][j - 1];
    }
    return *this;
}

// -----------------------------------------
//    TetrisGamePanel : wxPanel
// -----------------------------------------

wxBEGIN_EVENT_TABLE(TetrisGamePanel, wxPanel)
    EVT_BUTTON(TETRIS_START, TetrisGamePanel::OnStartGame)
    EVT_TIMER(TETRIS_TIMER, TetrisGamePanel::OnTimerUpdated)
    EVT_BUTTON(TETRIS_RESTART, TetrisGamePanel::OnRestartGame)
    EVT_BUTTON(TETRIS_QUIT, TetrisGamePanel::OnQuit)
wxEND_EVENT_TABLE()

TetrisGamePanel::TetrisGamePanel(wxWindow* parent)
    : wxPanel(parent, TETRIS_GAMEPANEL, wxDefaultPosition, wxSize(300, 610)) {
    (*startButton).Create(this, TETRIS_START,
                          wxT("START GAME!"),
                          wxPoint(100, 230), wxSize(100, 50));
    (*restartButton).Create(this, TETRIS_RESTART,
                            wxT("RESTART"),
                            wxPoint(100, 230), wxSize(100, 50));
    (*quitButton).Create(this, TETRIS_QUIT,
                         wxT("QUIT"), 
                         wxPoint(100, 300), wxSize(100, 50));
    (*startButton).SetForegroundColour(wxColour(255, 255, 255));
    (*startButton).SetBackgroundColour(wxColour(0, 0, 0));
    (*restartButton).SetForegroundColour(wxColour(255, 255, 255));
    (*restartButton).SetBackgroundColour(wxColour(0, 0, 0));
    (*quitButton).SetForegroundColour(wxColour(255, 255, 255));
    (*quitButton).SetBackgroundColour(wxColour(0, 0, 0));
    (*restartButton).Show(false);
    (*quitButton).Show(false);
}

inline void TetrisGamePanel::OnStartGame(wxCommandEvent& event) {
    (*startButton).Show(false);
    wxClientDC clientdc(this);
    clientdc.SetClippingRegion(wxPoint(0, 0), wxSize(300, 600));
    wxBufferedDC dc(&clientdc);
    dc.SetPen(wxColour(100, 100, 100));
    dc.SetBrush(wxColour(0, 0, 0));

    // FUNCTION: Initialize
    for (int i = 1; i <= 23; i++) {
        blockGroup[i - 1][0].type = 2;
        blockGroup[i - 1][11].type = 2;
    }

    for (int i = 1; i <= 12; i++)
        blockGroup[23][i - 1].type = 2;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 10; j++)
            blockGroup[i - 1][j].type = 0;
    }

    for (int i = 4; i <= 23; i++) {
        for (int j = 1; j <= 10; j++) {
            blockGroup[i - 1][j].type = 0;
            blockGroup[i - 1][j].rect.SetX(30 * (j - 1));
            blockGroup[i - 1][j].rect.SetY(30 * (i - 4));
            blockGroup[i - 1][j].rect.SetWidth(30);
            blockGroup[i - 1][j].rect.SetHeight(30);
            dc.DrawRectangle(blockGroup[i - 1][j].rect);
        }
    }
    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
    GenerateBlock();
    (*mainFrame).nextBlockUpdate();
    (*timer).Start();
}

inline void TetrisGamePanel::OnTimerUpdated(wxTimerEvent& event) {
    COUNT++;
    wxClientDC clientdc(this);
    clientdc.SetClippingRegion(wxPoint(0, 0), wxSize(300, 600));
    wxBufferedDC dc(&clientdc);
    dc.SetPen(wxColour(100, 100, 100));
    dc.SetBrush(wxColour(0, 0, 0));

    // FUNCTION: Clear the last BlockModule

    for (int i = 1; i <= 23; i++) {
        for (int j = 1; j <= 10; j++) {
            if (blockGroup[i - 1][j].type == 1)
                blockGroup[i - 1][j].type = 0;
        }
    }

    // FUNCTION: Calculate the position of each part of BlockModule object

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if ((*currentBlock).isBlock[i - 1][j - 1]) {
                int tempX = (*currentBlock).x + j - 1;
                int tempY = (*currentBlock).y + i - 1;
                blockGroup[tempY][tempX].type = 1;
            }
        }
    }

    // FUNCTION: Draw the three kinds of blocks

    for (int i = 4; i <= 23; i++) {
        for (int j = 1; j <= 10; j++) {
            switch (blockGroup[i - 1][j].type) {
                case 0 :
                    dc.SetBrush(wxColour(0, 0, 0));
                    dc.DrawRectangle(blockGroup[i - 1][j].rect);
                    break;
                case 1 :
                    dc.SetBrush(wxColour(200, 191, 231));
                    dc.DrawRectangle(blockGroup[i - 1][j].rect);
                    break;
                case 2 :
                    dc.SetBrush(wxColour(200, 200, 200));
                    dc.DrawRectangle(blockGroup[i - 1][j].rect);
                    break;
            }
        }
    }

    // FUNCTION: Call the DownCheck to decide if the BlockModule will go down

    if (COUNT >= 50 / SPEED) {
        if (DownCheck()) {
            (*currentBlock).y++;
        }
        else {
            for (int i = 1; i <= 4; i++) {
                for (int j = 1; j <= 4; j++) {
                    int tempX = (*currentBlock).x + j - 1;
                    int tempY = (*currentBlock).y + i - 1;
                    if (blockGroup[tempY][tempX].type == 1)
                        blockGroup[tempY][tempX].type = 2;
                }
            }
            ClearBlock();
            GenerateBlock();
            (*mainFrame).scoreShowUpdate();
            (*mainFrame).nextBlockUpdate();
        }
        COUNT = 0;
    }

    // FUNCTION: Check function

    if (!LoseCheck()) {
        (*timer).Stop();
        for (int i = 1; i <= 24; i++) {
            for (int j = 1; j <= 12; j++) {
                blockGroup[i - 1][j - 1].type = 0;
            }
        }
        (*currentBlock).type = -1;
        (*nextBlock).type = -1;
        wxMessageBox(wxT("Game Over! Your score is ") + wxString::Format(wxT("%i"), SCORE));
        dc.Clear();
        (*restartButton).Show(true);
        (*quitButton).Show(true);
        firstGenerate = true;
    }
}

inline void TetrisGamePanel::OnRestartGame(wxCommandEvent& event) {
    wxCommandEvent start(wxEVT_BUTTON, TETRIS_START);
    OnStartGame(start);
    (*restartButton).Show(false);
    (*quitButton).Show(false);
    SCORE = 0;
    (*mainFrame).scoreShowUpdate();
}

inline void TetrisGamePanel::OnQuit(wxCommandEvent& event) {
    wxGetApp().Exit();
}

void TetrisGamePanel::GenerateBlock() {
    srand(time(nullptr));
    int min = 1;
    int max = 19;
    int random = (rand() % (max - min + 1)) + min;
    currentBlock = nextBlock;
    if (firstGenerate) {
        int random = (rand() % (max - min + 1)) + min;
        BlockModule* tempBlock = new BlockModule(random);
        currentBlock = tempBlock;
        firstGenerate = false;
    }
    BlockModule* tempBlock = new BlockModule(random);
    nextBlock = tempBlock;
}

void TetrisGamePanel::ClearBlock() {
    bool Line[20];
    for (int i = 1; i <= 20; i++) {
        Line[i - 1] = true;
    }

    // FUNCTION: To check the line that need to be cleared

    for (int i = 4; i <= 23; i++) {
        for (int j = 1; j <= 10; j++) {
            if (blockGroup[i - 1][j].type == 0)
                Line[i - 4] = false;
        }
    }

    // FUNCTION: Clear the lines

    for (int i = 20; i >= 1; ) {
        if (Line[i - 1] == true) {
            for (int j = i + 3; j >= 4; j--) {
                for (int k = 1; k <= 10; k++)
                    blockGroup[j - 1][k].type = blockGroup[j - 2][k].type;
            }
            for (int u = i; u >= 2; u--)
                Line[u - 1] = Line[u - 2];
            Line[0] = false;
            SCORE++;
        }
        else {
            i--;
            // FUNCTION: When Line[i - 1] = true, we need i to keep its value
        }
    }
}

bool TetrisGamePanel::LoseCheck() {
    for (int i = 1; i <= 10; i++) {
        if (blockGroup[3][i].type == 2)
            return false;
    }
    return true;
}

bool TetrisGamePanel::DownCheck() {
    Point check[4];
    int checkNotEmpty = 0;

    // FUNCTION: To get the down check block position

    for (int i = 1; i <= 4; i++) {
        check[i - 1] = { 0, 0 };
        for (int j = 1; j <= 4; j++) {
            if ((*currentBlock).isBlock[j - 1][i - 1])
                check[i - 1] = { i, j };
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (check[i - 1].x != 0 && check[i - 1].y != 0) {
            checkNotEmpty = i - 1;
            break;
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (check[i - 1].x == 0 && check[i - 1].y == 0) {
            check[i - 1].x = check[checkNotEmpty].x;
            check[i - 1].y = check[checkNotEmpty].y;
        }
    }

    for (int i = 1; i <= 4; i++) {
        int tempX = (*currentBlock).x + check[i - 1].x - 1;
        int tempY = (*currentBlock).y + check[i - 1].y - 1;
        tempY++;
        if (blockGroup[tempY][tempX].type == 2)
            return false;
    }
    return true;
}

bool TetrisGamePanel::LeftCheck() {
    Point check[4];
    int checkNotEmpty = 0;

    // FUNCTION: To get the left check block position

    for (int i = 1; i <= 4; i++) {
        check[i - 1] = { 0, 0 };
        for (int j = 4; j >= 1; j--) {
            if ((*currentBlock).isBlock[i - 1][j - 1])
                check[i - 1] = { j, i };
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (check[i - 1].x != 0 && check[i - 1].y != 0) {
            checkNotEmpty = i - 1;
            break;
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (check[i - 1].x == 0 && check[i - 1].y == 0)
            check[i - 1] = check[checkNotEmpty];
    }

    for (int i = 1; i <= 4; i++) {
        int tempX = (*currentBlock).x + check[i - 1].x - 1;
        int tempY = (*currentBlock).y + check[i - 1].y - 1;
        tempX--;
        if (blockGroup[tempY][tempX].type == 2)
            return false;
    }
    return true;
}

bool TetrisGamePanel::RightCheck() {
    Point check[4];
    int checkNotEmpty = 0;

    // FUNCTION: To get the right check block position

    for (int i = 1; i <= 4; i++) {
        check[i - 1] = { 0, 0 };
        for (int j = 1; j <= 4; j++) {
            if ((*currentBlock).isBlock[i - 1][j - 1])
                check[i - 1] = { j, i };
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (check[i - 1].x != 0 && check[i - 1].y != 0) {
            checkNotEmpty = i - 1;
            break;
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (check[i - 1].x == 0 && check[i - 1].y == 0)
            check[i - 1] = check[checkNotEmpty];
    }

    for (int i = 1; i <= 4; i++) {
        int tempX = (*currentBlock).x + check[i - 1].x - 1;
        int tempY = (*currentBlock).y + check[i - 1].y - 1;
        tempX++;
        if (blockGroup[tempY][tempX].type == 2)
            return false;
    }
    return true;
}

bool TetrisGamePanel::RotateCheck(int t) {
    BlockModule* rotateBlock = new BlockModule(t);
    (*rotateBlock).x = (*currentBlock).x;
    (*rotateBlock).y = (*currentBlock).y;

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            int tempX = (*rotateBlock).x + j - 1;
            int tempY = (*rotateBlock).y + i - 1;
            if (tempX < 1 || tempX > 11 || 
                ((*rotateBlock).isBlock[i - 1][j - 1] == true &&
                blockGroup[tempY][tempX].type == 2)
                )
                return false;
        }
    }
    delete rotateBlock;
    return true;
}

// -----------------------------------------
//    TetrisMainFrame : wxFrame
// -----------------------------------------

wxBEGIN_EVENT_TABLE(TetrisMainFrame, wxFrame)
    EVT_BUTTON(TETRIS_LEFT, TetrisMainFrame::OnLeftMove)
    EVT_BUTTON(TETRIS_RIGHT, TetrisMainFrame::OnRightMove)
    EVT_BUTTON(TETRIS_DOWN, TetrisMainFrame::OnDownSpeed)
    EVT_BUTTON(TETRIS_UP, TetrisMainFrame::OnUpRotate)
    EVT_BUTTON(TETRIS_PAUSE, TetrisMainFrame::OnPause)
    EVT_BUTTON(TETRIS_QUIT, TetrisMainFrame::OnQuit)
wxEND_EVENT_TABLE()

TetrisMainFrame::TetrisMainFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 630)) {
    (*this).Center();
    (*gamePanel).SetBackgroundColour(wxColour(40, 40, 40));
    (*gamePanel).SetFocus();
    (*gamePanel).getMainFrame(this);
    (*gameBarPanel).Create(this, wxID_ANY, 
                           wxDefaultPosition, wxSize(100, 630));
    (*gameBarPanel).SetBackgroundColour(wxColour(120, 120, 120));
    wxFont font(24, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    (*scoreShow).Create(gameBarPanel, wxID_ANY,
                        wxEmptyString, wxPoint(15, 120), wxSize(65, 20), wxALIGN_RIGHT);
    (*scoreShow).SetFont(font);
    (*scoreShow).SetLabel(wxString::Format(wxT("%i"), SCORE));
    (*nextBlockShow).Create(gameBarPanel, wxID_ANY,
                            wxPoint(0, 0), wxSize(100, 100));
    (*pauseButton).Create(gameBarPanel, TETRIS_PAUSE,
                          wxT("PAUSE"), wxPoint(15, 170), wxSize(70, 50));
    (*pauseButton).SetForegroundColour(wxColour(255, 255, 255));
    (*pauseButton).SetBackgroundColour(wxColour(0, 0, 0));
    (*quitButton).Create(gameBarPanel, TETRIS_QUIT,
                         wxT("QUIT"), wxPoint(15, 210), wxSize(70, 50));
    (*quitButton).SetForegroundColour(wxColour(255, 255, 255));
    (*quitButton).SetBackgroundColour(wxColour(0, 0, 0));
    wxImage downImage;
    downImage.LoadFile(wxT("resource/down.png"), wxBITMAP_TYPE_ANY);
    downImage.Rescale(25, 25);
    wxBitmap* downBitmap = new wxBitmap(downImage);
    (*downButton).Create(gameBarPanel, TETRIS_DOWN,
                         *downBitmap,
                         wxPoint(25, 400), wxSize(50, 50));
    wxImage leftImage;
    leftImage.LoadFile(wxT("resource/left.png"), wxBITMAP_TYPE_ANY);
    leftImage.Rescale(25, 25);
    wxBitmap* leftBitmap = new wxBitmap(leftImage);
    (*leftButton).Create(gameBarPanel, TETRIS_LEFT,
                         *leftBitmap,
                         wxPoint(0, 350), wxSize(50, 50));
    wxImage rightImage;
    rightImage.LoadFile(wxT("resource/right.png"), wxBITMAP_TYPE_ANY);
    rightImage.Rescale(25, 25);
    wxBitmap* rightBitmap = new wxBitmap(rightImage);
    (*rightButton).Create(gameBarPanel, TETRIS_RIGHT,
                          *rightBitmap,
                          wxPoint(50, 350), wxSize(50, 50));
    wxImage upImage;
    upImage.LoadFile(wxT("resource/up.png"), wxBITMAP_TYPE_ANY);
    upImage.Rescale(25, 25);
    wxBitmap* upBitmap = new wxBitmap(upImage);
    (*upButton).Create(gameBarPanel, TETRIS_UP,
                       *upBitmap,
                       wxPoint(25, 300), wxSize(50, 50));

    (*mainSizer).Add(gamePanel);
    (*mainSizer).Add(gameBarPanel);
    (*this).SetSizer(mainSizer);
}

inline void TetrisMainFrame::OnLeftMove(wxCommandEvent& event) {
    if ((*gamePanel).LeftCheck() == true)
        (*gamePanel).currentBlockCallback().x--;
}

inline void TetrisMainFrame::OnRightMove(wxCommandEvent& event) {
    if ((*gamePanel).RightCheck() == true)
        (*gamePanel).currentBlockCallback().x++;
}

inline void TetrisMainFrame::OnDownSpeed(wxCommandEvent& event) {
    SPEED = (SPEED == 1) ? 2 : 1;
}

inline void TetrisMainFrame::OnUpRotate(wxCommandEvent& event) {
    int rotate;
    int tempX;
    int tempY;
    switch ((*gamePanel).currentBlockCallback().type) {
        case 1 :
            rotate = 2;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 2 :
            rotate = 1;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 3 :
            rotate = 3;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 4 :
            rotate = 5;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 5 :
            rotate = 4;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 6 :
            rotate = 7;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 7 :
            rotate = 6;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 8 :
            rotate = 9;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 9 :
            rotate = 10;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 10 :
            rotate = 11;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 11 :
            rotate = 8;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 12 :
            rotate = 13;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 13 :
            rotate = 14;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 14 :
            rotate = 15;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 15 :
            rotate = 12;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 16 :
            rotate = 17;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 17 :
            rotate = 18;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 18 :
            rotate = 19;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
        case 19 :
            rotate = 16;
            if ((*gamePanel).RotateCheck(rotate)) {
                tempX = (*gamePanel).currentBlockCallback().x;
                tempY = (*gamePanel).currentBlockCallback().y;
                BlockModule* rotateBlock = new BlockModule(rotate);
                (*gamePanel).currentBlockCallback() = *rotateBlock;
                (*gamePanel).currentBlockCallback().x = tempX;
                (*gamePanel).currentBlockCallback().y = tempY;
            }
            break;
    }
}

inline void TetrisMainFrame::OnPause(wxCommandEvent& event) {
    switch ((*gamePanel).timerCallback().IsRunning()) {
        case true :
            (*gamePanel).timerCallback().Stop();
            (*leftButton).Disable();
            (*rightButton).Disable();
            (*upButton).Disable();
            (*downButton).Disable();
            break;
        case false :
            (*gamePanel).timerCallback().Start();
            (*leftButton).Enable();
            (*rightButton).Enable();
            (*upButton).Enable();
            (*downButton).Enable();
            break;
    }
}

inline void TetrisMainFrame::OnQuit(wxCommandEvent& event) {
    wxGetApp().Exit();
}

void TetrisMainFrame::scoreShowUpdate() {
    (*scoreShow).SetLabel(wxString::Format(wxT("%i"), SCORE));
}

void TetrisMainFrame::nextBlockUpdate() {
    wxClientDC nextdc(nextBlockShow);
    nextdc.SetClippingRegion(wxPoint(0, 0), wxSize(100, 100));
    wxBufferedDC dc(&nextdc);
    dc.SetPen(wxColour(100, 100, 100));
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            wxRect rect(25 * (j - 1), 25 * (i - 1), 25, 25);
            switch ((*gamePanel).nextBlockCallback().isBlock[i - 1][j - 1]) {
                case false :
                    dc.SetBrush(wxColour(0, 0, 0));
                    dc.DrawRectangle(rect);
                    break;
                case true :
                    dc.SetBrush(wxColour(200, 200, 200));
                    dc.DrawRectangle(rect);
                    break;
            }
        }
    }
}
