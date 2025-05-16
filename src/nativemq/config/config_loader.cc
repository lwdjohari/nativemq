// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 Linggawasistha Djohari
// <linggawasistha.djohari@outlook.com>

#include "nativemq/config/config_loader.h"
#include "nativemq/utils/cli/terminal_color.h"
#include <iostream>

NATIVEMQ_INNER_NAMESPACE(config)
NATIVEMQ_MAKE_NAMESPACE(loader)

bool FileExists(const std::string& path) {
  std::ifstream f(path);
  return f.good();
}

std::optional<MqttConfig> LoadConfig(const std::string& path) {
  bool is_file_exist = FileExists(path);
  if (!is_file_exist) {
    std::cerr << utils::cli::terminal_color.Error("[ERROR] File not exist: ")
              << path << utils::cli::terminal_color.Reset() << "\n";
    return std::nullopt;
  }

  try {
    YAML::Node root = YAML::LoadFile(path);
    MqttConfig cfg;

    if (!ConvertYaml(root, cfg)) {
      return std::nullopt;
    } else {
      return std::optional<MqttConfig>(std::move(cfg));
    }
  } catch (const std::exception& ex) {
     std::cerr << utils::cli::terminal_color.Error("[ERROR] Config: ")
              << ex.what() << utils::cli::terminal_color.Reset() << "\n";
    return std::nullopt;
  }
}

bool ConvertYaml(const YAML::Node& node, TlsConfig& out) {
  const std::string ctx = "TlsConfig";

  out.enable = utils::yaml::GetOrDefault(node, "enable", false, ctx);

  if (node["type"]) {
    out.type =
        utils::yaml::ParseEnum(node["type"], internal::tls_type_map, "TLSType");
  }

  out.tls_cert_file =
      utils::yaml::GetOrDefault(node, "tls_cert_file", NVMQ_ESTR, ctx);

  out.tls_key_file =
      utils::yaml::GetOrDefault(node, "tls_key_file", NVMQ_ESTR, ctx);

  return true;
}

bool ConvertYaml(const YAML::Node& node, MqttServerConfig& out) {
  const std::string ctx = "MqttServerConfig";

  out.enable = utils::yaml::GetOrDefault(node, "enable", false, ctx);

  if (node["type"]) {
    out.type = utils::yaml::ParseEnum(
        node["type"], internal::mqtt_server_type_map, "MqttServerType");
  }

  if (node["mqtt_versions"]) {
    out.mqtt_versions = utils::yaml::ParseEnum(
        node["mqtt_versions"], internal::mqtt_version_map, "MqttVersion");
  }

  out.port = utils::yaml::GetOrDefault(node, "port", uint16_t{8843}, ctx);
  out.worker = utils::yaml::GetOrDefault(node, "worker", uint16_t{4}, ctx);
  out.host = utils::yaml::GetOrDefault(node, "host", NVMQ_STR("0.0.0.0"), ctx);

  if (node["tls"]) {
    ConvertYaml(node["tls"], out.tls);
  }

  return true;
}

bool ConvertYaml(const YAML::Node& node, MqttVMBoxConfig& out) {
  const std::string ctx = "MqttVMBoxConfig";

  if (node["ipc_type"]) {
    out.ipc_type = utils::yaml::ParseEnum(
        node["ipc_type"], internal::ipc_type_map, "VMBoxIPCType");
  }

  if (node["ipc_connection_type"]) {
    out.ipc_connection_type =
        utils::yaml::ParseEnum(node["ipc_connection_type"],
                               internal::ipc_conn_map, "VMBOXIPCConnection");
  }

  out.port = utils::yaml::GetOrDefault(node, "port", uint16_t{8843}, ctx);
  out.worker = utils::yaml::GetOrDefault(node, "worker", uint16_t{4}, ctx);

  out.mailbox_connect_timeout = utils::yaml::GetOrDefault(
      node, "mailbox_connect_timeout", uint16_t{10}, ctx);

  out.mailbox_query_timeout = utils::yaml::GetOrDefault(
      node, "mailbox_query_timeout", uint16_t{5}, ctx);

  out.enable_backpressure_control =
      utils::yaml::GetOrDefault(node, "enable_backpressure_control", true, ctx);

  out.ingress_backlog_number = utils::yaml::GetOrDefault(
      node, "ingress_backlog_number", uint16_t{0}, ctx);

  out.ingress_backlog_cooldown = utils::yaml::GetOrDefault(
      node, "ingress_backlog_cooldown", uint16_t{0}, ctx);

  out.egress_backlog_number = utils::yaml::GetOrDefault(
      node, "egress_backlog_number", uint16_t{0}, ctx);

  out.egress_backlog_cooldown = utils::yaml::GetOrDefault(
      node, "egress_backlog_cooldown", uint16_t{0}, ctx);

  out.max_mailbox =
      utils::yaml::GetOrDefault(node, "max_mailbox", size_t{0}, ctx);

  out.host = utils::yaml::GetOrDefault(node, "host", NVMQ_STR("0.0.0.0"), ctx);

  return true;
}

bool ConvertYaml(const YAML::Node& node, MqttPayloadLimitConfig& out) {
  const std::string ctx = "MqttPayloadLimitConfig";
  out.max_publish_bytes = utils::yaml::GetOrDefault(node, "max_publish_bytes",
                                                    4 * 1024 * 1024, ctx);
  out.ipc_chunk_bytes =
      utils::yaml::GetOrDefault(node, "ipc_chunk_bytes", 64 * 1024, ctx);

  return true;
}

bool ConvertYaml(const YAML::Node& node, AuthConfig& out) {
  const std::string ctx = "AuthConfig";

  out.enable = utils::yaml::GetOrDefault(node, "enable", false, ctx);

  out.auth_client_id =
      utils::yaml::GetOrDefault(node, "auth_client_id", true, ctx);

  out.auth_username_password =
      utils::yaml::GetOrDefault(node, "auth_username_password", true, ctx);

  return true;
}

bool ConvertYaml(const YAML::Node& node, TopicConfig& out) {
  const std::string ctx = "TopicConfig";

  out.topic_id = utils::yaml::GetOrDefault(node, "topic_id", NVMQ_ESTR, ctx);

  out.max_client =
      utils::yaml::GetOrDefault(node, "max_client", size_t{0}, ctx);

  out.pacing = utils::yaml::GetOrDefault(node, "pacing", size_t{100}, ctx);
  out.enable = utils::yaml::GetOrDefault(node, "enable", false, ctx);

  return true;
}

bool ConvertYaml(const YAML::Node& node, TopicLimiterConfig& out) {
  const std::string ctx = "TopicLimiterConfig";

  out.topic_filter =
      utils::yaml::GetOrDefault(node, "topic_filter", NVMQ_ESTR, ctx);

  out.pub_pacing =
      utils::yaml::GetOrDefault(node, "pub_pacing", size_t{50}, ctx);

  out.sub_pacing =
      utils::yaml::GetOrDefault(node, "sub_pacing", size_t{50}, ctx);

  return true;
}

bool ConvertYaml(const YAML::Node& node, StormGuardModule& out) {
  const std::string ctx = "StormGuardModule";

  out.module_id = utils::yaml::GetOrDefault(node, "module_id", NVMQ_ESTR, ctx);

  out.enable = utils::yaml::GetOrDefault(node, "enable", false, ctx);

  if (node["properties"]) {
    for (const auto& kv : node["properties"]) {
      out.properties[kv.first.as<std::string>()] = kv.second.as<std::string>();
    }
  }

  return true;
}

bool ConvertYaml(const YAML::Node& node, StormGuardConfig& out) {
  const std::string ctx = "StormGuardConfig";

  out.enable = utils::yaml::GetOrDefault(node, "enable", false, ctx);

  if (node["modules"]) {
    for (const auto& mod : node["modules"]) {
      StormGuardModule module;
      ConvertYaml(mod, module);
      out.modules.push_back(std::move(module));
    }
  }

  return true;
}

bool ConvertYaml(const YAML::Node& node, MqttConfig& out) {
  const std::string ctx = "MqttConfig";

  ConvertYaml(node["server_primary"], out.server_primary);
  ConvertYaml(node["server_secondary"], out.server_secondary);

  if (node["auth_config"]) {
    ConvertYaml(node["auth_config"], out.auth_config);
  }

  ConvertYaml(node["vmbox"], out.vmbox);

  if (node["payload_limit"]) {
    ConvertYaml(node["payload_limit"], out.payload_limit);
  }

  if (node["topics"]) {
    for (const auto& topic : node["topics"]) {
      TopicConfig cfg;
      ConvertYaml(topic, cfg);
      out.topics.push_back(std::move(cfg));
    }
  }

  if (node["topic_limiters"]) {
    for (const auto& topic : node["topic_limiters"]) {
      TopicLimiterConfig cfg;
      ConvertYaml(topic, cfg);
      out.topic_limiters.push_back(std::move(cfg));
    }
  }

  if (node["storm_guard"]) {
    ConvertYaml(node["storm_guard"], out.storm_guard);
  }

  return true;
}

NATIVEMQ_END_NAMESPACE
NATIVEMQ_INNER_END_NAMESPACE
