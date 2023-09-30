#include "squorder.h"
#include "ui_squorder.h"
#include <QLocale>

#include <QDir>


squorder::squorder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::squorder)
{
    trans.load(qApp->applicationDirPath() + QDir().separator()  + QLocale::system().name());

    qApp->installTranslator(&trans);

    ui->setupUi(this);



    ui->PlotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

squorder::~squorder()
{
    delete ui;
}


void squorder::on_btn_find_root_clicked()
{
    double coef_a = ui->sb_coef_a->value();
    double coef_b = ui->sb_coef_b->value();
    double coef_c = ui->sb_coef_c->value();

    if (ui->sb_step->value() != 0) {
        step = ui->sb_step->value();
    } else {
        step = 0.01;
        ui->sb_step->setValue(0.01);
    }
    xBegin = ui->sb_xbegin->value();
    xEnd = ui->sb_xend->value() + step;

    ui->PlotWidget->xAxis->setRange(-10, 10);
    ui->PlotWidget->yAxis->setRange(-10, 10);

    QVector<double> roots;




    try {

        roots = findRoot(coef_a, coef_b, coef_c); // Get Roots



        if (roots.size() == 1) {
            ui->lbl_roots->setText("X = " + QString::number(roots.at(0)));
        } else if (roots.size() == 2) {
            ui->lbl_roots->setText("X1 = " + QString::number(roots.at(0)) +
                                   "\nX2 = " + QString::number(roots.at(1)));
        }

    } catch(const std::runtime_error& err) { // If root not find
        ui->lbl_roots->setText(tr("Roots no exitst"));
    }

    ui->PlotWidget->clearGraphs();
    // Draw Graph
    QVector<double> x,y;
    double X = xBegin;
    N = (xEnd - xBegin) / step + 2;


    for (X = xBegin; X <= xEnd; X += step) {
        x.push_back(X);
        y.push_back( (coef_a * (X*X)) + (coef_b * X) + coef_c );
    }

    ui->PlotWidget->addGraph();
    ui->PlotWidget->graph(0)->addData(x, y);

    ui->PlotWidget->replot();
}

double squorder::findD(double a, double b, double c)
{
    return (b*b) - (4 * a * c);
}

QVector<double> squorder::findRoot(double a, double b, double c) {
    QVector<double> res;

    if (a != 0) {
        double D = findD(a,b,c);

        if (D == 0) {
            res.push_back( -(b/(2*a)) );
        } else if (D > 0) {
            res.push_back( (-b + qSqrt(D)) / (2 * a) );
            res.push_back( (-b - qSqrt(D)) / (2 * a) );
        } else { // if D < 0 then throw error
            throw std::runtime_error("NO ROOT");
        }
    } else {
        res.push_back( -(c/b));
    }

    return res;
}
