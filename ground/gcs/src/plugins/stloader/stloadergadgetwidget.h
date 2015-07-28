/**
 ******************************************************************************
 *
 * @file       stloadergadgetwidget.h
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

#ifndef STLOADERGADGETWIDGET_H
#define STLOADERGADGETWIDGET_H

#include "ui_stloader.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "uavtalk/telemetrymanager.h"
#include "extensionsystem/pluginmanager.h"
#include "uavobjects/uavobjectmanager.h"
#include "uavobjects/uavobject.h"

#include "coreplugin/icore.h"
#include "coreplugin/connectionmanager.h"

#include "rawhid/rawhidplugin.h"

//#include <QtGui/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QThread>
#include <QMessageBox>
#include <QTimer>
#include <QtCore/QVector>
#include <QtCore/QIODevice>
#include <QtCore/QLinkedList>
#include <QMutex>
#include <QMutexLocker>

class StLoaderGadgetWidget : public QWidget
{
    Q_OBJECT

public:
    StLoaderGadgetWidget(QWidget *parent = 0);
    ~StLoaderGadgetWidget();

public slots:
    void onComboBoxPorts_currentIndexChanged(int index);

protected:
    void resizeEvent(QResizeEvent *event);
    // Constants
    static const int TYPE_MASK = 0xF8;
    static const int TYPE_VER = 0x20;
    static const int TYPE_OBJ = (TYPE_VER | 0x00);
    static const int TYPE_OBJ_REQ = (TYPE_VER | 0x01);
    static const int TYPE_OBJ_ACK = (TYPE_VER | 0x02);
    static const int TYPE_ACK = (TYPE_VER | 0x03);
    static const int TYPE_NACK = (TYPE_VER | 0x04);

    static const int MIN_HEADER_LENGTH = 8; // sync(1), type (1), size(2), object ID(4)
    static const int MAX_HEADER_LENGTH = 10; // sync(1), type (1), size(2), object ID (4), instance ID(2, not used in single objects)

    static const int CHECKSUM_LENGTH = 1;

    static const int MAX_PAYLOAD_LENGTH = 256;

    static const int MAX_PACKET_LENGTH = (MAX_HEADER_LENGTH + MAX_PAYLOAD_LENGTH + CHECKSUM_LENGTH);

    static const quint8 crc_table[256];

private:
    Ui_StLoaderWidget	*m_widget;

    QString getSerialPortDevice(const QString &friendName);
    void setButtonsEnabled(bool);

    void disconnectPort();
    int connectPort();

    UAVObjectManager * getObjectManager();
    int enterDfu();

    bool connectedStatus;
    quint8 txBuffer[MAX_PACKET_LENGTH];

    QSerialPort *serial_dev;

    quint8 updateCRC(quint8 crc, const quint8 data);
    quint8 updateCRC(quint8 crc, const quint8* data, qint32 length);

private slots:
    void getPorts();

    void connected();
    void disconnected();

    void updateProgress(float);
    void sendIapCommand(UAVObject*);
    void rescueCode();
    void updateCode();
};

#endif
