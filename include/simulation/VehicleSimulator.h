#pragma once

#include "common/Message.h"

#include <QObject>
#include <QTimer>

namespace vdp
{
class VehicleSimulator : public QObject
{
    Q_OBJECT

public:
    explicit VehicleSimulator(QObject* parent = nullptr);
    void start();

signals:
    void messageGenerated(const QByteArray& jsonMessage);

private:
    void generateMessages();

    QTimer m_timer;
    int m_tick {0};
};
} // namespace vdp
