#pragma once

#include "nativemq/global_macro.h"
#include <unordered_map>

NATIVEMQ_BEGIN_NAMESPACE

enum class MqttServerType { PRIMARY = 0, SECONDARY = 1 };

enum class MqttVersion : uint8_t {
  UNKNOWN = 0,
  MQTT_3_0 = 1,
  MQTT_3_1 = 2,
  MQTT_5_0 = 4
};

NATIVEMQ_ENUM_CLASS_ENABLE_BITMASK_OPERATORS(MqttVersion)

enum class VMBoxIPCType {
  NONE = 0,
  VMBOX_IPC = 1,
  VMBOX_TCP = 2,
  VMBOX_UNIX_SOCKET = 3
};

enum class VMBOXIPCConnectionType { NONE = 0, VMBOX_DIRECT = 1, VMBOX_ROUTER = 2 };

enum class TLSType { NONE = 0, SERVER_TLS = 1, MTLS = 2 };

enum class QoSLevel : uint8_t {
  QOS_0_AT_MOST_ONCE = 0,
  QOS_1_AT_LEAST_ONCE = 1,
  QOS_2_EXACTLY_ONCE = 2
};

namespace internal {

// Enum maps
inline const std::unordered_map<std::string, MqttVersion> mqtt_version_map = {
    {"UNKNOWN", MqttVersion::UNKNOWN},
    {"MQTT_3_0", MqttVersion::MQTT_3_0},
    {"MQTT_3_1", MqttVersion::MQTT_3_1},
    {"MQTT_5_0", MqttVersion::MQTT_5_0}};

inline const std::unordered_map<std::string, MqttServerType>
    mqtt_server_type_map = {{"PRIMARY", MqttServerType::PRIMARY},
                            {"SECONDARY", MqttServerType::SECONDARY}};

inline const std::unordered_map<std::string, VMBoxIPCType> ipc_type_map = {
    {"NONE", VMBoxIPCType::NONE},
    {"VMBOX_IPC", VMBoxIPCType::VMBOX_IPC},
    {"VMBOX_TCP", VMBoxIPCType::VMBOX_TCP},
    {"VMBOX_UNIX_SOCKET", VMBoxIPCType::VMBOX_UNIX_SOCKET}};

inline const std::unordered_map<std::string, VMBOXIPCConnectionType>
    ipc_conn_map = {{"NONE", VMBOXIPCConnectionType::NONE},
                    {"VMBOX_DIRECT", VMBOXIPCConnectionType::VMBOX_DIRECT},
                    {"VMBOX_ROUTER", VMBOXIPCConnectionType::VMBOX_ROUTER}};

inline const std::unordered_map<std::string, TLSType> tls_type_map = {
    {"NONE", TLSType::NONE},
    {"SERVER_TLS", TLSType::SERVER_TLS},
    {"MTLS", TLSType::MTLS}};

}  // namespace internal

NATIVEMQ_END_NAMESPACE