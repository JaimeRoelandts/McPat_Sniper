#include <filesystem>

#include "cacti_interface.h"

#include <lmdb.h>
class ResultsDB{
	private:
		std::filesystem::path database_path;
		MDB_env* env;
		MDB_dbi dbi;

		// sqlite3* open_database();
		// bool create_tables(sqlite3* db);
		bool open_database();
		void close_database();
		void delete_entry(MDB_val& key);

		static std::ostream& serialize(std::ostream& os, InputParameter& param);
		static std::istream& deserialize(std::istream& is, InputParameter& param);

	public:
		ResultsDB();
		ResultsDB(std::string database_path);
		ResultsDB(std::filesystem::path database_path);
		~ResultsDB();

		bool get(InputParameter& input_parameter_key, InputParameter& input_parameter_result);
		void put(InputParameter& input_parameter_key, InputParameter& input_parameter_result);
};
