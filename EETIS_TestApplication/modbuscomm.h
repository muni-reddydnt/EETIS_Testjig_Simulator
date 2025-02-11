#ifndef MODBUSCOMM_H
#define MODBUSCOMM_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QDebug>
#include <QTcpServer>

#define SERVER_PORT                 502

#define READ_HOLDING_REGS           3
#define WRITE_MULTIPLE_REGS         16

#define DI_TRANS_ID                 11
#define DO_TRANS_ID                 21
#define AI_TRANS_ID                 31
#define AO_TRANS_ID                 41

#define NO_OF_REGISTERS             125

#define NO_OF_DI_REG                4
#define NO_OF_DO_REG                4
#define NO_OF_AI_REG                16
#define WRITE_MULTIPLE_REGS         16
#define REQ_MULTIPLE_REGS           3
#define NO_OF_DIs                   16*NO_OF_DI_REG
#define NO_OF_DOs                   16*NO_OF_DO_REG
#define NO_OF_BYTES_AI              2*NO_OF_AI_REG
#define BYTES_IN_REG                2
#define MAX_BITS_IN_REG             16

#define SLAVE_ADDRESS               0
#define FUNCTION_CODE               3

class modbusComm : public QObject
{
    Q_OBJECT
public:
    explicit modbusComm(QObject *parent = nullptr);\

    QTcpSocket *clientSocket;

    int status = 0;
    int dotransactionId = 0;
    unsigned short inputReg[NO_OF_REGISTERS] = {0};
    char sendDOVals[NO_OF_DOs] = {0};
    bool aiReqSts = false;
    unsigned short baseAddrOfDO;
    char receivDIs[NO_OF_DIs] = {0};
    char statusData = 0;
    short dival[4] = {0};
    short plcAIs[NO_OF_BYTES_AI] = {0};

    void connectModbusTcpSocket(const QString &host, quint16 port);
    int setBitHigh(int val, int bitPosition, bool highLow);
    void setBaseAddrOfDO(unsigned short regAddr);
    void sendDiData(short *diVal);
    void sendAoData(short *aoVal);
    void sendDoAoData(int transId, int regLength,  short *inputArr);
    void setBitInRegister(int bitPosition);
    int getDiValue(int diChannel);
    int getAiValue(int aiChannel);
    void setDoValue(int doChannel, char data);
    void storeDoDataInRegArray(short *doDataInRegArray, unsigned short noOfRegToWrite, char *doData);

public slots:
    void sendData();
private slots:
    void onNewConnection();
    void readData();
    void sendModbusReadWriteRequest();

private:
    void decodeData(QByteArray responseData);
    void storeDoData(unsigned short noOfRegToRead);
    void storeAiData(unsigned short noOfRegToRead);
    bool getBitValFrmReg(unsigned short regValue, int bitPosition);
//    void setBitInRegister(int bitPosition);
    QTcpSocket *modbusTcpSocket;
    QTimer *sendReqTimer;
    QTcpServer *tcpServer;
    QTimer *receivReqTimer;
    QTcpServer *server;
    //qint16 dival[4] = {0};


    QTimer *recevTimer;
    QTimer *sendTimer;
};

#endif // MODBUSCOMM_H
