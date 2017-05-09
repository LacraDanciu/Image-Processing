----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2017 09:12:21 PM
-- Design Name: 
-- Module Name: DISPLAY - Behavioral
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

entity DISPLAY is
    PORT ( digit0: in STD_LOGIC_VECTOR(3 downto 0);
           digit1: in STD_LOGIC_VECTOR(3 downto 0);
           digit2: in STD_LOGIC_VECTOR(3 downto 0);
           digit3: in STD_LOGIC_VECTOR(3 downto 0);
           clk: in STD_LOGIC;
           an : out  STD_LOGIC_VECTOR (3 downto 0);
           cat : out  STD_LOGIC_VECTOR (6 downto 0) );
end DISPLAY;

architecture Behavioral of DISPLAY is

signal cnt : std_logic_vector(15 downto 0);
signal displayed_digit: std_logic_vector(3 downto 0);

begin
    --HEX-to-seven-segment decoder
    --   HEX:   in    STD_LOGIC_VECTOR (3 downto 0);
    --   LED:   out   STD_LOGIC_VECTOR (6 downto 0);
    -- 
    -- segment encoinputg
    --      0
    --     ---  
    --  5 |   | 1
    --     ---   <- 6
    --  4 |   | 2
    --     ---
    --      3
   
    with displayed_digit Select
   cat<= "1111001" when "0001",   --1
         "0100100" when "0010",   --2
         "0110000" when "0011",   --3
         "0011001" when "0100",   --4
         "0010010" when "0101",   --5
         "0000010" when "0110",   --6
         "1111000" when "0111",   --7
         "0000000" when "1000",   --8
         "0010000" when "1001",   --9
         "0001000" when "1010",   --A
         "0000011" when "1011",   --b
         "1000110" when "1100",   --C
         "0100001" when "1101",   --d
         "0000110" when "1110",   --E
         "0001110" when "1111",   --F
         "1000000" when others;   --0
			

COUNTER: process(clk)
begin
	if rising_edge(clk) then
	   cnt<=cnt+1;
	end if;
end process COUNTER;

MUX1: process(cnt,digit0,digit1,digit2,digit3)
begin
	case cnt(15 downto 14) is
		when "00" => 
		      displayed_digit<=digit0;
		      an<="1110";
		when "01" => 
		      displayed_digit<=digit1;
		      an<="1101";
		when "10" => 
		      displayed_digit<=digit2;
		      an<="1011";
		when others =>
		      displayed_digit<=digit3;
		      an<="0111";
		
	end case;
end process MUX1;

end Behavioral;
