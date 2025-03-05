#include "results_db.h"
#include <cstring>

ResultsDB::ResultsDB(){
	std::filesystem::path tmp_dir = getenv("TEMPDIR") ? std::filesystem::path(getenv("TEMPDIR")) : std::filesystem::path("/tmp");
	std::string user = getenv("USER") ? getenv("USER") : "unknown";
	std::string file_name = "mcpat-" + user + ".db";
	ResultsDB(tmp_dir / file_name);
}

ResultsDB::ResultsDB(std::string database_path){
	ResultsDB(std::filesystem::path(database_path));
}

ResultsDB::ResultsDB(std::filesystem::path database_path): 
	database_path(database_path),
	env(nullptr),
	dbi(0)
{
	//sqlite3* db = open_database();
	open_database();
}

ResultsDB::~ResultsDB(){
	close_database();
}


// sqlite3* ResultsDB::open_database(){
// 	sqlite3* db;
// 	int return_code = sqlite3_open(database_path.c_str(), &db);
// 	if(return_code) {
// 		std::cerr << "Could not open a database at path " << database_path << std::endl;
// 		sqlite3_close(db);
// 		db = nullptr;
// 	}
// 
// 	return db;
// }
// 
// bool ResultsDB::create_tables(sqlite3* db){
// 	char* errmsg = nullptr;
// 
// 	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS results ("
// 			"key TEXT PRIMARY KEY, "
// 			"input_parameter BLOB)", NULL, NULL, &errmsg);
// 
// 	return true;
// }

bool ResultsDB::open_database(){
	int rc;
	rc = mdb_env_create(&this->env);
	if(rc){
		std::cerr << "Could not create LMDB environment with error code " << mdb_strerror(rc) << std::endl;
		this->env = nullptr;
		return false;
	}

	rc = mdb_env_set_maxdbs(this->env, 1);
	if(rc){
		std::cerr << "Failed to set max DBs with error code " << mdb_strerror(rc) << std::endl;
		return false;
	}

	rc = mdb_env_open(this->env, database_path.c_str(), MDB_NOSUBDIR, 0664);
	if(rc){
		std::cerr << "Failed to open LMDB database with error code " << mdb_strerror(rc) << std::endl;
		this->env = nullptr;
		return false;
	}


	//Write an empty transaction to create/open the database
	MDB_txn* txn;
	rc = mdb_txn_begin(this->env, NULL, 0, &txn);
	if(rc){
		std::cerr << "Failed to create a transaction with error code " << mdb_strerror(rc) << std::endl;
		return false;
	}

	rc = mdb_dbi_open(txn, "results", MDB_CREATE, &this->dbi);
	if(rc){
		std::cerr << "Failed to open results database with error code " << mdb_strerror(rc) << std::endl;
		return false;
	}

	rc = mdb_txn_commit(txn);
	if(rc){
		std::cerr << "Failed to commit the transaction with error code " << mdb_strerror(rc) << std::endl;
		return false;
	}

	return true;
}

void ResultsDB::close_database(){
	if(this->dbi && this->env)
		mdb_dbi_close(this->env, this->dbi);
	if(this->env)
		mdb_env_close(this->env);
}

bool ResultsDB::get(InputParameter& input_parameter_key, InputParameter& input_parameter_val){
	MDB_val key, data;

	std::stringstream ser_key;
	serialize(ser_key, input_parameter_key);
	std::string ser_key_str = ser_key.str();

	key.mv_size = ser_key_str.size();
	key.mv_data = ser_key_str.data();

	MDB_txn* txn;
	mdb_txn_begin(this->env, nullptr, MDB_RDONLY, &txn);

	int rc = mdb_get(txn, this->dbi, &key, &data);
	if(rc == MDB_NOTFOUND) {
		mdb_txn_abort(txn);
		return false;
	}

	if(data.mv_size != sizeof(InputParameter)){
		mdb_txn_abort(txn);
		delete_entry(key);
		return false;
	}

	std::stringstream ser_val;
	ser_val.write(static_cast<const char*>(data.mv_data), data.mv_size);
	deserialize(ser_val, input_parameter_val);

	//input_parameter_val = *static_cast<InputParameter*>(data.mv_data);
	mdb_txn_commit(txn);
	return true;
}

void ResultsDB::put(InputParameter& input_parameter_key, InputParameter& input_parameter_val){
	MDB_val key, data;

	std::stringstream ser_key;
	serialize(ser_key, input_parameter_key);
	std::string ser_key_str = ser_key.str();

	std::stringstream ser_val;
	serialize(ser_val, input_parameter_val);
	std::string ser_val_str = ser_val.str();

	key.mv_size = ser_key_str.size();
	key.mv_data = ser_key_str.data();

	data.mv_size = ser_val_str.size();
	data.mv_data = ser_val_str.data();

	MDB_txn* txn;
	mdb_txn_begin(this->env, NULL, 0, &txn);
	mdb_put(txn, this->dbi, &key, &data, 0);
	mdb_txn_commit(txn);
}

void ResultsDB::delete_entry(MDB_val& key){
	MDB_txn* txn;
	mdb_txn_begin(this->env, NULL, 0, &txn);

	int rc = mdb_del(txn, this->dbi, &key, NULL);
	if(rc == MDB_SUCCESS)
		mdb_txn_commit(txn);
	else
		mdb_txn_abort(txn);
}

std::ostream& ResultsDB::serialize(std::ostream& os, InputParameter& param){
	os.write(reinterpret_cast<const char*>(&param), offsetof(InputParameter, cl_vertical) + sizeof(param.cl_vertical));
	os.write(reinterpret_cast<const char*>(&param.long_channel_device), sizeof(param.long_channel_device));

	auto size_dvs_voltage = param.dvs_voltage.size();
	os.write(reinterpret_cast<const char*>(&size_dvs_voltage), sizeof(size_dvs_voltage));
	os.write(reinterpret_cast<const char*>(param.dvs_voltage.data()), size_dvs_voltage * sizeof(double));

	return os;
}

std::istream& ResultsDB::deserialize(std::istream& is, InputParameter& param){
	is.read(reinterpret_cast<char*>(&param), offsetof(InputParameter, cl_vertical) + sizeof(param.cl_vertical));
	is.read(reinterpret_cast<char*>(&param.long_channel_device), sizeof(param.long_channel_device));

	decltype(param.dvs_voltage.size()) size_dvs_voltage;
	is.read(reinterpret_cast<char*>(&size_dvs_voltage), sizeof(size_dvs_voltage));
	param.dvs_voltage.resize(size_dvs_voltage);
	is.read(reinterpret_cast<char*>(param.dvs_voltage.data()), size_dvs_voltage * sizeof(double));

	return is;
}
