#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <qzipreader_p.h>
#include <qzipwriter_p.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QStringList suffixes;
    QString currentPath;

    QFileInfo fileInfo;
    QImage image;

    QDir dir;
    QString tempPath;
    QStringList filters;
};
#endif // WIDGET_H
