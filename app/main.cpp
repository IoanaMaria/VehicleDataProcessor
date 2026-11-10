#include "processing/VehicleDataProcessor.h"
#include "simulation/VehicleSimulator.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    vdp::VehicleDataProcessor processor;
    vdp::VehicleSimulator simulator;

    QObject::connect(&simulator, &vdp::VehicleSimulator::messageGenerated,
                     &processor, &vdp::VehicleDataProcessor::processMessage);

    QObject::connect(&processor, &vdp::VehicleDataProcessor::stateUpdated,
                     [](const QString& messageId, const QJsonObject& payload)
    {
        qInfo().noquote() << "\n[" << messageId << "]";
        for (auto it = payload.begin(); it != payload.end(); ++it)
        {
            qInfo().noquote() << " " << it.key() << ":" << it.value().toVariant().toString();
        }
    });

    QObject::connect(&processor, &vdp::VehicleDataProcessor::processingError,
                     [](const QString& error)
    {
        qWarning() << "Message processing error:" << error;
    });

    qInfo() << "VehicleDataProcessor started. Press Ctrl+C to stop.";
    simulator.start();

    return app.exec();
}
