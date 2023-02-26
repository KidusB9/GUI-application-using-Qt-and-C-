return true;
}

void MainWindow::loadFile(const QString &fileName) {
QFile file(fileName);
if (!file.open(QFile::ReadOnly | QFile::Text)) {
QMessageBox::warning(this, tr("Text Editor"), tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
return;
}
