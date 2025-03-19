#include "results_db.h"
#include "Ucache.h"
#include <cstring>

ResultsDB::ResultsDB() : ResultsDB(create_tmp_path()){}

std::filesystem::path ResultsDB::create_tmp_path(){
	std::filesystem::path tmp_dir = getenv("TEMPDIR") ? std::filesystem::path(getenv("TEMPDIR")) : std::filesystem::path("/tmp");
	std::string user = getenv("USER") ? getenv("USER") : "unknown";
	std::string file_name = "mcpat-" + user + ".db";
	return tmp_dir / file_name;
}

ResultsDB::ResultsDB(std::string database_path) : ResultsDB(std::filesystem::path(database_path)){}

ResultsDB::ResultsDB(std::filesystem::path database_path): 
	database_path(database_path),
	env(nullptr),
	dbi(0)
{
	open_database();
}

ResultsDB::~ResultsDB(){
	close_database();
}

ResultsDB& ResultsDB::getInstance(){
	static ResultsDB instance;
	return instance;
}

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
void ResultsDB::delete_entry(MDB_val& key){
	MDB_txn* txn;
	mdb_txn_begin(this->env, NULL, 0, &txn);

	int rc = mdb_del(txn, this->dbi, &key, NULL);
	if(rc == MDB_SUCCESS)
		mdb_txn_commit(txn);
	else
		mdb_txn_abort(txn);
}

bool ResultsDB::get(InputParameter& input_parameter_key, uca_org_t& uca_org_val){
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

	// if(data.mv_size != sizeof(InputParameter)){
	// 	mdb_txn_abort(txn);
	// 	delete_entry(key);
	// 	return false;
	// }

	std::stringstream ser_val;
	ser_val.write(static_cast<const char*>(data.mv_data), data.mv_size);
	deserialize(ser_val, uca_org_val);

	mdb_txn_commit(txn);
	return true;
}

void ResultsDB::put(InputParameter& input_parameter_key, uca_org_t& uca_org_val){
	MDB_val key, data;

	std::stringstream ser_key;
	serialize(ser_key, input_parameter_key);
	std::string ser_key_str = ser_key.str();

	std::stringstream ser_val;
	serialize(ser_val, uca_org_val);
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

template<typename T> std::ostream& ResultsDB::serialize(std::ostream& os, T* param){
	bool present = false;
	if(param == nullptr || param == NULL)
		os.write(reinterpret_cast<const char*>(&present), sizeof(bool));
	else {
		present = true;
		os.write(reinterpret_cast<const char*>(&present), sizeof(bool));
		serialize(os, *param);
	}
	return os;
}

template<typename T> std::istream& ResultsDB::deserialize(std::istream& is, T** param){
	bool present = false;
	is.read(reinterpret_cast<char*>(&present), sizeof(bool));
	if (! present)
		*param = nullptr;
	else {
		T* temp = new T();
		deserialize(is, *temp);
		*param = temp;
	}

	return is;
}

template<typename T> std::ostream& ResultsDB::serialize(std::ostream& os, T &param){
	static_assert(sizeof(T) == 0, "serialize() is not implemented for this type.");
	return os;
}

template<typename T> std::istream& ResultsDB::deserialize(std::istream& is, T &param){
	static_assert(sizeof(T) == 0, "deserialize() is not implemented for this type.");
	return is;
}

template<> std::ostream& ResultsDB::serialize(std::ostream& os, InputParameter& param){
	os.write(reinterpret_cast<const char*>(&param), offsetof(InputParameter, cl_vertical) + sizeof(param.cl_vertical));

	//serialize vector dvs_voltage
	auto size_dvs_voltage = param.dvs_voltage.size();
	os.write(reinterpret_cast<const char*>(&size_dvs_voltage), sizeof(size_dvs_voltage));
	os.write(reinterpret_cast<const char*>(param.dvs_voltage.data()), size_dvs_voltage * sizeof(double));

	os.write(reinterpret_cast<const char*>(&param.long_channel_device), sizeof(param.long_channel_device));

	return os;
}

template<> std::istream& ResultsDB::deserialize(std::istream& is, InputParameter& param){
	is.read(reinterpret_cast<char*>(&param), offsetof(InputParameter, cl_vertical) + sizeof(param.cl_vertical));

	//deserialize vector dvs_voltage
	decltype(param.dvs_voltage.size()) size_dvs_voltage;
	is.read(reinterpret_cast<char*>(&size_dvs_voltage), sizeof(size_dvs_voltage));
	param.dvs_voltage.resize(size_dvs_voltage);
	is.read(reinterpret_cast<char*>(param.dvs_voltage.data()), size_dvs_voltage * sizeof(double));

	is.read(reinterpret_cast<char*>(&param.long_channel_device), sizeof(param.long_channel_device));

	return is;
}

//TODO !!!!!!!!!!!!!! I need to check for the pointers of uca_org_t if they are not null. Write a bool before it, to know wether it is present, if true, read it, if not, assume nullptr.

//need to serialize mem_array pointers, uca_q, uca_pg_reference
//PowerDef is fine, results_mem_array is fine too,
template<> std::ostream& ResultsDB::serialize(std::ostream& os, uca_org_t& param){
	size_t start_continuous_data = offsetof(uca_org_t, access_time);
	size_t end_continuous_data = offsetof(uca_org_t, data_array) + sizeof(results_mem_array);
	os.write(reinterpret_cast<const char*>(&param) + start_continuous_data, end_continuous_data - start_continuous_data);

	//tag_array2 pointer
	serialize(os, param.tag_array2);
	
	//data_array2 pointer
	serialize(os, param.data_array2);
	
	//uca_q vector<pointer>
	auto size_uca_q = param.uca_q.size();
	os.write(reinterpret_cast<const char*>(&size_uca_q), sizeof(size_uca_q));
	for(auto uca_entry: param.uca_q)
		serialize(os, uca_entry);
	
	//uca_pg_reference pointer
	serialize(os, param.uca_pg_reference);

	return os;
}

template<> std::istream& ResultsDB::deserialize(std::istream& is, uca_org_t& param){
	size_t start_continuous_data = offsetof(uca_org_t, access_time);
	size_t end_continuous_data = offsetof(uca_org_t, data_array) + sizeof(results_mem_array);
	is.read(reinterpret_cast<char*>(&param) + start_continuous_data, end_continuous_data - start_continuous_data);

	//tag_array2 pointer
	mem_array* tag_array2 = nullptr;
	deserialize(is, &tag_array2);
	param.tag_array2 = tag_array2;
	
	//data_array2 pointer
	mem_array* data_array2 = nullptr;
	deserialize(is, &data_array2);
	param.data_array2 = data_array2;
	
	//uca_q vector<pointer>
	decltype(param.uca_q.size()) size_uca_q;
	is.read(reinterpret_cast<char*>(&size_uca_q), sizeof(size_uca_q));
	param.uca_q.resize(size_uca_q);
	for(size_t idx = 0; idx < size_uca_q; idx++){
		uca_org_t* uca_entry = nullptr;
		deserialize(is, &uca_entry);
		param.uca_q[idx] = uca_entry;
	}
	
	//uca_pg_reference pointer
	uca_org_t* uca_pg_reference = nullptr;
	deserialize(is, &uca_pg_reference);
	param.uca_pg_reference = uca_pg_reference;

	return is;
}

template<> std::ostream& ResultsDB::serialize(std::ostream& os, mem_array& param){
	//part1 of continuous data
	os.write(reinterpret_cast<const char*>(&param), offsetof(mem_array, power_matchline_to_wordline_drv) + sizeof(powerDef));

	//arr_min pointer
	serialize(os, param.arr_min);

	//part2 of continuous data
	size_t start_part2 = offsetof(mem_array, wt);
	size_t end_part2 = offsetof(mem_array, long_channel_leakage_reduction_memcell) + sizeof(double);
	os.write(reinterpret_cast<const char*>(&param) + start_part2, end_part2 - start_part2);

	return os;
}

template<> std::istream& ResultsDB::deserialize(std::istream& is, mem_array& param){
	//part1 of continuous data
	is.read(reinterpret_cast<char*>(&param), offsetof(mem_array, power_matchline_to_wordline_drv) + sizeof(powerDef));

	//arr_min pointer
	min_values_t* arr_min = nullptr;
	deserialize(is, &arr_min);
	param.arr_min = arr_min;

	//part2 of continuous data
	size_t start_part2 = offsetof(mem_array, wt);
	size_t end_part2 = offsetof(mem_array, long_channel_leakage_reduction_memcell) + sizeof(double);
	is.read(reinterpret_cast<char*>(&param) + start_part2, end_part2 - start_part2);

	return is;
}

template<> std::ostream& ResultsDB::serialize(std::ostream& os, min_values_t& param){
	os.write(reinterpret_cast<const char*>(&param), sizeof(min_values_t));
	return os;
}

template<> std::istream& ResultsDB::deserialize(std::istream& is, min_values_t& param){
	is.read(reinterpret_cast<char*>(&param), sizeof(min_values_t));
	return is;
}
