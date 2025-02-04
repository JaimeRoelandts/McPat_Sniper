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


#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <charconv>
#include <algorithm>
#include <iostream>
#include "xmlParser.h"
#include "XML_Parse.h"

using namespace std;

void ParseXML::parse(char* filepath)
{
	// this open and parse the XML file:
	XMLNode xMainNode=XMLNode::openFileHelper(filepath,"component"); //the 'component' in the first layer

	XMLNode xNode2=xMainNode.getChildNode("component"); // the 'component' in the second layer
	//get all params in the second layer
	unsigned nr_params_component = xNode2.nChildNode("param");
	for(unsigned i=0; i<nr_params_component ; i++)
	{
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_of_cores")==0) {sys.number_of_cores=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_of_L1Directories")==0) {sys.number_of_L1Directories=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_of_L2Directories")==0) {sys.number_of_L2Directories=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_of_L2s")==0) {sys.number_of_L2s=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"Private_L2")==0) {sys.Private_L2=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_of_L3s")==0) {sys.number_of_L3s=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_of_NoCs")==0) {sys.number_of_NoCs=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_of_dir_levels")==0) {sys.number_of_dir_levels=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"domain_size")==0) {sys.domain_size=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"first_level_dir")==0) {sys.first_level_dir=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"homogeneous_cores")==0) {sys.homogeneous_cores=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"core_tech_node")==0) {sys.core_tech_node=atof(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"target_core_clockrate")==0) {sys.target_core_clockrate=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"target_chip_area")==0) {sys.target_chip_area=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"temperature")==0) {sys.temperature=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"number_cache_levels")==0) {sys.number_cache_levels=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"L1_property")==0) {sys.L1_property =atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"L2_property")==0) {sys.L2_property =atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"homogeneous_L2s")==0) {sys.homogeneous_L2s=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"homogeneous_L1Directories")==0) {sys.homogeneous_L1Directories=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"homogeneous_L2Directories")==0) {sys.homogeneous_L2Directories=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"L3_property")==0) {sys.L3_property =atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"homogeneous_L3s")==0) {sys.homogeneous_L3s=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"homogeneous_ccs")==0) {sys.homogeneous_ccs=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"homogeneous_NoCs")==0) {sys.homogeneous_NoCs=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"Max_area_deviation")==0) {sys.Max_area_deviation=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"Max_power_deviation")==0) {sys.Max_power_deviation=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"device_type")==0) {sys.device_type=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"longer_channel_device")==0) {sys.longer_channel_device=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"power_gating")==0) {sys.power_gating=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"opt_dynamic_power")==0) {sys.opt_dynamic_power=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"opt_lakage_power")==0) {sys.opt_lakage_power=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"opt_clockrate")==0) {sys.opt_clockrate=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"opt_area")==0) {sys.opt_area=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"Embedded")==0) {sys.Embedded=(bool)atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"interconnect_projection_type")==0) {sys.interconnect_projection_type=atoi(xNode2.getChildNode("param",i).getAttribute("value"))==0?0:1;continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"machine_bits")==0) {sys.machine_bits=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"virtual_address_width")==0) {sys.virtual_address_width=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"physical_address_width")==0) {sys.physical_address_width=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"virtual_memory_page_size")==0) {sys.virtual_memory_page_size=atoi(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"vdd")==0) {sys.vdd=atof(xNode2.getChildNode("param",i).getAttribute("value"));continue;}
		if (strcmp(xNode2.getChildNode("param",i).getAttribute("name"),"power_gating_vcc")==0) {sys.power_gating_vcc=atof(xNode2.getChildNode("param",i).getAttribute("value"));continue;}


	}

//	if (sys.Private_L2 && sys.number_of_cores!=sys.number_of_L2s)
//	{
//		cout<<"Private L2: Number of L2s must equal to Number of Cores"<<endl;
//		exit(0);
//	}


	//TODO later, instead of resize, use proper pointers and class constructor/destructor
	sys.core.resize(sys.number_of_cores);
	std::cout << "Size of Directory to become is "<< sys.number_of_L1Directories << std::endl;
	//TODO so yeah, the system says there are 0 directories, but then tries to assign them anyways... :upsidedown_smile:
	sys.L1Directory.resize(sys.number_of_L1Directories);
	sys.L2Directory.resize(sys.number_of_L2Directories);
	sys.L2.resize(sys.number_of_L2s);
	sys.L3.resize(sys.number_of_L3s);
	sys.NoC.resize(sys.number_of_NoCs);

	unsigned nr_stat_component=xNode2.nChildNode("stat");
	for(unsigned i=0; i<nr_stat_component; i++)
	{
		if (strcmp(xNode2.getChildNode("stat",i).getAttribute("name"),"total_cycles")==0) {sys.total_cycles=atof(xNode2.getChildNode("stat",i).getAttribute("value"));continue;}

	}

	//get the number of components within the second layer
	unsigned int NumofCom_3=xNode2.nChildNode("component");
	XMLNode xNode3,xNode4; //define the third-layer(system.core0) and fourth-layer(system.core0.predictor) xnodes

	string strtmp;
	unsigned int OrderofComponents_3layer=0;
	if (NumofCom_3>OrderofComponents_3layer)
	{
		//___________________________get all system.core0-n________________________________________________
		if (sys.homogeneous_cores==1) OrderofComponents_3layer=0;
		else OrderofComponents_3layer=sys.number_of_cores-1;
		for (unsigned i=0; i<=OrderofComponents_3layer; i++)
		{
			xNode3=xNode2.getChildNode("component",i);
			if (xNode3.isEmpty()==1) {
				printf("The value of homogeneous_cores or number_of_cores is not correct!");
				exit(0);
			}
			else{
				if (strstr(xNode3.getAttribute("name"),"core")!=NULL)
				{
					{ //For cpu0-cpui
						//Get all params with system.core?
						unsigned nr_cores=xNode3.nChildNode("param");
						for(unsigned k=0; k<nr_cores; k++)
						{
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clock_rate")==0) {sys.core[i].clock_rate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"opt_local")==0) {sys.core[i].opt_local=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"x86")==0) {sys.core[i].x86=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"machine_bits")==0) {sys.core[i].machine_bits=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"virtual_address_width")==0) {sys.core[i].virtual_address_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"physical_address_width")==0) {sys.core[i].physical_address_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"instruction_length")==0) {sys.core[i].instruction_length=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"opcode_width")==0) {sys.core[i].opcode_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"micro_opcode_width")==0) {sys.core[i].micro_opcode_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"machine_type")==0) {sys.core[i].machine_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"internal_datapath_width")==0) {sys.core[i].internal_datapath_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_hardware_threads")==0) {sys.core[i].number_hardware_threads=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"fetch_width")==0) {sys.core[i].fetch_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_instruction_fetch_ports")==0) {sys.core[i].number_instruction_fetch_ports=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"decode_width")==0) {sys.core[i].decode_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"issue_width")==0) {sys.core[i].issue_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"peak_issue_width")==0) {sys.core[i].peak_issue_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"commit_width")==0) {sys.core[i].commit_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"fp_issue_width")==0) {sys.core[i].fp_issue_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"prediction_width")==0) {sys.core[i].prediction_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.core[i].vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.core[i].power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"pipelines_per_core")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.core[i].pipelines_per_core);continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"pipeline_depth")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.core[i].pipeline_depth);continue;}

							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"FPU")==0) {sys.core[i].FPU=xNode3.getChildNode("param",k).getAttribute("value");continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"divider_multiplier")==0) {sys.core[i].divider_multiplier=xNode3.getChildNode("param",k).getAttribute("value");continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"ALU_per_core")==0) {sys.core[i].ALU_per_core=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"FPU_per_core")==0) {sys.core[i].FPU_per_core=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"MUL_per_core")==0) {sys.core[i].MUL_per_core=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"instruction_buffer_size")==0) {sys.core[i].instruction_buffer_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"decoded_stream_buffer_size")==0) {sys.core[i].decoded_stream_buffer_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"instruction_window_scheme")==0) {sys.core[i].instruction_window_scheme  =atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"instruction_window_size")==0) {sys.core[i].instruction_window_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"fp_instruction_window_size")==0) {sys.core[i].fp_instruction_window_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"ROB_size")==0) {sys.core[i].ROB_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"archi_Regs_IRF_size")==0) {sys.core[i].archi_Regs_IRF_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"archi_Regs_FRF_size")==0) {sys.core[i].archi_Regs_FRF_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"phy_Regs_IRF_size")==0) {sys.core[i].phy_Regs_IRF_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"phy_Regs_FRF_size")==0) {sys.core[i].phy_Regs_FRF_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"rename_scheme")==0) {sys.core[i].rename_scheme=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"checkpoint_depth")==0) {sys.core[i].checkpoint_depth=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"register_windows_size")==0) {sys.core[i].register_windows_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"LSU_order")==0) {sys.core[i].LSU_order=xNode3.getChildNode("param",k).getAttribute("value");continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"store_buffer_size")==0) {sys.core[i].store_buffer_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"load_buffer_size")==0) {sys.core[i].load_buffer_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"memory_ports")==0) {sys.core[i].memory_ports=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"Dcache_dual_pump")==0) {sys.core[i].Dcache_dual_pump=xNode3.getChildNode("param",k).getAttribute("value");continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"RAS_size")==0) {sys.core[i].RAS_size=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						}
						//Get all stats with system.core?
						unsigned nr_stats_core=xNode3.nChildNode("stat");
						for(unsigned k=0; k<nr_stats_core; k++)
						{
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_instructions")==0) {sys.core[i].total_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"int_instructions")==0) {sys.core[i].int_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fp_instructions")==0) {sys.core[i].fp_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"branch_instructions")==0) {sys.core[i].branch_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"branch_mispredictions")==0) {sys.core[i].branch_mispredictions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"committed_instructions")==0) {sys.core[i].committed_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"committed_int_instructions")==0) {sys.core[i].committed_int_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"committed_fp_instructions")==0) {sys.core[i].committed_fp_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"load_instructions")==0) {sys.core[i].load_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"store_instructions")==0) {sys.core[i].store_instructions=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_cycles")==0) {sys.core[i].total_cycles=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"idle_cycles")==0) {sys.core[i].idle_cycles=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"busy_cycles")==0) {sys.core[i].busy_cycles=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"instruction_buffer_reads")==0) {sys.core[i].instruction_buffer_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"instruction_buffer_write")==0) {sys.core[i].instruction_buffer_write=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"ROB_reads")==0) {sys.core[i].ROB_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"ROB_writes")==0) {sys.core[i].ROB_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"rename_reads")==0) {sys.core[i].rename_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"rename_writes")==0) {sys.core[i].rename_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fp_rename_reads")==0) {sys.core[i].fp_rename_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fp_rename_writes")==0) {sys.core[i].fp_rename_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"inst_window_reads")==0) {sys.core[i].inst_window_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"inst_window_writes")==0) {sys.core[i].inst_window_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"inst_window_wakeup_accesses")==0) {sys.core[i].inst_window_wakeup_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"inst_window_selections")==0) {sys.core[i].inst_window_selections=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fp_inst_window_reads")==0) {sys.core[i].fp_inst_window_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fp_inst_window_writes")==0) {sys.core[i].fp_inst_window_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fp_inst_window_wakeup_accesses")==0) {sys.core[i].fp_inst_window_wakeup_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"archi_int_regfile_reads")==0) {sys.core[i].archi_int_regfile_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"archi_float_regfile_reads")==0) {sys.core[i].archi_float_regfile_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"phy_int_regfile_reads")==0) {sys.core[i].phy_int_regfile_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"phy_float_regfile_reads")==0) {sys.core[i].phy_float_regfile_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"phy_int_regfile_writes")==0) {sys.core[i].archi_int_regfile_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"phy_float_regfile_writes")==0) {sys.core[i].archi_float_regfile_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"archi_int_regfile_writes")==0) {sys.core[i].phy_int_regfile_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"archi_float_regfile_writes")==0) {sys.core[i].phy_float_regfile_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"int_regfile_reads")==0) {sys.core[i].int_regfile_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"float_regfile_reads")==0) {sys.core[i].float_regfile_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"int_regfile_writes")==0) {sys.core[i].int_regfile_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"float_regfile_writes")==0) {sys.core[i].float_regfile_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"windowed_reg_accesses")==0) {sys.core[i].windowed_reg_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"windowed_reg_transports")==0) {sys.core[i].windowed_reg_transports=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"function_calls")==0) {sys.core[i].function_calls=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"context_switches")==0) {sys.core[i].context_switches=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"ialu_accesses")==0) {sys.core[i].ialu_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fpu_accesses")==0) {sys.core[i].fpu_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"mul_accesses")==0) {sys.core[i].mul_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"cdb_alu_accesses")==0) {sys.core[i].cdb_alu_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"cdb_mul_accesses")==0) {sys.core[i].cdb_mul_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"cdb_fpu_accesses")==0) {sys.core[i].cdb_fpu_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"load_buffer_reads")==0) {sys.core[i].load_buffer_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"load_buffer_writes")==0) {sys.core[i].load_buffer_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"load_buffer_cams")==0) {sys.core[i].load_buffer_cams=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"store_buffer_reads")==0) {sys.core[i].store_buffer_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"store_buffer_writes")==0) {sys.core[i].store_buffer_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"store_buffer_cams")==0) {sys.core[i].store_buffer_cams=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"store_buffer_forwards")==0) {sys.core[i].store_buffer_forwards=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"main_memory_access")==0) {sys.core[i].main_memory_access=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"main_memory_read")==0) {sys.core[i].main_memory_read=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"main_memory_write")==0) {sys.core[i].main_memory_write=atoi(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"pipeline_duty_cycle")==0) {sys.core[i].pipeline_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}

							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"IFU_duty_cycle")==0) {sys.core[i].IFU_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"BR_duty_cycle")==0) {sys.core[i].BR_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"LSU_duty_cycle")==0) {sys.core[i].LSU_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"MemManU_I_duty_cycle")==0) {sys.core[i].MemManU_I_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"MemManU_D_duty_cycle")==0) {sys.core[i].MemManU_D_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"ALU_duty_cycle")==0) {sys.core[i].ALU_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"MUL_duty_cycle")==0) {sys.core[i].MUL_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"FPU_duty_cycle")==0) {sys.core[i].FPU_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"ALU_cdb_duty_cycle")==0) {sys.core[i].ALU_cdb_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"MUL_cdb_duty_cycle")==0) {sys.core[i].MUL_cdb_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"FPU_cdb_duty_cycle")==0) {sys.core[i].FPU_cdb_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						}
					}

					unsigned NumofCom_4=xNode3.nChildNode("component"); //get the number of components within the third layer
					for(unsigned j=0; j<NumofCom_4; j++)
					{
						xNode4=xNode3.getChildNode("component",j);
						if (strcmp(xNode4.getAttribute("name"),"PBT")==0)
						{ //find PBT
							unsigned nr_params_branch_predictor=xNode4.nChildNode("param");
							for(unsigned k=0; k<nr_params_branch_predictor; k++)
							{ //get all items of param in system.core0.predictor--PBT
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"prediction_width")==0) {sys.core[i].predictor.prediction_width=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"prediction_scheme")==0) {sys.core[i].predictor.prediction_scheme=xNode4.getChildNode("param",k).getAttribute("value");continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"predictor_size")==0) {sys.core[i].predictor.predictor_size=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"predictor_entries")==0) {sys.core[i].predictor.predictor_entries=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"local_predictor_size")==0){split_string(xNode4.getChildNode("param",k).getAttribute("value"), sys.core[i].predictor.local_predictor_size);continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"local_predictor_entries")==0) {sys.core[i].predictor.local_predictor_entries=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"global_predictor_entries")==0) {sys.core[i].predictor.global_predictor_entries=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"global_predictor_bits")==0) {sys.core[i].predictor.global_predictor_bits=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"chooser_predictor_entries")==0) {sys.core[i].predictor.chooser_predictor_entries=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"chooser_predictor_bits")==0) {sys.core[i].predictor.chooser_predictor_bits=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
							}
							unsigned nr_stats_predictor=xNode4.nChildNode("stat");
							for(unsigned k=0; k<nr_stats_predictor; k++)
							{ //get all items of stat in system.core0.predictor--PBT
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"predictor_accesses")==0) sys.core[i].predictor.predictor_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));
							}
						}
						if (strcmp(xNode4.getAttribute("name"),"itlb")==0)
						{//find system.core0.itlb
							unsigned nr_params_itlb=xNode4.nChildNode("param");
							for(unsigned k=0; k<nr_params_itlb; k++)
							{ //get all items of param in system.core0.itlb--itlb
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"number_entries")==0) sys.core[i].itlb.number_entries=atoi(xNode4.getChildNode("param",k).getAttribute("value"));
							}
							unsigned nr_stat_itlb=xNode4.nChildNode("stat");
							for(unsigned k=0; k<nr_stat_itlb; k++)
							{ //get all items of stat in itlb
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_hits")==0) {sys.core[i].itlb.total_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.core[i].itlb.total_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_misses")==0) {sys.core[i].itlb.total_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.core[i].itlb.conflicts=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
							}
						}
						if (strcmp(xNode4.getAttribute("name"),"icache")==0)
						{//find system.core0.icache
							unsigned nr_param_icache=xNode4.nChildNode("param");
							for(unsigned k=0; k<nr_param_icache; k++)
							{ //get all items of param in system.core0.icache--icache
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"icache_config")==0){split_string(xNode4.getChildNode("param",k).getAttribute("value"),sys.core[i].icache.icache_config);continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"buffer_sizes")==0){split_string(xNode4.getChildNode("param",k).getAttribute("value"),sys.core[i].icache.buffer_sizes);continue;}
							}
							unsigned nr_stat_icache=xNode4.nChildNode("stat");
							for(unsigned k=0; k<nr_stat_icache; k++)
							{
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.core[i].icache.total_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.core[i].icache.read_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.core[i].icache.read_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"replacements")==0) {sys.core[i].icache.replacements=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_hits")==0) {sys.core[i].icache.read_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_hits")==0) {sys.core[i].icache.total_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_misses")==0) {sys.core[i].icache.total_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"miss_buffer_access")==0) {sys.core[i].icache.miss_buffer_access=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"fill_buffer_accesses")==0) {sys.core[i].icache.fill_buffer_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_accesses")==0) {sys.core[i].icache.prefetch_buffer_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_writes")==0) {sys.core[i].icache.prefetch_buffer_writes=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_reads")==0) {sys.core[i].icache.prefetch_buffer_reads=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_hits")==0) {sys.core[i].icache.prefetch_buffer_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.core[i].icache.conflicts=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
							}
						}
						if (strcmp(xNode4.getAttribute("name"),"dtlb")==0)
						{//find system.core0.dtlb
							unsigned nr_params_dtlb=xNode4.nChildNode("param");
							for(unsigned k=0; k<nr_params_dtlb; k++)
							{ //get all items of param in system.core0.dtlb--dtlb
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"number_entries")==0) sys.core[i].dtlb.number_entries=atoi(xNode4.getChildNode("param",k).getAttribute("value"));
							}
							unsigned nr_stat_dtlb=xNode4.nChildNode("stat");
							for(unsigned k=0; k<nr_stat_dtlb; k++)
							{ //get all items of stat in dtlb
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.core[i].dtlb.total_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.core[i].dtlb.read_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_accesses")==0) {sys.core[i].dtlb.write_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_hits")==0) {sys.core[i].dtlb.read_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_hits")==0) {sys.core[i].dtlb.write_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.core[i].dtlb.read_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_misses")==0) {sys.core[i].dtlb.write_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_hits")==0) {sys.core[i].dtlb.total_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_misses")==0) {sys.core[i].dtlb.total_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.core[i].dtlb.conflicts=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}

							}
						}
						if (strcmp(xNode4.getAttribute("name"),"dcache")==0)
						{//find system.core0.dcache
							unsigned nr_params_dache=xNode4.nChildNode("param");
							for(unsigned k=0; k<nr_params_dache; k++)
							{ //get all items of param in system.core0.dcache--dcache
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"dcache_config")==0){split_string(xNode4.getChildNode("param",k).getAttribute("value"),sys.core[i].dcache.dcache_config);continue;}
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"buffer_sizes")==0){split_string(xNode4.getChildNode("param",k).getAttribute("value"),sys.core[i].dcache.buffer_sizes);continue;}
							}
							unsigned nr_stat_dcache=xNode4.nChildNode("stat");
							for(unsigned k=0; k<nr_stat_dcache; k++)
							{ //get all items of stat in dcache
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.core[i].dcache.total_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.core[i].dcache.read_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_accesses")==0) {sys.core[i].dcache.write_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_hits")==0) {sys.core[i].dcache.total_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_misses")==0) {sys.core[i].dcache.total_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_hits")==0) {sys.core[i].dcache.read_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_hits")==0) {sys.core[i].dcache.write_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.core[i].dcache.read_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_misses")==0) {sys.core[i].dcache.write_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"replacements")==0) {sys.core[i].dcache.replacements=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_backs")==0) {sys.core[i].dcache.write_backs=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"miss_buffer_access")==0) {sys.core[i].dcache.miss_buffer_access=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"fill_buffer_accesses")==0) {sys.core[i].dcache.fill_buffer_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_accesses")==0) {sys.core[i].dcache.prefetch_buffer_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_writes")==0) {sys.core[i].dcache.prefetch_buffer_writes=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_reads")==0) {sys.core[i].dcache.prefetch_buffer_reads=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_hits")==0) {sys.core[i].dcache.prefetch_buffer_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"wbb_writes")==0) {sys.core[i].dcache.wbb_writes=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"wbb_reads")==0) {sys.core[i].dcache.wbb_reads=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.core[i].dcache.conflicts=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}

							}
						}
						if (strcmp(xNode4.getAttribute("name"),"BTB")==0)
						{//find system.core0.BTB
							unsigned nr_params_btb=xNode4.nChildNode("param");
							for(unsigned k=0; k<nr_params_btb; k++)
							{ //get all items of param in system.core0.BTB--BTB
								if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"BTB_config")==0){split_string(xNode4.getChildNode("param",k).getAttribute("value"),sys.core[i].BTB.BTB_config);continue;}
							}
							unsigned nr_stat_btb=xNode4.nChildNode("stat");
							for(unsigned k=0; k<nr_stat_btb; k++)
							{ //get all items of stat in BTB
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.core[i].BTB.total_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.core[i].BTB.read_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_accesses")==0) {sys.core[i].BTB.write_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_hits")==0) {sys.core[i].BTB.total_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"total_misses")==0) {sys.core[i].BTB.total_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_hits")==0) {sys.core[i].BTB.read_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_hits")==0) {sys.core[i].BTB.write_hits=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.core[i].BTB.read_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"write_misses")==0) {sys.core[i].BTB.write_misses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
								if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"replacements")==0) {sys.core[i].BTB.replacements=atof(xNode4.getChildNode("stat",k).getAttribute("value"));continue;}
							}
						}
					}
				}
				else {
					printf("The value of homogeneous_cores or number_of_cores is not correct!");
					exit(0);
				}
			}
		}

		//__________________________________________Get system.L1Directory0-n____________________________________________
		int w=OrderofComponents_3layer+1;
		int tmpOrderofComponents_3layer=OrderofComponents_3layer;
		if (sys.homogeneous_L1Directories==1) OrderofComponents_3layer=OrderofComponents_3layer+1;
		else OrderofComponents_3layer=OrderofComponents_3layer+sys.number_of_L1Directories;

		for (unsigned i=0; i<(OrderofComponents_3layer-tmpOrderofComponents_3layer) && i < sys.L1Directory.size(); i++)
		{
			xNode3=xNode2.getChildNode("component",w);
			if (xNode3.isEmpty()==1) {
				printf("The value of homogeneous_L1Directories or number_of_L1Directories is not correct!");
				exit(0);
			}
			else
			{
				if (strstr(xNode3.getAttribute("id"),"L1Directory")!=NULL)
				{
					unsigned nr_params_L1Directory=xNode3.nChildNode("param");
					for(unsigned k=0; k<nr_params_L1Directory; k++)
					{ //get all items of param in system.L1Directory
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"Dir_config")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L1Directory[i].Dir_config);continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"buffer_sizes")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L1Directory[i].buffer_sizes);continue;}

						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clockrate")==0) {sys.L1Directory[i].clockrate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.L1Directory[i].vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.L1Directory[i].power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"ports")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L1Directory[i].ports);continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"device_type")==0) {sys.L1Directory[i].device_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"Directory_type")==0) {sys.L1Directory[i].Directory_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"3D_stack")==0) {sys.L1Directory[i].threeD_stack=xNode3.getChildNode("param",k).getAttribute("value");continue;}
					}
					unsigned nr_stats_L1Directory=xNode3.nChildNode("stat");
					for(unsigned k=0; k<nr_stats_L1Directory; k++)
					{ //get all items of stat in system.L1directorydirectory
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.L1Directory[i].total_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.L1Directory[i].read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_accesses")==0) {sys.L1Directory[i].write_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.L1Directory[i].read_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_misses")==0) {sys.L1Directory[i].write_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.L1Directory[i].conflicts=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) {sys.L1Directory[i].duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
					}
					w=w+1;
				}
				else {
					printf("The value of homogeneous_L1Directories or number_of_L1Directories is not correct!");
					exit(0);
				}
			}
		}

		//__________________________________________Get system.L2Directory0-n____________________________________________
		w=OrderofComponents_3layer+1;
		tmpOrderofComponents_3layer=OrderofComponents_3layer;
		if (sys.homogeneous_L2Directories==1) OrderofComponents_3layer=OrderofComponents_3layer+1;
		else OrderofComponents_3layer=OrderofComponents_3layer+sys.number_of_L2Directories;

		for (unsigned i=0; i<(OrderofComponents_3layer-tmpOrderofComponents_3layer) && i < sys.L2Directory.size(); i++)
		{
			xNode3=xNode2.getChildNode("component",w);
			if (xNode3.isEmpty()==1) {
				printf("The value of homogeneous_L2Directories or number_of_L2Directories is not correct!");
				exit(0);
			}
			else
			{
				if (strstr(xNode3.getAttribute("id"),"L2Directory")!=NULL)
				{
					unsigned nr_params_L2Directory=xNode3.nChildNode("param");
					for(unsigned k=0; k<nr_params_L2Directory; k++)
					{ //get all items of param in system.L2Directory
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"Dir_config")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L2Directory[i].Dir_config);continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"buffer_sizes")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L2Directory[i].buffer_sizes);continue;}

						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clockrate")==0) {sys.L2Directory[i].clockrate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.L2Directory[i].vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.L2Directory[i].power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"Directory_type")==0) {sys.L2Directory[i].Directory_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"ports")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L2Directory[i].ports);continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"device_type")==0) {sys.L2Directory[i].device_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"3D_stack")==0) {sys.L2Directory[i].threeD_stack=xNode3.getChildNode("param",k).getAttribute("value");continue;}
					}
					unsigned nr_stat_L2Directory=xNode3.nChildNode("stat");
					for(unsigned k=0; k<nr_stat_L2Directory; k++)
					{ //get all items of stat in system.L2directorydirectory
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.L2Directory[i].total_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.L2Directory[i].read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_accesses")==0) {sys.L2Directory[i].write_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.L2Directory[i].read_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
     					if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_misses")==0) {sys.L2Directory[i].write_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.L2Directory[i].conflicts=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
						if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) {sys.L2Directory[i].duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}

					}
					w=w+1;
				}
				else {
					printf("The value of homogeneous_L2Directories or number_of_L2Directories is not correct!");
					exit(0);
				}
			}
		}

		//__________________________________________Get system.L2[0..n]____________________________________________
		w=OrderofComponents_3layer+1;
		tmpOrderofComponents_3layer=OrderofComponents_3layer;
		if (sys.homogeneous_L2s==1) OrderofComponents_3layer=OrderofComponents_3layer+1;
		else OrderofComponents_3layer=OrderofComponents_3layer+sys.number_of_L2s;

		for (unsigned i=0; i<(OrderofComponents_3layer-tmpOrderofComponents_3layer); i++)
		{
			xNode3=xNode2.getChildNode("component",w);
			if (xNode3.isEmpty()==1) {
				printf("The value of homogeneous_L2s or number_of_L2s is not correct!");
				exit(0);
			}
			else
			{
				if (strstr(xNode3.getAttribute("name"),"L2")!=NULL)
				{
					{ //For L20-L2i
						//Get all params with system.L2?
						unsigned nr_params_l2=xNode3.nChildNode("param");
						for(unsigned k=0; k<nr_params_l2; k++)
						{
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"L2_config")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L2[i].cache_config);continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clockrate")==0) {sys.L2[i].clockrate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.L2[i].vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.L2[i].power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"merged_dir")==0) {sys.L2[i].merged_dir=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"ports")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L2[i].ports);continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"device_type")==0) {sys.L2[i].device_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"threeD_stack")==0) {sys.L2[i].threeD_stack=(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"buffer_sizes")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L2[i].buffer_sizes);continue;}
						}
						//Get all stats with system.L2?
						unsigned nr_stats_l2=xNode3.nChildNode("stat");
						for(unsigned k=0; k<nr_stats_l2; k++)
						{
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.L2[i].total_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.L2[i].read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_accesses")==0) {sys.L2[i].write_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_hits")==0) {sys.L2[i].total_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_misses")==0) {sys.L2[i].total_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_hits")==0) {sys.L2[i].read_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_hits")==0) {sys.L2[i].write_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.L2[i].read_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_misses")==0) {sys.L2[i].write_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"replacements")==0) {sys.L2[i].replacements=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_backs")==0) {sys.L2[i].write_backs=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"miss_buffer_accesses")==0) {sys.L2[i].miss_buffer_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fill_buffer_accesses")==0) {sys.L2[i].fill_buffer_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_accesses")==0) {sys.L2[i].prefetch_buffer_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_writes")==0) {sys.L2[i].prefetch_buffer_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_reads")==0) {sys.L2[i].prefetch_buffer_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_hits")==0) {sys.L2[i].prefetch_buffer_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"wbb_writes")==0) {sys.L2[i].wbb_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"wbb_reads")==0) {sys.L2[i].wbb_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.L2[i].conflicts=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) {sys.L2[i].duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}

							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_accesses")==0) {sys.L2[i].homenode_read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_accesses")==0) {sys.L2[i].homenode_read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_hits")==0) {sys.L2[i].homenode_read_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_write_hits")==0) {sys.L2[i].homenode_write_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_misses")==0) {sys.L2[i].homenode_read_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_write_misses")==0) {sys.L2[i].homenode_write_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"dir_duty_cycle")==0) {sys.L2[i].dir_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}

						}
					}
					w=w+1;
				}
				else {
					printf("The value of homogeneous_L2s or number_of_L2s is not correct!");
					exit(0);
				}
			}
		}
		//__________________________________________Get system.L3[0..n]____________________________________________
		w=OrderofComponents_3layer+1;
		tmpOrderofComponents_3layer=OrderofComponents_3layer;
		if (sys.homogeneous_L3s==1) OrderofComponents_3layer=OrderofComponents_3layer+1;
		else OrderofComponents_3layer=OrderofComponents_3layer+sys.number_of_L3s;

		for (unsigned i=0; i<(OrderofComponents_3layer-tmpOrderofComponents_3layer); i++)
		{
			xNode3=xNode2.getChildNode("component",w);
			if (xNode3.isEmpty()==1) {
				printf("The value of homogeneous_L3s or number_of_L3s is not correct!");
				exit(0);
			}
			else
			{
				if (strstr(xNode3.getAttribute("name"),"L3")!=NULL)
				{
					{ //For L30-L3i
						//Get all params with system.L3?
						unsigned nr_param_l3=xNode3.nChildNode("param");
						for(unsigned k=0; k<nr_param_l3; k++)
						{
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"L3_config")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L3[i].cache_config);continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clockrate")==0) {sys.L3[i].clockrate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.L3[i].vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.L3[i].power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"merged_dir")==0) {sys.L3[i].merged_dir=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"ports")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L3[i].ports);continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"device_type")==0) {sys.L3[i].device_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"threeD_stack")==0) {sys.L3[i].threeD_stack=(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"buffer_sizes")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.L3[i].buffer_sizes);continue;}
						}
						//Get all stats with system.L3?
						unsigned nr_stats_l3=xNode3.nChildNode("stat");
						for(unsigned k=0; k<nr_stats_l3; k++)
						{
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) {sys.L3[i].total_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_accesses")==0) {sys.L3[i].read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_accesses")==0) {sys.L3[i].write_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_hits")==0) {sys.L3[i].total_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_misses")==0) {sys.L3[i].total_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_hits")==0) {sys.L3[i].read_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_hits")==0) {sys.L3[i].write_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"read_misses")==0) {sys.L3[i].read_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_misses")==0) {sys.L3[i].write_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"replacements")==0) {sys.L3[i].replacements=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"write_backs")==0) {sys.L3[i].write_backs=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"miss_buffer_accesses")==0) {sys.L3[i].miss_buffer_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"fill_buffer_accesses")==0) {sys.L3[i].fill_buffer_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_accesses")==0) {sys.L3[i].prefetch_buffer_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_writes")==0) {sys.L3[i].prefetch_buffer_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_reads")==0) {sys.L3[i].prefetch_buffer_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"prefetch_buffer_hits")==0) {sys.L3[i].prefetch_buffer_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"wbb_writes")==0) {sys.L3[i].wbb_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"wbb_reads")==0) {sys.L3[i].wbb_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"conflicts")==0) {sys.L3[i].conflicts=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) {sys.L3[i].duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}

							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_accesses")==0) {sys.L3[i].homenode_read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_accesses")==0) {sys.L3[i].homenode_read_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_hits")==0) {sys.L3[i].homenode_read_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_write_hits")==0) {sys.L3[i].homenode_write_hits=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_read_misses")==0) {sys.L3[i].homenode_read_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"homenode_write_misses")==0) {sys.L3[i].homenode_write_misses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"dir_duty_cycle")==0) {sys.L3[i].dir_duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}

						}
					}
					w=w+1;
				}
				else {
					printf("The value of homogeneous_L3s or number_of_L3s is not correct!");
					exit(0);
				}
			}
		}
		//__________________________________________Get system.NoC[0..n]____________________________________________
		w=OrderofComponents_3layer+1;
		tmpOrderofComponents_3layer=OrderofComponents_3layer;
		if (sys.homogeneous_NoCs==1) OrderofComponents_3layer=OrderofComponents_3layer+1;
		else OrderofComponents_3layer=OrderofComponents_3layer+sys.number_of_NoCs;

		for (unsigned i=0; i<(OrderofComponents_3layer-tmpOrderofComponents_3layer); i++)
		{
			xNode3=xNode2.getChildNode("component",w);
			if (xNode3.isEmpty()==1) {
				printf("The value of homogeneous_NoCs or number_of_NoCs is not correct!");
				exit(0);
			}
			else
			{
				if (strstr(xNode3.getAttribute("name"),"noc")!=NULL)
				{
					{ //For NoC0-NoCi
						//Get all params with system.NoC?
						unsigned nr_params_noc=xNode3.nChildNode("param");
						for(unsigned k=0; k<nr_params_noc; k++)
						{
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clockrate")==0) {sys.NoC[i].clockrate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"type")==0) {sys.NoC[i].type=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.NoC[i].vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.NoC[i].power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"topology")==0) {sys.NoC[i].topology=(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"horizontal_nodes")==0) {sys.NoC[i].horizontal_nodes=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vertical_nodes")==0) {sys.NoC[i].vertical_nodes=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"has_global_link")==0) {sys.NoC[i].has_global_link=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"link_throughput")==0) {sys.NoC[i].link_throughput=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"link_latency")==0) {sys.NoC[i].link_latency=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"input_ports")==0) {sys.NoC[i].input_ports=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"output_ports")==0) {sys.NoC[i].output_ports=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"virtual_channel_per_port")==0) {sys.NoC[i].virtual_channel_per_port=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"flit_bits")==0) {sys.NoC[i].flit_bits=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"input_buffer_entries_per_vc")==0) {sys.NoC[i].input_buffer_entries_per_vc=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"dual_pump")==0) {sys.NoC[i].dual_pump=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"chip_coverage")==0) {sys.NoC[i].chip_coverage=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"link_routing_over_percentage")==0) {sys.NoC[i].route_over_perc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"ports_of_input_buffer")==0){split_string(xNode3.getChildNode("param",k).getAttribute("value"),sys.NoC[i].ports_of_input_buffer);continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_of_crossbars")==0) {sys.NoC[i].number_of_crossbars=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"crossbar_type")==0) {sys.NoC[i].crossbar_type=(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"crosspoint_type")==0) {sys.NoC[i].crosspoint_type=(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
							if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"arbiter_type")==0) {sys.NoC[i].arbiter_type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
						}
						unsigned NumofCom_4=xNode3.nChildNode("component"); //get the number of components within the third layer
						for(unsigned j=0; j<NumofCom_4; j++)
						{
							xNode4=xNode3.getChildNode("component",j);
							if (strcmp(xNode4.getAttribute("name"),"xbar0")==0)
							{ //find PBT
								unsigned nr_params_pbt=xNode4.nChildNode("param");
								for(unsigned k=0; k<nr_params_pbt; k++)
								{ //get all items of param in system.XoC0.xbar0--xbar0
									if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"number_of_inputs_of_crossbars")==0) {sys.NoC[i].xbar0.number_of_inputs_of_crossbars=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
									if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"number_of_outputs_of_crossbars")==0) {sys.NoC[i].xbar0.number_of_outputs_of_crossbars=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
									if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"flit_bits")==0) {sys.NoC[i].xbar0.flit_bits=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
									if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"input_buffer_entries_per_port")==0) {sys.NoC[i].xbar0.input_buffer_entries_per_port=atoi(xNode4.getChildNode("param",k).getAttribute("value"));continue;}
									if (strcmp(xNode4.getChildNode("param",k).getAttribute("name"),"ports_of_input_buffer")==0){split_string(xNode4.getChildNode("param",k).getAttribute("value"),sys.NoC[i].xbar0.ports_of_input_buffer);continue;}
								}
								unsigned nr_stats_pbt=xNode4.nChildNode("stat");
								for(unsigned k=0; k<nr_stats_pbt; k++)
								{ //get all items of stat in system.core0.predictor--PBT
									if (strcmp(xNode4.getChildNode("stat",k).getAttribute("name"),"predictor_accesses")==0) sys.core[i].predictor.predictor_accesses=atof(xNode4.getChildNode("stat",k).getAttribute("value"));
								}
							}
						}
						//Get all stats with system.NoC?
						unsigned nr_stats_noc=xNode3.nChildNode("stat");
						for(unsigned k=0; k<nr_stats_noc; k++)
						{
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_accesses")==0) sys.NoC[i].total_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));
							if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) sys.NoC[i].duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));
						}
					}
					w=w+1;
				}
			}
		}
		//__________________________________________Get system.mem____________________________________________
//		if (OrderofComponents_3layer>0) OrderofComponents_3layer=OrderofComponents_3layer+1;
//		xNode3=xNode2.getChildNode("component",OrderofComponents_3layer);
//		if (xNode3.isEmpty()==1) {
//			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
//			exit(0);
//		}
//		if (strstr(xNode3.getAttribute("id"),"system.mem")!=NULL)
//		{
//
//			itmp=xNode3.nChildNode("param");
//			for(unsigned k=0; k<itmp; k++)
//			{ //get all items of param in system.mem
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"mem_tech_node")==0) {sys.mem.mem_tech_node=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"device_clock")==0) {sys.mem.device_clock=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"peak_transfer_rate")==0) {sys.mem.peak_transfer_rate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"capacity_per_channel")==0) {sys.mem.capacity_per_channel=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_ranks")==0) {sys.mem.number_ranks=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"num_banks_of_DRAM_chip")==0) {sys.mem.num_banks_of_DRAM_chip=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"block_width_of_DRAM_chip")==0) {sys.mem.block_width_of_DRAM_chip=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"output_width_of_DRAM_chip")==0) {sys.mem.output_width_of_DRAM_chip=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"page_size_of_DRAM_chip")==0) {sys.mem.page_size_of_DRAM_chip=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"burstlength_of_DRAM_chip")==0) {sys.mem.burstlength_of_DRAM_chip=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"internal_prefetch_of_DRAM_chip")==0) {sys.mem.internal_prefetch_of_DRAM_chip=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//			}
//			itmp=xNode3.nChildNode("stat");
//			for(unsigned k=0; k<itmp; k++)
//			{ //get all items of stat in system.mem
//				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_accesses")==0) {sys.mem.memory_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_reads")==0) {sys.mem.memory_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_writes")==0) {sys.mem.memory_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
//			}
//		}
//		else{
//			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
//			exit(0);
//		}
		//__________________________________________Get system.mc____________________________________________
		if (OrderofComponents_3layer>0) OrderofComponents_3layer=OrderofComponents_3layer+1;
		xNode3=xNode2.getChildNode("component",OrderofComponents_3layer);
		if (xNode3.isEmpty()==1) {
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}
		if (strstr(xNode3.getAttribute("id"),"system.mc")!=NULL)
		{
			unsigned nr_params_memory_controller=xNode3.nChildNode("param");
			for(unsigned k=0; k<nr_params_memory_controller; k++)
			{ //get all items of param in system.mem
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"mc_clock")==0) {sys.mc.mc_clock=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.mc.vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.mc.power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"block_size")==0) {sys.mc.llc_line_length=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_mcs")==0) {sys.mc.number_mcs=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"memory_channels_per_mc")==0) {sys.mc.memory_channels_per_mc=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"req_window_size_per_channel")==0) {sys.mc.req_window_size_per_channel=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"io_buffer_size_per_channel")==0) {sys.mc.io_buffer_size_per_channel=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"databus_width")==0) {sys.mc.databus_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"addressbus_width")==0) {sys.mc.addressbus_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"peak_transfer_rate")==0) {sys.mc.peak_transfer_rate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_ranks")==0) {sys.mc.number_ranks=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"lvds")==0) {sys.mc.lvds=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"type")==0) {sys.mc.type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"withPHY")==0) {sys.mc.withPHY=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

			}
			unsigned nr_stats_memory_controller=xNode3.nChildNode("stat");
			for(unsigned k=0; k<nr_stats_memory_controller; k++)
			{ //get all items of stat in system.mendirectory
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_accesses")==0) {sys.mc.memory_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_reads")==0) {sys.mc.memory_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_writes")==0) {sys.mc.memory_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
			}
		}
		else{
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}
		//__________________________________________Get system.niu____________________________________________
		if (OrderofComponents_3layer>0) OrderofComponents_3layer=OrderofComponents_3layer+1;
		xNode3=xNode2.getChildNode("component",OrderofComponents_3layer);
		if (xNode3.isEmpty()==1) {
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}
		if (strstr(xNode3.getAttribute("id"),"system.niu")!=NULL)
		{
			unsigned nr_params_niu=xNode3.nChildNode("param");
			for(unsigned k=0; k<nr_params_niu; k++)
			{ //get all items of param in system.mem
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clockrate")==0) {sys.niu.clockrate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_units")==0) {sys.niu.number_units=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"type")==0) {sys.niu.type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.niu.vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.niu.power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

			}
			unsigned nr_stats_niu=xNode3.nChildNode("stat");
			for(unsigned k=0; k<nr_stats_niu; k++)
			{ //get all items of stat in system.mendirectory
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) {sys.niu.duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_load_perc")==0) {sys.niu.total_load_perc=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
			}
		}
		else{
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}

		//__________________________________________Get system.pcie____________________________________________
		if (OrderofComponents_3layer>0) OrderofComponents_3layer=OrderofComponents_3layer+1;
		xNode3=xNode2.getChildNode("component",OrderofComponents_3layer);
		if (xNode3.isEmpty()==1) {
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}
		if (strstr(xNode3.getAttribute("id"),"system.pcie")!=NULL)
		{
			unsigned nr_params_pcie=xNode3.nChildNode("param");
			for(unsigned k=0; k<nr_params_pcie; k++)
			{ //get all items of param in system.mem
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"clockrate")==0) {sys.pcie.clockrate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_units")==0) {sys.pcie.number_units=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"num_channels")==0) {sys.pcie.num_channels=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"type")==0) {sys.pcie.type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.pcie.vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.pcie.power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"withPHY")==0) {sys.pcie.withPHY=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

			}
			unsigned nr_stats_pcie=xNode3.nChildNode("stat");
			for(unsigned k=0; k<nr_stats_pcie; k++)
			{ //get all items of stat in system.mendirectory
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) {sys.pcie.duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_load_perc")==0) {sys.pcie.total_load_perc=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
			}
		}
		else{
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}
		//__________________________________________Get system.flashcontroller____________________________________________
		if (OrderofComponents_3layer>0) OrderofComponents_3layer=OrderofComponents_3layer+1;
		xNode3=xNode2.getChildNode("component",OrderofComponents_3layer);
		if (xNode3.isEmpty()==1) {
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}
		if (strstr(xNode3.getAttribute("id"),"system.flashc")!=NULL)
		{
			unsigned nr_params_flashc=xNode3.nChildNode("param");
			for(unsigned k=0; k<nr_params_flashc; k++)
			{ //get all items of param in system.mem
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"flashc_clock")==0) {sys.flashc.mc_clock=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"block_size")==0) {sys.flashc.llc_line_length=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_flashcs")==0) {sys.flashc.number_mcs=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"vdd")==0) {sys.flashc.vdd=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"power_gating_vcc")==0) {sys.flashc.power_gating_vcc=atof(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"memory_channels_per_flashc")==0) {sys.flashc.memory_channels_per_mc=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"req_window_size_per_channel")==0) {sys.flashc.req_window_size_per_channel=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"io_buffer_size_per_channel")==0) {sys.flashc.io_buffer_size_per_channel=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"databus_width")==0) {sys.flashc.databus_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"addressbus_width")==0) {sys.flashc.addressbus_width=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"peak_transfer_rate")==0) {sys.flashc.peak_transfer_rate=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"number_ranks")==0) {sys.flashc.number_ranks=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"lvds")==0) {sys.flashc.lvds=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"type")==0) {sys.flashc.type=atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("param",k).getAttribute("name"),"withPHY")==0) {sys.flashc.withPHY=(bool)atoi(xNode3.getChildNode("param",k).getAttribute("value"));continue;}

			}
			unsigned nr_stats_params=xNode3.nChildNode("stat");
			for(unsigned k=0; k<nr_stats_params; k++)
			{ //get all items of stat in system.mendirectory
//				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_accesses")==0) {sys.flashc.memory_accesses=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_reads")==0) {sys.flashc.memory_reads=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
//				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"memory_writes")==0) {sys.flashc.memory_writes=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"duty_cycle")==0) {sys.flashc.duty_cycle=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}
				if (strcmp(xNode3.getChildNode("stat",k).getAttribute("name"),"total_load_perc")==0) {sys.flashc.total_load_perc=atof(xNode3.getChildNode("stat",k).getAttribute("value"));continue;}

			}
		}
		else{
			printf("some value(s) of number_of_cores/number_of_L2s/number_of_L3s/number_of_NoCs is/are not correct!");
			exit(0);
		}

	}
}

PredictorSystemCore::PredictorSystemCore():
	prediction_width(1),
	prediction_scheme("default"),
	predictor_size(1),
	predictor_entries(1),
	local_predictor_size(),
	local_predictor_entries(1),
	global_predictor_entries(1),
	global_predictor_bits(1),
	chooser_predictor_entries(1),
	chooser_predictor_bits(1),
	predictor_accesses(1)
{};


ItlbSystemCore::ItlbSystemCore():
	number_entries(1),
	cache_policy(0),
	total_hits(1),
	total_accesses(1),
	total_misses(1),
	conflicts(0)
{};

IcacheSystemCore::IcacheSystemCore():
	icache_config(),
	total_accesses(1),
	read_accesses(1),
	read_misses(1),
	replacements(1),
	read_hits(1),
	total_hits(1),
	total_misses(1),
	miss_buffer_access(1),
	fill_buffer_accesses(1),
	prefetch_buffer_accesses(1),
	prefetch_buffer_writes(1),
	prefetch_buffer_reads(1),
	prefetch_buffer_hits(1)
{};

DtlbSystemCore::DtlbSystemCore():
	number_entries(1),
	total_accesses(1),
	read_accesses(1),
	write_accesses(1),
	write_hits(1),
	read_hits(1),
	read_misses(1),
	write_misses(1),
	total_hits(1),
	total_misses(1)
{};

DcacheSystemCore::DcacheSystemCore():
	dcache_config(),
	total_accesses(1),
	read_accesses(1),
	write_accesses(1),
	total_hits(1),
	total_misses(1),
	read_hits(1),
	write_hits(1),
	read_misses(1),
	write_misses(1),
	replacements(1),
	write_backs(1),
	miss_buffer_access(1),
	fill_buffer_accesses(1),
	prefetch_buffer_accesses(1),
	prefetch_buffer_writes(1),
	prefetch_buffer_reads(1),
	prefetch_buffer_hits(1),
	wbb_writes(1),
	wbb_reads(1)
{};

BtbSystemCore::BtbSystemCore():
	BTB_config(),
	total_accesses(1),
	read_accesses(1),
	write_accesses(1),
	total_hits(1),
	total_misses(1),
	read_hits(1),
	write_hits(1),
	read_misses(1),
	write_misses(1),
	replacements(1)
{};

SystemCore::SystemCore():
	clock_rate(1),
	opt_local(true),
	x86(false),
	machine_bits(1),
	virtual_address_width(1),
	physical_address_width(1),
	opcode_width(1),
	micro_opcode_width(1),
	machine_type(0),
	internal_datapath_width(1),
	number_hardware_threads(1),
	fetch_width(1),
	number_instruction_fetch_ports(1),
	decode_width(1),
	issue_width(1),
	peak_issue_width(1),
	commit_width(1),
	pipelines_per_core(),
	pipeline_depth(),
	FPU("default"),
	divider_multiplier("default"),
	ALU_per_core(1),
	FPU_per_core(1.0),
	MUL_per_core(1),
	instruction_buffer_size(1),
	decoded_stream_buffer_size(1),
	instruction_window_scheme(0),
	instruction_window_size(1),
	ROB_size(1),
	archi_Regs_IRF_size(1),
	archi_Regs_FRF_size(1),
	phy_Regs_IRF_size(1),
	phy_Regs_FRF_size(1),
	rename_scheme(0),
	checkpoint_depth(1),
	register_windows_size(1),
	LSU_order("default"),
	store_buffer_size(1),
	load_buffer_size(1),
	memory_ports(1),
	Dcache_dual_pump("default"),
	RAS_size(1),
	//all stats at the level of system.core(0-n)
	total_instructions(1),
	int_instructions(1),
	fp_instructions(1),
	branch_instructions(1),
	branch_mispredictions(1),
	committed_instructions(1),
	load_instructions(1),
	store_instructions(1),
	total_cycles(1),
	idle_cycles(1),
	busy_cycles(1),
	instruction_buffer_reads(1),
	instruction_buffer_write(1),
	ROB_reads(1),
	ROB_writes(1),
	rename_accesses(1),
	inst_window_reads(1),
	inst_window_writes(1),
	inst_window_wakeup_accesses(1),
	inst_window_selections(1),
	archi_int_regfile_reads(1),
	archi_float_regfile_reads(1),
	phy_int_regfile_reads(1),
	phy_float_regfile_reads(1),
	windowed_reg_accesses(1),
	windowed_reg_transports(1),
	function_calls(1),
	ialu_accesses(1),
	fpu_accesses(1),
	mul_accesses(1),
	cdb_alu_accesses(1),
	cdb_mul_accesses(1),
	cdb_fpu_accesses(1),
	load_buffer_reads(1),
	load_buffer_writes(1),
	load_buffer_cams(1),
	store_buffer_reads(1),
	store_buffer_writes(1),
	store_buffer_cams(1),
	store_buffer_forwards(1),
	main_memory_access(1),
	main_memory_read(1),
	main_memory_write(1),
	pipeline_duty_cycle(1),
	IFU_duty_cycle(1),
	BR_duty_cycle(1),
	LSU_duty_cycle(1),
	MemManU_I_duty_cycle(1),
	MemManU_D_duty_cycle(1),
	ALU_duty_cycle(1),
	MUL_duty_cycle(1),
	FPU_duty_cycle(1),
	ALU_cdb_duty_cycle(1),
	MUL_cdb_duty_cycle(1),
	FPU_cdb_duty_cycle(1),
	vdd(0),
	power_gating_vcc(-1)
{};

SystemCacheDirectory::SystemCacheDirectory():
	Dir_config(),
	buffer_sizes(),
	clockrate(1),
	ports(), //TODO check if only 21st element needs to be 1?
	device_type(1),
	threeD_stack("default"),
	vdd(0),
	power_gating_vcc(-1),
	total_accesses(1),
	read_accesses(1),
	write_accesses(1),
	duty_cycle(1)
{};

SystemCache::SystemCache():
	cache_config(),
	clockrate(1),
	ports(),
	device_type(1),
	threeD_stack("default"),
	buffer_sizes(),
	vdd(0),
	power_gating_vcc(-1),
	total_accesses(1),
	read_accesses(1),
	write_accesses(1),
	total_hits(1),
	total_misses(1),
	read_hits(1),
	write_hits(1),
	read_misses(1),
	write_misses(1),
	replacements(1),
	write_backs(1),
	miss_buffer_accesses(1),
	fill_buffer_accesses(1),
	prefetch_buffer_accesses(1),
	prefetch_buffer_writes(1),
	prefetch_buffer_reads(1),
	prefetch_buffer_hits(1),
	wbb_writes(1),
	wbb_reads(1),
	duty_cycle(1),
	merged_dir(false),
	homenode_read_accesses(1),
	homenode_write_accesses(1),
	homenode_read_hits(1),
	homenode_write_hits(1),
	homenode_read_misses(1),
	homenode_write_misses(1),
	dir_duty_cycle(1)
{};

Xbar0SystemNoC::Xbar0SystemNoC():
	number_of_inputs_of_crossbars(1),
	number_of_outputs_of_crossbars(1),
	flit_bits(1),
	input_buffer_entries_per_port(1),
	ports_of_input_buffer(),
	crossbar_accesses(1)
{};

SystemNoC::SystemNoC():
	clockrate(1),
	type(true),
	has_global_link(true),
	topology("default"),
	horizontal_nodes(1),
	vertical_nodes(1),
	link_throughput(0),
	link_latency(0),
	input_ports(1),
	output_ports(1),
	virtual_channel_per_port(1),
	flit_bits(1),
	input_buffer_entries_per_vc(1),
	ports_of_input_buffer(),
	dual_pump(0),
	number_of_crossbars(1),
	crossbar_type("default"),
	crosspoint_type("default"),
	xbar0(),
	arbiter_type(0),
	chip_coverage(1),
	vdd(0),
	power_gating_vcc(-1),
	total_accesses(1),
	duty_cycle(1),
	route_over_perc(0.5)
{};

SystemMem::SystemMem():
	mem_tech_node(1),
	device_clock(1),
	peak_transfer_rate(1),
	internal_prefetch_of_DRAM_chip(1),
	capacity_per_channel(1),
	number_ranks(1),
	num_banks_of_DRAM_chip(1),
	block_width_of_DRAM_chip(1),
	output_width_of_DRAM_chip(1),
	page_size_of_DRAM_chip(1),
	burstlength_of_DRAM_chip(1),
	memory_accesses(1),
	memory_reads(1),
	memory_writes(1)
{};

SystemMemController::SystemMemController():
	peak_transfer_rate(1),
	number_mcs(1),
	withPHY(false),
	type(1),
	duty_cycle(1),
	total_load_perc(1),
	mc_clock(1),
	memory_channels_per_mc(1),
	number_ranks(1),
	req_window_size_per_channel(1),
	io_buffer_size_per_channel(1),
	databus_width(1),
	addressbus_width(1),
	lvds(true),
	vdd(0),
	power_gating_vcc(-1),
	memory_accesses(1),
	memory_reads(1),
	memory_writes(1)
{};

SystemNiu::SystemNiu():
	clockrate(1),
	number_units(1),
	type(1),
	vdd(0),
	power_gating_vcc(-1),
	duty_cycle(1),
	total_load_perc(1)
{};

SystemPcie::SystemPcie():
	clockrate(1),
	number_units(1),
	num_channels(1),
	type(1),
	withPHY(false),
	vdd(0),
	power_gating_vcc(-1),
	duty_cycle(1),
	total_load_perc(1)
{};

RootSystem::RootSystem():
	number_of_cores(1),
	number_of_L1Directories(1),
	number_of_L2Directories(1),
	number_of_L2s(1),
	Private_L2(false),
	number_of_L3s(1),
	number_of_NoCs(1),
	homogeneous_cores(1),
	homogeneous_L1Directories(1),
	homogeneous_L2Directories(1),
	core_tech_node(1),
	target_core_clockrate(1),
	target_chip_area(1),
	temperature(360),
	number_cache_levels(1),
	homogeneous_L2s(1),
	homogeneous_L3s(1),
	homogeneous_NoCs(1),
	homogeneous_ccs(1),

	Max_area_deviation(1),
	Max_power_deviation(1),
	device_type(1),
	longer_channel_device(true),
	power_gating(false),
	Embedded(false),
	opt_dynamic_power(false),
	opt_lakage_power(false),
	opt_clockrate(true),
	opt_area(false),
	interconnect_projection_type(1),
	vdd(0),
	power_gating_vcc(-1)
{};

template<typename T>
void ParseXML::split_string(const char* input_str, std::vector<T> &dst) {
    std::istringstream ss(input_str);
    std::string buffer;
    
    while (std::getline(ss, buffer, ',')) {
	buffer.erase(std::remove_if(buffer.begin(), buffer.end(), ::isspace), buffer.end());
        if constexpr (std::is_arithmetic_v<T>) {
            T value;
            auto [ptr, ec] = std::from_chars(buffer.data(), buffer.data() + buffer.size(), value);
            if (ec == std::errc()) {
                dst.push_back(value);
            } else {
                std::cerr << "Conversion failed for: " << buffer << std::endl;
            }
        } else {
            dst.push_back(buffer);  // If T is std::string, just append the value
        }
    }
}
