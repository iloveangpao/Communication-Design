#ifndef COMMS_H
#define COMMS_H

#include <cstdint>
#include <array>
#include <chrono>

constexpr size_t HANDSHAKE_PAYLOAD_SIZE = 100;
constexpr size_t REALTIME_PAYLOAD_SIZE = 50;

enum class MessageType : uint8_t {
    HANDSHAKE,
    REALTIME,
    TERMINATE,
    ACK
};

struct MessageHeader {
    uint8_t src_id;    // Source ID (Robot or Station ID)
    uint8_t dest_id;   // Destination ID (Robot or Station ID)
    MessageType type;  // Message type (HANDSHAKE, REALTIME, TERMINATE, ACK)
    uint16_t seq_num;  // Sequence number for tracking message order
    uint16_t crc;
};

struct HandshakeMessage {
    MessageHeader header;
    std::array<uint8_t, HANDSHAKE_PAYLOAD_SIZE> payload;
};

struct RealTimeMessage {
    MessageHeader header;
    std::array<uint8_t, REALTIME_PAYLOAD_SIZE> payload;
};

struct TerminateMessage {
    MessageHeader header;
};

struct AckMessage {
    MessageHeader header;
};

struct CommSession {
    uint8_t robot_id;
    uint8_t station_id;
    bool session_active;
    std::chrono::steady_clock::time_point start_time;
    uint16_t seq_num;

    CommSession(uint8_t robot, uint8_t station)
        : robot_id(robot), station_id(station), session_active(true), 
          start_time(std::chrono::steady_clock::now()), seq_num(1) {}
};

#endif