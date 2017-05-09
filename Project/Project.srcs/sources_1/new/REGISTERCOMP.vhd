----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/06/2017 10:11:26 PM
-- Design Name: 
-- Module Name: REGISTERCOMP - Behavioral
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

entity REGISTERCOMP is
  generic(n: natural);
  Port (D: in STD_LOGIC_VECTOR(n-1 downto 0);
         clock_enable: in STD_LOGIC;
         clk: in STD_LOGIC;
         rst: in STD_LOGIC;
         
         q: out STD_LOGIC_VECTOR(n-1 downto 0));
end REGISTERCOMP;

architecture Behavioral of REGISTERCOMP is

begin

gen_shift:process(clk)
          begin
            if rising_edge(clk) then
                if (rst = '1') then
                    q <= (others => '0');
                end if;
                
                if (clock_enable = '1') then
                    q <= d;
                end if;
            end if;
          end process gen_shift;

end Behavioral;
