/*****************************************************************************
 *                                McPAT/CACTI
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



#ifndef __CACTI_INTERFACE_H__
#define __CACTI_INTERFACE_H__

#include <map>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "const.h"

using namespace std;


class min_values_t;
class mem_array;
class uca_org_t;


class powerComponents
{
  public:
    double dynamic;
    double leakage;
    double gate_leakage;
    double short_circuit;
    double longer_channel_leakage;
    double power_gated_leakage;
    double power_gated_with_long_channel_leakage;

    powerComponents() : dynamic(0), leakage(0), gate_leakage(0), short_circuit(0),
    		longer_channel_leakage(0), power_gated_leakage(0),
    		power_gated_with_long_channel_leakage (0) { }
    powerComponents(const powerComponents & obj) { *this = obj; }
    powerComponents & operator=(const powerComponents & rhs)
    {
      dynamic = rhs.dynamic;
      leakage = rhs.leakage;
      gate_leakage  = rhs.gate_leakage;
      short_circuit = rhs.short_circuit;
      longer_channel_leakage = rhs.longer_channel_leakage;
      power_gated_leakage = rhs.power_gated_leakage;
      power_gated_with_long_channel_leakage = rhs.power_gated_with_long_channel_leakage;
      return *this;
    }
    void reset() { dynamic = 0; leakage = 0; gate_leakage = 0; short_circuit = 0;
    longer_channel_leakage = 0; power_gated_leakage = 0;power_gated_with_long_channel_leakage=0;}

    friend powerComponents operator+(const powerComponents & x, const powerComponents & y);
    friend powerComponents operator*(const powerComponents & x, double const * const y);
};



class powerDef
{
  public:
    powerComponents readOp;
    powerComponents writeOp;
    powerComponents searchOp;//Sheng: for CAM and FA

    powerDef() : readOp(), writeOp(), searchOp() { }
    void reset() { readOp.reset(); writeOp.reset(); searchOp.reset();}

    friend powerDef operator+(const powerDef & x, const powerDef & y);
    friend powerDef operator*(const powerDef & x, double const * const y);
};

enum Wire_type
{
    Global /* gloabl wires with repeaters */,
    Global_5 /* 5% delay penalty */,
    Global_10 /* 10% delay penalty */,
    Global_20 /* 20% delay penalty */,
    Global_30 /* 30% delay penalty */,
    Low_swing /* differential low power wires with high area overhead */,
    Semi_global /* mid-level wires with repeaters*/,
    Transmission /* tranmission lines with high area overhead */,
    Optical /* optical wires */,
    Invalid_wtype
};



class __attribute__((packed)) InputParameter
{
  public:

    InputParameter();
    void parse_cfg(const string & infile);

    bool error_checking();  // return false if the input parameters are problematic
    void display_ip();

    unsigned int cache_sz			= 0;  // in bytes
    unsigned int line_sz			= 0;
    unsigned int assoc				= 0;
    unsigned int nbanks				= 0;
    unsigned int out_w				= 0;// == nr_bits_out
    bool     specific_tag			= 0;
    unsigned int tag_w				= 0;
    unsigned int access_mode			= 0;
    unsigned int obj_func_dyn_energy		= 0;
    unsigned int obj_func_dyn_power		= 0;
    unsigned int obj_func_leak_power		= 0;
    unsigned int obj_func_cycle_t		= 0;

    double   F_sz_nm				= 0;          // feature size in nm
    double   F_sz_um				= 0;          // feature size in um
    bool     specific_hp_vdd			= 0;     // whether to have user defined vdd that is different from ITRS
    double   hp_Vdd				= 0;			   // user specified vdd
    bool     specific_lstp_vdd			= 0;     // whether to have user defined vdd that is different from ITRS
    double   lstp_Vdd				= 0;
    bool     specific_lop_vdd			= 0;     // whether to have user defined vdd that is different from ITRS
    double   lop_Vdd				= 0;
    bool     specific_vcc_min			= 0;     // whether to have user defined vcc_min for power-gating that is different from the value constrained by technology for maintaining states
    double   user_defined_vcc_min		= 0;
    bool     user_defined_vcc_underflow		= 0; //flag to indicate when user defined vcc is too low for the circuit to retain state
    unsigned int num_rw_ports			= 0;
    unsigned int num_rd_ports			= 0;
    unsigned int num_wr_ports			= 0;
    unsigned int num_se_rd_ports		= 0;  // number of single ended read ports
    unsigned int num_search_ports		= 0;  // number of search ports for CAM
    bool     is_main_mem			= 0;
    bool     is_cache				= 0;
    bool     pure_ram				= 0;
    bool     pure_cam				= 0;
    bool     rpters_in_htree			= 0;  // if there are repeaters in htree segment
    unsigned int ver_htree_wires_over_array	= 0;
    unsigned int broadcast_addr_din_over_ver_htrees= 0;
    unsigned int temp				= 0;

    unsigned int ram_cell_tech_type		= 0;
    unsigned int peri_global_tech_type		= 0;
    unsigned int data_arr_ram_cell_tech_type	= 0;
    unsigned int data_arr_peri_global_tech_type	= 0;
    unsigned int tag_arr_ram_cell_tech_type	= 0;
    unsigned int tag_arr_peri_global_tech_type	= 0;

    unsigned int burst_len			= 0;
    unsigned int int_prefetch_w			= 0;
    unsigned int page_sz_bits			= 0;

    unsigned int ic_proj_type			= 0;      // interconnect_projection_type
    unsigned int wire_is_mat_type		= 0;  // wire_inside_mat_type
    unsigned int wire_os_mat_type		= 0; // wire_outside_mat_type
    enum Wire_type wt				= (Wire_type)0;
    int force_wiretype				= 0;
    bool print_input_args			= 0;
    unsigned int nuca_cache_sz			= 0; // TODO
    int ndbl = 0, ndwl = 0, nspd = 0, ndsam1 = 0, ndsam2 = 0, ndcm = 0;
    bool force_cache_config			= 0;

    int cache_level				= 0;
    int cores					= 0;
    int nuca_bank_count				= 0;
    int force_nuca_bank				= 0;

    int delay_wt = 0, dynamic_power_wt = 0, leakage_power_wt = 0,
        cycle_time_wt = 0, area_wt = 0;
    int delay_wt_nuca = 0, dynamic_power_wt_nuca = 0, leakage_power_wt_nuca = 0,
        cycle_time_wt_nuca = 0, area_wt_nuca = 0;

    int delay_dev = 0, dynamic_power_dev = 0, leakage_power_dev = 0,
        cycle_time_dev = 0, area_dev = 0;
    int delay_dev_nuca = 0, dynamic_power_dev_nuca = 0, leakage_power_dev_nuca = 0,
        cycle_time_dev_nuca = 0, area_dev_nuca = 0;
    int ed					= 0; //ED or ED2 optimization
    int nuca					= 0;

    bool     fast_access			= 0;
    unsigned int block_sz			= 0;  // bytes
    unsigned int tag_assoc			= 0;
    unsigned int data_assoc			= 0;
    bool     is_seq_acc				= 0;
    bool     fully_assoc			= 0;
    unsigned int nsets				= 0;  // == number_of_sets
    int print_detail				= 0;


    bool     add_ecc_b_				= 0;
  //parameters for design constraint
  double throughput				= 0;
  double latency				= 0;
  bool pipelinable				= 0;
  int pipeline_stages				= 0;
  int per_stage_vector				= 0;
  bool with_clock_grid				= 0;

  bool array_power_gated			= 0;
  bool bitline_floating				= 0;
  bool wl_power_gated				= 0;
  bool cl_power_gated				= 0;
  bool interconect_power_gated			= 0;
  bool power_gating				= 0;

  double perfloss				= 0;

  bool cl_vertical				= 0;

  std::vector<double> dvs_voltage;

  bool long_channel_device			= 0;
};


typedef struct{
  int Ndwl;
  int Ndbl;
  double Nspd;
  int deg_bl_muxing;
  int Ndsam_lev_1;
  int Ndsam_lev_2;
  int number_activated_mats_horizontal_direction;
  int number_subbanks;
  int page_size_in_bits;
  double delay_route_to_bank;
  double delay_crossbar;
  double delay_addr_din_horizontal_htree;
  double delay_addr_din_vertical_htree;
  double delay_row_predecode_driver_and_block;
  double delay_row_decoder;
  double delay_bitlines;
  double delay_sense_amp;
  double delay_subarray_output_driver;
  double delay_bit_mux_predecode_driver_and_block;
  double delay_bit_mux_decoder;
  double delay_senseamp_mux_lev_1_predecode_driver_and_block;
  double delay_senseamp_mux_lev_1_decoder;
  double delay_senseamp_mux_lev_2_predecode_driver_and_block;
  double delay_senseamp_mux_lev_2_decoder;
  double delay_input_htree;
  double delay_output_htree;
  double delay_dout_vertical_htree;
  double delay_dout_horizontal_htree;
  double delay_comparator;
  double access_time;
  double cycle_time;
  double multisubbank_interleave_cycle_time;
  double delay_request_network;
  double delay_inside_mat;
  double delay_reply_network;
  double trcd;
  double cas_latency;
  double precharge_delay;
  powerDef power_routing_to_bank;
  powerDef power_addr_input_htree;
  powerDef power_data_input_htree;
  powerDef power_data_output_htree;
  powerDef power_addr_horizontal_htree;
  powerDef power_datain_horizontal_htree;
  powerDef power_dataout_horizontal_htree;
  powerDef power_addr_vertical_htree;
  powerDef power_datain_vertical_htree;
  powerDef power_row_predecoder_drivers;
  powerDef power_row_predecoder_blocks;
  powerDef power_row_decoders;
  powerDef power_bit_mux_predecoder_drivers;
  powerDef power_bit_mux_predecoder_blocks;
  powerDef power_bit_mux_decoders;
  powerDef power_senseamp_mux_lev_1_predecoder_drivers;
  powerDef power_senseamp_mux_lev_1_predecoder_blocks;
  powerDef power_senseamp_mux_lev_1_decoders;
  powerDef power_senseamp_mux_lev_2_predecoder_drivers;
  powerDef power_senseamp_mux_lev_2_predecoder_blocks;
  powerDef power_senseamp_mux_lev_2_decoders;
  powerDef power_bitlines;
  powerDef power_sense_amps;
  powerDef power_prechg_eq_drivers;
  powerDef power_output_drivers_at_subarray;
  powerDef power_dataout_vertical_htree;
  powerDef power_comparators;
  powerDef power_crossbar;
  powerDef total_power;
  double area;
  double all_banks_height;
  double all_banks_width;
  double bank_height;
  double bank_width;
  double subarray_memory_cell_area_height;
  double subarray_memory_cell_area_width;
  double mat_height;
  double mat_width;
  double routing_area_height_within_bank;
  double routing_area_width_within_bank;
  double area_efficiency;
//  double perc_power_dyn_routing_to_bank;
//  double perc_power_dyn_addr_horizontal_htree;
//  double perc_power_dyn_datain_horizontal_htree;
//  double perc_power_dyn_dataout_horizontal_htree;
//  double perc_power_dyn_addr_vertical_htree;
//  double perc_power_dyn_datain_vertical_htree;
//  double perc_power_dyn_row_predecoder_drivers;
//  double perc_power_dyn_row_predecoder_blocks;
//  double perc_power_dyn_row_decoders;
//  double perc_power_dyn_bit_mux_predecoder_drivers;
//  double perc_power_dyn_bit_mux_predecoder_blocks;
//  double perc_power_dyn_bit_mux_decoders;
//  double perc_power_dyn_senseamp_mux_lev_1_predecoder_drivers;
//  double perc_power_dyn_senseamp_mux_lev_1_predecoder_blocks;
//  double perc_power_dyn_senseamp_mux_lev_1_decoders;
//  double perc_power_dyn_senseamp_mux_lev_2_predecoder_drivers;
//  double perc_power_dyn_senseamp_mux_lev_2_predecoder_blocks;
//  double perc_power_dyn_senseamp_mux_lev_2_decoders;
//  double perc_power_dyn_bitlines;
//  double perc_power_dyn_sense_amps;
//  double perc_power_dyn_prechg_eq_drivers;
//  double perc_power_dyn_subarray_output_drivers;
//  double perc_power_dyn_dataout_vertical_htree;
//  double perc_power_dyn_comparators;
//  double perc_power_dyn_crossbar;
//  double perc_power_dyn_spent_outside_mats;
//  double perc_power_leak_routing_to_bank;
//  double perc_power_leak_addr_horizontal_htree;
//  double perc_power_leak_datain_horizontal_htree;
//  double perc_power_leak_dataout_horizontal_htree;
//  double perc_power_leak_addr_vertical_htree;
//  double perc_power_leak_datain_vertical_htree;
//  double perc_power_leak_row_predecoder_drivers;
//  double perc_power_leak_row_predecoder_blocks;
//  double perc_power_leak_row_decoders;
//  double perc_power_leak_bit_mux_predecoder_drivers;
//  double perc_power_leak_bit_mux_predecoder_blocks;
//  double perc_power_leak_bit_mux_decoders;
//  double perc_power_leak_senseamp_mux_lev_1_predecoder_drivers;
//  double perc_power_leak_senseamp_mux_lev_1_predecoder_blocks;
//  double perc_power_leak_senseamp_mux_lev_1_decoders;
//  double perc_power_leak_senseamp_mux_lev_2_predecoder_drivers;
//  double perc_power_leak_senseamp_mux_lev_2_predecoder_blocks;
//  double perc_power_leak_senseamp_mux_lev_2_decoders;
//  double perc_power_leak_bitlines;
//  double perc_power_leak_sense_amps;
//  double perc_power_leak_prechg_eq_drivers;
//  double perc_power_leak_subarray_output_drivers;
//  double perc_power_leak_dataout_vertical_htree;
//  double perc_power_leak_comparators;
//  double perc_power_leak_crossbar;
//  double perc_leak_mats;
//  double perc_active_mats;
  double refresh_power;
  double dram_refresh_period;
  double dram_array_availability;
  double dyn_read_energy_from_closed_page;
  double dyn_read_energy_from_open_page;
  double leak_power_subbank_closed_page;
  double leak_power_subbank_open_page;
  double leak_power_request_and_reply_networks;
  double activate_energy;
  double read_energy;
  double write_energy;
  double precharge_energy;
} results_mem_array;


class uca_org_t
{
  public:
    mem_array * tag_array2;
    mem_array * data_array2;
    double access_time;
    double cycle_time;
    double area;
    double area_efficiency;
    powerDef power;
    double leak_power_with_sleep_transistors_in_mats;
    double cache_ht;
    double cache_len;
    char file_n[100];
    double vdd_periph_global;
    bool valid;
    results_mem_array tag_array;
    results_mem_array data_array;
    std::vector<uca_org_t * > uca_q;//for results share the same settings (g_ip and dyn_p) but with different tech settings such as DVFS
    uca_org_t * uca_pg_reference;//for references results when power gating is enabled.
    uca_org_t();
    void find_delay();
    void find_energy();
    void find_area();
    void find_cyc();
    void adjust_area();//for McPAT only to adjust routing overhead
    void cleanup();
    ~uca_org_t();
};

void reconfigure(InputParameter *local_interface, uca_org_t *fin_res);

uca_org_t cacti_interface(const string & infile_name);
//McPAT's plain interface, please keep !!!
uca_org_t cacti_interface(InputParameter * const local_interface);
//McPAT's plain interface, please keep !!!
uca_org_t init_interface(InputParameter * const local_interface);
//McPAT's plain interface, please keep !!!
uca_org_t cacti_interface(
	    int cache_size,
	    int line_size,
	    int associativity,
	    int rw_ports,
	    int excl_read_ports,
	    int excl_write_ports,
	    int single_ended_read_ports,
	    int search_ports,
	    int banks,
	    double tech_node,
	    int output_width,
	    int specific_tag,
	    int tag_width,
	    int access_mode,
	    int cache,
	    int main_mem,
	    int obj_func_delay,
	    int obj_func_dynamic_power,
	    int obj_func_leakage_power,
	    int obj_func_cycle_time,
	    int obj_func_area,
	    int dev_func_delay,
	    int dev_func_dynamic_power,
	    int dev_func_leakage_power,
	    int dev_func_area,
	    int dev_func_cycle_time,
	    int ed_ed2_none, // 0 - ED, 1 - ED^2, 2 - use weight and deviate
	    int temp,
	    int wt, //0 - default(search across everything), 1 - global, 2 - 5% delay penalty, 3 - 10%, 4 - 20 %, 5 - 30%, 6 - low-swing
	    int data_arr_ram_cell_tech_flavor_in,
	    int data_arr_peri_global_tech_flavor_in,
	    int tag_arr_ram_cell_tech_flavor_in,
	    int tag_arr_peri_global_tech_flavor_in,
	    int interconnect_projection_type_in,
	    int wire_inside_mat_type_in,
	    int wire_outside_mat_type_in,
	    int REPEATERS_IN_HTREE_SEGMENTS_in,
	    int VERTICAL_HTREE_WIRES_OVER_THE_ARRAY_in,
	    int BROADCAST_ADDR_DATAIN_OVER_VERTICAL_HTREES_in,
	    int PAGE_SIZE_BITS_in,
	    int BURST_LENGTH_in,
	    int INTERNAL_PREFETCH_WIDTH_in,
	    int force_wiretype,
	    int wiretype,
	    int force_config,
	    int ndwl,
	    int ndbl,
	    int nspd,
	    int ndcm,
	    int ndsam1,
	    int ndsam2,
	    int ecc);
//    int cache_size,
//    int line_size,
//    int associativity,
//    int rw_ports,
//    int excl_read_ports,
//    int excl_write_ports,
//    int single_ended_read_ports,
//    int banks,
//    double tech_node,
//    int output_width,
//    int specific_tag,
//    int tag_width,
//    int access_mode,
//    int cache,
//    int main_mem,
//    int obj_func_delay,
//    int obj_func_dynamic_power,
//    int obj_func_leakage_power,
//    int obj_func_area,
//    int obj_func_cycle_time,
//    int dev_func_delay,
//    int dev_func_dynamic_power,
//    int dev_func_leakage_power,
//    int dev_func_area,
//    int dev_func_cycle_time,
//    int temp,
//    int data_arr_ram_cell_tech_flavor_in,
//    int data_arr_peri_global_tech_flavor_in,
//    int tag_arr_ram_cell_tech_flavor_in,
//    int tag_arr_peri_global_tech_flavor_in,
//    int interconnect_projection_type_in,
//    int wire_inside_mat_type_in,
//    int wire_outside_mat_type_in,
//    int REPEATERS_IN_HTREE_SEGMENTS_in,
//    int VERTICAL_HTREE_WIRES_OVER_THE_ARRAY_in,
//    int BROADCAST_ADDR_DATAIN_OVER_VERTICAL_HTREES_in,
////    double MAXAREACONSTRAINT_PERC_in,
////    double MAXACCTIMECONSTRAINT_PERC_in,
////    double MAX_PERC_DIFF_IN_DELAY_FROM_BEST_DELAY_REPEATER_SOLUTION_in,
//    int PAGE_SIZE_BITS_in,
//    int BURST_LENGTH_in,
//    int INTERNAL_PREFETCH_WIDTH_in);

//Naveen's interface
uca_org_t cacti_interface(
    int cache_size,
    int line_size,
    int associativity,
    int rw_ports,
    int excl_read_ports,
    int excl_write_ports,
    int single_ended_read_ports,
    int banks,
    double tech_node,
    int page_sz,
    int burst_length,
    int pre_width,
    int output_width,
    int specific_tag,
    int tag_width,
    int access_mode, //0 normal, 1 seq, 2 fast
    int cache, //scratch ram or cache
    int main_mem,
    int obj_func_delay,
    int obj_func_dynamic_power,
    int obj_func_leakage_power,
    int obj_func_area,
    int obj_func_cycle_time,
    int dev_func_delay,
    int dev_func_dynamic_power,
    int dev_func_leakage_power,
    int dev_func_area,
    int dev_func_cycle_time,
    int ed_ed2_none, // 0 - ED, 1 - ED^2, 2 - use weight and deviate
    int temp,
    int wt, //0 - default(search across everything), 1 - global, 2 - 5% delay penalty, 3 - 10%, 4 - 20 %, 5 - 30%, 6 - low-swing
    int data_arr_ram_cell_tech_flavor_in,
    int data_arr_peri_global_tech_flavor_in,
    int tag_arr_ram_cell_tech_flavor_in,
    int tag_arr_peri_global_tech_flavor_in,
    int interconnect_projection_type_in, // 0 - aggressive, 1 - normal
    int wire_inside_mat_type_in,
    int wire_outside_mat_type_in,
    int is_nuca, // 0 - UCA, 1 - NUCA
    int core_count,
    int cache_level, // 0 - L2, 1 - L3
    int nuca_bank_count,
    int nuca_obj_func_delay,
    int nuca_obj_func_dynamic_power,
    int nuca_obj_func_leakage_power,
    int nuca_obj_func_area,
    int nuca_obj_func_cycle_time,
    int nuca_dev_func_delay,
    int nuca_dev_func_dynamic_power,
    int nuca_dev_func_leakage_power,
    int nuca_dev_func_area,
    int nuca_dev_func_cycle_time,
    int REPEATERS_IN_HTREE_SEGMENTS_in,//TODO for now only wires with repeaters are supported
    int p_input);

class mem_array
{
  public:
  int    Ndcm;
  int    Ndwl;
  int    Ndbl;
  double Nspd;
  int    deg_bl_muxing;
  int    Ndsam_lev_1;
  int    Ndsam_lev_2;
  double access_time;
  double cycle_time;
  double multisubbank_interleave_cycle_time;
  double area_ram_cells;
  double area;
  powerDef power;
  double delay_senseamp_mux_decoder;
  double delay_before_subarray_output_driver;
  double delay_from_subarray_output_driver_to_output;
  double height;
  double width;

  double mat_height;
  double mat_length;
  double subarray_length;
  double subarray_height;

  double delay_route_to_bank,
         delay_input_htree,
         delay_row_predecode_driver_and_block,
         delay_row_decoder,
         delay_bitlines,
         delay_sense_amp,
         delay_subarray_output_driver,
         delay_dout_htree,
         delay_comparator,
         delay_matchlines;

  double all_banks_height,
         all_banks_width,
         area_efficiency;

  powerDef power_routing_to_bank;
  powerDef power_addr_input_htree;
  powerDef power_data_input_htree;
  powerDef power_data_output_htree;
  powerDef power_htree_in_search;
  powerDef power_htree_out_search;
  powerDef power_row_predecoder_drivers;
  powerDef power_row_predecoder_blocks;
  powerDef power_row_decoders;
  powerDef power_bit_mux_predecoder_drivers;
  powerDef power_bit_mux_predecoder_blocks;
  powerDef power_bit_mux_decoders;
  powerDef power_senseamp_mux_lev_1_predecoder_drivers;
  powerDef power_senseamp_mux_lev_1_predecoder_blocks;
  powerDef power_senseamp_mux_lev_1_decoders;
  powerDef power_senseamp_mux_lev_2_predecoder_drivers;
  powerDef power_senseamp_mux_lev_2_predecoder_blocks;
  powerDef power_senseamp_mux_lev_2_decoders;
  powerDef power_bitlines;
  powerDef power_sense_amps;
  powerDef power_prechg_eq_drivers;
  powerDef power_output_drivers_at_subarray;
  powerDef power_dataout_vertical_htree;
  powerDef power_comparators;

  powerDef power_cam_bitline_precharge_eq_drv;
  powerDef power_searchline;
  powerDef power_searchline_precharge;
  powerDef power_matchlines;
  powerDef power_matchline_precharge;
  powerDef power_matchline_to_wordline_drv;

  min_values_t *arr_min;
  enum Wire_type wt;

  // dram stats
  double activate_energy, read_energy, write_energy, precharge_energy,
  refresh_power, leak_power_subbank_closed_page, leak_power_subbank_open_page,
  leak_power_request_and_reply_networks;

  double precharge_delay;

  //Power-gating stats
  double  array_leakage;
  double  wl_leakage;
  double  cl_leakage;

  double sram_sleep_tx_width, wl_sleep_tx_width, cl_sleep_tx_width;
  double sram_sleep_tx_area, wl_sleep_tx_area, cl_sleep_tx_area;
  double sram_sleep_wakeup_latency, wl_sleep_wakeup_latency, cl_sleep_wakeup_latency, bl_floating_wakeup_latency;
  double sram_sleep_wakeup_energy, wl_sleep_wakeup_energy, cl_sleep_wakeup_energy, bl_floating_wakeup_energy;

  int num_active_mats;
  int num_submarray_mats;

  double long_channel_leakage_reduction_periperal;
  double long_channel_leakage_reduction_memcell;

  static bool lt(const mem_array * m1, const mem_array * m2);
};


#endif
