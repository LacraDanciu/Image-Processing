----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/09/2017 05:02:45 PM
-- Design Name: 
-- Module Name: RL16BITS - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity RL16BITS is
    Port (A: in STD_LOGIC_VECTOR(15 downto 0);
          NR: in STD_LOGIC_VECTOR(3 downto 0);
          B: out STD_LOGIC_VECTOR(15 downto 0));
end RL16BITS;

architecture Behavioral of RL16BITS is

component RL1BIT is
    Port (A: in std_logic;
          B: out std_logic);
end component;
constant number : INTEGER :=to_integer(unsigned(NR));
signal aux : STD_LOGIC_VECTOR(15 downto 0);

begin

    aux <= A;
    Gen1: for I in 0 to number generate
        Gen2: for J in 0 to 14 generate
                RL1 : RL1BIT port map (A(J), B(J+1));
               end generate;
           end generate;
    
    B(number-1 downto 0) <= aux(15 downto (15-number -1));
    
end Behavioral;