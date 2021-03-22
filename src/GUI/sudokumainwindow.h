#ifndef SUDOKUMAINWINDOW_H
#define SUDOKUMAINWINDOW_H

#include <QMainWindow>

#include "ISudokuMainWindow.h"
#include "sudoku.h"
//#include "qobject.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SudokuMainWindow; }
QT_END_NAMESPACE

class SudokuMainWindow : public QMainWindow, ISudokuMainWindow
{
    Q_OBJECT

public:
    SudokuMainWindow(QWidget *parent = nullptr);
    ~SudokuMainWindow();
	void fillView(std::array<std::array<short, 9>, 9>& grid, std::array<std::array<short, 9>, 9>& startingSudoku) override;
	void setIsValidLable(bool isValid) override;
	void setCellText(short row, short column, short number);
	void selectCell(short rowIndex, short columnIndex) override;
	void updateProgressBar(int) override;
	void processEvents() override;

private:
    Ui::SudokuMainWindow *ui;
	short currentRow = 0;
	short currentColumn = 0;
	Sudoku m_sudoku;
	void highlightSudokuPattern(unsigned short rowStart, unsigned short columnStart);
	void setEnableButtons(bool enabled);
	
signals:
	void pbSudokuClicked(unsigned short number);

private slots:
	void on_pb1_clicked();
	void on_pb2_clicked();
	void on_pb3_clicked();
	void on_pb4_clicked();
	void on_pb5_clicked();
	void on_pb6_clicked();
	void on_pb7_clicked();
	void on_pb8_clicked();
	void on_pb9_clicked();
	void on_pBEmpty_clicked();
	void on_pbCancel_clicked();

	void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void on_pbNewPuzzle_clicked();
	void on_pbSolve_clicked();
	void on_pbReset_clicked();
	void on_pbUndo_clicked();


};
#endif // SUDOKUMAINWINDOW_H
