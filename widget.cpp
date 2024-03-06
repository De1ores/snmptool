#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QList>
#include <QNetworkInterface>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
    Snmp_pp::Snmp socket_clearup();
}

void Widget::startConnect()
{
 //on Win32 this method must be called before creating Snmp or Address objects.
  QString ip = ui->IP->text();

  //Snmp_pp::UdpAddress target(tarstr.toStdString().c_str());


}
void Widget::on_connButton_clicked()
{//click to connect
  startConnect();
  ui->res->appendPlainText("connected to target");
}


void Widget::on_PORT_2_returnPressed()//Oid inputport
{


   Snmp_pp:: Snmp::socket_startup();
    QString ip = ui->IP->text();

//qDebug()<<ip.toStdString().c_str();//Snmp_pp::IpAddress(iipAddressChar

   Snmp_pp::CTarget target(Snmp_pp::IpAddress(ip.toStdString().c_str()), "public", "public");
    target.set_version(Snmp_pp::version1);
//"1.3.6.1.2.1.1.1.0"sysdesc
//1.3.6.1.2.1.1.3.0 sysuptime
//1.3.6.1.2.1.1.5.0 sysname
//1.3.6.1.2.1.2.1.0 ifnumber
    QString oidText = ui->PORT_2->text();
    QByteArray oidBytes = oidText.toLatin1();
    char* oidChar = oidBytes.data();
    Snmp_pp::Pdu pdu;
    Snmp_pp::Oid oid(oidChar);

     Snmp_pp::Vb vb(oid);
     pdu += vb;

    int status;
    Snmp_pp::Snmp snmp(status);

    if (SNMP_CLASS_SUCCESS != status)
    {
        qDebug() << snmp.error_msg(status);

    }

    qDebug()<< "目的IP：" << target.get_address().get_printable() << " 版本号：" << target.get_version() ;

    ui->res->appendPlainText( target.get_address().get_printable());

  if ( (status = snmp.get(pdu, target)) == SNMP_CLASS_SUCCESS )
    {
        pdu.get_vb(vb, 0);
        qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(timestamp);
        QString formattedTime = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz\n");
        qDebug() << "System Return  =" << vb.get_printable_value();
           ui->res->appendPlainText(formattedTime+vb.get_printable_value());
        if(!(vb.get_printable_value()))
           {
               ui->res->appendPlainText("value does not exist");
           }
    }
    else
    {
        qDebug()<<snmp.error_msg(status);

    }

    Snmp_pp::Snmp::socket_cleanup();


   //snmp return
  /* if (status == SNMP_CLASS_SUCCESS) {
       for (int i = 0; i < pdu.get_vb_count(); i++) {
           Snmp_pp::Vb vb = pdu.get_vb(i);
           qDebug() << "OID: " << vb.get_printable_oid();
           qDebug() << "Value: " << vb.get_printable_value();
           ui->res->appendPlainText("OID: ");
           ui->res->appendPlainText(vb.get_printable_oid());
           ui->res->appendPlainText( "Value: ");
           ui->res->appendPlainText( QString::fromUtf8(vb.get_printable_value()));

       }
   } else {
       qDebug()<<Snmp_pp::Snmp:: error_msg(status);
       qDebug() << "SNMP GET操作失败，错误码: " << status;
   }*/

}


void Widget::on_scanButton_clicked()//Scan devices' ip
{
   QList<QHostAddress> devices;//ip container
   QList<QString>desc;//description
   foreach (const QNetworkInterface &iface, QNetworkInterface::allInterfaces()) {
       foreach (const QNetworkAddressEntry &entry, iface.addressEntries()) {
           QHostAddress address = entry.ip();
           if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
               devices.append(address);
               qDebug()<<address;

           }
       }
       ui->iptable->setColumnCount(2);
       ui->iptable->setRowCount(devices.size());
       // display on iptable
       for (int i = 0; i < devices.size(); ++i) {

           QTableWidgetItem *item1 = new QTableWidgetItem(devices[i].toString());

           ui->iptable->insertRow(i);
           ui->iptable->setItem(i, 0, item1);

       }


}

}
