#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QFileDialog>

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr) : QMainWindow(parent) {
        createActions();
        createMenus();
        createToolBars();
        createStatusBar();
        createDockWidget();

        setWindowTitle(tr("Text Editor"));
        setMinimumSize(800, 600);
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        if (maybeSave()) {
            event->accept();
        } else {
            event->ignore();
        }
    }

private slots:
    void newFile() {
        if (maybeSave()) {
            textEdit->clear();
            setCurrentFile("");
        }
    }

    void open() {
        if (maybeSave()) {
            QString fileName = QFileDialog::getOpenFileName(this,
                                                            tr("Open File"), QString(),
                                                            tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;All Files (*)"));

            if (!fileName.isEmpty()) {
                loadFile(fileName);
            }
        }
    }

    bool save() {
        if (currentFile.isEmpty()) {
            return saveAs();
        } else {
            return saveFile(currentFile);
        }
    }

    bool saveAs() {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), QString(),
                                                        tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;All Files (*)"));

        if (fileName.isEmpty()) {
            return false;
        }

        return saveFile(fileName);
    }

    void about() {
        QMessageBox::about(this, tr("About Text Editor"),
                           tr("<h2>Text Editor</h2>"
                              "<p>A simple text editor implemented using Qt and C++.</p>"));
    }

    void documentWasModified() {
        setWindowModified(true);
    }

private:
    void createActions() {
        newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
        newAct->setShortcuts(QKeySequence::New);
        newAct->setStatusTip(tr("Create a new file"));
        connect(newAct, &QAction::triggered, this, &TextEditor::newFile);

        openAct = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
        openAct->setShortcuts(QKeySequence::Open);
        openAct->setStatusTip(tr("Open an existing file"));
        connect(openAct, &QAction::triggered, this, &TextEditor::open);

        saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
        saveAct->setShortcuts(QKeySequence::Save);
        saveAct->setStatusTip(tr("Save the document to disk"));
        connect(saveAct, &QAction::triggered, this, &TextEditor::save);

        saveAsAct = new QAction(tr("Save &As..."), this);
        saveAsAct->setShortcuts(QKeySequence::SaveAs);
        saveAsAct->setStatusTip(tr("Save the document under a new name"));
        connect(saveAsAct, &QAction::triggered, this, &TextEditor::saveAs);

        exitAct = new QAction(tr("Exit"), this);
exitAct->setShortcuts(QKeySequence::Quit);
exitAct->setStatusTip(tr("Exit the application"));
connect(exitAct, &QAction::triggered, qApp, &QApplication::quit);
