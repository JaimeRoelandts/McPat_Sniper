#ifdef ENABLE_MEMOIZATION
#include "Ucache.h"
#include <cstring>
#include "results_db.h"
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

//Serializing all elements one-by-one, instead of the whole class directly. As gcc or other compilers might have padded the class, which might contain random bits. This is not ideal, if this is used as a key to search the database.
//However, when using a packed compiler directive, the whole class can be serialized directly (except for the std::vector).
template<> std::ostream& ResultsDB::serialize(std::ostream& os, InputParameter& param){
	os.write(reinterpret_cast<const char*>(&param.cache_sz), sizeof(param.cache_sz));
	os.write(reinterpret_cast<const char*>(&param.line_sz), sizeof(param.line_sz));
	os.write(reinterpret_cast<const char*>(&param.assoc), sizeof(param.assoc));
	os.write(reinterpret_cast<const char*>(&param.nbanks), sizeof(param.nbanks));
	os.write(reinterpret_cast<const char*>(&param.out_w), sizeof(param.out_w));
	os.write(reinterpret_cast<const char*>(&param.specific_tag), sizeof(param.specific_tag));
	os.write(reinterpret_cast<const char*>(&param.tag_w), sizeof(param.tag_w));
	os.write(reinterpret_cast<const char*>(&param.access_mode), sizeof(param.access_mode));
	os.write(reinterpret_cast<const char*>(&param.obj_func_dyn_energy), sizeof(param.obj_func_dyn_energy));
	os.write(reinterpret_cast<const char*>(&param.obj_func_dyn_power), sizeof(param.obj_func_dyn_power));
	os.write(reinterpret_cast<const char*>(&param.obj_func_leak_power), sizeof(param.obj_func_leak_power));
	os.write(reinterpret_cast<const char*>(&param.obj_func_cycle_t), sizeof(param.obj_func_cycle_t));
	os.write(reinterpret_cast<const char*>(&param.F_sz_nm), sizeof(param.F_sz_nm));
	os.write(reinterpret_cast<const char*>(&param.F_sz_um), sizeof(param.F_sz_um));
	os.write(reinterpret_cast<const char*>(&param.specific_hp_vdd), sizeof(param.specific_hp_vdd));
	os.write(reinterpret_cast<const char*>(&param.hp_Vdd), sizeof(param.hp_Vdd));
	os.write(reinterpret_cast<const char*>(&param.specific_lstp_vdd), sizeof(param.specific_lstp_vdd));
	os.write(reinterpret_cast<const char*>(&param.lstp_Vdd), sizeof(param.lstp_Vdd));
	os.write(reinterpret_cast<const char*>(&param.specific_lop_vdd), sizeof(param.specific_lop_vdd));
	os.write(reinterpret_cast<const char*>(&param.lop_Vdd), sizeof(param.lop_Vdd));
	os.write(reinterpret_cast<const char*>(&param.specific_vcc_min), sizeof(param.specific_vcc_min));
	os.write(reinterpret_cast<const char*>(&param.user_defined_vcc_min), sizeof(param.user_defined_vcc_min));
	os.write(reinterpret_cast<const char*>(&param.user_defined_vcc_underflow), sizeof(param.user_defined_vcc_underflow));
	os.write(reinterpret_cast<const char*>(&param.num_rw_ports), sizeof(param.num_rw_ports));
	os.write(reinterpret_cast<const char*>(&param.num_rd_ports), sizeof(param.num_rd_ports));
	os.write(reinterpret_cast<const char*>(&param.num_wr_ports), sizeof(param.num_wr_ports));
	os.write(reinterpret_cast<const char*>(&param.num_se_rd_ports), sizeof(param.num_se_rd_ports));
	os.write(reinterpret_cast<const char*>(&param.num_search_ports), sizeof(param.num_search_ports));
	os.write(reinterpret_cast<const char*>(&param.is_main_mem), sizeof(param.is_main_mem));
	os.write(reinterpret_cast<const char*>(&param.is_cache), sizeof(param.is_cache));
	os.write(reinterpret_cast<const char*>(&param.pure_ram), sizeof(param.pure_ram));
	os.write(reinterpret_cast<const char*>(&param.pure_cam), sizeof(param.pure_cam));
	os.write(reinterpret_cast<const char*>(&param.rpters_in_htree), sizeof(param.rpters_in_htree));
	os.write(reinterpret_cast<const char*>(&param.ver_htree_wires_over_array), sizeof(param.ver_htree_wires_over_array));
	os.write(reinterpret_cast<const char*>(&param.broadcast_addr_din_over_ver_htrees), sizeof(param.broadcast_addr_din_over_ver_htrees));
	os.write(reinterpret_cast<const char*>(&param.temp), sizeof(param.temp));
	os.write(reinterpret_cast<const char*>(&param.ram_cell_tech_type), sizeof(param.ram_cell_tech_type));
	os.write(reinterpret_cast<const char*>(&param.peri_global_tech_type), sizeof(param.peri_global_tech_type));
	os.write(reinterpret_cast<const char*>(&param.data_arr_ram_cell_tech_type), sizeof(param.data_arr_ram_cell_tech_type));
	os.write(reinterpret_cast<const char*>(&param.data_arr_peri_global_tech_type), sizeof(param.data_arr_peri_global_tech_type));
	os.write(reinterpret_cast<const char*>(&param.tag_arr_ram_cell_tech_type), sizeof(param.tag_arr_ram_cell_tech_type));
	os.write(reinterpret_cast<const char*>(&param.tag_arr_peri_global_tech_type), sizeof(param.tag_arr_peri_global_tech_type));
	os.write(reinterpret_cast<const char*>(&param.burst_len), sizeof(param.burst_len));
	os.write(reinterpret_cast<const char*>(&param.int_prefetch_w), sizeof(param.int_prefetch_w));
	os.write(reinterpret_cast<const char*>(&param.page_sz_bits), sizeof(param.page_sz_bits));
	os.write(reinterpret_cast<const char*>(&param.ic_proj_type), sizeof(param.ic_proj_type));
	os.write(reinterpret_cast<const char*>(&param.wire_is_mat_type), sizeof(param.wire_is_mat_type));
	os.write(reinterpret_cast<const char*>(&param.wire_os_mat_type), sizeof(param.wire_os_mat_type));
	os.write(reinterpret_cast<const char*>(&param.wt), sizeof(param.wt));
	os.write(reinterpret_cast<const char*>(&param.force_wiretype), sizeof(param.force_wiretype));
	os.write(reinterpret_cast<const char*>(&param.print_input_args), sizeof(param.print_input_args));
	os.write(reinterpret_cast<const char*>(&param.nuca_cache_sz), sizeof(param.nuca_cache_sz));
	os.write(reinterpret_cast<const char*>(&param.ndbl), sizeof(param.ndbl));
	os.write(reinterpret_cast<const char*>(&param.ndwl), sizeof(param.ndwl));
	os.write(reinterpret_cast<const char*>(&param.nspd), sizeof(param.nspd));
	os.write(reinterpret_cast<const char*>(&param.ndsam1), sizeof(param.ndsam1));
	os.write(reinterpret_cast<const char*>(&param.ndsam2), sizeof(param.ndsam2));
	os.write(reinterpret_cast<const char*>(&param.ndcm), sizeof(param.ndcm));
	os.write(reinterpret_cast<const char*>(&param.force_cache_config), sizeof(param.force_cache_config));
	os.write(reinterpret_cast<const char*>(&param.cache_level), sizeof(param.cache_level));
	os.write(reinterpret_cast<const char*>(&param.cores), sizeof(param.cores));
	os.write(reinterpret_cast<const char*>(&param.nuca_bank_count), sizeof(param.nuca_bank_count));
	os.write(reinterpret_cast<const char*>(&param.force_nuca_bank), sizeof(param.force_nuca_bank));
	os.write(reinterpret_cast<const char*>(&param.delay_wt), sizeof(param.delay_wt));
	os.write(reinterpret_cast<const char*>(&param.dynamic_power_wt), sizeof(param.dynamic_power_wt));
	os.write(reinterpret_cast<const char*>(&param.leakage_power_wt), sizeof(param.leakage_power_wt));
	os.write(reinterpret_cast<const char*>(&param.cycle_time_wt), sizeof(param.cycle_time_wt));
	os.write(reinterpret_cast<const char*>(&param.area_wt), sizeof(param.area_wt));
	os.write(reinterpret_cast<const char*>(&param.delay_wt_nuca), sizeof(param.delay_wt_nuca));
	os.write(reinterpret_cast<const char*>(&param.dynamic_power_wt_nuca), sizeof(param.dynamic_power_wt_nuca));
	os.write(reinterpret_cast<const char*>(&param.leakage_power_wt_nuca), sizeof(param.leakage_power_wt_nuca));
	os.write(reinterpret_cast<const char*>(&param.cycle_time_wt_nuca), sizeof(param.cycle_time_wt_nuca));
	os.write(reinterpret_cast<const char*>(&param.area_wt_nuca), sizeof(param.area_wt_nuca));
	os.write(reinterpret_cast<const char*>(&param.delay_dev), sizeof(param.delay_dev));
	os.write(reinterpret_cast<const char*>(&param.dynamic_power_dev), sizeof(param.dynamic_power_dev));
	os.write(reinterpret_cast<const char*>(&param.leakage_power_dev), sizeof(param.leakage_power_dev));
	os.write(reinterpret_cast<const char*>(&param.cycle_time_dev), sizeof(param.cycle_time_dev));
	os.write(reinterpret_cast<const char*>(&param.area_dev), sizeof(param.area_dev));
	os.write(reinterpret_cast<const char*>(&param.delay_dev_nuca), sizeof(param.delay_dev_nuca));
	os.write(reinterpret_cast<const char*>(&param.dynamic_power_dev_nuca), sizeof(param.dynamic_power_dev_nuca));
	os.write(reinterpret_cast<const char*>(&param.leakage_power_dev_nuca), sizeof(param.leakage_power_dev_nuca));
	os.write(reinterpret_cast<const char*>(&param.cycle_time_dev_nuca), sizeof(param.cycle_time_dev_nuca));
	os.write(reinterpret_cast<const char*>(&param.area_dev_nuca), sizeof(param.area_dev_nuca));
	os.write(reinterpret_cast<const char*>(&param.ed), sizeof(param.ed));
	os.write(reinterpret_cast<const char*>(&param.nuca), sizeof(param.nuca));
	os.write(reinterpret_cast<const char*>(&param.fast_access), sizeof(param.fast_access));
	os.write(reinterpret_cast<const char*>(&param.block_sz), sizeof(param.block_sz));
	os.write(reinterpret_cast<const char*>(&param.tag_assoc), sizeof(param.tag_assoc));
	os.write(reinterpret_cast<const char*>(&param.data_assoc), sizeof(param.data_assoc));
	os.write(reinterpret_cast<const char*>(&param.is_seq_acc), sizeof(param.is_seq_acc));
	os.write(reinterpret_cast<const char*>(&param.fully_assoc), sizeof(param.fully_assoc));
	os.write(reinterpret_cast<const char*>(&param.nsets), sizeof(param.nsets));
	os.write(reinterpret_cast<const char*>(&param.print_detail), sizeof(param.print_detail));
	os.write(reinterpret_cast<const char*>(&param.add_ecc_b_), sizeof(param.add_ecc_b_));
	os.write(reinterpret_cast<const char*>(&param.throughput), sizeof(param.throughput));
	os.write(reinterpret_cast<const char*>(&param.latency), sizeof(param.latency));
	os.write(reinterpret_cast<const char*>(&param.pipelinable), sizeof(param.pipelinable));
	os.write(reinterpret_cast<const char*>(&param.pipeline_stages), sizeof(param.pipeline_stages));
	os.write(reinterpret_cast<const char*>(&param.per_stage_vector), sizeof(param.per_stage_vector));
	os.write(reinterpret_cast<const char*>(&param.with_clock_grid), sizeof(param.with_clock_grid));
	os.write(reinterpret_cast<const char*>(&param.array_power_gated), sizeof(param.array_power_gated));
	os.write(reinterpret_cast<const char*>(&param.bitline_floating), sizeof(param.bitline_floating));
	os.write(reinterpret_cast<const char*>(&param.wl_power_gated), sizeof(param.wl_power_gated));
	os.write(reinterpret_cast<const char*>(&param.cl_power_gated), sizeof(param.cl_power_gated));
	os.write(reinterpret_cast<const char*>(&param.interconect_power_gated), sizeof(param.interconect_power_gated));
	os.write(reinterpret_cast<const char*>(&param.power_gating), sizeof(param.power_gating));
	os.write(reinterpret_cast<const char*>(&param.perfloss), sizeof(param.perfloss));
	os.write(reinterpret_cast<const char*>(&param.cl_vertical), sizeof(param.cl_vertical));

	//serialize vector dvs_voltage
	auto size_dvs_voltage = param.dvs_voltage.size();
	os.write(reinterpret_cast<const char*>(&size_dvs_voltage), sizeof(size_dvs_voltage));
	os.write(reinterpret_cast<const char*>(param.dvs_voltage.data()), size_dvs_voltage * sizeof(double));

	os.write(reinterpret_cast<const char*>(&param.long_channel_device), sizeof(param.long_channel_device));

	return os;
}

//Serializing all elements one-by-one, instead of the whole class directly. As gcc or other compilers might have padded the class, which might contain random bits. This is not ideal, if this is used as a key to search the database.
template<> std::istream& ResultsDB::deserialize(std::istream& is, InputParameter& param){
	is.read(reinterpret_cast<char*>(&param.cache_sz), sizeof(param.cache_sz));
	is.read(reinterpret_cast<char*>(&param.line_sz), sizeof(param.line_sz));
	is.read(reinterpret_cast<char*>(&param.assoc), sizeof(param.assoc));
	is.read(reinterpret_cast<char*>(&param.nbanks), sizeof(param.nbanks));
	is.read(reinterpret_cast<char*>(&param.out_w), sizeof(param.out_w));
	is.read(reinterpret_cast<char*>(&param.specific_tag), sizeof(param.specific_tag));
	is.read(reinterpret_cast<char*>(&param.tag_w), sizeof(param.tag_w));
	is.read(reinterpret_cast<char*>(&param.access_mode), sizeof(param.access_mode));
	is.read(reinterpret_cast<char*>(&param.obj_func_dyn_energy), sizeof(param.obj_func_dyn_energy));
	is.read(reinterpret_cast<char*>(&param.obj_func_dyn_power), sizeof(param.obj_func_dyn_power));
	is.read(reinterpret_cast<char*>(&param.obj_func_leak_power), sizeof(param.obj_func_leak_power));
	is.read(reinterpret_cast<char*>(&param.obj_func_cycle_t), sizeof(param.obj_func_cycle_t));
	is.read(reinterpret_cast<char*>(&param.F_sz_nm), sizeof(param.F_sz_nm));
	is.read(reinterpret_cast<char*>(&param.F_sz_um), sizeof(param.F_sz_um));
	is.read(reinterpret_cast<char*>(&param.specific_hp_vdd), sizeof(param.specific_hp_vdd));
	is.read(reinterpret_cast<char*>(&param.hp_Vdd), sizeof(param.hp_Vdd));
	is.read(reinterpret_cast<char*>(&param.specific_lstp_vdd), sizeof(param.specific_lstp_vdd));
	is.read(reinterpret_cast<char*>(&param.lstp_Vdd), sizeof(param.lstp_Vdd));
	is.read(reinterpret_cast<char*>(&param.specific_lop_vdd), sizeof(param.specific_lop_vdd));
	is.read(reinterpret_cast<char*>(&param.lop_Vdd), sizeof(param.lop_Vdd));
	is.read(reinterpret_cast<char*>(&param.specific_vcc_min), sizeof(param.specific_vcc_min));
	is.read(reinterpret_cast<char*>(&param.user_defined_vcc_min), sizeof(param.user_defined_vcc_min));
	is.read(reinterpret_cast<char*>(&param.user_defined_vcc_underflow), sizeof(param.user_defined_vcc_underflow));
	is.read(reinterpret_cast<char*>(&param.num_rw_ports), sizeof(param.num_rw_ports));
	is.read(reinterpret_cast<char*>(&param.num_rd_ports), sizeof(param.num_rd_ports));
	is.read(reinterpret_cast<char*>(&param.num_wr_ports), sizeof(param.num_wr_ports));
	is.read(reinterpret_cast<char*>(&param.num_se_rd_ports), sizeof(param.num_se_rd_ports));
	is.read(reinterpret_cast<char*>(&param.num_search_ports), sizeof(param.num_search_ports));
	is.read(reinterpret_cast<char*>(&param.is_main_mem), sizeof(param.is_main_mem));
	is.read(reinterpret_cast<char*>(&param.is_cache), sizeof(param.is_cache));
	is.read(reinterpret_cast<char*>(&param.pure_ram), sizeof(param.pure_ram));
	is.read(reinterpret_cast<char*>(&param.pure_cam), sizeof(param.pure_cam));
	is.read(reinterpret_cast<char*>(&param.rpters_in_htree), sizeof(param.rpters_in_htree));
	is.read(reinterpret_cast<char*>(&param.ver_htree_wires_over_array), sizeof(param.ver_htree_wires_over_array));
	is.read(reinterpret_cast<char*>(&param.broadcast_addr_din_over_ver_htrees), sizeof(param.broadcast_addr_din_over_ver_htrees));
	is.read(reinterpret_cast<char*>(&param.temp), sizeof(param.temp));
	is.read(reinterpret_cast<char*>(&param.ram_cell_tech_type), sizeof(param.ram_cell_tech_type));
	is.read(reinterpret_cast<char*>(&param.peri_global_tech_type), sizeof(param.peri_global_tech_type));
	is.read(reinterpret_cast<char*>(&param.data_arr_ram_cell_tech_type), sizeof(param.data_arr_ram_cell_tech_type));
	is.read(reinterpret_cast<char*>(&param.data_arr_peri_global_tech_type), sizeof(param.data_arr_peri_global_tech_type));
	is.read(reinterpret_cast<char*>(&param.tag_arr_ram_cell_tech_type), sizeof(param.tag_arr_ram_cell_tech_type));
	is.read(reinterpret_cast<char*>(&param.tag_arr_peri_global_tech_type), sizeof(param.tag_arr_peri_global_tech_type));
	is.read(reinterpret_cast<char*>(&param.burst_len), sizeof(param.burst_len));
	is.read(reinterpret_cast<char*>(&param.int_prefetch_w), sizeof(param.int_prefetch_w));
	is.read(reinterpret_cast<char*>(&param.page_sz_bits), sizeof(param.page_sz_bits));
	is.read(reinterpret_cast<char*>(&param.ic_proj_type), sizeof(param.ic_proj_type));
	is.read(reinterpret_cast<char*>(&param.wire_is_mat_type), sizeof(param.wire_is_mat_type));
	is.read(reinterpret_cast<char*>(&param.wire_os_mat_type), sizeof(param.wire_os_mat_type));
	is.read(reinterpret_cast<char*>(&param.wt), sizeof(param.wt));
	is.read(reinterpret_cast<char*>(&param.force_wiretype), sizeof(param.force_wiretype));
	is.read(reinterpret_cast<char*>(&param.print_input_args), sizeof(param.print_input_args));
	is.read(reinterpret_cast<char*>(&param.nuca_cache_sz), sizeof(param.nuca_cache_sz));
	is.read(reinterpret_cast<char*>(&param.ndbl), sizeof(param.ndbl));
	is.read(reinterpret_cast<char*>(&param.ndwl), sizeof(param.ndwl));
	is.read(reinterpret_cast<char*>(&param.nspd), sizeof(param.nspd));
	is.read(reinterpret_cast<char*>(&param.ndsam1), sizeof(param.ndsam1));
	is.read(reinterpret_cast<char*>(&param.ndsam2), sizeof(param.ndsam2));
	is.read(reinterpret_cast<char*>(&param.ndcm), sizeof(param.ndcm));
	is.read(reinterpret_cast<char*>(&param.force_cache_config), sizeof(param.force_cache_config));
	is.read(reinterpret_cast<char*>(&param.cache_level), sizeof(param.cache_level));
	is.read(reinterpret_cast<char*>(&param.cores), sizeof(param.cores));
	is.read(reinterpret_cast<char*>(&param.nuca_bank_count), sizeof(param.nuca_bank_count));
	is.read(reinterpret_cast<char*>(&param.force_nuca_bank), sizeof(param.force_nuca_bank));
	is.read(reinterpret_cast<char*>(&param.delay_wt), sizeof(param.delay_wt));
	is.read(reinterpret_cast<char*>(&param.dynamic_power_wt), sizeof(param.dynamic_power_wt));
	is.read(reinterpret_cast<char*>(&param.leakage_power_wt), sizeof(param.leakage_power_wt));
	is.read(reinterpret_cast<char*>(&param.cycle_time_wt), sizeof(param.cycle_time_wt));
	is.read(reinterpret_cast<char*>(&param.area_wt), sizeof(param.area_wt));
	is.read(reinterpret_cast<char*>(&param.delay_wt_nuca), sizeof(param.delay_wt_nuca));
	is.read(reinterpret_cast<char*>(&param.dynamic_power_wt_nuca), sizeof(param.dynamic_power_wt_nuca));
	is.read(reinterpret_cast<char*>(&param.leakage_power_wt_nuca), sizeof(param.leakage_power_wt_nuca));
	is.read(reinterpret_cast<char*>(&param.cycle_time_wt_nuca), sizeof(param.cycle_time_wt_nuca));
	is.read(reinterpret_cast<char*>(&param.area_wt_nuca), sizeof(param.area_wt_nuca));
	is.read(reinterpret_cast<char*>(&param.delay_dev), sizeof(param.delay_dev));
	is.read(reinterpret_cast<char*>(&param.dynamic_power_dev), sizeof(param.dynamic_power_dev));
	is.read(reinterpret_cast<char*>(&param.leakage_power_dev), sizeof(param.leakage_power_dev));
	is.read(reinterpret_cast<char*>(&param.cycle_time_dev), sizeof(param.cycle_time_dev));
	is.read(reinterpret_cast<char*>(&param.area_dev), sizeof(param.area_dev));
	is.read(reinterpret_cast<char*>(&param.delay_dev_nuca), sizeof(param.delay_dev_nuca));
	is.read(reinterpret_cast<char*>(&param.dynamic_power_dev_nuca), sizeof(param.dynamic_power_dev_nuca));
	is.read(reinterpret_cast<char*>(&param.leakage_power_dev_nuca), sizeof(param.leakage_power_dev_nuca));
	is.read(reinterpret_cast<char*>(&param.cycle_time_dev_nuca), sizeof(param.cycle_time_dev_nuca));
	is.read(reinterpret_cast<char*>(&param.area_dev_nuca), sizeof(param.area_dev_nuca));
	is.read(reinterpret_cast<char*>(&param.ed), sizeof(param.ed));
	is.read(reinterpret_cast<char*>(&param.nuca), sizeof(param.nuca));
	is.read(reinterpret_cast<char*>(&param.fast_access), sizeof(param.fast_access));
	is.read(reinterpret_cast<char*>(&param.block_sz), sizeof(param.block_sz));
	is.read(reinterpret_cast<char*>(&param.tag_assoc), sizeof(param.tag_assoc));
	is.read(reinterpret_cast<char*>(&param.data_assoc), sizeof(param.data_assoc));
	is.read(reinterpret_cast<char*>(&param.is_seq_acc), sizeof(param.is_seq_acc));
	is.read(reinterpret_cast<char*>(&param.fully_assoc), sizeof(param.fully_assoc));
	is.read(reinterpret_cast<char*>(&param.nsets), sizeof(param.nsets));
	is.read(reinterpret_cast<char*>(&param.print_detail), sizeof(param.print_detail));
	is.read(reinterpret_cast<char*>(&param.add_ecc_b_), sizeof(param.add_ecc_b_));
	is.read(reinterpret_cast<char*>(&param.throughput), sizeof(param.throughput));
	is.read(reinterpret_cast<char*>(&param.latency), sizeof(param.latency));
	is.read(reinterpret_cast<char*>(&param.pipelinable), sizeof(param.pipelinable));
	is.read(reinterpret_cast<char*>(&param.pipeline_stages), sizeof(param.pipeline_stages));
	is.read(reinterpret_cast<char*>(&param.per_stage_vector), sizeof(param.per_stage_vector));
	is.read(reinterpret_cast<char*>(&param.with_clock_grid), sizeof(param.with_clock_grid));
	is.read(reinterpret_cast<char*>(&param.array_power_gated), sizeof(param.array_power_gated));
	is.read(reinterpret_cast<char*>(&param.bitline_floating), sizeof(param.bitline_floating));
	is.read(reinterpret_cast<char*>(&param.wl_power_gated), sizeof(param.wl_power_gated));
	is.read(reinterpret_cast<char*>(&param.cl_power_gated), sizeof(param.cl_power_gated));
	is.read(reinterpret_cast<char*>(&param.interconect_power_gated), sizeof(param.interconect_power_gated));
	is.read(reinterpret_cast<char*>(&param.power_gating), sizeof(param.power_gating));
	is.read(reinterpret_cast<char*>(&param.perfloss), sizeof(param.perfloss));
	is.read(reinterpret_cast<char*>(&param.cl_vertical), sizeof(param.cl_vertical));

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
#endif //ENABLE_MEMOIZATION
