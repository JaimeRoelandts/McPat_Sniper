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

void printInputParameter(const InputParameter& val){
	std::cout << "Input Parameter " << std::endl << std::hexfloat;
	std::cout << "cache_sz" << std::setw(15) << val.cache_sz << std::endl;
	std::cout << "line_sz" << std::setw(15) << val.line_sz << std::endl;
	std::cout << "assoc" << std::setw(15) << val.assoc << std::endl;
	std::cout << "nbanks" << std::setw(15) << val.nbanks << std::endl;
	std::cout << "out_w" << std::setw(15) << val.out_w << std::endl;
	std::cout << "specific_tag" << std::setw(15) << val.specific_tag << std::endl;
	std::cout << "tag_w" << std::setw(15) << val.tag_w << std::endl;
	std::cout << "access_mode" << std::setw(15) << val.access_mode << std::endl;
	std::cout << "obj_func_dyn_energy" << std::setw(15) << val.obj_func_dyn_energy << std::endl;
	std::cout << "obj_func_dyn_power" << std::setw(15) << val.obj_func_dyn_power << std::endl;
	std::cout << "obj_func_leak_power" << std::setw(15) << val.obj_func_leak_power << std::endl;
	std::cout << "obj_func_cycle_t" << std::setw(15) << val.obj_func_cycle_t << std::endl;
	std::cout << "F_sz_nm" << std::setw(15) << val.F_sz_nm << std::endl;
	std::cout << "F_sz_um" << std::setw(15) << val.F_sz_um << std::endl;
	std::cout << "specific_hp_vdd" << std::setw(15) << val.specific_hp_vdd << std::endl;
	std::cout << "hp_Vdd" << std::setw(15) << val.hp_Vdd << std::endl;
	std::cout << "specific_lstp_vdd" << std::setw(15) << val.specific_lstp_vdd << std::endl;
	std::cout << "lstp_Vdd" << std::setw(15) << val.lstp_Vdd << std::endl;
	std::cout << "specific_lop_vdd" << std::setw(15) << val.specific_lop_vdd << std::endl;
	std::cout << "lop_Vdd" << std::setw(15) << val.lop_Vdd << std::endl;
	std::cout << "specific_vcc_min" << std::setw(15) << val.specific_vcc_min << std::endl;
	std::cout << "user_defined_vcc_min" << std::setw(15) << val.user_defined_vcc_min << std::endl;
	std::cout << "user_defined_vcc_underflow" << std::setw(15) << val.user_defined_vcc_underflow << std::endl;
	std::cout << "num_rw_ports" << std::setw(15) << val.num_rw_ports << std::endl;
	std::cout << "num_rd_ports" << std::setw(15) << val.num_rd_ports << std::endl;
	std::cout << "num_wr_ports" << std::setw(15) << val.num_wr_ports << std::endl;
	std::cout << "num_se_rd_ports" << std::setw(15) << val.num_se_rd_ports << std::endl;
	std::cout << "num_search_ports" << std::setw(15) << val.num_search_ports << std::endl;
	std::cout << "is_main_mem" << std::setw(15) << val.is_main_mem << std::endl;
	std::cout << "is_cache" << std::setw(15) << val.is_cache << std::endl;
	std::cout << "pure_ram" << std::setw(15) << val.pure_ram << std::endl;
	std::cout << "pure_cam" << std::setw(15) << val.pure_cam << std::endl;
	std::cout << "rpters_in_htree" << std::setw(15) << val.rpters_in_htree << std::endl;
	std::cout << "ver_htree_wires_over_array" << std::setw(15) << val.ver_htree_wires_over_array << std::endl;
	std::cout << "broadcast_addr_din_over_ver_htrees" << std::setw(15) << val.broadcast_addr_din_over_ver_htrees << std::endl;
	std::cout << "temp" << std::setw(15) << val.temp << std::endl;
	std::cout << "ram_cell_tech_type" << std::setw(15) << val.ram_cell_tech_type << std::endl;
	std::cout << "peri_global_tech_type" << std::setw(15) << val.peri_global_tech_type << std::endl;
	std::cout << "data_arr_ram_cell_tech_type" << std::setw(15) << val.data_arr_ram_cell_tech_type << std::endl;
	std::cout << "data_arr_peri_global_tech_type" << std::setw(15) << val.data_arr_peri_global_tech_type << std::endl;
	std::cout << "tag_arr_ram_cell_tech_type" << std::setw(15) << val.tag_arr_ram_cell_tech_type << std::endl;
	std::cout << "tag_arr_peri_global_tech_type" << std::setw(15) << val.tag_arr_peri_global_tech_type << std::endl;
	std::cout << "burst_len" << std::setw(15) << val.burst_len << std::endl;
	std::cout << "int_prefetch_w" << std::setw(15) << val.int_prefetch_w << std::endl;
	std::cout << "page_sz_bits" << std::setw(15) << val.page_sz_bits << std::endl;
	std::cout << "ic_proj_type" << std::setw(15) << val.ic_proj_type << std::endl;
	std::cout << "wire_is_mat_type" << std::setw(15) << val.wire_is_mat_type << std::endl;
	std::cout << "wire_os_mat_type" << std::setw(15) << val.wire_os_mat_type << std::endl;
	std::cout << "wt" << std::setw(15) << val.wt << std::endl;
	std::cout << "force_wiretype" << std::setw(15) << val.force_wiretype << std::endl;
	std::cout << "print_input_args" << std::setw(15) << val.print_input_args << std::endl;
	std::cout << "nuca_cache_sz" << std::setw(15) << val.nuca_cache_sz << std::endl;
	std::cout << "ndbl" << std::setw(15) << val.ndbl << std::endl;
	std::cout << "ndwl" << std::setw(15) << val.ndwl << std::endl;
	std::cout << "nspd" << std::setw(15) << val.nspd << std::endl;
	std::cout << "ndsam1" << std::setw(15) << val.ndsam1 << std::endl;
	std::cout << "ndsam2" << std::setw(15) << val.ndsam2 << std::endl;
	std::cout << "ndcm" << std::setw(15) << val.ndcm << std::endl;
	std::cout << "force_cache_config" << std::setw(15) << val.force_cache_config << std::endl;
	std::cout << "cache_level" << std::setw(15) << val.cache_level << std::endl;
	std::cout << "cores" << std::setw(15) << val.cores << std::endl;
	std::cout << "nuca_bank_count" << std::setw(15) << val.nuca_bank_count << std::endl;
	std::cout << "force_nuca_bank" << std::setw(15) << val.force_nuca_bank << std::endl;
	std::cout << "delay_wt" << std::setw(15) << val.delay_wt << std::endl;
	std::cout << "dynamic_power_wt" << std::setw(15) << val.dynamic_power_wt << std::endl;
	std::cout << "leakage_power_wt" << std::setw(15) << val.leakage_power_wt << std::endl;
	std::cout << "cycle_time_wt" << std::setw(15) << val.cycle_time_wt << std::endl;
	std::cout << "area_wt" << std::setw(15) << val.area_wt << std::endl;
	std::cout << "delay_wt_nuca" << std::setw(15) << val.delay_wt_nuca << std::endl;
	std::cout << "dynamic_power_wt_nuca" << std::setw(15) << val.dynamic_power_wt_nuca << std::endl;
	std::cout << "leakage_power_wt_nuca" << std::setw(15) << val.leakage_power_wt_nuca << std::endl;
	std::cout << "cycle_time_wt_nuca" << std::setw(15) << val.cycle_time_wt_nuca << std::endl;
	std::cout << "area_wt_nuca" << std::setw(15) << val.area_wt_nuca << std::endl;
	std::cout << "delay_dev" << std::setw(15) << val.delay_dev << std::endl;
	std::cout << "dynamic_power_dev" << std::setw(15) << val.dynamic_power_dev << std::endl;
	std::cout << "leakage_power_dev" << std::setw(15) << val.leakage_power_dev << std::endl;
	std::cout << "cycle_time_dev" << std::setw(15) << val.cycle_time_dev << std::endl;
	std::cout << "area_dev" << std::setw(15) << val.area_dev << std::endl;
	std::cout << "delay_dev_nuca" << std::setw(15) << val.delay_dev_nuca << std::endl;
	std::cout << "dynamic_power_dev_nuca" << std::setw(15) << val.dynamic_power_dev_nuca << std::endl;
	std::cout << "leakage_power_dev_nuca" << std::setw(15) << val.leakage_power_dev_nuca << std::endl;
	std::cout << "cycle_time_dev_nuca" << std::setw(15) << val.cycle_time_dev_nuca << std::endl;
	std::cout << "area_dev_nuca" << std::setw(15) << val.area_dev_nuca << std::endl;
	std::cout << "ed" << std::setw(15) << val.ed << std::endl;
	std::cout << "nuca" << std::setw(15) << val.nuca << std::endl;
	std::cout << "fast_access" << std::setw(15) << val.fast_access << std::endl;
	std::cout << "block_sz" << std::setw(15) << val.block_sz << std::endl;
	std::cout << "tag_assoc" << std::setw(15) << val.tag_assoc << std::endl;
	std::cout << "data_assoc" << std::setw(15) << val.data_assoc << std::endl;
	std::cout << "is_seq_acc" << std::setw(15) << val.is_seq_acc << std::endl;
	std::cout << "fully_assoc" << std::setw(15) << val.fully_assoc << std::endl;
	std::cout << "nsets" << std::setw(15) << val.nsets << std::endl;
	std::cout << "print_detail" << std::setw(15) << val.print_detail << std::endl;
	std::cout << "add_ecc_b_" << std::setw(15) << val.add_ecc_b_ << std::endl;
	std::cout << "throughput" << std::setw(15) << val.throughput << std::endl;
	std::cout << "latency" << std::setw(15) << val.latency << std::endl;
	std::cout << "pipelinable" << std::setw(15) << val.pipelinable << std::endl;
	std::cout << "pipeline_stages" << std::setw(15) << val.pipeline_stages << std::endl;
	std::cout << "per_stage_vector" << std::setw(15) << val.per_stage_vector << std::endl;
	std::cout << "with_clock_grid" << std::setw(15) << val.with_clock_grid << std::endl;
	std::cout << "array_power_gated" << std::setw(15) << val.array_power_gated << std::endl;
	std::cout << "bitline_floating" << std::setw(15) << val.bitline_floating << std::endl;
	std::cout << "wl_power_gated" << std::setw(15) << val.wl_power_gated << std::endl;
	std::cout << "cl_power_gated" << std::setw(15) << val.cl_power_gated << std::endl;
	std::cout << "interconect_power_gated" << std::setw(15) << val.interconect_power_gated << std::endl;
	std::cout << "power_gating" << std::setw(15) << val.power_gating << std::endl;
	std::cout << "perfloss" << std::setw(15) << val.perfloss << std::endl;
	std::cout << "cl_vertical" << std::setw(15) << val.cl_vertical << std::endl;
	std::cout << "dvs_voltage_size" << std::setw(15) << val.dvs_voltage.size() << std::endl;
	for (auto voltage : val.dvs_voltage)
		std::cout << "voltage" << std::setw(15) << voltage << std::endl;
	std::cout << "long_channel_device" << std::setw(15) << val.long_channel_device << std::endl;
	std::cout << "============================================================================" << std::endl << std::defaultfloat;
}

bool ResultsDB::get(InputParameter& input_parameter_key, uca_org_t& uca_org_val){
	MDB_val key, data;

	std::stringstream ser_key;
	serialize(ser_key, input_parameter_key);
	std::cout << "Finding key: " << std::endl;
	printInputParameter(input_parameter_key);
	std::string ser_key_str = ser_key.str();
	std::cout << "Key size is " << ser_key_str.size() << ", and data: " << std::hex << std::setfill('0');
	for (unsigned char c: ser_key_str)
		std::cout << std::setw(2) << static_cast<int>(c) << " ";
	std::cout << std::setfill(' ') << std::dec << std::endl;

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
