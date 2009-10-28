
#ifndef __COMMAND_EDIT_H__
#define __COMMAND_EDIT_H__

#include <QtGui>

#include <string>
#include <vector>
#include <list>

#include "history.h"

using namespace std;


class CommandEdit : public QTextEdit {
    Q_OBJECT
    public:
        CommandEdit(QWidget *parent=0);

    public Q_SLOTS:
        void clear();

    protected:
        virtual void keyPressEvent(QKeyEvent* event);
        virtual void paintEvent(QPaintEvent* event);
        virtual void onReturn(void);
        virtual void setText(QString text);

        virtual QString getCurrentLine();
        virtual void   setCurrentLine(QString text);

    protected:
        QFont        textFont;
        QColor       textColor;
        QString      prompt;
        QString      currLine;

        IterHistory      history;

        unsigned int cursorColNum, lineNum;
    private:
        QTextCursor  prevCursor;
};

#endif

