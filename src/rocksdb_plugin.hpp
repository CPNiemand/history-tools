// copyright defined in LICENSE.txt

#pragma once
#include <appbase/application.hpp>

#include "query_config_plugin.hpp"
#include "state_history_rocksdb.hpp"

struct rocksdb_inst {
    state_history::rdb::database                     database;
    std::unique_ptr<const state_history::kv::config> query_config{};

    rocksdb_inst(const char* db_path, std::optional<uint32_t> threads, std::optional<uint32_t> max_open_files, bool fast_reads)
        : database{db_path, threads, max_open_files, fast_reads} {}
};

class rocksdb_plugin : public appbase::plugin<rocksdb_plugin> {
  public:
    APPBASE_PLUGIN_REQUIRES((query_config_plugin))

    rocksdb_plugin();
    virtual ~rocksdb_plugin();

    virtual void set_program_options(appbase::options_description& cli, appbase::options_description& cfg) override;
    void         plugin_initialize(const appbase::variables_map& options);
    void         plugin_startup();
    void         plugin_shutdown();

    std::shared_ptr<rocksdb_inst> get_rocksdb_inst(bool fast_reads);

  private:
    std::shared_ptr<struct rocksdb_plugin_impl> my;
};
