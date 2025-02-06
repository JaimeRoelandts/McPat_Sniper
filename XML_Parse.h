/*****************************************************************************
 *                                McPAT
 *                      SOFTWARE LICENSE AGREEMENT
 *            Copyright 2012 Hewlett-Packard Development Company, L.P.
 *                          All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.”
 *
 ***************************************************************************/

#ifndef XML_PARSE_H_
#define XML_PARSE_H_

#include <string>
#include <vector>
#include <boost/property_tree/xml_parser.hpp>

//all subnodes at the level of system.core(0-n)
//cache_policy is added into cache property arrays;//0 no write or write-though with non-write allocate;1 write-back with write-allocate

class PredictorSystemCore{
	public:
		int prediction_width;
		std::string prediction_scheme;
		int predictor_size;
		int predictor_entries;
		std::vector<int> local_predictor_size;
		int local_predictor_entries;
		int global_predictor_entries;
		int global_predictor_bits;
		int chooser_predictor_entries;
		int chooser_predictor_bits;
		double predictor_accesses;

		//constructor
		PredictorSystemCore() = default;
		PredictorSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class ItlbSystemCore{
	public:
		int number_entries;
		int cache_policy;//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		double total_hits;
		double total_accesses;
		double total_misses;
		double conflicts;

		//constructor
		ItlbSystemCore() = default;
		ItlbSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class IcacheSystemCore{
	public:
		//params
		std::vector<double> icache_config;
		std::vector<int> buffer_sizes;
		int cache_policy;//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		//stats
		double total_accesses;
		double read_accesses;
		double read_misses;
		double replacements;
		double read_hits;
		double total_hits;
		double total_misses;
		double miss_buffer_access;
		double fill_buffer_accesses;
		double prefetch_buffer_accesses;
		double prefetch_buffer_writes;
		double prefetch_buffer_reads;
		double prefetch_buffer_hits;
		double conflicts;

		//constructor
		IcacheSystemCore() = default;
		IcacheSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class DtlbSystemCore{
	public:
		//params
		int number_entries;
		int cache_policy;//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		//stats
		double total_accesses;
		double read_accesses;
		double write_accesses;
		double write_hits;
		double read_hits;
		double read_misses;
		double write_misses;
		double total_hits;
		double total_misses;
		double conflicts;

		//constructor
		DtlbSystemCore() = default;
		DtlbSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class DcacheSystemCore{
	public:
		//params
		std::vector<double> dcache_config;
		std::vector<int> buffer_sizes;
		int cache_policy;//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		//stats
		double total_accesses;
		double read_accesses;
		double write_accesses;
		double total_hits;
		double total_misses;
		double read_hits;
		double write_hits;
		double read_misses;
		double write_misses;
		double replacements;
		double write_backs;
		double miss_buffer_access;
		double fill_buffer_accesses;
		double prefetch_buffer_accesses;
		double prefetch_buffer_writes;
		double prefetch_buffer_reads;
		double prefetch_buffer_hits;
		double wbb_writes;
		double wbb_reads;
		double conflicts;

		//constructor
		DcacheSystemCore() = default;
		DcacheSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class BtbSystemCore{
	public:
		//params
		std::vector<int> BTB_config;
		//stats
		double total_accesses;
		double read_accesses;
		double write_accesses;
		double total_hits;
		double total_misses;
		double read_hits;
		double write_hits;
		double read_misses;
		double write_misses;
		double replacements;

		//constructor
		BtbSystemCore() = default;
		BtbSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemCore{
	public:
		//all params at the level of system.core(0-n)
		int clock_rate;
		bool opt_local;
		bool x86;
		int machine_bits;
		int virtual_address_width;
		int physical_address_width;
		int opcode_width;
		int micro_opcode_width;
		int instruction_length;
		int machine_type;
		int internal_datapath_width;
		int number_hardware_threads;
		int fetch_width;
		int number_instruction_fetch_ports;
		int decode_width;
		int issue_width;
		int peak_issue_width;
		int commit_width;
		std::vector<int> pipelines_per_core;
		std::vector<int> pipeline_depth;
		std::string FPU;
		std::string divider_multiplier;
		int ALU_per_core;
		double FPU_per_core;
		int MUL_per_core;
		int instruction_buffer_size;
		int decoded_stream_buffer_size;
		int instruction_window_scheme;
		int instruction_window_size;
		int fp_instruction_window_size;
		int ROB_size;
		int archi_Regs_IRF_size;
		int archi_Regs_FRF_size;
		int phy_Regs_IRF_size;
		int phy_Regs_FRF_size;
		int rename_scheme;
		int checkpoint_depth;
		int register_windows_size;
		std::string LSU_order;
		int store_buffer_size;
		int load_buffer_size;
		int memory_ports;
		std::string Dcache_dual_pump;
		int RAS_size;
		int fp_issue_width;
		int prediction_width;
		int number_of_BTB;
		int number_of_BPT;

		//all stats at the level of system.core(0-n)
		double total_instructions;
		double int_instructions;
		double fp_instructions;
		double branch_instructions;
		double branch_mispredictions;
		double committed_instructions;
		double committed_int_instructions;
		double committed_fp_instructions;
		double load_instructions;
		double store_instructions;
		double total_cycles;
		double idle_cycles;
		double busy_cycles;
		double instruction_buffer_reads;
		double instruction_buffer_write;
		double ROB_reads;
		double ROB_writes;
		double rename_accesses;
		double fp_rename_accesses;
		double rename_reads;
		double rename_writes;
		double fp_rename_reads;
		double fp_rename_writes;
		double inst_window_reads;
		double inst_window_writes;
		double inst_window_wakeup_accesses;
		double inst_window_selections;
		double fp_inst_window_reads;
		double fp_inst_window_writes;
		double fp_inst_window_wakeup_accesses;
		double fp_inst_window_selections;
		double archi_int_regfile_reads;
		double archi_float_regfile_reads;
		double phy_int_regfile_reads;
		double phy_float_regfile_reads;
		double phy_int_regfile_writes;
		double phy_float_regfile_writes;
		double archi_int_regfile_writes;
		double archi_float_regfile_writes;
		double int_regfile_reads;
		double float_regfile_reads;
		double int_regfile_writes;
		double float_regfile_writes;
		double windowed_reg_accesses;
		double windowed_reg_transports;
		double function_calls;
		double context_switches;
		double ialu_accesses;
		double fpu_accesses;
		double mul_accesses;
		double cdb_alu_accesses;
		double cdb_mul_accesses;
		double cdb_fpu_accesses;
		double load_buffer_reads;
		double load_buffer_writes;
		double load_buffer_cams;
		double store_buffer_reads;
		double store_buffer_writes;
		double store_buffer_cams;
		double store_buffer_forwards;
		double main_memory_access;
		double main_memory_read;
		double main_memory_write;
		double pipeline_duty_cycle;

		double IFU_duty_cycle ;
		double BR_duty_cycle ;
		double LSU_duty_cycle ;
		double MemManU_I_duty_cycle;
		double MemManU_D_duty_cycle ;
		double ALU_duty_cycle ;
		double MUL_duty_cycle ;
		double FPU_duty_cycle ;
		double ALU_cdb_duty_cycle ;
		double MUL_cdb_duty_cycle ;
		double FPU_cdb_duty_cycle ;

		double vdd;
		double power_gating_vcc;

		//all subnodes at the level of system.core(0-n)
		PredictorSystemCore predictor;
		ItlbSystemCore itlb;
		IcacheSystemCore icache;
		DtlbSystemCore dtlb;
		DcacheSystemCore dcache;
		BtbSystemCore BTB;

		//constructor
		SystemCore() = default;
		SystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemCacheDirectory{
	public:
		//params
		int Directory_type;
		std::vector<double> Dir_config;
		std::vector<int> buffer_sizes;
		int clockrate;
		std::vector<int> ports;
		int device_type;
		int cache_policy;//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		std::string threeD_stack;
		double vdd;
		double power_gating_vcc;
		//stats
		double total_accesses;
		double read_accesses;
		double write_accesses;
		double read_misses;
		double write_misses;
		double conflicts;
		double duty_cycle;

		//constructor
		SystemCacheDirectory() = default;
		SystemCacheDirectory(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class SystemCache{
	public:
		//params
		std::vector<double> cache_config;
		int clockrate;
		std::vector<int> ports;
		int device_type;
		int cache_policy;//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		std::string threeD_stack = "default";
		std::vector<int> buffer_sizes;
		double vdd;
		double power_gating_vcc = -1;
		bool   merged_dir;
		//stats
		double total_accesses;
		double read_accesses;
		double write_accesses;
		double total_hits;
		double total_misses;
		double read_hits;
		double write_hits;
		double read_misses;
		double write_misses;
		double replacements;
		double write_backs;
		double miss_buffer_accesses;
		double fill_buffer_accesses;
		double prefetch_buffer_accesses;
		double prefetch_buffer_writes;
		double prefetch_buffer_reads;
		double prefetch_buffer_hits;
		double wbb_writes;
		double wbb_reads;
		double conflicts;
		double duty_cycle;

		double homenode_read_accesses;
		double homenode_write_accesses;
		double homenode_read_hits;
		double homenode_write_hits;
		double homenode_read_misses;
		double homenode_write_misses;
		double dir_duty_cycle;

		//constructor
		SystemCache() = default;
		SystemCache(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class Xbar0SystemNoC{
	public:
		//params
		int number_of_inputs_of_crossbars;
		int number_of_outputs_of_crossbars;
		int flit_bits;
		int input_buffer_entries_per_port;
		std::vector<int> ports_of_input_buffer;
		//stats
		double crossbar_accesses;

		//constructor
		Xbar0SystemNoC() = default;
		Xbar0SystemNoC(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemNoC{
	public:
		//params
		int clockrate;
		bool type;
		bool has_global_link;
		std::string topology;
		int horizontal_nodes;
		int vertical_nodes;
		int link_throughput;
		int link_latency;
		int input_ports;
		int output_ports;
		int virtual_channel_per_port;
		int flit_bits;
		int input_buffer_entries_per_vc;
		std::vector<int> ports_of_input_buffer;
		int dual_pump;
		int number_of_crossbars;
		std::string crossbar_type;
		std::string crosspoint_type;
		Xbar0SystemNoC xbar0;
		int arbiter_type;
		double chip_coverage;
		double vdd;
		double power_gating_vcc;
		//stats
		double total_accesses;
		double duty_cycle;
		double route_over_perc;

		//constructor
		SystemNoC() = default;
		SystemNoC(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemMem{
	public:
		//params
		int mem_tech_node;
		int device_clock;
		int peak_transfer_rate;
		int internal_prefetch_of_DRAM_chip;
		int capacity_per_channel;
		int number_ranks;
		int num_banks_of_DRAM_chip;
		int block_width_of_DRAM_chip;
		int output_width_of_DRAM_chip;
		int page_size_of_DRAM_chip;
		int burstlength_of_DRAM_chip;
		//stats
		double memory_accesses;
		double memory_reads;
		double memory_writes;

		//constructor
		SystemMem() = default;
		SystemMem(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemMemController{
	public:
		//params
		//Common Param for mc and fc
		double peak_transfer_rate;
		int number_mcs;
		bool withPHY;
		int type;

		//FCParam
		//stats
		double duty_cycle;
		double total_load_perc;

		//McParam
		int mc_clock;
		int llc_line_length;
		int memory_channels_per_mc;
		int number_ranks;
		int req_window_size_per_channel;
		int io_buffer_size_per_channel;
		int databus_width;
		int addressbus_width;
		bool lvds;
		double vdd;
		double power_gating_vcc;

		//stats
		double memory_accesses;
		double memory_reads;
		double memory_writes;

		//constructor
		SystemMemController() = default;
		SystemMemController(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemNiu{
	public:
		//params
		int clockrate;
		int number_units;
		int type;
		double vdd;
		double power_gating_vcc;
		//stats
		double duty_cycle;
		double total_load_perc;

		//constructor
		SystemNiu() = default;
		SystemNiu(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class SystemPcie{
	public:
		//params
		int clockrate;
		int number_units;
		int num_channels;
		int type;
		bool withPHY;
		double vdd;
		double power_gating_vcc;
		//stats
		double duty_cycle;
		double total_load_perc;

		//constructor
		SystemPcie() = default;
		SystemPcie(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class RootSystem{
	public:
		//All number_of_* at the level of 'system' Ying 03/21/2009
		int number_of_cores;
		int number_of_L1Directories;
		int number_of_L2Directories;
		int number_of_L2s;
		bool Private_L2;
		int number_of_L3s;
		int number_of_NoCs;
		int number_of_dir_levels;
		int domain_size;
		int first_level_dir;
		// All params at the level of 'system'
		int homogeneous_cores;
		int homogeneous_L1Directories;
		int homogeneous_L2Directories;
		double core_tech_node;
		int target_core_clockrate;
		int target_chip_area;
		int temperature;
		int number_cache_levels;
		int L1_property;
		int L2_property;
		int homogeneous_L2s;
		int L3_property;
		int homogeneous_L3s;
		int homogeneous_NoCs;
		int homogeneous_ccs;
		int Max_area_deviation;
		int Max_power_deviation;
		int device_type;
		bool longer_channel_device;
		bool power_gating;
		bool Embedded;
		bool opt_dynamic_power;
		bool opt_lakage_power;
		bool opt_clockrate;
		bool opt_area;
		int interconnect_projection_type;
		int machine_bits;
		int virtual_address_width;
		int physical_address_width;
		int virtual_memory_page_size;
		double total_cycles;
		double vdd;
		double power_gating_vcc;
		//system.core(0-n):3rd level
		std::vector<SystemCore> core;
		std::vector<SystemCacheDirectory> L1Directory;
		std::vector<SystemCacheDirectory> L2Directory;
		std::vector<SystemCache> L2;
		std::vector<SystemCache> L3;
		std::vector<SystemNoC> NoC;
		SystemMem mem;
		SystemMemController mc;
		SystemMemController flashc;
		SystemNiu niu;
		SystemPcie pcie;

		//constructor
		RootSystem() = default;
		RootSystem(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class ParseXML{
	public:
		ParseXML(std::string xml_path);
		template<typename T> static void split_string(const std::string&, std::vector<T>&);
		RootSystem sys;
};


#endif /* XML_PARSE_H_ */




