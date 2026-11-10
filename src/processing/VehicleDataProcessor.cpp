#include "processing/VehicleDataProcessor.h"

#include <QDebug>

namespace vdp
{
VehicleDataProcessor::VehicleDataProcessor(QObject* parent)
    : QObject(parent)
{
}

void VehicleDataProcessor::processMessage(const QByteArray& jsonMessage)
{
    Message message;
    QString error;

    if (!Message::fromJson(jsonMessage, message, error))
    {
        emit processingError(error);
        return;
    }

    if (message.messageId.isEmpty())
    {
        emit processingError(QStringLiteral("Message ID cannot be empty"));
        return;
    }

    m_latestMessages.insert(message.messageId, message.payload);
    emit stateUpdated(message.messageId, message.payload);
}
} // namespace vdp
