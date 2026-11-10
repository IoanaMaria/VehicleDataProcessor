#pragma once

#include "common/Message.h"

#include <QObject>
#include <QMap>

namespace vdp
{
class VehicleDataProcessor : public QObject
{
    Q_OBJECT

public:
    explicit VehicleDataProcessor(QObject* parent = nullptr);
    void processMessage(const QByteArray& jsonMessage);

signals:
    void stateUpdated(const QString& messageId, const QJsonObject& payload);
    void processingError(const QString& error);

private:
    QMap<QString, QJsonObject> m_latestMessages;
};
} // namespace vdp
