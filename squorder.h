#ifndef SQUORDER_H
#define SQUORDER_H

#include <QMainWindow>
#include <QVector>
#include <qmath.h>
#include <qstring.h>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class squorder; }
QT_END_NAMESPACE

class squorder : public QMainWindow
{
    Q_OBJECT

public:
    squorder(QWidget *parent = nullptr);
    ~squorder();

private slots:
    void on_btn_find_root_clicked();



private:
    Ui::squorder *ui;
    QTranslator trans;

    int N;
    double step;
    double xBegin, xEnd;

    double findD(double a, double b, double c);
    QVector<double> findRoot(double a, double b, double c);



};
#endif // SQUORDER_H
