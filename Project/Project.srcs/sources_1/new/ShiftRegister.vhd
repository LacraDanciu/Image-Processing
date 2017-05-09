----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2017 10:23:50 PM
-- Design Name: 
-- Module Name: ShiftRegister - Behavioral
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

entity ShiftRegister is
   port( clk: in STD_LOGIC;
         L: in STD_LOGIC; 
         Input: in STD_LOGIC_VECTOR(15 downto 0);
         Output: out STD_LOGIC_VECTOR(15 downto 0));

end ShiftRegister;

architecture Behavioral of ShiftRegister is
begin
   process
   variable temp: STD_LOGIC_VECTOR(15 downto 0); 
   variable aux: STD_LOGIC;
   begin
      wait until rising_edge (clk);
      temp := Input; 
      -- shift right
      if L='1' then 
         aux := temp(0);
         for i in 0 to 14 loop
            temp(i) := temp(i+1);
         end loop;
         temp(15) := aux;
      else 
        aux := temp(15);
        for i in 15 downto 1 loop
           temp(i) := temp(i-1);
        end loop;
        temp(0) := aux;
      end if;
      Output <= temp;
    end process;
end Behavioral;