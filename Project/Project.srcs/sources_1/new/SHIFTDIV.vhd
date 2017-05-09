----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/06/2017 11:08:38 PM
-- Design Name: 
-- Module Name: SHIFTDIV - Behavioral
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

entity SHIFTDIV is
 generic(n:natural);
    Port (clk:in STD_LOGIC;
          d: in STD_LOGIC_VECTOR(n-1 downto 0);
          sri: in STD_LOGIC;
          rst: in STD_LOGIC;
          load: in STD_LOGIC;
          clock_enable: in STD_LOGIC;
          q: out STD_LOGIC_VECTOR(n-1 downto 0));
end SHIFTDIV;

architecture Behavioral of SHIFTDIV is

signal temp: STD_LOGIC_VECTOR(n-1 downto 0);

begin

gen_reg: process(clk)
        begin
           if rising_edge(clk) then
            if (rst = '1') then
             temp <= (others=>'0');
            end if;
            
            if (load = '1') then 
                temp <= d;
            else
                if (clock_enable = '1') then
                    temp <= temp(n-2 downto 0) & sri; 
                end if;
            end if;     
           end if;
 end process gen_reg;

q <= temp;

end Behavioral;