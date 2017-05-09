----------------------------------------------------------------------------------
-- Company: UTCN
-- Engineer: Diana Lacramioara Danciu
-- 
-- Create Date: 04/08/2017 03:10:13 PM
-- Design Name: 
-- Module Name: AND1BIT - Behavioral
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

entity AND1BIT is
    Port (A, B : in std_logic;
            F : out std_logic);
end AND1BIT;

architecture Behavioral of AND1BIT is

begin
    F <= A and B;
end Behavioral;