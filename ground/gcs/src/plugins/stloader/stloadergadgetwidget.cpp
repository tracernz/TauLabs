/**
 ******************************************************************************
 *
 * @file       stloadergadgetwidget.cpp
 * @author     Tau Labs Team, http://www.taulabs.org Copyright (C) 2015.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @{
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <QDebug>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>

#include "firmwareiapobj.h"

#include "stloadergadgetwidget.h"
#include "stm32.h"

#define NO_PORT         0
#define SERIAL_PORT     1

#define SYNC_VAL 0x3C

const quint8 StLoaderGadgetWidget::crc_table[256] = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};

class SleepThread : public QThread
{
public:
    static void usleep(unsigned long usecs)
    {
        QThread::usleep(usecs);
    }
};

// constructor
StLoaderGadgetWidget::StLoaderGadgetWidget(QWidget *parent) :
    QWidget(parent),
    m_widget(NULL),
    connectedStatus(false)
{
    m_widget = new Ui_StLoaderWidget();
    m_widget->setupUi(this);

    getPorts();

    setEnabled(true);

    m_widget->progressUpload->hide();

    m_widget->buttonRescue->setEnabled(true);
    m_widget->buttonUpgrade->setEnabled(true);

    connect(m_widget->buttonRescue, SIGNAL(clicked()), this, SLOT(rescueCode()));
    connect(m_widget->buttonUpgrade, SIGNAL(clicked()), this, SLOT(updateCode()));
}

StLoaderGadgetWidget::~StLoaderGadgetWidget()
{
}

void StLoaderGadgetWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}

void StLoaderGadgetWidget::onComboBoxPorts_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}

bool sortSerialPorts(const QSerialPortInfo &s1, const QSerialPortInfo &s2)
{
    return (s1.portName() < s2.portName());
}

void StLoaderGadgetWidget::getPorts()
{
    disconnect(m_widget->comboBox_Ports, 0, 0, 0);

    m_widget->comboBox_Ports->clear();

    // Populate the telemetry combo box with serial ports
    QList<QSerialPortInfo> serial_ports = QSerialPortInfo::availablePorts();
    qSort(serial_ports.begin(), serial_ports.end(), sortSerialPorts);
    QStringList list;
    foreach (QSerialPortInfo port, serial_ports)
        m_widget->comboBox_Ports->addItem("com: " + port.portName(), SERIAL_PORT);

    connect(m_widget->comboBox_Ports, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxPorts_currentIndexChanged(int)));

    onComboBoxPorts_currentIndexChanged(m_widget->comboBox_Ports->currentIndex());

}

void StLoaderGadgetWidget::setButtonsEnabled(bool enable)
{
    if(enable) {
        m_widget->buttonRescue->setEnabled(!connectedStatus);
        m_widget->buttonUpgrade->setEnabled(!connectedStatus);
        m_widget->comboBox_Ports->setEnabled(!connectedStatus);
    }
    else {
        m_widget->buttonRescue->setEnabled(false);
        m_widget->buttonUpgrade->setEnabled(false);
        m_widget->comboBox_Ports->setEnabled(false);
    }
}

QString StLoaderGadgetWidget::getSerialPortDevice(const QString &friendName)
{
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

        foreach (QSerialPortInfo port, ports)
        {
#ifdef Q_OS_WIN
            if (port.portName() == friendName)
                return port.portName();
#else
            if (port.portName().trimmed() == friendName)
                return port.portName();
#endif
        }

        return "";
}

/**
  * @brief Disconnect the selected port
  */
void StLoaderGadgetWidget::disconnectPort()
{
    if(!serial_dev || !serial_dev->isOpen())
        return;

    qDebug() << "Closing serial port: " << serial_dev->portName();
    serial_dev->close();
    delete serial_dev;
    serial_dev = NULL;
    connectedStatus = false;
    disconnected();
}

/**
  * @brief Connect to the selected port
  */
int StLoaderGadgetWidget::connectPort()
{
    int device_idx = m_widget->comboBox_Ports->currentIndex();
    if (device_idx < 0)
        return -2;

    QString device_str = m_widget->comboBox_Ports->currentText().trimmed();
    Q_ASSERT(!device_str.isEmpty());

    if (device_str.toLower().startsWith("com: "))
    {
        device_str.remove(0, 5);
        device_str = device_str.trimmed();

        QString str = getSerialPortDevice(device_str);
        if (str.isEmpty())
            return -3;

        serial_dev = new QSerialPort(str);
        if (!serial_dev)
            return -4;

        serial_dev->setBaudRate(QSerialPort::Baud57600);
        serial_dev->setDataBits(QSerialPort::Data8);
        serial_dev->setParity(QSerialPort::NoParity);
        serial_dev->setStopBits(QSerialPort::OneStop);
        serial_dev->setFlowControl(QSerialPort::NoFlowControl);

        if (!serial_dev->open(QIODevice::ReadWrite))
        {
            qDebug() << "Opening port failed: " << device_str;
            delete serial_dev;
            return -5;
        }

    } else
        return -6;

    connectedStatus = true;
    connected();

    return 0;
}

/**
  * When connected enable UI
  */
void StLoaderGadgetWidget::connected()
{
    connect(FirmwareIAPObj::GetInstance(getObjectManager()),
                SIGNAL(objectUpdated(UAVObject*)), this,
                SLOT(sendIapCommand(UAVObject*)));
    m_widget->buttonRescue->setEnabled(false);
    m_widget->buttonUpgrade->setEnabled(false);
    m_widget->comboBox_Ports->setEnabled(false);
}

/**
  * When disconnected disable UI and signals
  */
void StLoaderGadgetWidget::disconnected()
{
    disconnect(FirmwareIAPObj::GetInstance(getObjectManager()),
                SIGNAL(objectUpdated(UAVObject*)), this,
                SLOT(sendIapCommand(UAVObject*)));

    m_widget->buttonRescue->setEnabled(true);
    m_widget->buttonUpgrade->setEnabled(true);
    m_widget->comboBox_Ports->setEnabled(true);
}

/**
  * @brief Return handle to object manager
  */
UAVObjectManager * StLoaderGadgetWidget::getObjectManager()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager * objMngr = pm->getObject<UAVObjectManager>();
    Q_ASSERT(objMngr);
    return objMngr;
}

/**
 * @brief Send IAP command over serial
 */
void StLoaderGadgetWidget::sendIapCommand(UAVObject *firmwareIap)
{
    qint32 length;
    qint32 dataOffset;
    quint32 objId;
    quint8 type = TYPE_OBJ;

    // Setup type and object id fields
    objId = firmwareIap->getObjID();
    txBuffer[0] = SYNC_VAL;
    txBuffer[1] = type;
    qToLittleEndian<quint32>(objId, &txBuffer[4]);

    // assume single instance
    dataOffset = 8;

    // Determine data length
    if (type == TYPE_OBJ_REQ || type == TYPE_ACK)
    {
        length = 0;
    }
    else
    {
        length = firmwareIap->getNumBytes();
    }

    // Check length
    if (length >= MAX_PAYLOAD_LENGTH)
    {
        return;
    }

    // Copy data (if any)
    if (length > 0)
    {
        if (!firmwareIap->pack(&txBuffer[dataOffset]))
        {
            return;
        }
    }

    qToLittleEndian<quint16>(dataOffset + length, &txBuffer[2]);

    // Calculate checksum
    txBuffer[dataOffset+length] = updateCRC(0, txBuffer, dataOffset + length);

    serial_dev->write((char *)txBuffer, dataOffset + length + CHECKSUM_LENGTH);

    firmwareIap->emitTransactionCompleted(true);
}

/**
 * Update the crc value with new data.
 *
 * Generated by pycrc v0.7.5, http://www.tty1.net/pycrc/
 * using the configuration:
 *    Width        = 8
 *    Poly         = 0x07
 *    XorIn        = 0x00
 *    ReflectIn    = False
 *    XorOut       = 0x00
 *    ReflectOut   = False
 *    Algorithm    = table-driven
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param length   Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 */
quint8 StLoaderGadgetWidget::updateCRC(quint8 crc, const quint8 data)
{
    return crc_table[crc ^ data];
}
quint8 StLoaderGadgetWidget::updateCRC(quint8 crc, const quint8* data, qint32 length)
{
    while (length--)
        crc = crc_table[crc ^ *data++];
    return crc;
}

/**
 * @brief Put the board into dfu mode
 */
int StLoaderGadgetWidget::enterDfu()
{
    FirmwareIAPObj *firmwareIap = FirmwareIAPObj::GetInstance(getObjectManager());
    QEventLoop loop;
    QTimer timeout;
    timeout.setSingleShot(true);
    firmwareIap->setBoardRevision(0);
    firmwareIap->setBoardType(0);
    connect(&timeout, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(firmwareIap,SIGNAL(transactionCompleted(UAVObject*,bool)), &loop, SLOT(quit()));
    quint16 magicValue = 1122;
    quint16 magicStep = 1111;

    for(int i = 0; i < 3; ++i)
    {
        //Firmware IAP module specifies that the timing between iap commands must be
        //between 500 and 5000ms
        timeout.start(600);
        loop.exec();
        firmwareIap->setCommand(magicValue);
        magicValue += magicStep;
        qDebug() << "Sending IAP Step " << i + 1;
        firmwareIap->updated();
        timeout.start(1000);
        loop.exec();
        if(!timeout.isActive())
        {
            qDebug() << "Sending IAP Step " << i + 1 << " failed";
            //return -1;
        }
        timeout.stop();
    }

    // give time to reboot
    timeout.start(1000);
    loop.exec();

    return 0;
}

/**
  * @brief Update the code on the device
  */
void StLoaderGadgetWidget::rescueCode()
{
    int device_idx = m_widget->comboBox_Ports->currentIndex();
    if (device_idx < 0)
        return;

    QString device_str = m_widget->comboBox_Ports->currentText().trimmed();
    Q_ASSERT(!device_str.isEmpty());

    if (device_str.toLower().startsWith("com: "))
    {
        device_str.remove(0, 5);
        device_str = device_str.trimmed();

        QString str = getSerialPortDevice(device_str);
        if (str.isEmpty())
            return;

        setButtonsEnabled(false);

        Stm32Bl bl;
        if (bl.openDevice(str) != 0) {
            setButtonsEnabled(true);
            return;
        }

        QFileDialog::Options options;
        QString selectedFilter;
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Select firmware file"),
                                                        "",
                                                        tr("Firmware Files (*.tlfw)"),
                                                        &selectedFilter,
                                                        options);

        if(fileName.isEmpty()) {
            bl.stm32_go(0x0);
            bl.stm32_close();
            setButtonsEnabled(true);
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            bl.stm32_go(0x0);
            bl.stm32_close();
            setButtonsEnabled(true);
            qDebug() << "Can't open file";
            return;
        }

        QByteArray loadedFW = file.readAll();

        m_widget->progressUpload->show();
        connect(&bl, SIGNAL(uploadProgress(float)), this, SLOT(updateProgress(float)));

        bl.uploadCode(loadedFW);
        bl.stm32_go(0x0);
        bl.stm32_close();

        disconnect(&bl, SIGNAL(uploadProgress(float)), this, SLOT(updateProgress(float)));
        m_widget->progressUpload->hide();
    }
    setButtonsEnabled(true);

    return;
}

/**
 * @brief Update the progress bar
 * @param progress
 */
void StLoaderGadgetWidget::updateProgress(float progress)
{
    m_widget->progressUpload->setValue((int)progress);
}

void StLoaderGadgetWidget::updateCode()
{
    setButtonsEnabled(false);

    if(connectPort() < 0) {
        return;
    }

    qDebug() << "Halting...";
    if(enterDfu() < 0) {
        disconnectPort();
        return;
    }

    disconnectPort();

    rescueCode();

    setButtonsEnabled(true);
}
