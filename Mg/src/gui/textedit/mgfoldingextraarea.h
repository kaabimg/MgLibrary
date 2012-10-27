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
#ifndef MGFOLDINGEXTRAAREA_H_
#define MGFOLDINGEXTRAAREA_H_
#include <QWidget>
#include <QList>
#include <QSet>
#include <QDebug>
class MgBaseTextEdit;
class MgFoldingExtraArea : public QWidget
{
	Q_OBJECT

	struct FoldingArea
	{
		FoldingArea(int b,int e):begin(b),end(e),isExpanded(true){}
		FoldingArea():begin(-1),end(-1),isExpanded(true){}
		bool isValid(){return begin>-1 && end >-1;}

		bool contains(int line)const
		{
			return begin<=line && end>= line;
		}
		bool contains(const FoldingArea & another)const
		{
			return begin<=another.begin && end>= another.end;
		}

		bool operator==(const FoldingArea & another)const
		{
			return begin==another.begin && end== another.end;
		}

		void addSubFoldingArea(const FoldingArea & area)
		{
			for (int i = 0; i < subFoldingAreas.size(); ++i)
				if(subFoldingAreas[i].contains(area))
				{
					subFoldingAreas[i].addSubFoldingArea(area);
					return;
				}
			subFoldingAreas<<area;
		}

		FoldingArea * findLine(int line)
		{
			if(!isExpanded)
				return this;

			for (int i = 0; i < subFoldingAreas.size(); ++i)
				if(subFoldingAreas[i].contains(line))
					return subFoldingAreas[i].findLine(line);

			return this;
		}

		int begin,end;
		bool isExpanded;
		QList<FoldingArea> subFoldingAreas;
	};

public:

	MgFoldingExtraArea(MgBaseTextEdit *edit);
    QSize sizeHint() const ;

public Q_SLOTS:
	void clearFoldingAreas();
	void addFoldingArea(int begin,int end);
	void setCurrentFoldingArea(int block);

Q_SIGNALS:
	void highlightBlockRequest(int ,int);
	void unHighlightRequest();

	void foldingRequest(int begin,int end,bool visible);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void drawFoldingMarker(QPainter*,const QRect &, bool) const;
    void drawFoldingAreaMarker(QPainter *,const FoldingArea &);
    void drawFoldingAreaLimiters(QPainter *,const FoldingArea &);

    QRect rectFromLine(int)const;
private:
     bool setCurrentFoldingBlock(const QPoint&);
     FoldingArea * lookAreaContaining(int line);
     MgBaseTextEdit * m_editor;
     FoldingArea * m_currentArea;
     int m_lastActiveBlock;
     QList<FoldingArea> m_topFoldingAreas;
     QSet<int> m_drawnMarkers;
     bool m_isHighlighing;

};


#endif /* MGFOLDINGEXTRAAREA_H_ */
