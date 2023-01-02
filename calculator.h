#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QWidget
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();

private slots:
    void NumClick();
    void MathOp();
    void SingneChange();
    void EqualClick();
    void ClaerDisply();
    void DoteClick();

private:
    Ui::calculator *ui;
};
#endif // CALCULATOR_H
