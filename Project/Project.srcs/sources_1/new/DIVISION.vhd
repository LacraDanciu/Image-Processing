----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/06/2017 11:30:45 PM
-- Design Name: 
-- Module Name: DIVISION - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DIVISION is
    Port (clk: in STD_LOGIC;
          reset: in STD_LOGIC;
          start: in STD_LOGIC;
          A: in STD_LOGIC_VECTOR(15 downto 0);
          B: in STD_LOGIC_VECTOR(7 downto 0);
          
          remainder: out STD_LOGIC_VECTOR(7 downto 0);
          quotient: out STD_LOGIC_VECTOR(7 downto 0);
          term: out STD_LOGIC);
end DIVISION;

architecture Behavioral of DIVISION is

component ADDWITHOVER is
 Port (a, b: in STD_LOGIC_VECTOR(8 downto 0);
       cin: in STD_LOGIC;
       s: out STD_LOGIC_VECTOR(8 downto 0);
       cout: out STD_LOGIC;
       overflow: out STD_LOGIC);
end component;

component CONTROLDIVI is
    Port (
      clk: in STD_LOGIC;
      rst: in STD_LOGIC;
      start: in STD_LOGIC;
      an: in STD_LOGIC;
      
      term: out STD_LOGIC;
      loadb: out STD_LOGIC;
      loadq: out STD_LOGIC;
      shlaq: out STD_LOGIC;
      subb: out STD_LOGIC;
      loada: out STD_LOGIC);
end component;

component REGISTERCOMP is
  generic(n: natural);
  Port (D: in STD_LOGIC_VECTOR(n-1 downto 0);
         clock_enable: in STD_LOGIC;
         clk: in STD_LOGIC;
         rst: in STD_LOGIC;
         
         q: out STD_LOGIC_VECTOR(n-1 downto 0));
end component;

component SHIFTDIV is
 generic(n: natural);
    Port (clk: in STD_LOGIC;
          d: in STD_LOGIC_VECTOR(n-1 downto 0);
          sri: in STD_LOGIC;
          rst: in STD_LOGIC;
          load: in STD_LOGIC;
          clock_enable: in STD_LOGIC;
          q: out STD_LOGIC_VECTOR(n-1 downto 0));
end component;

component CHECKCOMPONENT is
  GENERIC(N: natural);
  Port (A: in STD_LOGIC_VECTOR(n-1 downto 0);
        NEGATIVE: in STD_LOGIC;
        B: out STD_LOGIC_VECTOR(n-1 DOWNTO 0));
end component;

signal q_load, q_perm: STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal loadq, loadb, subb, ovf, tout, shlaq , loada, term_aux: STD_LOGIC := '0';
signal b_load, a_load, b_temp, a_sum, a_perm: STD_LOGIC_VECTOR(8 downto 0) :=(others => '0');
signal negativeBoth, negativeOne: STD_LOGIC;
signal AUXB, auxQuotient: STD_LOGIC_VECTOR(7 downto 0);
signal AUXA: STD_LOGIC_VECTOR(15 downto 0);
begin

INITIALIZE: process(A, B, AUXA, AUXB)
            begin
                negativeBoth <= A(15) and B(7);
                if (negativeBoth = '1') then
                   AUXA <= not(A) + '1';
                   AUXB <= not(B) + '1';
                else
                   AUXA <= A;
                   AUXB <= B;
                end if;
                
                negativeOne <= A(15) xor B(7);
                if (negativeOne = '1') then
                   if (A(15) = '1') then
                       AUXA <= not(A) + '1';
                   elsif (B(7) = '1') then
                       AUXB <= not(B) + '1';
                   end if;
                end if;
            if (B = "00000000") then
                report "you are trying a division by 0. We'll change the variable to 1" severity error;
                AUXB <= "00000001";
            end if;
            end process INITIALIZE;


q_perm <= AUXA(7 downto 0) when loadb = '1' else q_load(7 downto 1) & not a_load(8);
a_perm <= '0' & AUXA(15 downto 8) when loadb = '1' else a_sum;

divider: REGISTERCOMP generic map(n => 9) port map('0' & AUXB, loadb, clk, reset, b_load);

dut2: ADDWITHOVER port map(a_load, b_temp, subb, a_sum, tout, ovf);
                       
dut3: SHIFTDIV generic map(n => 8) port map(clk, q_perm, '0', reset, loadq, shlaq, q_load);

dut4: SHIFTDIV generic map(n => 9) 
                            port map(clk, a_perm, q_load(7), reset, loada, shlaq, a_load);
                                 
dut6: CONTROLDIVI port map(clk, reset, start, a_perm(7), term_aux, loadb, loadq, shlaq, subb, loada);
   
genFOR: for i in 0 to 8 generate
            b_temp(i) <= b_load(i) xor subb;
        end generate genFOR;
   
rezRemainder: REGISTERCOMP generic map(n => 8) port map(a_load(7 downto 0), term_aux, clk, reset, remainder);

rezQuotient: REGISTERCOMP generic map(n => 8) port map(q_load, term_aux, clk, reset, auxQuotient);

endF: CHECKCOMPONENT generic map(n => 8) port map (auxQuotient, negativeOne, quotient);               

term <= term_aux;

end Behavioral;