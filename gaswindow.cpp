#include "gaswindow.h"
#include "ui_gaswindow.h"
#include <iostream>
#include <winsock2.h>
#include <stdio.h>



char buf[256];
SOCKET server, client;
SOCKADDR_IN serverAddr, clientAddr;

GasWindow::GasWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GasWindow)
{
    ui->setupUi(this);
}


GasWindow::~GasWindow()
{
    delete ui;
}

void GasWindow::on_updateButton_clicked()
{
   /* if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize))!= INVALID_SOCKET){

                        recv(client,buf,sizeof(buf),0);
                            //recv(client,buf,sizeof(buf),0);

                            memset(buf,0,sizeof(buf));


        }
*/
    QString status = QString("Gas Sensor Reads: %1").arg(buf);
    ui->gasLabel->setText(status);

}

void GasWindow::on_connectButton_clicked()
{

/*
       WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);

        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(10500);

      bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        listen(server, 0);



       int clientAddrSize = sizeof(clientAddr);
       */
}
