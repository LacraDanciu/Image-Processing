----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    04/08/2017 11:09:20 PM
-- Design Name: 
-- Module Name:    MPG - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity MPG is
	Port ( clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           enable : out STD_LOGIC_VECTOR (4 downto 0));
end MPG;

architecture Behavioral of MPG is

signal count:std_logic_vector(15 downto 0);
signal q1:std_logic_vector(4 downto 0);
signal q2:std_logic_vector(4 downto 0);
signal q3:std_logic_vector(4 downto 0);

begin
 process(clk)
 begin
    if rising_edge(clk)then
    count<=count+1;
    end if;
 end process;
 
 process(clk)
 begin
    if rising_edge(clk)then
         if count=x"FFFF" then
            q1<=btn;
         end if;
    end if;
 end process;
 
  process(clk)
 begin
    if rising_edge(clk)then
    q2<=q1;
    q3<=q2;
    end if;
 end process;
 
 enable<= not q3 and q2;
	
end Behavioral;