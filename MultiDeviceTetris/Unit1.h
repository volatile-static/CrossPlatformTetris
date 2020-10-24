//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Tetris.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <random>
#include <ctime>
#include <algorithm>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *GameTimer;
	TPanel *Panel1;
	TButton *InitButton;
	TLayout *Layout1;
	TSpeedButton *sbDown;
	TSpeedButton *sbLeft;
	TSpeedButton *sbRight;
	TSpeedButton *sbUp;
	TLayout *TetrisLayout;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall GameTimerTimer(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall sbLeftClick(TObject *Sender);
	void __fastcall sbRightClick(TObject *Sender);
	void __fastcall sbUpClick(TObject *Sender);
	void __fastcall InitButtonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
