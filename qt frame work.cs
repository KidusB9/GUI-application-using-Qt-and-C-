private slots:
void newFile();
void openFile();
void saveFile();
void saveFileAs();
void printFile();
void search();
void updateStatistics();
void about();

private:
QString currentFile;
QTextEdit *textEdit;
QLabel *lineCount;
QLabel *wordCount;
QLabel *charCount;
void createMenuBar();
void createToolBar();
void createStatusBar();
void createCentralWidget();
bool saveToFile(const QString &fileName);
void setCurrentFile(const QString &fileName);
};

void MainWindow::createMenuBar() {
QMenu *fileMenu = menuBar()->addMenu(tr("File"));
QAction *newAct = new QAction(tr("New"), this);
newAct->setShortcut(QKeySequence::New);
connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
fileMenu->addAction(newAct);
