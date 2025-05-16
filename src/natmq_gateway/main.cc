// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 Linggawasistha Djohari
// <linggawasistha.djohari@outlook.com>

#include <nativemq/config/config_loader.h>
#include <nativemq/utils/cli/terminal_color.h>

#include <CLI/CLI.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace fs = std::filesystem;
namespace config = nativemq::config;
namespace nv_cli = nativemq::utils::cli;

std::filesystem::path GetExecutablePath(char* argv0) {
  try {
    return std::filesystem::canonical(std::filesystem::path(argv0));
  } catch (...) {
    return std::filesystem::absolute(std::filesystem::path(argv0));
  }
}

std::filesystem::path ResolveConfigPath(const std::string& user_input) {
  std::filesystem::path p(user_input);
  return std::filesystem::absolute(p);
}

int main(int argc, char** argv) {
  CLI::App app{"Nativemq v0.7.0"};

  std::cout << nv_cli::terminal_color.Blue() << "Nativemq v0.7.0 "
              << nv_cli::terminal_color.Reset() << "\n";
  std::cout << nv_cli::terminal_color.Blue() << "-----------------" 
              << nv_cli::terminal_color.Reset() << "\n\n";

  std::string default_path = "config.yaml";
  std::string config_path;
  bool is_validate_only = false;
  bool is_dump_config = false;

  app.add_option("-c,--config", config_path, "Path to YAML config file")
      ->default_val(default_path)
      ->check(CLI::ExistingFile);

  app.add_flag("--validate", is_validate_only,
               "Validate the config file then exit");

  app.add_flag("--dump", is_dump_config, "Dump loaded config info to stdout");

  CLI11_PARSE(app, argc, argv);

  std::string real_path = ResolveConfigPath(config_path);
  auto mqtt_conf = config::loader::LoadConfig(real_path);

  if (!mqtt_conf.has_value()) {
    std::cerr << nv_cli::terminal_color.Error(
                     "[ERROR] Failed to parse config: ")
              << real_path << nv_cli::terminal_color.Reset() << "\n";
    return 1;
  }

  if (is_validate_only) {
    std::cout << nv_cli::terminal_color.Success("[OK] ")
              << "Mqtt Config: " << config_path
              << nv_cli::terminal_color.Reset() << "\n";
    return 0;
  }

  if (is_dump_config || mqtt_conf.has_value()) {
    std::cout << nv_cli::terminal_color.Success("[OK] ")
              << "Mqtt Config: " << config_path
              << nv_cli::terminal_color.Reset() << "\n";

    std::cout << nv_cli::terminal_color.DimText("MQTT Primary:\n");
    std::cout << "  Enabled: " << mqtt_conf.value().server_primary.enable
              << "\n";
    std::cout << "  Host:    " << mqtt_conf.value().server_primary.host << "\n";
    std::cout << "  Port:    " << mqtt_conf.value().server_primary.port << "\n";
    std::cout << "  TLS:     "
              << (mqtt_conf.value().server_primary.tls.enable ? "enabled"
                                                              : "disabled")
              << "\n";

    std::cout << nv_cli::terminal_color.DimText("VMBox:\n");
    std::cout << "  IPC Type: "
              << static_cast<int>(mqtt_conf.value().vmbox.ipc_type) << "\n";
    std::cout << "  Max Mailbox: " << mqtt_conf.value().vmbox.max_mailbox
              << "\n";

    std::cout << nv_cli::terminal_color.DimText("Auth:\n");
    std::cout << "  Username/Password required: "
              << mqtt_conf.value().auth_config.auth_username_password << "\n";
  }

  return 0;
}