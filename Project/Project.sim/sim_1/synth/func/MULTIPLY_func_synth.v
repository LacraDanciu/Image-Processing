// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2016.4 (win64) Build 1756540 Mon Jan 23 19:11:23 MST 2017
// Date        : Tue May 09 15:27:04 2017
// Host        : Lacramioara running 64-bit major release  (build 9200)
// Command     : write_verilog -mode funcsim -nolib -force -file
//               E:/Vivado/Projects/Project/Project.sim/sim_1/synth/func/MULTIPLY_func_synth.v
// Design      : DIVISION
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a35tcpg236-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module CONTROLDIVI
   (loadb,
    term_OBUF,
    subb,
    \q_reg[7] ,
    \q_reg[7]_0 ,
    E,
    \temp_reg[8] ,
    D,
    \temp_reg[7] ,
    \q_reg[0] ,
    \q_reg[0]_0 ,
    clk_IBUF_BUFG,
    reset_IBUF,
    a_perm__0,
    Q,
    A_IBUF,
    \temp_reg[8]_0 ,
    \q_reg[1] ,
    s,
    a_perm,
    \temp_reg[7]_0 ,
    start_IBUF);
  output loadb;
  output term_OBUF;
  output subb;
  output \q_reg[7] ;
  output \q_reg[7]_0 ;
  output [0:0]E;
  output [0:0]\temp_reg[8] ;
  output [8:0]D;
  output [7:0]\temp_reg[7] ;
  output \q_reg[0] ;
  output \q_reg[0]_0 ;
  input clk_IBUF_BUFG;
  input reset_IBUF;
  input [3:0]a_perm__0;
  input [7:0]Q;
  input [11:0]A_IBUF;
  input [8:0]\temp_reg[8]_0 ;
  input [1:0]\q_reg[1] ;
  input [2:0]s;
  input [0:0]a_perm;
  input \temp_reg[7]_0 ;
  input start_IBUF;

  wire \/i__n_0 ;
  wire [11:0]A_IBUF;
  wire [8:0]D;
  wire [0:0]E;
  wire \FSM_sequential_stateVal[0]_i_1_n_0 ;
  wire \FSM_sequential_stateVal[1]_i_1_n_0 ;
  wire \FSM_sequential_stateVal[2]_i_1_n_0 ;
  wire [7:0]Q;
  wire [0:0]a_perm;
  wire [3:0]a_perm__0;
  wire [30:0]c;
  wire c0_carry__0_i_1_n_0;
  wire c0_carry__0_i_2_n_0;
  wire c0_carry__0_i_3_n_0;
  wire c0_carry__0_i_4_n_0;
  wire c0_carry__0_n_0;
  wire c0_carry__0_n_1;
  wire c0_carry__0_n_2;
  wire c0_carry__0_n_3;
  wire c0_carry__0_n_4;
  wire c0_carry__0_n_5;
  wire c0_carry__0_n_6;
  wire c0_carry__0_n_7;
  wire c0_carry__1_i_1_n_0;
  wire c0_carry__1_i_2_n_0;
  wire c0_carry__1_i_3_n_0;
  wire c0_carry__1_i_4_n_0;
  wire c0_carry__1_n_0;
  wire c0_carry__1_n_1;
  wire c0_carry__1_n_2;
  wire c0_carry__1_n_3;
  wire c0_carry__1_n_4;
  wire c0_carry__1_n_5;
  wire c0_carry__1_n_6;
  wire c0_carry__1_n_7;
  wire c0_carry__2_i_1_n_0;
  wire c0_carry__2_i_2_n_0;
  wire c0_carry__2_i_3_n_0;
  wire c0_carry__2_i_4_n_0;
  wire c0_carry__2_n_0;
  wire c0_carry__2_n_1;
  wire c0_carry__2_n_2;
  wire c0_carry__2_n_3;
  wire c0_carry__2_n_4;
  wire c0_carry__2_n_5;
  wire c0_carry__2_n_6;
  wire c0_carry__2_n_7;
  wire c0_carry__3_i_1_n_0;
  wire c0_carry__3_i_2_n_0;
  wire c0_carry__3_i_3_n_0;
  wire c0_carry__3_i_4_n_0;
  wire c0_carry__3_n_0;
  wire c0_carry__3_n_1;
  wire c0_carry__3_n_2;
  wire c0_carry__3_n_3;
  wire c0_carry__3_n_4;
  wire c0_carry__3_n_5;
  wire c0_carry__3_n_6;
  wire c0_carry__3_n_7;
  wire c0_carry__4_i_1_n_0;
  wire c0_carry__4_i_2_n_0;
  wire c0_carry__4_i_3_n_0;
  wire c0_carry__4_i_4_n_0;
  wire c0_carry__4_n_0;
  wire c0_carry__4_n_1;
  wire c0_carry__4_n_2;
  wire c0_carry__4_n_3;
  wire c0_carry__4_n_4;
  wire c0_carry__4_n_5;
  wire c0_carry__4_n_6;
  wire c0_carry__4_n_7;
  wire c0_carry__5_i_1_n_0;
  wire c0_carry__5_i_2_n_0;
  wire c0_carry__5_i_3_n_0;
  wire c0_carry__5_i_4_n_0;
  wire c0_carry__5_n_0;
  wire c0_carry__5_n_1;
  wire c0_carry__5_n_2;
  wire c0_carry__5_n_3;
  wire c0_carry__5_n_4;
  wire c0_carry__5_n_5;
  wire c0_carry__5_n_6;
  wire c0_carry__5_n_7;
  wire c0_carry__6_i_1_n_0;
  wire c0_carry__6_i_2_n_0;
  wire c0_carry__6_n_3;
  wire c0_carry__6_n_6;
  wire c0_carry__6_n_7;
  wire c0_carry_i_1_n_0;
  wire c0_carry_i_2_n_0;
  wire c0_carry_i_3_n_0;
  wire c0_carry_i_4_n_0;
  wire c0_carry_n_0;
  wire c0_carry_n_1;
  wire c0_carry_n_2;
  wire c0_carry_n_3;
  wire c0_carry_n_4;
  wire c0_carry_n_5;
  wire c0_carry_n_6;
  wire c0_carry_n_7;
  wire \c[0]_i_1_n_0 ;
  wire \c[30]_i_1_n_0 ;
  wire \c[30]_i_2_n_0 ;
  wire \c[3]_i_1_n_0 ;
  wire clk_IBUF_BUFG;
  wire i__i_2_n_0;
  wire i__i_4_n_0;
  wire i__i_5_n_0;
  wire i__i_6_n_0;
  wire i__i_7_n_0;
  wire i__i_8_n_0;
  wire loada__0;
  wire loada_n_0;
  wire loadb;
  wire loadb_i_1_n_0;
  wire loadq;
  wire loadq_i_1_n_0;
  wire \q_reg[0] ;
  wire \q_reg[0]_0 ;
  wire [1:0]\q_reg[1] ;
  wire \q_reg[7] ;
  wire \q_reg[7]_0 ;
  wire reset_IBUF;
  wire [2:0]s;
  wire shlaq__0;
  wire shlaq_n_0;
  wire start_IBUF;
  (* RTL_KEEP = "yes" *) wire [2:0]stateVal;
  wire subb;
  wire subb__0_n_0;
  wire \temp[1]_i_2_n_0 ;
  wire [7:0]\temp_reg[7] ;
  wire \temp_reg[7]_0 ;
  wire [0:0]\temp_reg[8] ;
  wire [8:0]\temp_reg[8]_0 ;
  wire term_OBUF;
  wire term_n_0;
  wire [3:1]NLW_c0_carry__6_CO_UNCONNECTED;
  wire [3:2]NLW_c0_carry__6_O_UNCONNECTED;

  LUT6 #(
    .INIT(64'h00FFFFFFE400E400)) 
    \/i_ 
       (.I0(loadb),
        .I1(s[2]),
        .I2(A_IBUF[11]),
        .I3(stateVal[2]),
        .I4(i__i_2_n_0),
        .I5(stateVal[1]),
        .O(\/i__n_0 ));
  LUT5 #(
    .INIT(32'h000000F4)) 
    \FSM_sequential_stateVal[0]_i_1 
       (.I0(stateVal[2]),
        .I1(start_IBUF),
        .I2(\/i__n_0 ),
        .I3(stateVal[0]),
        .I4(reset_IBUF),
        .O(\FSM_sequential_stateVal[0]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00000FF2)) 
    \FSM_sequential_stateVal[1]_i_1 
       (.I0(stateVal[2]),
        .I1(a_perm),
        .I2(stateVal[0]),
        .I3(stateVal[1]),
        .I4(reset_IBUF),
        .O(\FSM_sequential_stateVal[1]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00005878)) 
    \FSM_sequential_stateVal[2]_i_1 
       (.I0(stateVal[1]),
        .I1(stateVal[0]),
        .I2(stateVal[2]),
        .I3(i__i_2_n_0),
        .I4(reset_IBUF),
        .O(\FSM_sequential_stateVal[2]_i_1_n_0 ));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_sequential_stateVal_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(\FSM_sequential_stateVal[0]_i_1_n_0 ),
        .Q(stateVal[0]),
        .R(1'b0));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_sequential_stateVal_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(\FSM_sequential_stateVal[1]_i_1_n_0 ),
        .Q(stateVal[1]),
        .R(1'b0));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_sequential_stateVal_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(\FSM_sequential_stateVal[2]_i_1_n_0 ),
        .Q(stateVal[2]),
        .R(1'b0));
  CARRY4 c0_carry
       (.CI(1'b0),
        .CO({c0_carry_n_0,c0_carry_n_1,c0_carry_n_2,c0_carry_n_3}),
        .CYINIT(c[0]),
        .DI(c[4:1]),
        .O({c0_carry_n_4,c0_carry_n_5,c0_carry_n_6,c0_carry_n_7}),
        .S({c0_carry_i_1_n_0,c0_carry_i_2_n_0,c0_carry_i_3_n_0,c0_carry_i_4_n_0}));
  CARRY4 c0_carry__0
       (.CI(c0_carry_n_0),
        .CO({c0_carry__0_n_0,c0_carry__0_n_1,c0_carry__0_n_2,c0_carry__0_n_3}),
        .CYINIT(1'b0),
        .DI(c[8:5]),
        .O({c0_carry__0_n_4,c0_carry__0_n_5,c0_carry__0_n_6,c0_carry__0_n_7}),
        .S({c0_carry__0_i_1_n_0,c0_carry__0_i_2_n_0,c0_carry__0_i_3_n_0,c0_carry__0_i_4_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__0_i_1
       (.I0(c[8]),
        .O(c0_carry__0_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__0_i_2
       (.I0(c[7]),
        .O(c0_carry__0_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__0_i_3
       (.I0(c[6]),
        .O(c0_carry__0_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__0_i_4
       (.I0(c[5]),
        .O(c0_carry__0_i_4_n_0));
  CARRY4 c0_carry__1
       (.CI(c0_carry__0_n_0),
        .CO({c0_carry__1_n_0,c0_carry__1_n_1,c0_carry__1_n_2,c0_carry__1_n_3}),
        .CYINIT(1'b0),
        .DI(c[12:9]),
        .O({c0_carry__1_n_4,c0_carry__1_n_5,c0_carry__1_n_6,c0_carry__1_n_7}),
        .S({c0_carry__1_i_1_n_0,c0_carry__1_i_2_n_0,c0_carry__1_i_3_n_0,c0_carry__1_i_4_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__1_i_1
       (.I0(c[12]),
        .O(c0_carry__1_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__1_i_2
       (.I0(c[11]),
        .O(c0_carry__1_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__1_i_3
       (.I0(c[10]),
        .O(c0_carry__1_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__1_i_4
       (.I0(c[9]),
        .O(c0_carry__1_i_4_n_0));
  CARRY4 c0_carry__2
       (.CI(c0_carry__1_n_0),
        .CO({c0_carry__2_n_0,c0_carry__2_n_1,c0_carry__2_n_2,c0_carry__2_n_3}),
        .CYINIT(1'b0),
        .DI(c[16:13]),
        .O({c0_carry__2_n_4,c0_carry__2_n_5,c0_carry__2_n_6,c0_carry__2_n_7}),
        .S({c0_carry__2_i_1_n_0,c0_carry__2_i_2_n_0,c0_carry__2_i_3_n_0,c0_carry__2_i_4_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__2_i_1
       (.I0(c[16]),
        .O(c0_carry__2_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__2_i_2
       (.I0(c[15]),
        .O(c0_carry__2_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__2_i_3
       (.I0(c[14]),
        .O(c0_carry__2_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__2_i_4
       (.I0(c[13]),
        .O(c0_carry__2_i_4_n_0));
  CARRY4 c0_carry__3
       (.CI(c0_carry__2_n_0),
        .CO({c0_carry__3_n_0,c0_carry__3_n_1,c0_carry__3_n_2,c0_carry__3_n_3}),
        .CYINIT(1'b0),
        .DI(c[20:17]),
        .O({c0_carry__3_n_4,c0_carry__3_n_5,c0_carry__3_n_6,c0_carry__3_n_7}),
        .S({c0_carry__3_i_1_n_0,c0_carry__3_i_2_n_0,c0_carry__3_i_3_n_0,c0_carry__3_i_4_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__3_i_1
       (.I0(c[20]),
        .O(c0_carry__3_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__3_i_2
       (.I0(c[19]),
        .O(c0_carry__3_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__3_i_3
       (.I0(c[18]),
        .O(c0_carry__3_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__3_i_4
       (.I0(c[17]),
        .O(c0_carry__3_i_4_n_0));
  CARRY4 c0_carry__4
       (.CI(c0_carry__3_n_0),
        .CO({c0_carry__4_n_0,c0_carry__4_n_1,c0_carry__4_n_2,c0_carry__4_n_3}),
        .CYINIT(1'b0),
        .DI(c[24:21]),
        .O({c0_carry__4_n_4,c0_carry__4_n_5,c0_carry__4_n_6,c0_carry__4_n_7}),
        .S({c0_carry__4_i_1_n_0,c0_carry__4_i_2_n_0,c0_carry__4_i_3_n_0,c0_carry__4_i_4_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__4_i_1
       (.I0(c[24]),
        .O(c0_carry__4_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__4_i_2
       (.I0(c[23]),
        .O(c0_carry__4_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__4_i_3
       (.I0(c[22]),
        .O(c0_carry__4_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__4_i_4
       (.I0(c[21]),
        .O(c0_carry__4_i_4_n_0));
  CARRY4 c0_carry__5
       (.CI(c0_carry__4_n_0),
        .CO({c0_carry__5_n_0,c0_carry__5_n_1,c0_carry__5_n_2,c0_carry__5_n_3}),
        .CYINIT(1'b0),
        .DI(c[28:25]),
        .O({c0_carry__5_n_4,c0_carry__5_n_5,c0_carry__5_n_6,c0_carry__5_n_7}),
        .S({c0_carry__5_i_1_n_0,c0_carry__5_i_2_n_0,c0_carry__5_i_3_n_0,c0_carry__5_i_4_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__5_i_1
       (.I0(c[28]),
        .O(c0_carry__5_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__5_i_2
       (.I0(c[27]),
        .O(c0_carry__5_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__5_i_3
       (.I0(c[26]),
        .O(c0_carry__5_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__5_i_4
       (.I0(c[25]),
        .O(c0_carry__5_i_4_n_0));
  CARRY4 c0_carry__6
       (.CI(c0_carry__5_n_0),
        .CO({NLW_c0_carry__6_CO_UNCONNECTED[3:1],c0_carry__6_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,c[29]}),
        .O({NLW_c0_carry__6_O_UNCONNECTED[3:2],c0_carry__6_n_6,c0_carry__6_n_7}),
        .S({1'b0,1'b0,c0_carry__6_i_1_n_0,c0_carry__6_i_2_n_0}));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__6_i_1
       (.I0(c[30]),
        .O(c0_carry__6_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry__6_i_2
       (.I0(c[29]),
        .O(c0_carry__6_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry_i_1
       (.I0(c[4]),
        .O(c0_carry_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry_i_2
       (.I0(c[3]),
        .O(c0_carry_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry_i_3
       (.I0(c[2]),
        .O(c0_carry_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    c0_carry_i_4
       (.I0(c[1]),
        .O(c0_carry_i_4_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    \c[0]_i_1 
       (.I0(c[0]),
        .O(\c[0]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0004)) 
    \c[30]_i_1 
       (.I0(reset_IBUF),
        .I1(stateVal[0]),
        .I2(stateVal[1]),
        .I3(stateVal[2]),
        .O(\c[30]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0018)) 
    \c[30]_i_2 
       (.I0(stateVal[1]),
        .I1(stateVal[2]),
        .I2(stateVal[0]),
        .I3(reset_IBUF),
        .O(\c[30]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFBF00000380)) 
    \c[3]_i_1 
       (.I0(c0_carry_n_5),
        .I1(stateVal[1]),
        .I2(stateVal[2]),
        .I3(stateVal[0]),
        .I4(reset_IBUF),
        .I5(c[3]),
        .O(\c[3]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(\c[0]_i_1_n_0 ),
        .Q(c[0]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[10] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__1_n_6),
        .Q(c[10]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[11] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__1_n_5),
        .Q(c[11]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[12] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__1_n_4),
        .Q(c[12]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[13] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__2_n_7),
        .Q(c[13]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[14] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__2_n_6),
        .Q(c[14]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[15] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__2_n_5),
        .Q(c[15]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[16] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__2_n_4),
        .Q(c[16]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[17] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__3_n_7),
        .Q(c[17]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[18] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__3_n_6),
        .Q(c[18]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[19] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__3_n_5),
        .Q(c[19]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry_n_7),
        .Q(c[1]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[20] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__3_n_4),
        .Q(c[20]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[21] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__4_n_7),
        .Q(c[21]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[22] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__4_n_6),
        .Q(c[22]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[23] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__4_n_5),
        .Q(c[23]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[24] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__4_n_4),
        .Q(c[24]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[25] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__5_n_7),
        .Q(c[25]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[26] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__5_n_6),
        .Q(c[26]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[27] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__5_n_5),
        .Q(c[27]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[28] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__5_n_4),
        .Q(c[28]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[29] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__6_n_7),
        .Q(c[29]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry_n_6),
        .Q(c[2]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[30] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__6_n_6),
        .Q(c[30]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(\c[3]_i_1_n_0 ),
        .Q(c[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[4] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry_n_4),
        .Q(c[4]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[5] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__0_n_7),
        .Q(c[5]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[6] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__0_n_6),
        .Q(c[6]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[7] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__0_n_5),
        .Q(c[7]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[8] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__0_n_4),
        .Q(c[8]),
        .R(\c[30]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \c_reg[9] 
       (.C(clk_IBUF_BUFG),
        .CE(\c[30]_i_2_n_0 ),
        .D(c0_carry__1_n_7),
        .Q(c[9]),
        .R(\c[30]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    i__i_2
       (.I0(i__i_4_n_0),
        .I1(i__i_5_n_0),
        .I2(i__i_6_n_0),
        .I3(i__i_7_n_0),
        .I4(i__i_8_n_0),
        .O(i__i_2_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    i__i_4
       (.I0(c[5]),
        .I1(c[6]),
        .I2(c[3]),
        .I3(c[4]),
        .I4(c[2]),
        .I5(c[1]),
        .O(i__i_4_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    i__i_5
       (.I0(c[23]),
        .I1(c[24]),
        .I2(c[21]),
        .I3(c[22]),
        .I4(c[20]),
        .I5(c[19]),
        .O(i__i_5_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    i__i_6
       (.I0(c[29]),
        .I1(c[30]),
        .I2(c[27]),
        .I3(c[28]),
        .I4(c[26]),
        .I5(c[25]),
        .O(i__i_6_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    i__i_7
       (.I0(c[17]),
        .I1(c[18]),
        .I2(c[15]),
        .I3(c[16]),
        .I4(c[14]),
        .I5(c[13]),
        .O(i__i_7_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    i__i_8
       (.I0(c[11]),
        .I1(c[12]),
        .I2(c[9]),
        .I3(c[10]),
        .I4(c[8]),
        .I5(c[7]),
        .O(i__i_8_n_0));
  LUT3 #(
    .INIT(8'h2A)) 
    loada
       (.I0(stateVal[0]),
        .I1(stateVal[2]),
        .I2(stateVal[1]),
        .O(loada_n_0));
  FDRE #(
    .INIT(1'b0)) 
    loada_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(loada_n_0),
        .Q(loada__0),
        .R(1'b0));
  LUT3 #(
    .INIT(8'h02)) 
    loadb_i_1
       (.I0(stateVal[0]),
        .I1(stateVal[2]),
        .I2(stateVal[1]),
        .O(loadb_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    loadb_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(loadb_i_1_n_0),
        .Q(loadb),
        .R(1'b0));
  LUT3 #(
    .INIT(8'h06)) 
    loadq_i_1
       (.I0(stateVal[2]),
        .I1(stateVal[0]),
        .I2(stateVal[1]),
        .O(loadq_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    loadq_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(loadq_i_1_n_0),
        .Q(loadq),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \q[7]_i_1 
       (.I0(reset_IBUF),
        .I1(loadb),
        .O(\q_reg[0] ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \q[7]_i_1__0 
       (.I0(reset_IBUF),
        .I1(term_OBUF),
        .O(\q_reg[0]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \q[7]_i_2 
       (.I0(loadb),
        .I1(reset_IBUF),
        .O(\q_reg[7] ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \q[7]_i_2__0 
       (.I0(term_OBUF),
        .I1(reset_IBUF),
        .O(\q_reg[7]_0 ));
  LUT3 #(
    .INIT(8'h02)) 
    shlaq
       (.I0(stateVal[1]),
        .I1(stateVal[2]),
        .I2(stateVal[0]),
        .O(shlaq_n_0));
  FDRE #(
    .INIT(1'b0)) 
    shlaq_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(shlaq_n_0),
        .Q(shlaq__0),
        .R(1'b0));
  LUT3 #(
    .INIT(8'h40)) 
    subb__0
       (.I0(stateVal[2]),
        .I1(stateVal[0]),
        .I2(stateVal[1]),
        .O(subb__0_n_0));
  FDRE #(
    .INIT(1'b0)) 
    subb_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(subb__0_n_0),
        .Q(subb),
        .R(1'b0));
  LUT4 #(
    .INIT(16'hB888)) 
    \temp[0]_i_1 
       (.I0(a_perm__0[0]),
        .I1(loada__0),
        .I2(shlaq__0),
        .I3(Q[7]),
        .O(D[0]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'hA202)) 
    \temp[0]_i_1__0 
       (.I0(loadq),
        .I1(\temp_reg[8]_0 [8]),
        .I2(loadb),
        .I3(A_IBUF[0]),
        .O(\temp_reg[7] [0]));
  LUT6 #(
    .INIT(64'h8FFF8F008F008F00)) 
    \temp[1]_i_1 
       (.I0(loadb),
        .I1(A_IBUF[8]),
        .I2(\temp[1]_i_2_n_0 ),
        .I3(loada__0),
        .I4(shlaq__0),
        .I5(\temp_reg[8]_0 [0]),
        .O(D[1]));
  LUT6 #(
    .INIT(64'hB8FFB800B800B800)) 
    \temp[1]_i_1__0 
       (.I0(A_IBUF[1]),
        .I1(loadb),
        .I2(Q[1]),
        .I3(loadq),
        .I4(shlaq__0),
        .I5(Q[0]),
        .O(\temp_reg[7] [1]));
  LUT6 #(
    .INIT(64'hEFBFBAEABAEAEFBF)) 
    \temp[1]_i_2 
       (.I0(loadb),
        .I1(\temp_reg[8]_0 [0]),
        .I2(\q_reg[1] [0]),
        .I3(subb),
        .I4(\q_reg[1] [1]),
        .I5(\temp_reg[8]_0 [1]),
        .O(\temp[1]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'hB888)) 
    \temp[2]_i_1 
       (.I0(a_perm__0[1]),
        .I1(loada__0),
        .I2(shlaq__0),
        .I3(\temp_reg[8]_0 [1]),
        .O(D[2]));
  LUT6 #(
    .INIT(64'hB8FFB800B800B800)) 
    \temp[2]_i_1__0 
       (.I0(A_IBUF[2]),
        .I1(loadb),
        .I2(Q[2]),
        .I3(loadq),
        .I4(shlaq__0),
        .I5(Q[1]),
        .O(\temp_reg[7] [2]));
  LUT6 #(
    .INIT(64'hACFFAC00AC00AC00)) 
    \temp[3]_i_1 
       (.I0(A_IBUF[9]),
        .I1(s[0]),
        .I2(loadb),
        .I3(loada__0),
        .I4(shlaq__0),
        .I5(\temp_reg[8]_0 [2]),
        .O(D[3]));
  LUT6 #(
    .INIT(64'hB8FFB800B800B800)) 
    \temp[3]_i_1__0 
       (.I0(A_IBUF[3]),
        .I1(loadb),
        .I2(Q[3]),
        .I3(loadq),
        .I4(shlaq__0),
        .I5(Q[2]),
        .O(\temp_reg[7] [3]));
  LUT4 #(
    .INIT(16'hB888)) 
    \temp[4]_i_1 
       (.I0(a_perm__0[2]),
        .I1(loada__0),
        .I2(shlaq__0),
        .I3(\temp_reg[8]_0 [3]),
        .O(D[4]));
  LUT6 #(
    .INIT(64'hB8FFB800B800B800)) 
    \temp[4]_i_1__0 
       (.I0(A_IBUF[4]),
        .I1(loadb),
        .I2(Q[4]),
        .I3(loadq),
        .I4(shlaq__0),
        .I5(Q[3]),
        .O(\temp_reg[7] [4]));
  LUT6 #(
    .INIT(64'hACFFAC00AC00AC00)) 
    \temp[5]_i_1 
       (.I0(A_IBUF[10]),
        .I1(s[1]),
        .I2(loadb),
        .I3(loada__0),
        .I4(shlaq__0),
        .I5(\temp_reg[8]_0 [4]),
        .O(D[5]));
  LUT6 #(
    .INIT(64'hB8FFB800B800B800)) 
    \temp[5]_i_1__0 
       (.I0(A_IBUF[5]),
        .I1(loadb),
        .I2(Q[5]),
        .I3(loadq),
        .I4(shlaq__0),
        .I5(Q[4]),
        .O(\temp_reg[7] [5]));
  LUT4 #(
    .INIT(16'hB888)) 
    \temp[6]_i_1 
       (.I0(a_perm__0[3]),
        .I1(loada__0),
        .I2(shlaq__0),
        .I3(\temp_reg[8]_0 [5]),
        .O(D[6]));
  LUT6 #(
    .INIT(64'hB8FFB800B800B800)) 
    \temp[6]_i_1__0 
       (.I0(A_IBUF[6]),
        .I1(loadb),
        .I2(Q[6]),
        .I3(loadq),
        .I4(shlaq__0),
        .I5(Q[5]),
        .O(\temp_reg[7] [6]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \temp[7]_i_1 
       (.I0(shlaq__0),
        .I1(loadq),
        .I2(reset_IBUF),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'hB888)) 
    \temp[7]_i_1__0 
       (.I0(a_perm),
        .I1(loada__0),
        .I2(shlaq__0),
        .I3(\temp_reg[8]_0 [6]),
        .O(D[7]));
  LUT6 #(
    .INIT(64'hB8FFB800B800B800)) 
    \temp[7]_i_2 
       (.I0(A_IBUF[7]),
        .I1(loadb),
        .I2(Q[7]),
        .I3(loadq),
        .I4(shlaq__0),
        .I5(Q[6]),
        .O(\temp_reg[7] [7]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'hFE)) 
    \temp[8]_i_1 
       (.I0(shlaq__0),
        .I1(loada__0),
        .I2(reset_IBUF),
        .O(\temp_reg[8] ));
  LUT6 #(
    .INIT(64'h06FF060006000600)) 
    \temp[8]_i_2 
       (.I0(\temp_reg[7]_0 ),
        .I1(\temp_reg[8]_0 [8]),
        .I2(loadb),
        .I3(loada__0),
        .I4(shlaq__0),
        .I5(\temp_reg[8]_0 [7]),
        .O(D[8]));
  LUT3 #(
    .INIT(8'h80)) 
    term
       (.I0(stateVal[1]),
        .I1(stateVal[0]),
        .I2(stateVal[2]),
        .O(term_n_0));
  FDRE #(
    .INIT(1'b0)) 
    term_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(term_n_0),
        .Q(term_OBUF),
        .R(1'b0));
endmodule

(* NotValidForBitStream *)
module DIVISION
   (clk,
    reset,
    start,
    A,
    B,
    remainder,
    quotient,
    term);
  input clk;
  input reset;
  input start;
  input [15:0]A;
  input [7:0]B;
  output [7:0]remainder;
  output [7:0]quotient;
  output term;

  wire [15:0]A;
  wire [15:0]A_IBUF;
  wire [7:0]B;
  wire [7:0]B_IBUF;
  wire [8:0]a_load;
  wire [7:7]a_perm;
  wire [6:0]a_perm__0;
  wire clk;
  wire clk_IBUF;
  wire clk_IBUF_BUFG;
  wire divider_n_9;
  wire dut3_n_7;
  wire dut6_n_10;
  wire dut6_n_11;
  wire dut6_n_12;
  wire dut6_n_13;
  wire dut6_n_14;
  wire dut6_n_15;
  wire dut6_n_16;
  wire dut6_n_17;
  wire dut6_n_18;
  wire dut6_n_19;
  wire dut6_n_20;
  wire dut6_n_21;
  wire dut6_n_22;
  wire dut6_n_23;
  wire dut6_n_24;
  wire dut6_n_25;
  wire dut6_n_3;
  wire dut6_n_4;
  wire dut6_n_5;
  wire dut6_n_6;
  wire dut6_n_7;
  wire dut6_n_8;
  wire dut6_n_9;
  wire loadb;
  wire [1:0]q;
  wire [7:1]q_load;
  wire [7:0]quotient;
  wire [7:0]quotient_OBUF;
  wire [7:0]remainder;
  wire [7:0]remainder_OBUF;
  wire reset;
  wire reset_IBUF;
  wire [7:3]s;
  wire start;
  wire start_IBUF;
  wire subb;
  wire term;
  wire term_OBUF;

  IBUF \A_IBUF[0]_inst 
       (.I(A[0]),
        .O(A_IBUF[0]));
  IBUF \A_IBUF[10]_inst 
       (.I(A[10]),
        .O(A_IBUF[10]));
  IBUF \A_IBUF[11]_inst 
       (.I(A[11]),
        .O(A_IBUF[11]));
  IBUF \A_IBUF[12]_inst 
       (.I(A[12]),
        .O(A_IBUF[12]));
  IBUF \A_IBUF[13]_inst 
       (.I(A[13]),
        .O(A_IBUF[13]));
  IBUF \A_IBUF[14]_inst 
       (.I(A[14]),
        .O(A_IBUF[14]));
  IBUF \A_IBUF[15]_inst 
       (.I(A[15]),
        .O(A_IBUF[15]));
  IBUF \A_IBUF[1]_inst 
       (.I(A[1]),
        .O(A_IBUF[1]));
  IBUF \A_IBUF[2]_inst 
       (.I(A[2]),
        .O(A_IBUF[2]));
  IBUF \A_IBUF[3]_inst 
       (.I(A[3]),
        .O(A_IBUF[3]));
  IBUF \A_IBUF[4]_inst 
       (.I(A[4]),
        .O(A_IBUF[4]));
  IBUF \A_IBUF[5]_inst 
       (.I(A[5]),
        .O(A_IBUF[5]));
  IBUF \A_IBUF[6]_inst 
       (.I(A[6]),
        .O(A_IBUF[6]));
  IBUF \A_IBUF[7]_inst 
       (.I(A[7]),
        .O(A_IBUF[7]));
  IBUF \A_IBUF[8]_inst 
       (.I(A[8]),
        .O(A_IBUF[8]));
  IBUF \A_IBUF[9]_inst 
       (.I(A[9]),
        .O(A_IBUF[9]));
  IBUF \B_IBUF[0]_inst 
       (.I(B[0]),
        .O(B_IBUF[0]));
  IBUF \B_IBUF[1]_inst 
       (.I(B[1]),
        .O(B_IBUF[1]));
  IBUF \B_IBUF[2]_inst 
       (.I(B[2]),
        .O(B_IBUF[2]));
  IBUF \B_IBUF[3]_inst 
       (.I(B[3]),
        .O(B_IBUF[3]));
  IBUF \B_IBUF[4]_inst 
       (.I(B[4]),
        .O(B_IBUF[4]));
  IBUF \B_IBUF[5]_inst 
       (.I(B[5]),
        .O(B_IBUF[5]));
  IBUF \B_IBUF[6]_inst 
       (.I(B[6]),
        .O(B_IBUF[6]));
  IBUF \B_IBUF[7]_inst 
       (.I(B[7]),
        .O(B_IBUF[7]));
  BUFG clk_IBUF_BUFG_inst
       (.I(clk_IBUF),
        .O(clk_IBUF_BUFG));
  IBUF clk_IBUF_inst
       (.I(clk),
        .O(clk_IBUF));
  REGISTERCOMP divider
       (.A_IBUF({A_IBUF[15:14],A_IBUF[12],A_IBUF[10]}),
        .B_IBUF(B_IBUF),
        .Q(a_load[7:0]),
        .a_perm(a_perm),
        .a_perm__0({a_perm__0[6],a_perm__0[4],a_perm__0[2]}),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .loadb(loadb),
        .loadb_reg(dut6_n_24),
        .loadb_reg_0(dut6_n_3),
        .s({s[7],s[5],s[3]}),
        .subb(subb),
        .\temp_reg[1] (q),
        .\temp_reg[8] (divider_n_9));
  SHIFTDIV dut3
       (.D({dut6_n_16,dut6_n_17,dut6_n_18,dut6_n_19,dut6_n_20,dut6_n_21,dut6_n_22,dut6_n_23}),
        .E(dut6_n_5),
        .Q({q_load,dut3_n_7}),
        .clk_IBUF_BUFG(clk_IBUF_BUFG));
  SHIFTDIV__parameterized1 dut4
       (.A_IBUF(A_IBUF[8]),
        .D({dut6_n_7,dut6_n_8,dut6_n_9,dut6_n_10,dut6_n_11,dut6_n_12,dut6_n_13,dut6_n_14,dut6_n_15}),
        .E(dut6_n_6),
        .Q(a_load),
        .a_perm__0(a_perm__0[0]),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .loadb(loadb),
        .\q_reg[0] (q[0]));
  CONTROLDIVI dut6
       (.A_IBUF({A_IBUF[15],A_IBUF[13],A_IBUF[11],A_IBUF[9],A_IBUF[7:0]}),
        .D({dut6_n_7,dut6_n_8,dut6_n_9,dut6_n_10,dut6_n_11,dut6_n_12,dut6_n_13,dut6_n_14,dut6_n_15}),
        .E(dut6_n_5),
        .Q({q_load,dut3_n_7}),
        .a_perm(a_perm),
        .a_perm__0({a_perm__0[6],a_perm__0[4],a_perm__0[2],a_perm__0[0]}),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .loadb(loadb),
        .\q_reg[0] (dut6_n_24),
        .\q_reg[0]_0 (dut6_n_25),
        .\q_reg[1] (q),
        .\q_reg[7] (dut6_n_3),
        .\q_reg[7]_0 (dut6_n_4),
        .reset_IBUF(reset_IBUF),
        .s({s[7],s[5],s[3]}),
        .start_IBUF(start_IBUF),
        .subb(subb),
        .\temp_reg[7] ({dut6_n_16,dut6_n_17,dut6_n_18,dut6_n_19,dut6_n_20,dut6_n_21,dut6_n_22,dut6_n_23}),
        .\temp_reg[7]_0 (divider_n_9),
        .\temp_reg[8] (dut6_n_6),
        .\temp_reg[8]_0 (a_load),
        .term_OBUF(term_OBUF));
  OBUF \quotient_OBUF[0]_inst 
       (.I(quotient_OBUF[0]),
        .O(quotient[0]));
  OBUF \quotient_OBUF[1]_inst 
       (.I(quotient_OBUF[1]),
        .O(quotient[1]));
  OBUF \quotient_OBUF[2]_inst 
       (.I(quotient_OBUF[2]),
        .O(quotient[2]));
  OBUF \quotient_OBUF[3]_inst 
       (.I(quotient_OBUF[3]),
        .O(quotient[3]));
  OBUF \quotient_OBUF[4]_inst 
       (.I(quotient_OBUF[4]),
        .O(quotient[4]));
  OBUF \quotient_OBUF[5]_inst 
       (.I(quotient_OBUF[5]),
        .O(quotient[5]));
  OBUF \quotient_OBUF[6]_inst 
       (.I(quotient_OBUF[6]),
        .O(quotient[6]));
  OBUF \quotient_OBUF[7]_inst 
       (.I(quotient_OBUF[7]),
        .O(quotient[7]));
  OBUF \remainder_OBUF[0]_inst 
       (.I(remainder_OBUF[0]),
        .O(remainder[0]));
  OBUF \remainder_OBUF[1]_inst 
       (.I(remainder_OBUF[1]),
        .O(remainder[1]));
  OBUF \remainder_OBUF[2]_inst 
       (.I(remainder_OBUF[2]),
        .O(remainder[2]));
  OBUF \remainder_OBUF[3]_inst 
       (.I(remainder_OBUF[3]),
        .O(remainder[3]));
  OBUF \remainder_OBUF[4]_inst 
       (.I(remainder_OBUF[4]),
        .O(remainder[4]));
  OBUF \remainder_OBUF[5]_inst 
       (.I(remainder_OBUF[5]),
        .O(remainder[5]));
  OBUF \remainder_OBUF[6]_inst 
       (.I(remainder_OBUF[6]),
        .O(remainder[6]));
  OBUF \remainder_OBUF[7]_inst 
       (.I(remainder_OBUF[7]),
        .O(remainder[7]));
  IBUF reset_IBUF_inst
       (.I(reset),
        .O(reset_IBUF));
  REGISTERCOMP__parameterized3 rezQuotient
       (.Q({q_load,dut3_n_7}),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .quotient_OBUF(quotient_OBUF),
        .term_reg(dut6_n_25),
        .term_reg_0(dut6_n_4));
  REGISTERCOMP__parameterized1 rezRemainder
       (.Q(a_load[7:0]),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .remainder_OBUF(remainder_OBUF),
        .term_reg(dut6_n_25),
        .term_reg_0(dut6_n_4));
  IBUF start_IBUF_inst
       (.I(start),
        .O(start_IBUF));
  OBUF term_OBUF_inst
       (.I(term_OBUF),
        .O(term));
endmodule

module REGISTERCOMP
   (a_perm__0,
    \temp_reg[1] ,
    s,
    a_perm,
    \temp_reg[8] ,
    A_IBUF,
    Q,
    subb,
    loadb,
    loadb_reg,
    loadb_reg_0,
    B_IBUF,
    clk_IBUF_BUFG);
  output [2:0]a_perm__0;
  output [1:0]\temp_reg[1] ;
  output [2:0]s;
  output [0:0]a_perm;
  output \temp_reg[8] ;
  input [3:0]A_IBUF;
  input [7:0]Q;
  input subb;
  input loadb;
  input loadb_reg;
  input loadb_reg_0;
  input [7:0]B_IBUF;
  input clk_IBUF_BUFG;

  wire [3:0]A_IBUF;
  wire [7:0]B_IBUF;
  wire [7:0]Q;
  wire [0:0]a_perm;
  wire [2:0]a_perm__0;
  wire clk_IBUF_BUFG;
  wire \dut2/s13__3 ;
  wire \dut2/s19__3 ;
  wire \dut2/s4__3 ;
  wire \dut2/s7__3 ;
  wire loadb;
  wire loadb_reg;
  wire loadb_reg_0;
  wire [7:2]q;
  wire [2:0]s;
  wire subb;
  wire [1:0]\temp_reg[1] ;
  wire \temp_reg[8] ;

  LUT6 #(
    .INIT(64'hAAAAAAAA3CC3C33C)) 
    \FSM_sequential_stateVal[1]_i_2 
       (.I0(A_IBUF[3]),
        .I1(Q[7]),
        .I2(q[7]),
        .I3(subb),
        .I4(\dut2/s4__3 ),
        .I5(loadb),
        .O(a_perm));
  LUT4 #(
    .INIT(16'hF660)) 
    \FSM_sequential_stateVal[1]_i_3 
       (.I0(subb),
        .I1(q[6]),
        .I2(\dut2/s7__3 ),
        .I3(Q[6]),
        .O(\dut2/s4__3 ));
  LUT6 #(
    .INIT(64'h6969996699669696)) 
    i__i_1
       (.I0(Q[7]),
        .I1(q[7]),
        .I2(subb),
        .I3(q[6]),
        .I4(\dut2/s7__3 ),
        .I5(Q[6]),
        .O(s[2]));
  LUT6 #(
    .INIT(64'hD5FDFEEA4054A880)) 
    i__i_3
       (.I0(q[5]),
        .I1(Q[4]),
        .I2(\dut2/s13__3 ),
        .I3(q[4]),
        .I4(subb),
        .I5(Q[5]),
        .O(\dut2/s7__3 ));
  LUT6 #(
    .INIT(64'hD5FDFEEA4054A880)) 
    i__i_9
       (.I0(q[3]),
        .I1(Q[2]),
        .I2(\dut2/s19__3 ),
        .I3(q[2]),
        .I4(subb),
        .I5(Q[3]),
        .O(\dut2/s13__3 ));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[0]),
        .Q(\temp_reg[1] [0]),
        .R(loadb_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[1]),
        .Q(\temp_reg[1] [1]),
        .R(loadb_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[2]),
        .Q(q[2]),
        .R(loadb_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[3]),
        .Q(q[3]),
        .R(loadb_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[4] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[4]),
        .Q(q[4]),
        .R(loadb_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[5] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[5]),
        .Q(q[5]),
        .R(loadb_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[6] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[6]),
        .Q(q[6]),
        .R(loadb_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[7] 
       (.C(clk_IBUF_BUFG),
        .CE(loadb_reg_0),
        .D(B_IBUF[7]),
        .Q(q[7]),
        .R(loadb_reg));
  LUT6 #(
    .INIT(64'hAAAAAAAA3CC3C33C)) 
    \temp[2]_i_2 
       (.I0(A_IBUF[0]),
        .I1(Q[2]),
        .I2(q[2]),
        .I3(subb),
        .I4(\dut2/s19__3 ),
        .I5(loadb),
        .O(a_perm__0[0]));
  LUT6 #(
    .INIT(64'h6969996699669696)) 
    \temp[3]_i_2 
       (.I0(Q[3]),
        .I1(q[3]),
        .I2(subb),
        .I3(q[2]),
        .I4(\dut2/s19__3 ),
        .I5(Q[2]),
        .O(s[0]));
  LUT5 #(
    .INIT(32'hDEFA4850)) 
    \temp[3]_i_3 
       (.I0(\temp_reg[1] [1]),
        .I1(Q[0]),
        .I2(subb),
        .I3(\temp_reg[1] [0]),
        .I4(Q[1]),
        .O(\dut2/s19__3 ));
  LUT6 #(
    .INIT(64'hAAAAAAAA3CC3C33C)) 
    \temp[4]_i_2 
       (.I0(A_IBUF[1]),
        .I1(Q[4]),
        .I2(q[4]),
        .I3(subb),
        .I4(\dut2/s13__3 ),
        .I5(loadb),
        .O(a_perm__0[1]));
  LUT6 #(
    .INIT(64'h6969996699669696)) 
    \temp[5]_i_2 
       (.I0(Q[5]),
        .I1(q[5]),
        .I2(subb),
        .I3(q[4]),
        .I4(\dut2/s13__3 ),
        .I5(Q[4]),
        .O(s[1]));
  LUT6 #(
    .INIT(64'hAAAAAAAA3CC3C33C)) 
    \temp[6]_i_2 
       (.I0(A_IBUF[2]),
        .I1(Q[6]),
        .I2(q[6]),
        .I3(subb),
        .I4(\dut2/s7__3 ),
        .I5(loadb),
        .O(a_perm__0[2]));
  LUT6 #(
    .INIT(64'h5DDF0445FEEAA880)) 
    \temp[8]_i_3 
       (.I0(Q[7]),
        .I1(q[6]),
        .I2(\dut2/s7__3 ),
        .I3(Q[6]),
        .I4(q[7]),
        .I5(subb),
        .O(\temp_reg[8] ));
endmodule

(* ORIG_REF_NAME = "REGISTERCOMP" *) 
module REGISTERCOMP__parameterized1
   (remainder_OBUF,
    term_reg,
    term_reg_0,
    Q,
    clk_IBUF_BUFG);
  output [7:0]remainder_OBUF;
  input term_reg;
  input term_reg_0;
  input [7:0]Q;
  input clk_IBUF_BUFG;

  wire [7:0]Q;
  wire clk_IBUF_BUFG;
  wire [7:0]remainder_OBUF;
  wire term_reg;
  wire term_reg_0;

  FDRE #(
    .INIT(1'b0)) 
    \q_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[0]),
        .Q(remainder_OBUF[0]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[1]),
        .Q(remainder_OBUF[1]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[2]),
        .Q(remainder_OBUF[2]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[3]),
        .Q(remainder_OBUF[3]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[4] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[4]),
        .Q(remainder_OBUF[4]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[5] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[5]),
        .Q(remainder_OBUF[5]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[6] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[6]),
        .Q(remainder_OBUF[6]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[7] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[7]),
        .Q(remainder_OBUF[7]),
        .R(term_reg));
endmodule

(* ORIG_REF_NAME = "REGISTERCOMP" *) 
module REGISTERCOMP__parameterized3
   (quotient_OBUF,
    term_reg,
    term_reg_0,
    Q,
    clk_IBUF_BUFG);
  output [7:0]quotient_OBUF;
  input term_reg;
  input term_reg_0;
  input [7:0]Q;
  input clk_IBUF_BUFG;

  wire [7:0]Q;
  wire clk_IBUF_BUFG;
  wire [7:0]quotient_OBUF;
  wire term_reg;
  wire term_reg_0;

  FDRE #(
    .INIT(1'b0)) 
    \q_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[0]),
        .Q(quotient_OBUF[0]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[1]),
        .Q(quotient_OBUF[1]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[2]),
        .Q(quotient_OBUF[2]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[3]),
        .Q(quotient_OBUF[3]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[4] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[4]),
        .Q(quotient_OBUF[4]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[5] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[5]),
        .Q(quotient_OBUF[5]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[6] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[6]),
        .Q(quotient_OBUF[6]),
        .R(term_reg));
  FDRE #(
    .INIT(1'b0)) 
    \q_reg[7] 
       (.C(clk_IBUF_BUFG),
        .CE(term_reg_0),
        .D(Q[7]),
        .Q(quotient_OBUF[7]),
        .R(term_reg));
endmodule

module SHIFTDIV
   (Q,
    E,
    D,
    clk_IBUF_BUFG);
  output [7:0]Q;
  input [0:0]E;
  input [7:0]D;
  input clk_IBUF_BUFG;

  wire [7:0]D;
  wire [0:0]E;
  wire [7:0]Q;
  wire clk_IBUF_BUFG;

  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[0]),
        .Q(Q[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[1]),
        .Q(Q[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[2]),
        .Q(Q[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[3]),
        .Q(Q[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[4] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[4]),
        .Q(Q[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[5] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[5]),
        .Q(Q[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[6] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[6]),
        .Q(Q[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[7] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[7]),
        .Q(Q[7]),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "SHIFTDIV" *) 
module SHIFTDIV__parameterized1
   (a_perm__0,
    Q,
    A_IBUF,
    \q_reg[0] ,
    loadb,
    E,
    D,
    clk_IBUF_BUFG);
  output [0:0]a_perm__0;
  output [8:0]Q;
  input [0:0]A_IBUF;
  input [0:0]\q_reg[0] ;
  input loadb;
  input [0:0]E;
  input [8:0]D;
  input clk_IBUF_BUFG;

  wire [0:0]A_IBUF;
  wire [8:0]D;
  wire [0:0]E;
  wire [8:0]Q;
  wire [0:0]a_perm__0;
  wire clk_IBUF_BUFG;
  wire loadb;
  wire [0:0]\q_reg[0] ;

  LUT4 #(
    .INIT(16'hAA3C)) 
    \temp[0]_i_2 
       (.I0(A_IBUF),
        .I1(Q[0]),
        .I2(\q_reg[0] ),
        .I3(loadb),
        .O(a_perm__0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[0]),
        .Q(Q[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[1]),
        .Q(Q[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[2]),
        .Q(Q[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[3]),
        .Q(Q[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[4] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[4]),
        .Q(Q[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[5] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[5]),
        .Q(Q[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[6] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[6]),
        .Q(Q[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[7] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[7]),
        .Q(Q[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \temp_reg[8] 
       (.C(clk_IBUF_BUFG),
        .CE(E),
        .D(D[8]),
        .Q(Q[8]),
        .R(1'b0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (weak1, weak0) GSR = GSR_int;
    assign (weak1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
