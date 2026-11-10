#pragma once

#include <QJsonObject>
#include <QString>
#include <QJsonDocument>

namespace vdp
{
struct Message
{
    QString messageId;
    qint64 timestampMs {0};
    QJsonObject payload;

    QJsonObject toJson() const
    {
        return {
            {QStringLiteral("message_id"), messageId},
            {QStringLiteral("timestamp_ms"), timestampMs},
            {QStringLiteral("payload"), payload}
        };
    }

    static bool fromJson(const QByteArray& data, Message& message, QString& error)
    {
        QJsonParseError parseError;
        const auto document = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error != QJsonParseError::NoError || !document.isObject())
        {
            error = parseError.errorString();
            return false;
        }

        const auto object = document.object();
        if (!object.value(QStringLiteral("message_id")).isString()
            || !object.value(QStringLiteral("timestamp_ms")).isDouble()
            || !object.value(QStringLiteral("payload")).isObject())
        {
            error = QStringLiteral("Message must contain message_id, timestamp_ms and payload");
            return false;
        }

        message.messageId = object.value(QStringLiteral("message_id")).toString();
        message.timestampMs = static_cast<qint64>(
            object.value(QStringLiteral("timestamp_ms")).toDouble());
        message.payload = object.value(QStringLiteral("payload")).toObject();
        return true;
    }
};
} // namespace vdp
