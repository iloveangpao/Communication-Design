#include "comms.h"

class Station {
public:
    void run() {
        while (true) {
            auto msg = receiveMessage();
            if (msg.type == MessageType::HANDSHAKE && stationIsAvailable()) {
                sendAck(msg.src_id);
                startRealTimeSession(msg.src_id);
            }
            // Perform other station tasks
        }
    }

private:
    MessageHeader receiveMessage() {
        // Receive and return the next message header
        return MessageHeader{};  // Placeholder
    }

    bool stationIsAvailable() {
        // Check if the station is available for a new session
        return true;  // Placeholder
    }

    void sendAck(uint8_t dest_id) {
        AckMessage ack_msg;
        ack_msg.header.src_id = station_id;
        ack_msg.header.dest_id = dest_id;
        ack_msg.header.type = MessageType::ACK;
        ack_msg.header.seq_num = 0;

        ack_msg.header.crc = calculate_crc16(reinterpret_cast<const uint8_t*>(&ack_msg), sizeof(ack_msg) - sizeof(ack_msg.header.crc));
        sendMessage(ack_msg);
    }

    void startRealTimeSession(uint8_t robot_id) {
        bool session_active = true;
        while (session_active) {
            auto msg = receiveMessage();
            if (msg.type == MessageType::REALTIME) {
                processRealTimeData(reinterpret_cast<const RealTimeMessage&>(msg));
                sendAck(robot_id);
            } else if (msg.type == MessageType::TERMINATE) {
                session_active = false;
                sendAck(robot_id);  // Acknowledge termination
            } else {
                handleCommunicationError();
            }
        }
        markStationAvailable();
    }

    void processRealTimeData(const RealTimeMessage& msg) {
        // Process the received real-time data
    }

    void handleCommunicationError() {
        // Handle communication error (e.g., retry or abort)
    }

    void markStationAvailable() {
        // Mark the station as available for the next robot
    }

    void sendMessage(const AckMessage& msg) {
        sendOverRF(reinterpret_cast<const uint8_t*>(&msg), sizeof(msg));
    }

    void sendOverRF(const uint8_t* data, size_t length) {
        // Implement the actual RF sending logic
    }

    uint8_t station_id = 2;
};
