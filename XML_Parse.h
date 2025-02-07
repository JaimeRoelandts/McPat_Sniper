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
		int prediction_width			= 1;
		std::string prediction_scheme		= "default";
		int predictor_size			= 1;
		int predictor_entries			= 1;
		std::vector<int> local_predictor_size;
		int local_predictor_entries		= 1;
		int global_predictor_entries		= 1;
		int global_predictor_bits		= 1;
		int chooser_predictor_entries		= 1;
		int chooser_predictor_bits		= 1;
		double predictor_accesses		= 1;

		//constructor
		PredictorSystemCore() = default;
		PredictorSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class ItlbSystemCore{
	public:
		//params
		int number_entries			= 1;
		//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		int cache_policy			= 0;

		//stats
		double total_hits			= 1;
		double total_accesses			= 1;
		double total_misses			= 1;
		double conflicts			= 0;

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
		//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		int cache_policy			= 0;

		//stats
		double total_accesses			= 1;
		double read_accesses			= 1;
		double read_misses			= 1;
		double replacements			= 1;
		double read_hits			= 1;
		double total_hits			= 1;
		double total_misses			= 1;
		double miss_buffer_access		= 1;
		double fill_buffer_accesses		= 1;
		double prefetch_buffer_accesses		= 1;
		double prefetch_buffer_writes		= 1;
		double prefetch_buffer_reads		= 1;
		double prefetch_buffer_hits		= 1;
		double conflicts			= 0;

		//constructor
		IcacheSystemCore() = default;
		IcacheSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class DtlbSystemCore{
	public:
		//params
		int number_entries			= 1;
		//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		int cache_policy 			= 0;

		//stats
		double total_accesses			= 1;
		double read_accesses			= 1;
		double write_accesses			= 1;
		double write_hits			= 1;
		double read_hits			= 1;
		double read_misses			= 1;
		double write_misses			= 1;
		double total_hits			= 1;
		double total_misses			= 1;
		double conflicts			= 0;

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
		//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		int cache_policy			= 0;

		//stats
		double total_accesses			= 1;
		double read_accesses			= 1;
		double write_accesses			= 1;
		double total_hits			= 1;
		double total_misses			= 1;
		double read_hits			= 1;
		double write_hits			= 1;
		double read_misses			= 1;
		double write_misses			= 1;
		double replacements			= 1;
		double write_backs			= 1;
		double miss_buffer_access		= 1;
		double fill_buffer_accesses		= 1;
		double prefetch_buffer_accesses		= 1;
		double prefetch_buffer_writes		= 1;
		double prefetch_buffer_reads		= 1;
		double prefetch_buffer_hits		= 1;
		double wbb_writes			= 1;
		double wbb_reads			= 1;
		double conflicts			= 0;

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
		double total_accesses			= 1;
		double read_accesses			= 1;
		double write_accesses			= 1;
		double total_hits			= 1;
		double total_misses			= 1;
		double read_hits			= 1;
		double write_hits			= 1;
		double read_misses			= 1;
		double write_misses			= 1;
		double replacements			= 1;

		//constructor
		BtbSystemCore() = default;
		BtbSystemCore(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemCore{
	public:
		//all params at the level of system.core(0-n)
		int clock_rate				= 1;
		bool opt_local				= true;
		bool x86				= false;
		int machine_bits			= 1;
		int virtual_address_width		= 1;
		int physical_address_width		= 1;
		int opcode_width			= 1;
		int micro_opcode_width			= 1;
		int instruction_length			= 0;
		int machine_type			= 0;
		int internal_datapath_width		= 1;
		int number_hardware_threads		= 1;
		int fetch_width				= 1;
		int number_instruction_fetch_ports	= 1;
		int decode_width			= 1;
		int issue_width				= 1;
		int peak_issue_width			= 1;
		int commit_width			= 1;
		std::vector<int> pipelines_per_core;
		std::vector<int> pipeline_depth;
		std::string FPU				= "default";
		std::string divider_multiplier		= "default";
		int ALU_per_core			= 1;
		double FPU_per_core			= 1.0;
		int MUL_per_core			= 1;
		int instruction_buffer_size		= 1;
		int decoded_stream_buffer_size		= 1;
		int instruction_window_scheme		= 0;
		int instruction_window_size		= 1;
		int fp_instruction_window_size		= 0;
		int ROB_size				= 1;
		int archi_Regs_IRF_size			= 1;
		int archi_Regs_FRF_size			= 1;
		int phy_Regs_IRF_size			= 1;
		int phy_Regs_FRF_size			= 1;
		int rename_scheme			= 0;
		int checkpoint_depth			= 1;
		int register_windows_size		= 1;
		std::string LSU_order			= "default";
		int store_buffer_size			= 1;
		int load_buffer_size			= 1;
		int memory_ports			= 1;
		std::string Dcache_dual_pump		= "default";
		int RAS_size				= 1;
		int fp_issue_width			= 0;
		int prediction_width			= 0;
		int number_of_BTB			= 0;
		int number_of_BPT			= 0;
		double vdd				= 0;
		double power_gating_vcc			= -1;

		//all stats at the level of system.core(0-n)
		double total_instructions		= 1;
		double int_instructions			= 1;
		double fp_instructions			= 1;
		double branch_instructions		= 1;
		double branch_mispredictions		= 1;
		double committed_instructions		= 1;
		double committed_int_instructions	= 0;
		double committed_fp_instructions	= 0;
		double load_instructions		= 1;
		double store_instructions		= 1;
		double total_cycles			= 1;
		double idle_cycles			= 1;
		double busy_cycles			= 1;
		double instruction_buffer_reads		= 1;
		double instruction_buffer_write		= 1;
		double ROB_reads			= 1;
		double ROB_writes			= 1;
		double rename_accesses			= 1;
		double fp_rename_accesses		= 0;
		double rename_reads			= 0;
		double rename_writes			= 0;
		double fp_rename_reads			= 0;
		double fp_rename_writes			= 0;
		double inst_window_reads		= 1;
		double inst_window_writes		= 1;
		double inst_window_wakeup_accesses	= 1;
		double inst_window_selections		= 1;
		double fp_inst_window_reads		= 0;
		double fp_inst_window_writes		= 0;
		double fp_inst_window_wakeup_accesses	= 0;
		double fp_inst_window_selections	= 0;
		double archi_int_regfile_reads		= 1;
		double archi_float_regfile_reads	= 1;
		double phy_int_regfile_reads		= 1;
		double phy_float_regfile_reads		= 1;
		double phy_int_regfile_writes		= 0;
		double phy_float_regfile_writes		= 0;
		double archi_int_regfile_writes		= 0;
		double archi_float_regfile_writes	= 0;
		double int_regfile_reads		= 0;
		double float_regfile_reads		= 0;
		double int_regfile_writes		= 0;
		double float_regfile_writes		= 0;
		double windowed_reg_accesses		= 1;
		double windowed_reg_transports		= 1;
		double function_calls			= 1;
		double context_switches			= 0;
		double ialu_accesses			= 1;
		double fpu_accesses			= 1;
		double mul_accesses			= 1;
		double cdb_alu_accesses			= 1;
		double cdb_mul_accesses			= 1;
		double cdb_fpu_accesses			= 1;
		double load_buffer_reads		= 1;
		double load_buffer_writes		= 1;
		double load_buffer_cams			= 1;
		double store_buffer_reads		= 1;
		double store_buffer_writes		= 1;
		double store_buffer_cams		= 1;
		double store_buffer_forwards		= 1;
		double main_memory_access		= 1;
		double main_memory_read			= 1;
		double main_memory_write		= 1;
		double pipeline_duty_cycle		= 1;

		double IFU_duty_cycle 			= 1;
		double BR_duty_cycle 			= 1;
		double LSU_duty_cycle 			= 1;
		double MemManU_I_duty_cycle		= 1;
		double MemManU_D_duty_cycle 		= 1;
		double ALU_duty_cycle 			= 1;
		double MUL_duty_cycle 			= 1;
		double FPU_duty_cycle 			= 1;
		double ALU_cdb_duty_cycle 		= 1;
		double MUL_cdb_duty_cycle 		= 1;
		double FPU_cdb_duty_cycle 		= 1;


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
		int Directory_type			= 0;
		std::vector<double> Dir_config;
		std::vector<int> buffer_sizes;
		int clockrate				= 1;
		std::vector<int> ports;
		int device_type				= 1;
		//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		int cache_policy			= 0;
		std::string threeD_stack		= "default";
		double vdd				= 0;
		double power_gating_vcc			= -1;

		//stats
		double total_accesses			= 1;
		double read_accesses			= 1;
		double write_accesses			= 1;
		double read_misses			= 0;
		double write_misses			= 0;
		double conflicts			= 0;
		double duty_cycle			= 1;

		//constructor
		SystemCacheDirectory() = default;
		SystemCacheDirectory(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class SystemCache{
	public:
		//params
		std::vector<double> cache_config;
		int clockrate				= 1;
		std::vector<int> ports;
		int device_type				= 1;
		//0 no write or write-though with non-write allocate;1 write-back with write-allocate
		int cache_policy			= 0;
		std::string threeD_stack 		= "default";
		std::vector<int> buffer_sizes;
		double vdd				= 0;
		double power_gating_vcc 		= -1;
		bool   merged_dir			= false;

		//stats
		double total_accesses			= 1;
		double read_accesses			= 1;
		double write_accesses			= 1;
		double total_hits			= 1;
		double total_misses			= 1;
		double read_hits			= 1;
		double write_hits			= 1;
		double read_misses			= 1;
		double write_misses			= 1;
		double replacements			= 1;
		double write_backs			= 1;
		double miss_buffer_accesses		= 1;
		double fill_buffer_accesses		= 1;
		double prefetch_buffer_accesses		= 1;
		double prefetch_buffer_writes		= 1;
		double prefetch_buffer_reads		= 1;
		double prefetch_buffer_hits		= 1;
		double wbb_writes			= 1;
		double wbb_reads			= 1;
		double conflicts			= 0;
		double duty_cycle			= 1;

		double homenode_read_accesses		= 1;
		double homenode_write_accesses		= 1;
		double homenode_read_hits		= 1;
		double homenode_write_hits		= 1;
		double homenode_read_misses		= 1;
		double homenode_write_misses		= 1;
		double dir_duty_cycle			= 1;

		//constructor
		SystemCache() = default;
		SystemCache(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class Xbar0SystemNoC{
	public:
		//params
		int number_of_inputs_of_crossbars	= 1;
		int number_of_outputs_of_crossbars	= 1;
		int flit_bits				= 1;
		int input_buffer_entries_per_port	= 1;
		std::vector<int> ports_of_input_buffer;

		//stats
		double crossbar_accesses		= 1;

		//constructor
		Xbar0SystemNoC() = default;
		Xbar0SystemNoC(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemNoC{
	public:
		//params
		int clockrate				= 1;
		bool type				= true;
		bool has_global_link			= true;
		std::string topology			= "default";
		int horizontal_nodes			= 1;
		int vertical_nodes			= 1;
		int link_throughput			= 0;
		int link_latency			= 0;
		int input_ports				= 1;
		int output_ports			= 1;
		int virtual_channel_per_port		= 1;
		int flit_bits				= 1;
		int input_buffer_entries_per_vc		= 1;
		std::vector<int> ports_of_input_buffer;
		int dual_pump				= 0;
		int number_of_crossbars			= 1;
		std::string crossbar_type		= "default";
		std::string crosspoint_type		= "default";
		Xbar0SystemNoC xbar0;
		int arbiter_type			= 0;
		double chip_coverage			= 1;
		double vdd				= 0;
		double power_gating_vcc			= -1;

		//stats
		double total_accesses			= 1;
		double duty_cycle			= 1;
		double route_over_perc			= 0.5;

		//constructor
		SystemNoC() = default;
		SystemNoC(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemMem{
	public:
		//params
		int mem_tech_node			= 1;
		int device_clock			= 1;
		int peak_transfer_rate			= 1;
		int internal_prefetch_of_DRAM_chip	= 1;
		int capacity_per_channel		= 1;
		int number_ranks			= 1;
		int num_banks_of_DRAM_chip		= 1;
		int block_width_of_DRAM_chip		= 1;
		int output_width_of_DRAM_chip		= 1;
		int page_size_of_DRAM_chip		= 1;
		int burstlength_of_DRAM_chip		= 1;

		//stats
		double memory_accesses			= 1;
		double memory_reads			= 1;
		double memory_writes			= 1;

		//constructor
		SystemMem() = default;
		SystemMem(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemMemController{
	public:
		//params
		//Common Param for mc and fc
		double peak_transfer_rate		= 1;
		int number_mcs				= 1;
		bool withPHY				= false;
		int type				= 1;

		//FCParam
		//stats
		double duty_cycle			= 1;
		double total_load_perc			= 1;

		//McParam
		int mc_clock				= 1;
		int llc_line_length			= 0;
		int memory_channels_per_mc		= 1;
		int number_ranks			= 1;
		int req_window_size_per_channel		= 1;
		int io_buffer_size_per_channel		= 1;
		int databus_width			= 1;
		int addressbus_width			= 1;
		bool lvds				= true;
		double vdd				= 0;
		double power_gating_vcc			= -1;

		//stats
		double memory_accesses			= 1;
		double memory_reads			= 1;
		double memory_writes			= 1;

		//constructor
		SystemMemController() = default;
		SystemMemController(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class SystemNiu{
	public:
		//params
		int clockrate				= 1;
		int number_units			= 1;
		int type				= 1;
		double vdd				= 0;
		double power_gating_vcc			= -1;

		//stats
		double duty_cycle			= 1;
		double total_load_perc			= 1;

		//constructor
		SystemNiu() = default;
		SystemNiu(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);
};

class SystemPcie{
	public:
		//params
		int clockrate				= 1;
		int number_units			= 1;
		int num_channels			= 1;
		int type				= 1;
		bool withPHY				= false;
		double vdd				= 0;
		double power_gating_vcc			= -1;

		//stats
		double duty_cycle			= 1;
		double total_load_perc			= 1;

		//constructor
		SystemPcie() = default;
		SystemPcie(const boost::property_tree::ptree& xml_pt);
		void set_xml(const boost::property_tree::ptree& xml_pt);

};

class RootSystem{
	public:
		//All number_of_* at the level of 'system' Ying 03/21/2009
		//params
		int number_of_cores			= 1;
		int number_of_L1Directories		= 1;
		int number_of_L2Directories		= 1;
		int number_of_L2s			= 1;
		bool Private_L2				= false;
		int number_of_L3s			= 1;
		int number_of_NoCs			= 1;
		int number_of_dir_levels		= 0;
		int domain_size				= 0;
		int first_level_dir			= 0;
		// All params at the level of 'system'
		int homogeneous_cores			= 1;
		int homogeneous_L1Directories		= 1;
		int homogeneous_L2Directories		= 1;
		double core_tech_node			= 1;
		int target_core_clockrate		= 1;
		int target_chip_area			= 1;
		int temperature				= 360;
		int number_cache_levels			= 1;
		int L1_property				= 0;
		int L2_property				= 0;
		int homogeneous_L2s			= 1;
		int L3_property				= 0;
		int homogeneous_L3s			= 1;
		int homogeneous_NoCs			= 1;
		int homogeneous_ccs			= 1;
		int Max_area_deviation			= 1;
		int Max_power_deviation			= 1;
		int device_type				= 1;
		bool longer_channel_device		= true;
		bool power_gating			= false;
		bool Embedded				= false;
		bool opt_dynamic_power			= false;
		bool opt_lakage_power			= false;
		bool opt_clockrate			= true;
		bool opt_area				= false;
		int interconnect_projection_type	= 1;
		int machine_bits			= 0;
		int virtual_address_width		= 0;
		int physical_address_width		= 0;
		int virtual_memory_page_size		= 0;
		double vdd				= 0;
		double power_gating_vcc			= -1;

		//stat
		double total_cycles			= 0;
		double idle_cycles			= 0;
		double busy_cycles			= 0;

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




