#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "snmp_pp.h"
#include<QtCore>

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
    void on_connButton_clicked();

    void on_PORT_2_returnPressed();

    void on_scanButton_clicked();

private:

    Ui::Widget *ui;

    Snmp_pp::UdpAddress target;
    void startConnect();
    void multiConnect();

};
#endif // WIDGET_H
