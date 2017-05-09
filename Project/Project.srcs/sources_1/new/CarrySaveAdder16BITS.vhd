----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2017 08:51:16 PM
-- Design Name: 
-- Module Name: CarrySaveAdder16BITS - Behavioral
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

entity CarrySaveAdder16BITS is
    GENERIC (N: natural);
    Port ( A : in  STD_LOGIC_VECTOR (N-1 downto 0);
          B : in  STD_LOGIC_VECTOR (N-1 downto 0);
          C : in  STD_LOGIC_VECTOR (N-1 downto 0);
          S : out  STD_LOGIC_VECTOR (N-1 downto 0);
          COUT : out  STD_LOGIC_VECTOR (N-1 downto 0));
end CarrySaveAdder16BITS;

architecture Behavioral of CarrySaveAdder16BITS is

component ADD1BIT is
    Port ( A : in  STD_LOGIC;
           B : in  STD_LOGIC;
           CIN : in  STD_LOGIC;
           S : out  STD_LOGIC;
           COUT : out  STD_LOGIC);
end component;

begin
    Gen1: for I in 0 to N-1 generate
         SUM1: ADD1BIT port map (A(I), B(I), C(I), S(I), COUT(I));
    end generate;

end Behavioral;