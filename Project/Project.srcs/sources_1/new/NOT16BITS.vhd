----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/08/2017 11:24:13 PM
-- Design Name: 
-- Module Name: NOT16BITS - Behavioral
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity NOT16BITS is
  Port (A: in std_logic_vector(15 downto 0);
        F : out std_logic_vector(15 downto 0));
end NOT16BITS;

architecture Behavioral of NOT16BITS is

component NOT1BIT is
    Port (A: in std_logic;
          F : out std_logic);
end component; 

begin
    Gen1: for I in 0 to 15 generate
            NOT1 : NOT1BIT port map (A(I),F(I));
          end generate;

end Behavioral;