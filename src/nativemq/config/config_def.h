// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 Linggawasistha Djohari
// <linggawasistha.djohari@outlook.com>

#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "nativemq/declare.h"
#include "nativemq/global_macro.h"

NATIVEMQ_INNER_NAMESPACE(config)

struct TlsConfig {
  bool enable = false;
  TLSType type = TLSType::NONE;
  std::string tls_cert_file = std::string();
  std::string tls_key_file = std::string();
  ;
};

struct MqttServerConfig {
  bool enable = false;
  MqttServerType type = MqttServerType::PRIMARY;
  MqttVersion mqtt_versions = MqttVersion::MQTT_5_0;
  uint16_t port = 8843;
  uint16_t worker = 4;
  std::string host = "0.0.0.0";
  TlsConfig tls = TlsConfig();
};

struct MqttVMBoxConfig {
  VMBoxIPCType ipc_type = VMBoxIPCType::VMBOX_IPC;
  VMBOXIPCConnectionType ipc_connection_type = VMBOXIPCConnectionType::VMBOX_DIRECT;
  uint16_t port = 8843;
  uint16_t worker = 4;
  uint16_t mailbox_connect_timeout = 10;
  uint16_t mailbox_query_timeout = 5;
  bool enable_backpressure_control = true;
  uint16_t ingress_backlog_number = 0;
  uint16_t ingress_backlog_cooldown = 0;
  uint16_t egress_backlog_number = 0;
  uint16_t egress_backlog_cooldown = 0;
  size_t max_mailbox = 0;
  std::string host = "0.0.0.0";
};

struct StormGuardModule {
  std::string module_id = std::string();
  std::unordered_map<std::string, std::string> properties;
  bool enable = false;
};

struct StormGuardConfig {
  bool enable = false;
  std::vector<StormGuardModule> modules;
};

struct MqttPayloadLimitConfig {
  // Max MQTT payload size (default: 4 MB)
  size_t max_publish_bytes = 4 * 1024 * 1024;

  // Max IPC chunk size (default: 64 KB)
  size_t ipc_chunk_bytes = 64 * 1024;
};

struct AuthConfig {
  bool enable = false;
  bool auth_client_id = true;
  bool auth_username_password = true;
};

struct TopicConfig {
  std::string topic_id = std::string();
  size_t max_client = 0;
  size_t pacing = 100;  // in ms
  bool enable = false;
};

struct TopicLimiterConfig {
  std::string topic_filter = std::string();
  size_t pub_pacing = 50;  // in ms
  size_t sub_pacing = 50;  // in ms
};

struct MqttConfig {
  MqttServerConfig server_primary;
  MqttServerConfig server_secondary;
  AuthConfig auth_config;
  MqttVMBoxConfig vmbox;
  MqttPayloadLimitConfig payload_limit;
  std::vector<TopicConfig> topics;
  std::vector<TopicLimiterConfig> topic_limiters;
  StormGuardConfig storm_guard = StormGuardConfig();
};

NATIVEMQ_END_NAMESPACE
NATIVEMQ_END_NAMESPACE