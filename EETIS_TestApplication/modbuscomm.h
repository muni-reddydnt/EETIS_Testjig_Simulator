#ifndef MODBUSCOMM_H
#define MODBUSCOMM_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QDebug>
#include <QTcpServer>



#define READ_HOLDING_REGS           3
#define WRITE_MULTIPLE_REGS         16

//#define DI_TRANS_ID                 11
#define DI_TRANS_ID                 11
#define AI_TRANS_ID                 31


//#define DO_TRANS_ID                 31
#define DO_TRANS_ID                 21
//#define AI_TRANS_ID                 51
#define AO_TRANS_ID                 71
#define NO_OF_REGISTERS             125

#define NO_OF_DI_REG                4
#define NO_OF_DO_REG                4
#define WRITE_MULTIPLE_REGS         16
#define REQ_MULTIPLE_REGS           3
#define NO_OF_DIs                   16*NO_OF_DI_REG
#define NO_OF_DOs                   16*NO_OF_DO_REG
#define MAX_BITS_IN_REG             16

#define SLAVE_ADDRESS               0
#define FUNCTION_CODE               3

class modbusComm : public QObject
{
    Q_OBJECT
public:
    explicit modbusComm(QObject *parent = nullptr);
    void connectModbusTcpSocket(const QString &host, quint16 port);
    int status = 0;
    int dotransactionId = 0;
    //int aoTransactionId = 0;
    unsigned short inputReg[NO_OF_REGISTERS] = {0};
    void setBaseAddrOfDO(unsigned short regAddr);
    unsigned short baseAddrOfDO;
    void sendDiData(short *diVal);
    void sendAoData(short *aoVal);
    void sendDoAoData(int transId, int regLength,  short *inputArr);
    void setBitInRegister(int bitPosition);
    char receivDIs[NO_OF_DIs] = {0};
    //char sendDOs[NO_OF_DOs] = {0};
    char statusData = 0;
    //int dival[4] = {0}; temp
    short dival[4] = {0};
    int getDiValue(int diChannel);
    void setDoValue(int doChannel, char data);
    void storeDoDataInRegArray(short *doDataInRegArray, unsigned short noOfRegToWrite, char *doData);
    char sendDOVals[NO_OF_DOs] = {0};
    //char startSendData = 0;
    int setBitHigh(int val, int bitPosition, bool highLow);
    bool aiReqSts = false;
public slots:
    void sendData();
private slots:
    void onNewConnection();
    void readData();
    void sendModbusReadWriteRequest();



private:
    void decodeData(QByteArray responseData);
    void storeDoData(unsigned short noOfRegToRead);
    bool getBitValFrmReg(unsigned short regValue, int bitPosition);
//    void setBitInRegister(int bitPosition);
    QTcpSocket *modbusTcpSocket;
    QTimer *sendReqTimer;
    QTcpServer *tcpServer;
    QTimer *receivReqTimer;
    QTcpServer *server;

    QTcpSocket *clientSocket;
    //qint16 dival[4] = {0};


    QTimer *recevTimer;
    QTimer *sendTimer;
};

#endif // MODBUSCOMM_H
