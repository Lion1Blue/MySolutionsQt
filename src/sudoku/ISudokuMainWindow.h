#pragma once

class ISudokuMainWindow {
public:
	//virtual ~ISudokuMainWindow();
	virtual void fillView(std::array<std::array<short, 9>, 9>& grid, std::array<std::array<short, 9>, 9>& startingSudoku) = 0;
	virtual	void setIsValidLable(bool isValid) = 0;
	virtual void setCellText(short row, short column, short number) = 0;
	virtual void selectCell(short rowIndex, short columnIndex) = 0;
	virtual void updateProgressBar(int) = 0;
	virtual void processEvents() = 0;
};
