// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 Linggawasistha Djohari
// <linggawasistha.djohari@outlook.com>

#include "nativemq/config/config_def.h"
#include "nativemq/declare.h"
#include "nativemq/global_macro.h"
#include "nativemq/utils/yaml/yaml_helper.h"
#include <filesystem>
#include <fstream>
#include <optional>

NATIVEMQ_INNER_NAMESPACE(config)
NATIVEMQ_MAKE_NAMESPACE(loader)

bool ConvertYaml(const YAML::Node& node, TlsConfig& out);
bool ConvertYaml(const YAML::Node& node, MqttServerConfig& out);
bool ConvertYaml(const YAML::Node& node, MqttVMBoxConfig& out);
bool ConvertYaml(const YAML::Node& node, MqttPayloadLimitConfig& out);
bool ConvertYaml(const YAML::Node& node, AuthConfig& out);
bool ConvertYaml(const YAML::Node& node, TopicConfig& out);
bool ConvertYaml(const YAML::Node& node, TopicLimiterConfig& out);
bool ConvertYaml(const YAML::Node& node, StormGuardModule& out);
bool ConvertYaml(const YAML::Node& node, StormGuardConfig& out);
bool ConvertYaml(const YAML::Node& node, MqttConfig& out);

bool FileExists(const std::string& path);
std::optional<MqttConfig> LoadConfig(const std::string& path);

NATIVEMQ_END_NAMESPACE
NATIVEMQ_INNER_END_NAMESPACE
