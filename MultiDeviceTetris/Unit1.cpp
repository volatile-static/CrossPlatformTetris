// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

const TAlphaColor SpaceColor(0xFFE0E0E0);
TAlphaColor CurrentColor;
double BlockSize;
TForm1 *Form1;
TRectangle *Blocks[SizeY][SizeX];
TCmd Messenger;

void Update() {
    for (int i(0); i < Messenger.cnt[0]; ++i)
	Blocks[Messenger.Erase[i].Y][Messenger.Erase[i].X]->Fill->Color =
	    SpaceColor;
    for (int i(0); i < Messenger.cnt[1]; ++i)
	Blocks[Messenger.Paint[i].Y][Messenger.Paint[i].X]->Fill->Color =
	    CurrentColor;
}

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
    srand(time(0));
    for (int i(0); i < SizeY; ++i)
	for (int j(0); j < SizeX; ++j) {
	    Blocks[i][j] = new TRectangle(TetrisLayout);
	    Blocks[i][j]->Stroke->Kind = Graphics::TBrushKind::None;
	    Blocks[i][j]->Parent = TetrisLayout;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::GameTimerTimer(TObject *Sender) {
    if (!MoveDown(&Messenger)) {
	switch (rand() % 6) {
	case 0:
	    CurrentColor = TAlphaColorRec::Green;
	    break;
	case 1:
	    CurrentColor = TAlphaColorRec::Black;
	    break;
	case 2:
	    CurrentColor = TAlphaColorRec::Yellowgreen;
	    break;
	case 3:
	    CurrentColor = TAlphaColorRec::Brown;
	    break;
	case 4:
	    CurrentColor = TAlphaColorRec::Blue;
	    break;
	case 5:
	    CurrentColor = TAlphaColorRec::Red;
	    break;
	default: ;
	}
	Update();
	return;
    }
    if (GameOver()) {
	for (int i(0); i < SizeX; ++i)
	    for (int j(0); j < SizeY; ++j)
		Blocks[i][j]->Fill->Color = SpaceColor;
	NewGame(&Messenger);
    }
    Update();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender) {
    BlockSize = std::min(TetrisLayout->Width / SizeX,
	TetrisLayout->Height / SizeY);
    for (int i(0); i < SizeY; ++i)
	for (int j(0); j < SizeX; ++j) {
	    Blocks[i][j]->Width = BlockSize;
	    Blocks[i][j]->Height = BlockSize;
	    Blocks[i][j]->Position->Y = i * BlockSize;
	    Blocks[i][j]->Position->X = j * BlockSize;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::sbLeftClick(TObject *Sender) {
    MoveLeft(&Messenger);
    Update();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::sbRightClick(TObject *Sender) {
    MoveRight(&Messenger);
    Update();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::sbUpClick(TObject *Sender) {
    Transform(&Messenger);
    Update();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::InitButtonClick(TObject *Sender) {
    NewGame(&Messenger);
    Update();
    GameTimer->Enabled = true;
    InitButton->Enabled = false;
    sbUp->Enabled = true;
    sbLeft->Enabled = true;
    sbRight->Enabled = true;
    sbDown->Enabled = true;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
    System::WideChar &KeyChar, TShiftState Shift) {
    if (!GameTimer->Enabled)
	return;
    if (Key == 37 || tolower(KeyChar) == 'a')
	MoveLeft(&Messenger);
    if (Key == 39 || tolower(KeyChar) == 'd')
	MoveRight(&Messenger);
    if (Key == 38 || tolower(KeyChar) == 'w')
	Transform(&Messenger);
    if (Key == 40 || tolower(KeyChar) == 's')
	for (int i(0); ++i < 20 && MoveDown(&Messenger); Update());
    Update();
}
// ---------------------------------------------------------------------------
