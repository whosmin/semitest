
#include "CommandEdit.h"
#include <iostream>


CommandEdit::CommandEdit(QWidget* parent) : QTextEdit(parent) {
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);

    textFont = QFont("Lucida Console", 14);
    textColor = QColor( 0, 0, 255, 127);
//    setTextBackgroundColor( QColor(0, 0, 255, 127)); // Qt 4.4 onwards
    
    prompt = "> ";

    clear();

    prevCursor = textCursor();
}

QString CommandEdit::getCurrentLine() {
    QTextCursor cursor = textCursor();
    cursor.movePosition( QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cursor.movePosition( QTextCursor::EndOfLine,   QTextCursor::KeepAnchor);

    QString lineText = cursor.selectedText();

    if(lineText.left(prompt.size()) == prompt)
        lineText.remove( 1, prompt.size());

    return lineText;
}

void CommandEdit::setCurrentLine(QString text) {
    QTextCursor cursor = textCursor();
    cursor.movePosition( QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cursor.movePosition( QTextCursor::EndOfLine,   QTextCursor::KeepAnchor);
    cursor.removeSelectedText();

    if(text == prompt)
        cursor.insertText(prompt);
    else
        cursor.insertText(prompt + text);

    return;
}

void CommandEdit::onReturn() {

    history.addEntry( currLine.toStdString());
    currLine.clear();
    append(prompt);
    cursorColNum = 0;
    lineNum++;
//        QTextEdit::keyPressEvent(event);
//
}
void CommandEdit::clear() {
    history.clear();
    QTextEdit::clear();
    this->setCurrentFont( textFont);
    setTextColor( textColor);
    cursorColNum = 0;
    lineNum = 0;
    append(prompt);
}

//
// * process return to display newline, prompt and set cursor to end
// * process backspace to delete chars but not prompt
//
void CommandEdit::keyPressEvent(QKeyEvent* event) {
    QString text = event->text();
    int     key  = event->key();


    // Reset cursor position to end of document ie: last command
    setTextCursor(prevCursor);

    unsigned int numPrint = 0;
    for(unsigned int i=0; i < text.size(); i++) {
        if(text[i].isPrint() == true)
            numPrint++;
    }
    cursorColNum += numPrint;

    if(key == Qt::Key_Return || key == Qt::Key_Enter) {
        onReturn();
    }
    else if(key == Qt::Key_Backspace) {
        if(cursorColNum > 0) {
            cursorColNum--;
            QTextEdit::keyPressEvent(event);
        }
    }
    else if(key == Qt::Key_Up) {
        string prevEntry;
        bool isValid = history.getPrevEntry(prevEntry);
        QString temp = prevEntry.c_str();
//        append(prompt + temp);
        setCurrentLine( temp);
    }
    else if(key == Qt::Key_Down) {
        string nextEntry;
        bool isValid = history.getNextEntry(nextEntry);
        QString temp = nextEntry.c_str();
//        append(prompt + temp);
        setCurrentLine( temp);
    }
    else {
        currLine += text;
        QTextEdit::keyPressEvent(event);
    }
//    std::cout << cursorColNum << std::endl;
}

void CommandEdit::paintEvent(QPaintEvent* event) {
    QTextEdit::paintEvent(event);
}

void CommandEdit::setText(QString text) {
}

