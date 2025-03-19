#include <filesystem>

#include "cacti_interface.h"

#include <lmdb.h>
#include <ostream>
#include <istream>
#pragma once
class ResultsDB{
	public:
		static ResultsDB& getInstance();

	private:
		std::filesystem::path database_path;
		MDB_env* env;
		MDB_dbi dbi;

		bool open_database();
		void close_database();
		void delete_entry(MDB_val& key);

		template<typename T> static std::ostream& serialize(std::ostream& os, T* param);
		template<typename T> static std::istream& deserialize(std::istream& is, T** param);

		template<typename T> static std::ostream& serialize(std::ostream& os, T& param);
		template<typename T> static std::istream& deserialize(std::istream& is, T& param);

		ResultsDB();
		std::filesystem::path create_tmp_path();
		ResultsDB(std::string database_path);
		ResultsDB(std::filesystem::path database_path);
		~ResultsDB();

	public:

		ResultsDB(ResultsDB const&) = delete;
		void operator=(ResultsDB const&) = delete;

		bool get(InputParameter& input_parameter_key, uca_org_t& uca_org_val);
		void put(InputParameter& input_parameter_key, uca_org_t& uca_org_val);
};

template<> std::ostream& ResultsDB::serialize(std::ostream& os, InputParameter& param);
template<> std::istream& ResultsDB::deserialize(std::istream& is, InputParameter& param);
template<> std::ostream& ResultsDB::serialize(std::ostream& os, uca_org_t& param);
template<> std::istream& ResultsDB::deserialize(std::istream& is, uca_org_t& param);
template<> std::ostream& ResultsDB::serialize(std::ostream& os, mem_array& param);
template<> std::istream& ResultsDB::deserialize(std::istream& is, mem_array& param);
template<> std::ostream& ResultsDB::serialize(std::ostream& os, min_values_t& param);
template<> std::istream& ResultsDB::deserialize(std::istream& is, min_values_t& param);
