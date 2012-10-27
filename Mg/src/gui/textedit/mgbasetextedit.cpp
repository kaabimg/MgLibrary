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
#include "mgbasetextedit.h"

#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QTextBlock>
#include <QPainter>
#include <QHash>
#include <QDebug>

#include <MgCore/MgFileManager>

#include "mgfoldingextraarea.h"
#include "mglinesnumbersextraarea.h"


struct MgBaseTextEditPrivate
{
	MgBaseTextEditPrivate():fileManager(NULL){}
	QString errorString;
	MgFileManager * fileManager;
	MgLinesNumbersExtraArea *linesNumbersArea;
	MgFoldingExtraArea * foldingArea;
	int baseLineNumber;
	int linesNumbersAreaToggleBlockNumber;
	QHash<int,int> hiddenBlocks;

};

//=================================================================================================

MgBaseTextEdit::MgBaseTextEdit(QWidget * parent):QPlainTextEdit(parent),
		d_ptr(new MgBaseTextEditPrivate)
{
	createContent();
}

MgBaseTextEdit::MgBaseTextEdit(MgFileManager * fileManager,QWidget * parent)
:QPlainTextEdit(parent),d_ptr(new MgBaseTextEditPrivate)
{
	d_ptr->fileManager = fileManager;
	d_ptr->fileManager->setParent(this);
	createContent();
}

MgBaseTextEdit::MgBaseTextEdit(const QString & fileName,QWidget * parent)
:QPlainTextEdit(parent),d_ptr(new MgBaseTextEditPrivate)
{
	d_ptr->fileManager = new MgFileManager(fileName,this);
	createContent();
}
void MgBaseTextEdit::createContent()
{
	d_ptr->baseLineNumber = 1;

	d_ptr->linesNumbersArea = new MgLinesNumbersExtraArea(this);

	d_ptr->foldingArea = new MgFoldingExtraArea(this);

	connect(this, SIGNAL(blockCountChanged(int)),
			this, SLOT(updateExtraAreaWidth()));
	connect(this, SIGNAL(updateRequest(QRect,int)),
			this, SLOT(updateExtraArea(QRect,int)));
	connect(this, SIGNAL(cursorPositionChanged()),
			this, SLOT(highlightCurrentLine()));


	connect(d_ptr->foldingArea,SIGNAL(highlightBlockRequest(int ,int))
			,this,SLOT(highlightBlock(int,int)));
	connect(d_ptr->foldingArea,SIGNAL(unHighlightRequest())
			,this,SLOT(unHighlightBlock()));
	connect(d_ptr->foldingArea,SIGNAL(foldingRequest(int ,int,bool))
			,this,SLOT(showOrHideBlocks(int,int,bool)));


	connect(this,SIGNAL(cursorPositionChanged()),
			this,SLOT(onCursorPositionChanged()));

	updateExtraAreaWidth();
}

MgBaseTextEdit::~MgBaseTextEdit()
{
	delete d_ptr;
}


//===============================================================================
void MgBaseTextEdit::updateFileManager(const QString & fileName)
{
	if(d_ptr->fileManager)
	{
		d_ptr->fileManager->setPath(fileName);
		Q_EMIT handledFileChanged(fileName);
	}
	else
	{
		d_ptr->fileManager = new MgFileManager(fileName,this);
		connect(d_ptr->fileManager,SIGNAL(),this,SLOT());
	}
}


QString MgBaseTextEdit::handledFile()const
{
	if(d_ptr->fileManager)
		return d_ptr->fileManager->path();
	return "";
}
QString MgBaseTextEdit::handledFileDirectory()const
{
	if(d_ptr->fileManager)
		return d_ptr->fileManager->parentDirectory();
	return "";

}

QString MgBaseTextEdit::errorString()const
{
	return d_ptr->errorString;
}


//****************************************************************
void MgBaseTextEdit::save()
{
	if(!d_ptr->fileManager)
	{
		saveAs();
		return;
	}
	if( ! d_ptr->fileManager->save(toPlainText()))
	{
		d_ptr->errorString = d_ptr->fileManager->errorString();
		QMessageBox::critical(this,"Error while saving "+d_ptr->fileManager->fileName(),
				d_ptr->errorString);
		Q_EMIT error();
	}

}
void MgBaseTextEdit::saveAs()
{
	QString filePath = QFileDialog::getOpenFileName(this,"Save as ...",
			d_ptr->fileManager ? d_ptr->fileManager->parentDirectory() : QApplication::applicationDirPath());

	if(filePath.isEmpty())
		return;

	updateFileManager(filePath);
	save();

}

void MgBaseTextEdit::onFileChanged()
{
	//TODO
}

//====================================================================================================
int MgBaseTextEdit::baseLineNumber() const
{
	return d_ptr->baseLineNumber;
}

void MgBaseTextEdit::setBaseLineNumber(int base)
{
	d_ptr->baseLineNumber = base;
	d_ptr->linesNumbersArea->update();
}


int MgBaseTextEdit::currentLineNumber() const
{
	return textCursor().blockNumber() + d_ptr->baseLineNumber;
}

void MgBaseTextEdit::gotoLine(int lineNumber)
{
	int blockNumber = lineNumber - d_ptr->baseLineNumber;
	const QTextBlock &block = document()->findBlockByNumber(blockNumber);
	if (block.isValid()) {
		setTextCursor(QTextCursor(block));
		centerCursor();
	}
}



void MgBaseTextEdit::paintEvent(QPaintEvent *e)
{
	QPlainTextEdit::paintEvent(e);
}

void MgBaseTextEdit::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();

	d_ptr->foldingArea->setGeometry(cr.left(),cr.top(), foldingAreaWidth(),cr.height());

	d_ptr->linesNumbersArea->setGeometry(cr.left()+foldingAreaWidth(),
			cr.top(), linesNumbersAreaWidth(),cr.height());
}

void MgBaseTextEdit::updateExtraAreaWidth()
{
	setViewportMargins(linesNumbersAreaWidth()+foldingAreaWidth()
			, 0, 0, 0);
}

void MgBaseTextEdit::updateExtraArea(const QRect &rect, int dy)
{
	if (dy)
		d_ptr->linesNumbersArea->scroll(0, dy);
	else
		d_ptr->linesNumbersArea->update(0, rect.y(), d_ptr->linesNumbersArea->width(), rect.height());
	if (dy)
		d_ptr->foldingArea->scroll(0, dy);
	else
		d_ptr->foldingArea->update(0, rect.y(), d_ptr->foldingArea->width(), rect.height());



	if (rect.contains(viewport()->rect()))
		updateExtraAreaWidth();
}

void MgBaseTextEdit::highlightCurrentLine()
{
	updateExtraSelections();
}

void MgBaseTextEdit::updateExtraSelections()
{
	QList<QTextEdit::ExtraSelection> extraSelections;
	QTextEdit::ExtraSelection selection;
	QColor lineColor = QColor("#70CFE4");
	lineColor.setAlpha(50);
	selection.format.setBackground(lineColor);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
	selection.cursor = textCursor();
	selection.cursor.clearSelection();
	extraSelections.append(selection);
	setExtraSelections(extraSelections);
}


int MgBaseTextEdit::linesNumbersAreaWidth()const
{
	int space = 0;
	const QFontMetrics fm(fontMetrics());

	int digits = 1;
	int max = qMax(1, blockCount() + d_ptr->baseLineNumber);
	while (max >= 10)
	{
		max /= 10;
		++digits;
	}
	space += fm.width(QLatin1Char('9')) * digits;

	space += 10;
	//    int markWidth = fm.lineSpacing();
	//    space += markWidth;

	return space;
}
int MgBaseTextEdit::foldingAreaWidth()const
{
	return 20;
}

/***************************************************************************************/


void MgBaseTextEdit::keyPressEvent(QKeyEvent* event)
{
	if(event->key()==Qt::Key_F && (event->modifiers()&Qt::ControlModifier))
	{
		Q_EMIT findRequest();
		qDebug()<<"in find";
		return;
	}

	QPlainTextEdit::keyPressEvent(event);

}


void MgBaseTextEdit::highlightBlock(int beginBlock,int endBlock)
{
	QList<QTextEdit::ExtraSelection> extraSelections;
	QTextEdit::ExtraSelection selection;
	QColor color = Qt::darkGray;
	color.setAlpha(50);
	selection.format.setBackground(color);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);

	QTextCursor originalCursor(textCursor());
	QTextCursor navigationCursor(originalCursor);

	if(navigationCursor.blockNumber()>0)

			navigationCursor.movePosition(QTextCursor::PreviousBlock,
				QTextCursor::MoveAnchor,navigationCursor.blockNumber());

	for(int i=0;i< beginBlock;++i)
	{
		selection.cursor =  navigationCursor;
		selection.cursor.clearSelection();
		extraSelections.append(selection);
		navigationCursor.movePosition(QTextCursor::NextBlock,
				QTextCursor::MoveAnchor,1);
	}


	if(endBlock<blockCount())
	{
		navigationCursor.movePosition(QTextCursor::NextBlock,
				QTextCursor::MoveAnchor,endBlock+1-navigationCursor.blockNumber());

		for(int i=endBlock+1;i< blockCount();++i)
		{
			selection.cursor =  navigationCursor;
			selection.cursor.clearSelection();
			extraSelections.append(selection);
			navigationCursor.movePosition(QTextCursor::NextBlock,
					QTextCursor::MoveAnchor,1);
		}
	}


	setExtraSelections(extraSelections);
}
void MgBaseTextEdit::unHighlightBlock()
{
	highlightCurrentLine();
}


///////////////////////////////////////////////////////////////////

void MgBaseTextEdit::showOrHideBlocks(int begin,int end,bool visible)
{
	QTextBlock block = document()->findBlockByNumber(begin);
	int position = block.position();
	int length(0);
	if(visible)
	{
		for (int i = 0; i <=  end-begin; ++i)
		{
			d_ptr->hiddenBlocks[block.blockNumber()]--;
			if(!d_ptr->hiddenBlocks[block.blockNumber()])
				block.setVisible(true);
			length+= block.length();
			block = block.next();
		}
	}
	else
	{
		for (int i = 0; i <=  end-begin; ++i)
		{
			if(!this->d_ptr->hiddenBlocks.contains(block.blockNumber()))
				d_ptr->hiddenBlocks.insert(block.blockNumber(),1);
			else
				d_ptr->hiddenBlocks[block.blockNumber()]++;

			block.setVisible(false);
			length+= block.length();
			block = block.next();
		}
	}



	document()->markContentsDirty(position,length);
}

void MgBaseTextEdit::onCursorPositionChanged()
{
	int blockNumber = textCursor().block().blockNumber();
	d_ptr->foldingArea->setCurrentFoldingArea(blockNumber);
}
