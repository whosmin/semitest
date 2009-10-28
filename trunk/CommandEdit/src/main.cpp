
#include <QtGui>
#include <QApplication>
#include <QWidget>
#include "CommandEdit.h"

class CommandWindow : public QWidget {
    public:
        CommandWindow(QWidget* parent=0);
        virtual ~CommandWindow();

    protected:
        CommandEdit* cmdEdit;
};

CommandWindow::CommandWindow(QWidget* parent) : QWidget(parent) {
    cmdEdit = new CommandEdit(this);

    QPushButton* clearButton = new QPushButton("Clear", this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(clearButton);
    layout->addWidget(cmdEdit);
    setLayout(layout);

    connect( clearButton, SIGNAL(clicked()), cmdEdit, SLOT(clear()));
}

CommandWindow::~CommandWindow() {

}

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    
    CommandWindow* pWidget = new CommandWindow();
    pWidget->resize( 300, 400);
    pWidget->setWindowTitle("Command Editor");
    pWidget->show();
    return app.exec();
}


