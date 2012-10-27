/*************************************************************************
** 
** Copyright 2011 Mohamed-Ghaïth KAABI (mohamedghaith.kaabi@gmail.com)
** This file is part of MgLibrary.
** 
** MgLibrary is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** any later version.
** 
** MgLibrary is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with MgLibrary.  If not, see <http://www.gnu.org/licenses/>.
** 
****************************************************************************/
#ifndef MGBASETEXTEDIT_H_
#define MGBASETEXTEDIT_H_

//MG_INCLUDE_INFO:MgBaseTextEdit

#include <QPlainTextEdit>
#include <MgCore/MgGlobal>

class MgFileManager;

MG_USE_PRIVATE_CLASS(MgBaseTextEdit)

class MgBaseTextEdit : public QPlainTextEdit
{
	Q_OBJECT
public:
	MgBaseTextEdit(QWidget * parent=0);
	MgBaseTextEdit(MgFileManager * fileManager,QWidget * parent=0);
	MgBaseTextEdit(const QString & fileName,QWidget * parent=0);

	virtual ~MgBaseTextEdit();

	QString errorString()const;

	QString handledFile()const;
	QString handledFileDirectory()const;


public Q_SLOTS:
	void save();
	void saveAs();

	void showOrHideBlocks(int,int,bool);

Q_SIGNALS:
	void error();
	void handledFileChanged(const QString&);
	void findRequest();

protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent*);

private Q_SLOTS:
	void onFileChanged();

    void updateExtraAreaWidth();
    void updateExtraArea(const QRect &, int);
    void highlightCurrentLine();

    virtual void highlightBlock(int,int);
    void unHighlightBlock();

    void onCursorPositionChanged();


private:
	Q_DISABLE_COPY(MgBaseTextEdit)
	MG_PRIVATE_CLASS(MgBaseTextEdit)

	friend class MgLinesNumbersExtraArea;
	friend class MgFoldingExtraArea;

	void createContent();
	void updateFileManager(const QString &);

	QTextEdit::ExtraSelection currentLineSelection() const;
    QTextEdit::ExtraSelection currentExecutionLineSelection() const;
    void updateExtraSelections();

    int baseLineNumber() const;
    void setBaseLineNumber(int base);
    int currentLineNumber() const;
    void gotoLine(int lineNumber);


    int linesNumbersAreaWidth()const;
    int foldingAreaWidth()const;

};

#endif /* MGBASETEXTEDIT_H_ */
