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


#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/property_tree/detail/xml_parser_flags.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include "XML_Parse.h"
		
PredictorSystemCore::PredictorSystemCore(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void PredictorSystemCore::set_xml(const boost::property_tree::ptree& xml_pt){
	for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "prediction_width") 		prediction_width 		=node.get<int>("<xmlattr>.value");
			else if (name == "prediction_scheme") 		prediction_scheme 		=node.get<int>("<xmlattr>.value");
			else if (name == "predictor_size") 		predictor_size 			=node.get<int>("<xmlattr>.value");
			else if (name == "predictor_entries") 		predictor_entries 		=node.get<int>("<xmlattr>.value");
			else if (name == "local_predictor_size") 	ParseXML::split_string(node.get<std::string>("<xmlattr>.value"),local_predictor_size);
			else if (name == "local_predictor_entries") 	local_predictor_entries 	=node.get<int>("<xmlattr>.value");
			else if (name == "global_predictor_entries") 	global_predictor_entries 	=node.get<int>("<xmlattr>.value");
			else if (name == "global_predictor_bits") 	global_predictor_bits 		=node.get<int>("<xmlattr>.value");
			else if (name == "chooser_predictor_entries") 	chooser_predictor_entries 	=node.get<int>("<xmlattr>.value");
			else if (name == "chooser_predictor_bits") 	chooser_predictor_bits 		=node.get<int>("<xmlattr>.value");
            	} else if (param.first == "stat") {
			if (name == "predictor_accesses") 		predictor_accesses 		= node.get<double>("<xmlattr>.value");
		}
	}
}

ItlbSystemCore::ItlbSystemCore(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void ItlbSystemCore::set_xml(const boost::property_tree::ptree& xml_pt){
	for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "number_entries") 			number_entries 			=node.get<int>("<xmlattr>.value");
			else if (name == "cache_policy") 		cache_policy 			=node.get<int>("<xmlattr>.value");
            	} else if (param.first == "stat") {
			if (name == "total_hits") 			total_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_accesses") 		total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_misses") 		total_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "conflicts") 			conflicts 			= node.get<double>("<xmlattr>.value");
		}
	}
}

IcacheSystemCore::IcacheSystemCore(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void IcacheSystemCore::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "icache_config") 			ParseXML::split_string(node.get<std::string>("<xmlattr>.value"),icache_config);
			else if (name == "buffer_sizes") 		ParseXML::split_string(node.get<std::string>("<xmlattr>.value"),buffer_sizes);
			else if (name == "cache_policy") 		cache_policy			= node.get<int>("<xmlattr>.value");
            	} else if (param.first == "stat") {
			if (name == "total_accesses") 			total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_accesses") 		read_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_hits") 			total_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_misses") 		total_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_hits") 			read_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_misses") 		read_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "replacements") 		replacements 			= node.get<double>("<xmlattr>.value");
			else if (name == "miss_buffer_access") 		miss_buffer_access 		= node.get<double>("<xmlattr>.value");
			else if (name == "fill_buffer_accesses") 	fill_buffer_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_accesses") 	prefetch_buffer_accesses 	= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_writes") 	prefetch_buffer_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_reads") 	prefetch_buffer_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_hits") 	prefetch_buffer_hits 		= node.get<double>("<xmlattr>.value");
			else if (name == "conflicts") 			conflicts 			= node.get<double>("<xmlattr>.value");
		}
	}
}

DtlbSystemCore::DtlbSystemCore(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void DtlbSystemCore::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "number_entries") 			number_entries 			=node.get<int>("<xmlattr>.value");
			else if (name == "cache_policy") 		cache_policy 			=node.get<int>("<xmlattr>.value");
            	} else if (param.first == "stat") {
			if (name == "total_accesses") 			total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_accesses") 		read_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_accesses") 		write_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_hits") 			total_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_misses") 		total_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_hits") 			read_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_hits") 			write_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_misses") 		read_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_misses") 		write_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "conflicts") 			conflicts 			= node.get<double>("<xmlattr>.value");
		}
	}
}

DcacheSystemCore::DcacheSystemCore(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void DcacheSystemCore::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "dcache_config") 			ParseXML::split_string(node.get<std::string>("<xmlattr>.value"),dcache_config);
			else if (name == "buffer_sizes") 		ParseXML::split_string(node.get<std::string>("<xmlattr>.value"),buffer_sizes);
			else if (name == "cache_policy") 		cache_policy			= node.get<int>("<xmlattr>.value");
            	} else if (param.first == "stat") {
			if (name == "total_accesses") 			total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_accesses") 		read_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_accesses") 		write_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_hits") 			total_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_misses") 		total_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_hits") 			read_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_hits") 			write_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_misses") 		read_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_misses") 		write_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "replacements") 		replacements 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_backs") 		write_backs 			= node.get<double>("<xmlattr>.value");
			else if (name == "miss_buffer_access") 		miss_buffer_access 		= node.get<double>("<xmlattr>.value");
			else if (name == "fill_buffer_accesses") 	fill_buffer_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_accesses") 	prefetch_buffer_accesses 	= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_writes") 	prefetch_buffer_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_reads") 	prefetch_buffer_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_hits") 	prefetch_buffer_hits 		= node.get<double>("<xmlattr>.value");
			else if (name == "wbb_writes") 			wbb_writes 			= node.get<double>("<xmlattr>.value");
			else if (name == "wbb_reads") 			wbb_reads 			= node.get<double>("<xmlattr>.value");
			else if (name == "conflicts") 			conflicts 			= node.get<double>("<xmlattr>.value");
		}
	}
}


BtbSystemCore::BtbSystemCore(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void BtbSystemCore::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "BTB_config") 			ParseXML::split_string(node.get<std::string>("<xmlattr>.value"),BTB_config);
            	} else if (param.first == "stat") {
			if (name == "total_accesses") 			total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_accesses") 		read_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_accesses") 		write_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_hits") 			total_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_misses") 		total_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_hits") 			read_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_hits") 			write_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_misses") 		read_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_misses") 		write_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "replacements") 		replacements 			= node.get<double>("<xmlattr>.value");
		}
	}
}


SystemCore::SystemCore(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemCore::set_xml(const boost::property_tree::ptree& xml_pt){
	std::string this_component_name = xml_pt.get<std::string>("<xmlattr>.id");
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "clock_rate") 			clock_rate 			= node.get<int>("<xmlattr>.value");
			else if (name == "opt_local") 			opt_local 			= node.get<bool>("<xmlattr>.value");
			else if (name == "x86") 			x86 				= node.get<bool>("<xmlattr>.value");
			else if (name == "machine_bits") 		machine_bits 			= node.get<int>("<xmlattr>.value");
			else if (name == "virtual_address_width") 	virtual_address_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "physical_address_width") 	physical_address_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "opcode_width") 		opcode_width 			= node.get<int>("<xmlattr>.value");
			else if (name == "micro_opcode_width") 		micro_opcode_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "instruction_length") 		instruction_length 		= node.get<int>("<xmlattr>.value");
			else if (name == "machine_type") 		machine_type 			= node.get<int>("<xmlattr>.value");
			else if (name == "internal_datapath_width") 	internal_datapath_width 	= node.get<int>("<xmlattr>.value");
			else if (name == "number_hardware_threads") 	number_hardware_threads 	= node.get<int>("<xmlattr>.value");
			else if (name == "fetch_width") 		fetch_width 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_instruction_fetch_ports")number_instruction_fetch_ports= node.get<int>("<xmlattr>.value");
			else if (name == "decode_width") 		decode_width 			= node.get<int>("<xmlattr>.value");
			else if (name == "issue_width") 		issue_width 			= node.get<int>("<xmlattr>.value");
			else if (name == "peak_issue_width") 		peak_issue_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "commit_width") 		commit_width 			= node.get<int>("<xmlattr>.value");
			else if (name == "pipelines_per_core") 		ParseXML::split_string(node.get<std::string>("<xmlattr>.value"), pipelines_per_core);
			else if (name == "pipeline_depth") 		ParseXML::split_string(node.get<std::string>("<xmlattr>.value"), pipeline_depth);
			else if (name == "FPU") 			FPU 				= node.get<std::string>("<xmlattr>.value");
			else if (name == "divider_multiplier") 		divider_multiplier 		= node.get<std::string>("<xmlattr>.value");
			else if (name == "ALU_per_core") 		ALU_per_core 			= node.get<int>("<xmlattr>.value");
			else if (name == "FPU_per_core") 		FPU_per_core 			= node.get<double>("<xmlattr>.value");
			else if (name == "MUL_per_core") 		MUL_per_core 			= node.get<int>("<xmlattr>.value");
			else if (name == "instruction_buffer_size") 	instruction_buffer_size 	= node.get<int>("<xmlattr>.value");
			else if (name == "decoded_stream_buffer_size") 	decoded_stream_buffer_size 	= node.get<int>("<xmlattr>.value");
			else if (name == "instruction_window_scheme") 	instruction_window_scheme 	= node.get<int>("<xmlattr>.value");
			else if (name == "instruction_window_size") 	instruction_window_size 	= node.get<int>("<xmlattr>.value");
			else if (name == "fp_instruction_window_size") 	fp_instruction_window_size 	= node.get<int>("<xmlattr>.value");
			else if (name == "ROB_size") 			ROB_size 			= node.get<int>("<xmlattr>.value");
			else if (name == "archi_Regs_IRF_size") 	archi_Regs_IRF_size 		= node.get<int>("<xmlattr>.value");
			else if (name == "archi_Regs_FRF_size") 	archi_Regs_FRF_size 		= node.get<int>("<xmlattr>.value");
			else if (name == "phy_Regs_IRF_size") 		phy_Regs_IRF_size 		= node.get<int>("<xmlattr>.value");
			else if (name == "phy_Regs_FRF_size") 		phy_Regs_FRF_size 		= node.get<int>("<xmlattr>.value");
			else if (name == "rename_scheme") 		rename_scheme 			= node.get<int>("<xmlattr>.value");
			else if (name == "checkpoint_depth") 		checkpoint_depth 		= node.get<int>("<xmlattr>.value");
			else if (name == "register_windows_size") 	register_windows_size 		= node.get<int>("<xmlattr>.value");
			else if (name == "LSU_order") 			LSU_order 			= node.get<std::string>("<xmlattr>.value");
			else if (name == "store_buffer_size") 		store_buffer_size 		= node.get<int>("<xmlattr>.value");
			else if (name == "load_buffer_size") 		load_buffer_size 		= node.get<int>("<xmlattr>.value");
			else if (name == "memory_ports") 		memory_ports 			= node.get<int>("<xmlattr>.value");
			else if (name == "Dcache_dual_pump") 		Dcache_dual_pump 		= node.get<std::string>("<xmlattr>.value");
			else if (name == "RAS_size") 			RAS_size 			= node.get<int>("<xmlattr>.value");
			else if (name == "fp_issue_width") 		fp_issue_width 			= node.get<int>("<xmlattr>.value");
			else if (name == "prediction_width") 		prediction_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_BTB") 		number_of_BTB 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_BPT") 		number_of_BPT 			= node.get<int>("<xmlattr>.value");
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
            	} else if (param.first == "stat") {
			if (name == "total_instructions") 		total_instructions 		= node.get<double>("<xmlattr>.value");
			else if (name == "int_instructions") 		int_instructions 		= node.get<double>("<xmlattr>.value");
			else if (name == "fp_instructions") 		fp_instructions 		= node.get<double>("<xmlattr>.value");
			else if (name == "branch_instructions") 	branch_instructions 		= node.get<double>("<xmlattr>.value");
			else if (name == "branch_mispredictions") 	branch_mispredictions 		= node.get<double>("<xmlattr>.value");
			else if (name == "committed_instructions") 	committed_instructions 		= node.get<double>("<xmlattr>.value");
			else if (name == "committed_int_instructions") 	committed_int_instructions 	= node.get<double>("<xmlattr>.value");
			else if (name == "committed_fp_instructions") 	committed_fp_instructions 	= node.get<double>("<xmlattr>.value");
			else if (name == "load_instructions") 		load_instructions 		= node.get<double>("<xmlattr>.value");
			else if (name == "store_instructions") 		store_instructions 		= node.get<double>("<xmlattr>.value");
			else if (name == "total_cycles") 		total_cycles 			= node.get<double>("<xmlattr>.value");
			else if (name == "idle_cycles") 		idle_cycles 			= node.get<double>("<xmlattr>.value");
			else if (name == "busy_cycles") 		busy_cycles 			= node.get<double>("<xmlattr>.value");
			else if (name == "instruction_buffer_reads") 	instruction_buffer_reads 	= node.get<double>("<xmlattr>.value");
			else if (name == "instruction_buffer_write") 	instruction_buffer_write 	= node.get<double>("<xmlattr>.value");
			else if (name == "ROB_reads") 			ROB_reads 			= node.get<double>("<xmlattr>.value");
			else if (name == "ROB_writes") 			ROB_writes 			= node.get<double>("<xmlattr>.value");
			else if (name == "rename_accesses") 		rename_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "fp_rename_accesses") 		fp_rename_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "rename_reads") 		rename_reads 			= node.get<double>("<xmlattr>.value");
			else if (name == "rename_writes") 		rename_writes 			= node.get<double>("<xmlattr>.value");
			else if (name == "fp_rename_reads") 		fp_rename_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "fp_rename_writes") 		fp_rename_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "inst_window_reads") 		inst_window_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "inst_window_writes") 		inst_window_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "inst_window_wakeup_accesses") inst_window_wakeup_accesses 	= node.get<double>("<xmlattr>.value");
			else if (name == "inst_window_selections") 	inst_window_selections 		= node.get<double>("<xmlattr>.value");
			else if (name == "fp_inst_window_reads") 	fp_inst_window_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "fp_inst_window_writes") 	fp_inst_window_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "fp_inst_window_wakeup_accesses")fp_inst_window_wakeup_accesses= node.get<double>("<xmlattr>.value");
			else if (name == "fp_inst_window_selections") 	fp_inst_window_selections 	= node.get<double>("<xmlattr>.value");
			else if (name == "archi_int_regfile_reads") 	archi_int_regfile_reads 	= node.get<double>("<xmlattr>.value");
			else if (name == "archi_float_regfile_reads") 	archi_float_regfile_reads 	= node.get<double>("<xmlattr>.value");
			else if (name == "phy_int_regfile_reads") 	phy_int_regfile_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "phy_float_regfile_reads") 	phy_float_regfile_reads 	= node.get<double>("<xmlattr>.value");
			else if (name == "phy_int_regfile_writes") 	phy_int_regfile_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "phy_float_regfile_writes") 	phy_float_regfile_writes 	= node.get<double>("<xmlattr>.value");
			else if (name == "archi_int_regfile_writes") 	archi_int_regfile_writes 	= node.get<double>("<xmlattr>.value");
			else if (name == "archi_float_regfile_writes") 	archi_float_regfile_writes 	= node.get<double>("<xmlattr>.value");
			else if (name == "int_regfile_reads") 		int_regfile_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "float_regfile_reads") 	float_regfile_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "int_regfile_writes") 		int_regfile_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "float_regfile_writes") 	float_regfile_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "windowed_reg_accesses") 	windowed_reg_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "windowed_reg_transports") 	windowed_reg_transports 	= node.get<double>("<xmlattr>.value");
			else if (name == "function_calls") 		function_calls 			= node.get<double>("<xmlattr>.value");
			else if (name == "context_switches") 		context_switches 		= node.get<double>("<xmlattr>.value");
			else if (name == "ialu_accesses") 		ialu_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "fpu_accesses") 		fpu_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "mul_accesses") 		mul_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "cdb_alu_accesses") 		cdb_alu_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "cdb_mul_accesses") 		cdb_mul_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "cdb_fpu_accesses") 		cdb_fpu_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "load_buffer_reads") 		load_buffer_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "load_buffer_writes") 		load_buffer_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "load_buffer_cams") 		load_buffer_cams 		= node.get<double>("<xmlattr>.value");
			else if (name == "store_buffer_reads") 		store_buffer_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "store_buffer_writes") 	store_buffer_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "store_buffer_cams") 		store_buffer_cams 		= node.get<double>("<xmlattr>.value");
			else if (name == "store_buffer_forwards") 	store_buffer_forwards 		= node.get<double>("<xmlattr>.value");
			else if (name == "main_memory_access") 		main_memory_access 		= node.get<double>("<xmlattr>.value");
			else if (name == "main_memory_read") 		main_memory_read 		= node.get<double>("<xmlattr>.value");
			else if (name == "main_memory_write") 		main_memory_write 		= node.get<double>("<xmlattr>.value");
			else if (name == "pipeline_duty_cycle") 	pipeline_duty_cycle 		= node.get<double>("<xmlattr>.value");
			else if (name == "IFU_duty_cycle") 		IFU_duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "BR_duty_cycle") 		BR_duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "LSU_duty_cycle") 		LSU_duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "MemManU_I_duty_cycle") 	MemManU_I_duty_cycle 		= node.get<double>("<xmlattr>.value");
			else if (name == "MemManU_D_duty_cycle") 	MemManU_D_duty_cycle 		= node.get<double>("<xmlattr>.value");
			else if (name == "ALU_duty_cycle") 		ALU_duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "MUL_duty_cycle") 		MUL_duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "FPU_duty_cycle") 		FPU_duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "ALU_cdb_duty_cycle") 		ALU_cdb_duty_cycle 		= node.get<double>("<xmlattr>.value");
			else if (name == "MUL_cdb_duty_cycle") 		MUL_cdb_duty_cycle 		= node.get<double>("<xmlattr>.value");
			else if (name == "FPU_cdb_duty_cycle") 		FPU_cdb_duty_cycle 		= node.get<double>("<xmlattr>.value");
		} else if (param.first == "component"){
			if (id == this_component_name + ".predictor") 	predictor 			= PredictorSystemCore(node);
			else if (id == this_component_name + ".itlb") 	itlb 				= ItlbSystemCore(node);
			else if (id == this_component_name + ".icache")	icache 				= IcacheSystemCore(node);
			else if (id == this_component_name + ".dtlb") 	dtlb 				= DtlbSystemCore(node);
			else if (id == this_component_name + ".dcache")	dcache 				= DcacheSystemCore(node);
			else if (id == this_component_name + ".BTB") 	BTB 				= BtbSystemCore(node);
		}
		else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
        }
}


SystemCacheDirectory::SystemCacheDirectory(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemCacheDirectory::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name == "Directory_type") 			Directory_type 			= node.get<int>("<xmlattr>.value");
			else if (name == "Dir_config") 			ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), Dir_config);
			else if (name == "buffer_sizes") 		ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), buffer_sizes);
			else if (name == "clockrate") 			clockrate 			= node.get<int>("<xmlattr>.value");
			else if (name == "ports") 			ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), ports);
			else if (name == "device_type") 		device_type 			= node.get<int>("<xmlattr>.value");
			else if (name == "cache_policy") 		cache_policy 			= node.get<int>("<xmlattr>.value");
			else if (name == "threeD_stack") 		threeD_stack 			= node.get<std::string>("<xmlattr>.value");
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
		} else if (param.first == "stat"){
			if (name == "total_accesses") 			total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_accesses") 		read_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_accesses") 		write_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_misses") 		read_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_misses") 		write_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "conflicts") 			conflicts 			= node.get<double>("<xmlattr>.value");
			else if (name == "duty_cycle") 			duty_cycle 			= node.get<double>("<xmlattr>.value");
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}

SystemCache::SystemCache(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemCache::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name.find("_config") != std::string::npos)	ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), cache_config);
			else if (name == "clockrate") 			clockrate 			= node.get<int>("<xmlattr>.value");
			else if (name == "ports") 			ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), ports);
			else if (name == "device_type") 		device_type 			= node.get<int>("<xmlattr>.value");
			else if (name == "cache_policy") 		cache_policy 			= node.get<int>("<xmlattr>.value");
			else if (name == "threeD_stack") 		threeD_stack 			= node.get<std::string>("<xmlattr>.value");
			else if (name == "buffer_sizes") 		ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), buffer_sizes);
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
			else if (name == "merged_dir") 			merged_dir 			= node.get<bool>("<xmlattr>.value");
		} else if (param.first == "stat"){
			if (name == "total_accesses") 			total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_accesses") 		read_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_accesses") 		write_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_hits") 			total_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_misses") 		total_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_hits") 			read_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_hits") 			write_hits 			= node.get<double>("<xmlattr>.value");
			else if (name == "read_misses") 		read_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_misses") 		write_misses 			= node.get<double>("<xmlattr>.value");
			else if (name == "replacements") 		replacements 			= node.get<double>("<xmlattr>.value");
			else if (name == "write_backs") 		write_backs 			= node.get<double>("<xmlattr>.value");
			else if (name == "miss_buffer_accesses") 	miss_buffer_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "fill_buffer_accesses") 	fill_buffer_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_accesses") 	prefetch_buffer_accesses 	= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_writes") 	prefetch_buffer_writes 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_reads") 	prefetch_buffer_reads 		= node.get<double>("<xmlattr>.value");
			else if (name == "prefetch_buffer_hits") 	prefetch_buffer_hits 		= node.get<double>("<xmlattr>.value");
			else if (name == "wbb_writes") 			wbb_writes 			= node.get<double>("<xmlattr>.value");
			else if (name == "wbb_reads") 			wbb_reads 			= node.get<double>("<xmlattr>.value");
			else if (name == "conflicts") 			conflicts 			= node.get<double>("<xmlattr>.value");
			else if (name == "duty_cycle") 			duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "homenode_read_accesses") 	homenode_read_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "homenode_write_accesses") 	homenode_write_accesses 	= node.get<double>("<xmlattr>.value");
			else if (name == "homenode_read_hits") 		homenode_read_hits 		= node.get<double>("<xmlattr>.value");
			else if (name == "homenode_write_hits") 	homenode_write_hits 		= node.get<double>("<xmlattr>.value");
			else if (name == "homenode_read_misses") 	homenode_read_misses 		= node.get<double>("<xmlattr>.value");
			else if (name == "homenode_write_misses") 	homenode_write_misses 		= node.get<double>("<xmlattr>.value");
			else if (name == "dir_duty_cycle") 		dir_duty_cycle 			= node.get<double>("<xmlattr>.value");
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}

Xbar0SystemNoC::Xbar0SystemNoC(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void Xbar0SystemNoC::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name == "number_of_inputs_of_crossbars") 	number_of_inputs_of_crossbars 	= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_outputs_of_crossbars")number_of_outputs_of_crossbars= node.get<int>("<xmlattr>.value");
			else if (name == "flit_bits") 			flit_bits 			= node.get<int>("<xmlattr>.value");
			else if (name == "input_buffer_entries_per_port")input_buffer_entries_per_port 	= node.get<int>("<xmlattr>.value");
			else if (name == "ports_of_input_buffer") 	ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), ports_of_input_buffer);
		} else if (param.first == "stat"){
			if (name == "crossbar_accesses") 		crossbar_accesses 		= node.get<double>("<xmlattr>.value");
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}


SystemNoC::SystemNoC(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemNoC::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name == "clockrate") 			clockrate 			= node.get<int>("<xmlattr>.value");
			else if (name == "type") 			type 				= node.get<bool>("<xmlattr>.value");
			else if (name == "has_global_link") 		has_global_link 		= node.get<bool>("<xmlattr>.value");
			else if (name == "topology") 			topology 			= node.get<std::string>("<xmlattr>.value", "");
			else if (name == "horizontal_nodes") 		horizontal_nodes 		= node.get<int>("<xmlattr>.value");
			else if (name == "vertical_nodes") 		vertical_nodes 			= node.get<int>("<xmlattr>.value");
			else if (name == "link_throughput") 		link_throughput 		= node.get<int>("<xmlattr>.value");
			else if (name == "link_latency") 		link_latency 			= node.get<int>("<xmlattr>.value");
			else if (name == "input_ports") 		input_ports 			= node.get<int>("<xmlattr>.value");
			else if (name == "output_ports") 		output_ports 			= node.get<int>("<xmlattr>.value");
			else if (name == "virtual_channel_per_port") 	virtual_channel_per_port 	= node.get<int>("<xmlattr>.value");
			else if (name == "flit_bits") 			flit_bits 			= node.get<int>("<xmlattr>.value");
			else if (name == "input_buffer_entries_per_vc")	input_buffer_entries_per_vc 	= node.get<int>("<xmlattr>.value");
			else if (name == "ports_of_input_buffer") 	ParseXML::split_string(node.get<std::string>("<xmlattr>.value", ""), ports_of_input_buffer);
			else if (name == "dual_pump") 			dual_pump 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_crossbars") 	number_of_crossbars 		= node.get<int>("<xmlattr>.value");
			else if (name == "crossbar_type") 		crossbar_type 			= node.get<std::string>("<xmlattr>.value", "");
			else if (name == "crosspoint_type") 		crosspoint_type 		= node.get<std::string>("<xmlattr>.value", "");
			else if (name == "arbiter_type") 		arbiter_type 			= node.get<int>("<xmlattr>.value");
			else if (name == "chip_coverage") 		chip_coverage 			= node.get<double>("<xmlattr>.value");
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
		} else if (param.first == "stat"){
			if (name == "total_accesses") 			total_accesses 			= node.get<double>("<xmlattr>.value");
			else if (name == "duty_cycle") 			duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "route_over_perc") 		route_over_perc 		= node.get<double>("<xmlattr>.value");
		} else if (param.first == "component"){
			if (id.find("xbar0") != std::string::npos) 	xbar0 				= Xbar0SystemNoC(node);
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}

SystemMem::SystemMem(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemMem::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name == "mem_tech_node") 			mem_tech_node 			= node.get<int>("<xmlattr>.value");
			else if (name == "device_clock") 		device_clock 			= node.get<int>("<xmlattr>.value");
			else if (name == "peak_transfer_rate") 		peak_transfer_rate 		= node.get<int>("<xmlattr>.value");
			else if (name == "internal_prefetch_of_DRAM_chip")internal_prefetch_of_DRAM_chip= node.get<int>("<xmlattr>.value");
			else if (name == "capacity_per_channel") 	capacity_per_channel 		= node.get<int>("<xmlattr>.value");
			else if (name == "number_ranks") 		number_ranks 			= node.get<int>("<xmlattr>.value");
			else if (name == "num_banks_of_DRAM_chip") 	num_banks_of_DRAM_chip 		= node.get<int>("<xmlattr>.value");
			else if (name == "Block_width_of_DRAM_chip" || name == "block_width_of_DRAM_chip")block_width_of_DRAM_chip 	= node.get<int>("<xmlattr>.value");
			else if (name == "output_width_of_DRAM_chip")	output_width_of_DRAM_chip 	= node.get<int>("<xmlattr>.value");
			else if (name == "page_size_of_DRAM_chip") 	page_size_of_DRAM_chip 		= node.get<int>("<xmlattr>.value");
			else if (name == "burstlength_of_DRAM_chip") 	burstlength_of_DRAM_chip 	= node.get<int>("<xmlattr>.value");
		} else if (param.first == "stat"){
			if (name == "memory_accesses") 			memory_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "memory_reads") 		memory_reads 			= node.get<double>("<xmlattr>.value");
			else if (name == "memory_writes") 		memory_writes 			= node.get<double>("<xmlattr>.value");
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}


SystemMemController::SystemMemController(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemMemController::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name == "peak_transfer_rate") 		peak_transfer_rate 		= node.get<double>("<xmlattr>.value");
			else if (name == "number_mcs" || name == "number_flashcs")number_mcs 		= node.get<int>("<xmlattr>.value");
			else if (name == "withPHY") 			withPHY 			= node.get<bool>("<xmlattr>.value");
			else if (name == "type") 			type 				= node.get<int>("<xmlattr>.value");
			else if (name == "mc_clock") 			mc_clock 			= node.get<int>("<xmlattr>.value");
			else if (name == "llc_line_length" || name == "block_size")llc_line_length 		= node.get<int>("<xmlattr>.value");
			else if (name == "memory_channels_per_mc") 	memory_channels_per_mc 		= node.get<int>("<xmlattr>.value");
			else if (name == "number_ranks") 		number_ranks 			= node.get<int>("<xmlattr>.value");
			else if (name == "req_window_size_per_channel")	req_window_size_per_channel 	= node.get<int>("<xmlattr>.value");
			else if (name == "IO_buffer_size_per_channel" || name == "io_buffer_size_per_channel")io_buffer_size_per_channel 	= node.get<int>("<xmlattr>.value");
			else if (name == "databus_width") 		databus_width 			= node.get<int>("<xmlattr>.value");
			else if (name == "addressbus_width") 		addressbus_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "LVDS" || name == "lvds")	lvds 				= node.get<bool>("<xmlattr>.value");
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
		} else if (param.first == "stat"){
			if (name == "duty_cycle") 			duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_load_perc") 		total_load_perc 		= node.get<double>("<xmlattr>.value");
			else if (name == "memory_accesses") 		memory_accesses 		= node.get<double>("<xmlattr>.value");
			else if (name == "memory_reads") 		memory_reads 			= node.get<double>("<xmlattr>.value");
			else if (name == "memory_writes") 		memory_writes 			= node.get<double>("<xmlattr>.value");
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}

SystemNiu::SystemNiu(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemNiu::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name == "clockrate") 			clockrate 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_units") 		number_units 			= node.get<int>("<xmlattr>.value");
			else if (name == "type") 			type 				= node.get<int>("<xmlattr>.value");
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
		} else if (param.first == "stat"){
			if (name == "duty_cycle") 			duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_load_perc") 		total_load_perc 		= node.get<double>("<xmlattr>.value");
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}

SystemPcie::SystemPcie(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
}

void SystemPcie::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
            	if (param.first == "param") {
			if (name == "clockrate") 			clockrate 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_units") 		number_units 			= node.get<int>("<xmlattr>.value");
			else if (name == "num_channels") 		num_channels 			= node.get<int>("<xmlattr>.value");
			else if (name == "type") 			type 				= node.get<int>("<xmlattr>.value");
			else if (name == "withPHY") 			withPHY 			= node.get<bool>("<xmlattr>.value");
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
		} else if (param.first == "stat"){
			if (name == "duty_cycle") 			duty_cycle 			= node.get<double>("<xmlattr>.value");
			else if (name == "total_load_perc") 		total_load_perc 		= node.get<double>("<xmlattr>.value");
		} else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
	}
}


RootSystem::RootSystem(const boost::property_tree::ptree& xml_pt){
	set_xml(xml_pt);
	check_consitency();
}

void RootSystem::set_xml(const boost::property_tree::ptree& xml_pt){
        for (const auto &param : xml_pt) {
		if(param.first == "<xmlattr>" || param.first == "<xmlcomment>") continue;
		auto node = param.second;
		std::string id    = node.get<std::string>("<xmlattr>.id", "");
		std::string name  = node.get<std::string>("<xmlattr>.name");
		if (param.first == "param") {
			if (name == "number_of_cores") 			number_of_cores 		= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_L1Directories") 	number_of_L1Directories 	= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_L2Directories") 	number_of_L2Directories 	= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_L2s") 		number_of_L2s 			= node.get<int>("<xmlattr>.value");
			else if (name == "Private_L2") 			Private_L2 			= node.get<bool>("<xmlattr>.value");
			else if (name == "number_of_L3s") 		number_of_L3s 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_NoCs") 		number_of_NoCs 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_of_dir_levels") 	number_of_dir_levels 		= node.get<int>("<xmlattr>.value");
			else if (name == "domain_size") 		domain_size 			= node.get<int>("<xmlattr>.value");
			else if (name == "first_level_dir") 		first_level_dir 		= node.get<int>("<xmlattr>.value");
			else if (name == "homogeneous_cores") 		homogeneous_cores 		= node.get<int>("<xmlattr>.value");
			else if (name == "homogeneous_L1Directories") 	homogeneous_L1Directories 	= node.get<int>("<xmlattr>.value");
			else if (name == "homogeneous_L2Directories") 	homogeneous_L2Directories 	= node.get<int>("<xmlattr>.value");
			else if (name == "core_tech_node") 		core_tech_node 			= node.get<double>("<xmlattr>.value");
			else if (name == "target_core_clockrate") 	target_core_clockrate 		= node.get<int>("<xmlattr>.value");
			else if (name == "target_chip_area") 		target_chip_area 		= node.get<int>("<xmlattr>.value");
			else if (name == "temperature") 		temperature 			= node.get<int>("<xmlattr>.value");
			else if (name == "number_cache_levels") 	number_cache_levels 		= node.get<int>("<xmlattr>.value");
			else if (name == "L1_property") 		L1_property 			= node.get<int>("<xmlattr>.value");
			else if (name == "L2_property") 		L2_property 			= node.get<int>("<xmlattr>.value");
			else if (name == "homogeneous_L2s") 		homogeneous_L2s 		= node.get<int>("<xmlattr>.value");
			else if (name == "L3_property") 		L3_property 			= node.get<int>("<xmlattr>.value");
			else if (name == "homogeneous_L3s") 		homogeneous_L3s 		= node.get<int>("<xmlattr>.value");
			else if (name == "homogeneous_NoCs") 		homogeneous_NoCs 		= node.get<int>("<xmlattr>.value");
			else if (name == "homogeneous_ccs") 		homogeneous_ccs 		= node.get<int>("<xmlattr>.value");
			else if (name == "Max_area_deviation") 		Max_area_deviation 		= node.get<int>("<xmlattr>.value");
			else if (name == "Max_power_deviation") 	Max_power_deviation 		= node.get<int>("<xmlattr>.value");
			else if (name == "device_type") 		device_type 			= node.get<int>("<xmlattr>.value");
			else if (name == "longer_channel_device") 	longer_channel_device 		= node.get<bool>("<xmlattr>.value");
			else if (name == "power_gating") 		power_gating 			= node.get<bool>("<xmlattr>.value");
			else if (name == "Embedded") 			Embedded 			= node.get<bool>("<xmlattr>.value");
			else if (name == "opt_dynamic_power") 		opt_dynamic_power 		= node.get<bool>("<xmlattr>.value");
			else if (name == "opt_lakage_power") 		opt_lakage_power 		= node.get<bool>("<xmlattr>.value");
			else if (name == "opt_clockrate") 		opt_clockrate 			= node.get<bool>("<xmlattr>.value");
			else if (name == "opt_area") 			opt_area 			= node.get<bool>("<xmlattr>.value");
			else if (name == "interconnect_projection_type")interconnect_projection_type 	= node.get<int>("<xmlattr>.value");
			else if (name == "machine_bits") 		machine_bits 			= node.get<int>("<xmlattr>.value");
			else if (name == "virtual_address_width") 	virtual_address_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "physical_address_width") 	physical_address_width 		= node.get<int>("<xmlattr>.value");
			else if (name == "virtual_memory_page_size") 	virtual_memory_page_size 	= node.get<int>("<xmlattr>.value");
			else if (name == "vdd") 			vdd 				= node.get<double>("<xmlattr>.value");
			else if (name == "power_gating_vcc") 		power_gating_vcc 		= node.get<double>("<xmlattr>.value");
            	} else if (param.first == "stat") {
            	    	if (name == "total_cycles") 			total_cycles 			= node.get<double>("<xmlattr>.value");
            	    	else if (name == "idle_cycles") 		idle_cycles 			= node.get<double>("<xmlattr>.value");
            	    	else if (name == "busy_cycles") 		busy_cycles 			= node.get<double>("<xmlattr>.value");
		} else if (param.first == "component"){
			if (id.find("system.core") != std::string::npos) 				core.emplace_back(node);
			else if (id.find("system.L1Directory") != std::string::npos) 			L1Directory.emplace_back(node);
			else if (id.find("system.L2Directory") != std::string::npos) 			L2Directory.emplace_back(node);
			else if (id.find("system.L2") != std::string::npos) 				L2.emplace_back(node);
			else if (id.find("system.L3") != std::string::npos) 				L3.emplace_back(node);
			else if (id.find("system.NoC") != std::string::npos) 				NoC.emplace_back(node);
			else if (id == "system.mem") 			mem 				= SystemMem(node);
			else if (id == "system.mc") 			mc 				= SystemMemController(node);
			else if (id == "system.flashc") 		flashc 				= SystemMemController(node);
			else if (id == "system.niu") 			niu 				= SystemNiu(node);
			else if (id == "system.pcie") 			pcie 				= SystemPcie(node);
		}
		else std::cerr << "Warning, found component with id " << id << ", and name " << name << ". But has not been handled by McPat." << std::endl;
        }
}

void RootSystem::check_consitency(){
	bool issues_found = false;
	std::stringstream issues;
	issues << "Inconsistency has been found in the XML input:" << std::endl;
	if (! ((this->homogeneous_cores && this->core.size() >= 1) || (unsigned) this->number_of_cores <= this->core.size())) {
		issues_found = true;
		issues << "The number of cores in the system (" << this->number_of_cores << ") does not match the number of configurations seen (" << this->core.size() << ")" << std::endl;
	}
	if (! ((this->homogeneous_L1Directories && this->L1Directory.size() >= 1) || (unsigned) this->number_of_L1Directories <= this->L1Directory.size())) {
		issues_found = true;
		issues << "The number of L1Directories in the system (" << this->number_of_L1Directories << ") does not match the number of configurations seen (" << this->L1Directory.size() << ")" << std::endl;
	}
	if (! ((this->homogeneous_L2Directories && this->L2Directory.size() >= 1) || (unsigned) this->number_of_L2Directories <= this->L2Directory.size())) {
		issues_found = true;
		issues << "The number of L2Directories in the system (" << this->number_of_L2Directories << ") does not match the number of configurations seen (" << this->L2Directory.size() << ")" << std::endl;
	}
	if (! ((this->homogeneous_L2s && this->L2.size() >= 1) || (unsigned) this->number_of_L2s <= this->L2.size())) {
		issues_found = true;
		issues << "The number of L2s in the system (" << this->number_of_L2s << ") does not match the number of configurations seen (" << this->L2.size() << ")" << std::endl;
	}
	if (! ((this->homogeneous_L3s && this->L3.size() >= 1) || (unsigned) this->number_of_L3s <= this->L3.size())) {
		issues_found = true;
		issues << "The number of L3s in the system (" << this->number_of_L3s << ") does not match the number of configurations seen (" << this->L3.size() << ")" << std::endl;
	}
	if (! ((this->homogeneous_NoCs && this->NoC.size() >= 1) || (unsigned) this->number_of_NoCs <= this->NoC.size())) {
		issues_found = true;
		issues << "The number of NoCs in the system (" << this->number_of_NoCs << ") does not match the number of configurations seen (" << this->NoC.size() << ")" << std::endl;
	}

	if(issues_found){
		std::cerr << issues.str();
		std::exit(1);
	}
}

ParseXML::ParseXML(std::string xml_path){
	boost::property_tree::ptree xml_pt;
	boost::property_tree::read_xml(xml_path, xml_pt, boost::property_tree::xml_parser::trim_whitespace | boost::property_tree::xml_parser::no_comments);
	sys = RootSystem(xml_pt.get_child("component").get_child("component"));
}

template<typename T> 
void ParseXML::split_string(const std::string &input_str, std::vector<T> &dst){
	std::string buffer(input_str);
	buffer.erase(std::remove_if(buffer.begin(), buffer.end(), ::isspace), buffer.end());
	std::vector<std::string> tokens;
	boost::algorithm::split(tokens, buffer, boost::is_any_of(", "), boost::token_compress_on); 
	dst.reserve(dst.size() + tokens.size());
	std::transform(tokens.begin(), tokens.end(), std::back_inserter(dst), &boost::lexical_cast<T,std::string>);
}
