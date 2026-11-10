#include "simulation/VehicleSimulator.h"

#include <QDateTime>
#include <QJsonDocument>

namespace vdp
{
VehicleSimulator::VehicleSimulator(QObject* parent)
    : QObject(parent)
{
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this, &VehicleSimulator::generateMessages);
}

void VehicleSimulator::start()
{
    m_timer.start();
}

void VehicleSimulator::generateMessages()
{
    const qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

    const double speed = (m_tick % 12 < 8)
        ? 45.0 + static_cast<double>((m_tick * 7) % 55)
        : 0.0;

    Message vehicleMessage;
    vehicleMessage.messageId = QStringLiteral("vehicle_status");
    vehicleMessage.timestampMs = timestamp;
    vehicleMessage.payload = {
        {QStringLiteral("power_state"), QStringLiteral("ON")},
        {QStringLiteral("gear_position"),
            speed == 0.0 ? QStringLiteral("PARK") : QStringLiteral("DRIVE")},
        {QStringLiteral("left_door_open"), false},
        {QStringLiteral("right_door_open"), false},
        {QStringLiteral("hood_open"), false},
        {QStringLiteral("trunk_open"), false},
        {QStringLiteral("left_indicator"), (m_tick % 10 == 2)},
        {QStringLiteral("right_indicator"), (m_tick % 10 == 6)},
        {QStringLiteral("hazard_lights"), false},
        {QStringLiteral("vehicle_speed_kph"), speed}
    };

    Message adasMessage;
    adasMessage.messageId = QStringLiteral("adas_status");
    adasMessage.timestampMs = timestamp;
    adasMessage.payload = {
        {QStringLiteral("fcw"), speed > 85.0 ? QStringLiteral("WARNING") : QStringLiteral("PASSIVE")},
        {QStringLiteral("aeb"), QStringLiteral("PASSIVE")},
        {QStringLiteral("pedestrian_detection"), QStringLiteral("PASSIVE")},
        {QStringLiteral("blind_spot_monitoring"), QStringLiteral("ACTIVE")},
        {QStringLiteral("lane_departure_warning"), QStringLiteral("PASSIVE")},
        {QStringLiteral("lane_keeping_assist"), QStringLiteral("PASSIVE")},
        {QStringLiteral("adaptive_cruise_control"), QStringLiteral("OFF")},
        {QStringLiteral("park_assist"), speed == 0.0 ? QStringLiteral("ACTIVE") : QStringLiteral("PASSIVE")},
        {QStringLiteral("rear_cross_traffic_alert"), QStringLiteral("PASSIVE")}
    };

    emit messageGenerated(QJsonDocument(vehicleMessage.toJson()).toJson(QJsonDocument::Compact));
    emit messageGenerated(QJsonDocument(adasMessage.toJson()).toJson(QJsonDocument::Compact));

    ++m_tick;
}
} // namespace vdp
