#include "modbuscomm.h"
#include "mainwindow.h"

extern MainWindow *mainAppWin;

modbusComm::modbusComm(QObject *parent) : QObject(parent)
{
    server = new QTcpServer();
    //  mavSock = new QUdpSocket();

    if (server->listen(QHostAddress::LocalHost, SERVER_PORT))
    {
        qDebug() << "Server started. Waiting for connections...";
    }
    else
    {
        qDebug() << "Server could not start. Error:" << server->errorString();
    }
    // Connect the newConnection signal to a slot that will handle incoming client connections
    connect(server, &QTcpServer::newConnection, this, &modbusComm::onNewConnection);

    sendTimer = new QTimer(this);
    connect(sendTimer, SIGNAL(timeout()), this, SLOT(sendData()));
    status = 0;

    clientSocket = new QTcpSocket(this);
}

void modbusComm::setBaseAddrOfDO(unsigned short regAddr)
{
    baseAddrOfDO = regAddr;
}

void modbusComm::sendDiData(short *diVal)
{
    if (clientSocket == nullptr)
    {
        return;
    }

    if (clientSocket->state() != QAbstractSocket::ConnectedState)
    {
//        qDebug() << "Socket is not connected!";
        return;
    }

    QByteArray request;

    QDataStream stream(&request, QIODevice::ReadWrite);
    //int dotransactionId = DI_TRANS_ID;
    stream << quint16(dotransactionId);
    stream << quint16(0);                   // Protocol identifier (0 for Modbus TCP/IP)
    //stream << quint16(19);
    stream << quint16(3 + (4*2));        /*(noOfReg * 2)*/

    stream << quint8(SLAVE_ADDRESS);
    stream << quint8(FUNCTION_CODE);
    stream << quint8(04*02);
    for(int i = 0 ; i < 4; i++)
    {
        stream << quint16(diVal[i]);
    }
    clientSocket->write(request);
    if (!clientSocket->waitForBytesWritten(3000))
    {
        qDebug() << "Failed to send Modbus request:" << clientSocket->errorString();
    }
    //qDebug()<<"data sending = "<<request.toHex();
}

void modbusComm::sendAoData(short *aoVal)
{
    //    if (clientSocket == nullptr) {
    //        return;
    //    }
    //    if (clientSocket->state() != QAbstractSocket::ConnectedState) {
    //        //        qDebug() << "Socket is not connected!";
    //        return;
    //    }
    int totalRegisters = 16;
    int aoTransactionId = AI_TRANS_ID;
    QByteArray request;

    QDataStream stream(&request, QIODevice::ReadWrite);

    stream << quint16(aoTransactionId);
    stream << quint16(0);                   // Protocol identifier (0 for Modbus TCP/IP)
    //stream << quint16(19);
    stream << quint16(3 + (totalRegisters * 2));        /*(noOfReg * 2)*/

    stream << quint8(SLAVE_ADDRESS);
    stream << quint8(FUNCTION_CODE);
    stream << quint8(totalRegisters * 02);
    for(int i = 0 ; i < totalRegisters; i++)
    {
        stream << quint16(aoVal[i]);
    }
    clientSocket->write(request);
    if (!clientSocket->waitForBytesWritten(3000))
    {
        qDebug() << "Failed to send Modbus request:" << clientSocket->errorString();
    }
}

void modbusComm::sendDoAoData(int transId, int regLength, short *inputArr)
{
    if (clientSocket == nullptr)
    {
        return;
    }
    if (clientSocket->state() != QAbstractSocket::ConnectedState)
    {
//        qDebug() << "Socket is not connected!";
        return;
    }

    //qDebug()<<"hello";
    QByteArray request;

    QDataStream stream(&request, QIODevice::ReadWrite);
    //int dotransactionId = DI_TRANS_ID;
    stream << quint16(transId);
    stream << quint16(0);                   // Protocol identifier (0 for Modbus TCP/IP)
    //stream << quint16(19);
    stream << quint16(3 + (regLength *2));        /*(noOfReg * 2)*/

    stream << quint8(SLAVE_ADDRESS);
    stream << quint8(FUNCTION_CODE);
    stream << quint8(regLength * 02);
    for(int i = 0 ; i < regLength; i++)
    {
        stream << quint16(inputArr[i]);
    }
    clientSocket->write(request);
    if (!clientSocket->waitForBytesWritten(3000)) {
        qDebug() << "Failed to send Modbus request:" << clientSocket->errorString();
    }
    //qDebug()<<"data sending = "<<request.toHex();
    if(transId == DI_TRANS_ID)
    {
        //qDebug()<<"data sending = "<<request.toHex();
    }
}

void modbusComm::onNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();

    // Handle incoming data (if needed)
    connect(clientSocket, &QTcpSocket::readyRead, this, &modbusComm::readData);


    // Optionally, you can also handle disconnection events:
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    if(!clientSocket->isOpen())
    {
        sendTimer->stop();
    }

}

void modbusComm::readData()
{
    //sendTimer->start(50);
    //startSendData = 1;
    clientSocket = new QTcpSocket(this);
    clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket)
    {
        QByteArray data = clientSocket->readAll();

        unsigned char funcCode = data.at(7);
        unsigned short transId = (data.at(0) << 8) | data.at(1);
        //qDebug() << "Received received:" << data.toHex();
        mainAppWin->startSendData = 1;
        if(transId == DO_TRANS_ID)
        {
            //qDebug() << "Received received:" << data.toHex();

            //qDebug("in modbus mainAppWin->statusData: %d",mainAppWin->startSendData);
        }
        decodeData(data);
    }
    else
    {
        statusData = 0;
    }

}

void modbusComm::sendModbusReadWriteRequest()
{

}

void modbusComm::sendData()
{
    //qDebug()
    // storeDoDataInRegArray(&dival[0], 4, &sendDOVals[0]);
    sendDiData(dival);
}

void modbusComm::decodeData(QByteArray responseData)
{
    //Check if correct modbus response is received
    if(responseData.length() < 5)
    {
        qDebug("Invalid packet");
        return;
    }
    unsigned char funcCode = responseData.at(7);
    switch(funcCode)
    {
    case WRITE_MULTIPLE_REGS:
    {
        //Extract data length
        unsigned char dataLength = responseData.at(11);
        //qDebug()<<"dataLength = "<<dataLength;
        for (int i = 0; i < (dataLength * 2); i += 2)
        {
            unsigned char lowByte = responseData.at(13+i);
            unsigned char highByte = responseData.at(14+i);
            //            qDebug("lowByte = %x ",lowByte);
            //            qDebug("highByte = %x ",highByte);
            inputReg[i/2] = ((lowByte << 8) | (highByte));

        }


        //Check if the data is for DI or AI based on transaction ID
        unsigned short transId = (responseData.at(0) << 8) | responseData.at(1);
        if (transId == DO_TRANS_ID)
        {
            // Data is for DI
            // Process DI data here
            unsigned short noOfRegToRead = (((responseData.at(10) << 8) | responseData.at(11)));
            //unsigned short noOfRegToRead = ((((responseData.at(4) << 8) | responseData.at(5))-3) - 2)/2;
            //
            //qDebug()<<"noOfRegToRead = "<<noOfRegToRead;
            storeDoData(noOfRegToRead);
#if 0
            //qDebug()<<"noOfRegToRead = "<<noOfRegToRead;
            qDebug()<<"dataLength = "<<dataLength;
            qDebug("inputReg[0] = %x\n",inputReg[0]);
            qDebug("inputReg[1] = %x\n",inputReg[1]);
            qDebug("inputReg[2] = %x\n",inputReg[2]);
            qDebug("inputReg[3] = %x\n",inputReg[3]);
#endif
#if 0
                        qDebug("receivDIs[5] = %d\n",receivDIs[5]);
                        qDebug("receivDIs[33] = %d\n",receivDIs[33]);
            //            qDebug("receivDIs[1] = %d\n",receivDIs[1]);
            //            qDebug("receivDIs[2] = %d\n",receivDIs[2]);
            //            qDebug("receivDIs[3] = %d\n",receivDIs[3]);
            //            qDebug("receivDIs[4] = %d\n",receivDIs[4]);
            //            qDebug("receivDIs[5] = %d\n",receivDIs[5]);
//            qDebug("receivDIs[6] = %d\n",receivDIs[6]);
            //            qDebug("receivDIs[7] = %d\n",receivDIs[7]);
            //            qDebug("receivDIs[8] = %d\n",receivDIs[8]);
            //            qDebug("receivDIs[9] = %d\n",receivDIs[9]);
#endif
#if 0
            qDebug("receivDIs[10] = %d\n",receivDIs[10]);
            qDebug("receivDIs[11] = %d\n",receivDIs[11]);
            qDebug("receivDIs[12] = %d\n",receivDIs[12]);
            qDebug("receivDIs[13] = %d\n",receivDIs[13]);
            qDebug("receivDIs[14] = %d\n",receivDIs[14]);
            qDebug("receivDIs[15] = %d\n",receivDIs[15]);
            qDebug("receivDIs[16] = %d\n",receivDIs[16]);
            qDebug("receivDIs[17] = %d\n",receivDIs[17]);
            qDebug("receivDIs[18] = %d\n",receivDIs[18]);
            qDebug("receivDIs[19] = %d\n",receivDIs[19]);
            qDebug("receivDIs[20] = %d\n",receivDIs[20]);
            qDebug("receivDIs[21] = %d\n",receivDIs[21]);
            qDebug("receivDIs[22] = %d\n",receivDIs[22]);
            qDebug("receivDIs[23] = %d\n",receivDIs[23]);

#endif

        }




    }
    case REQ_MULTIPLE_REGS:
    {
        //Check if the data is for DI or AI based on transaction ID
        unsigned short transId = (responseData.at(0) << 8) | responseData.at(1);
        if (transId == 0x1f)
        {
            aiReqSts = true;
            //qDebug()<<"aiReqSts = "<<aiReqSts;

        }
        break;
    }
    }
}

//delete
void modbusComm::storeDoData(unsigned short noOfRegToRead)
{
    int index = 0, i = 0, bitPos = 0;

    //checking if no of regs are less than or equal to no of DIs
    if(noOfRegToRead <= (NO_OF_DIs / MAX_BITS_IN_REG))
    {
        for(int j = 0; j < noOfRegToRead; j++)
        {
            for(i = index, bitPos = 0; bitPos < MAX_BITS_IN_REG, i < (index + MAX_BITS_IN_REG); bitPos++, i++)
            {
                receivDIs[i] = getBitValFrmReg(inputReg[j] , bitPos);
                qDebug() << "receivDIs " << i << ": " << ((int)(receivDIs[i]));
            }
            index = i;
        }
    }
    else
    {
        qDebug("No of regs are more than DI channels");
    }
}

bool modbusComm::getBitValFrmReg(unsigned short regValue, int bitPosition)
{
    int temp = ( (regValue & (1 << bitPosition)) != 0 );
    return(temp);
}

int modbusComm::getDiValue(int diChannel)
{
    return (receivDIs[diChannel]);
}

void modbusComm::setDoValue(int doChannel, char data)
{
    sendDOVals[doChannel] = data;
    //qDebug("sendDOVals[%d] = %d", doChannel,sendDOVals[doChannel]);
}



void modbusComm::storeDoDataInRegArray(short *doDataInRegArray, unsigned short noOfRegToWrite, char *doData)
{
    for(int i = 0; i < (noOfRegToWrite * 16); i++)
    {
        for(int i = 0; i < (noOfRegToWrite * 16); i++)
        {
            int regNo = i/16;
            short int dataMask = doData[i] << (i % 16);
            doDataInRegArray[regNo] = doDataInRegArray[regNo] | dataMask;
        }
    }
}

int modbusComm::setBitHigh(int val, int bitPosition, bool highLow)
{
    if (highLow)
    {
        return val |= (1 << bitPosition);
    }
    else
    {
        return val &= ~(1 << bitPosition);
    }
}









