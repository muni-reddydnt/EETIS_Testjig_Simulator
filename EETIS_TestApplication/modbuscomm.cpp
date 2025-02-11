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
        if(transId == AO_TRANS_ID)
        {
            //qDebug() << "Received received:" << data.toHex();
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
            // Process DI data here
            unsigned short noOfRegToRead = (((responseData.at(10) << 8) | responseData.at(11)));
            storeDoData(noOfRegToRead);
        }
        if(transId == AO_TRANS_ID)
        {
            unsigned short noOfRegToRead = (((responseData.at(10) << 8) | responseData.at(11)));
            storeAiData(noOfRegToRead);
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
                //qDebug() << "receivDIs " << i << ": " << ((int)(receivDIs[i]));
            }
            index = i;
        }
    }
    else
    {
        qDebug("No of regs are more than DI channels");
    }
}

void modbusComm::storeAiData(unsigned short noOfRegToRead)
{
    if (noOfRegToRead <= (NO_OF_BYTES_AI / BYTES_IN_REG))
    {
        for (int i = 0; i < noOfRegToRead; i++)
        {
            plcAIs[i] = inputReg[i];
            //qDebug() << "plcAIs " << i << ": " << ((int)(plcAIs[i]));
        }
    }
    else
    {
        qDebug("Number of registers exceeds available AI channels.");
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

int modbusComm::getAiValue(int aiChannel)
{
    return (plcAIs[aiChannel]);
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









