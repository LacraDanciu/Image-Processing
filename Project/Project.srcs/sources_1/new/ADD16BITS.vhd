----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/08/2017 11:32:08 PM
-- Design Name: 
-- Module Name: ADD16BITS - Behavioral
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

entity ADD16BITS is
  Port (A, B: in STD_LOGIC_VECTOR(15 downto 0);
        CIN: in STD_LOGIC;
        SUM: out STD_LOGIC_VECTOR(15 downto 0);
        COUT: out STD_LOGIC);
end ADD16BITS;

architecture Behavioral of ADD16BITS is

component ADD1BIT is
    Port ( A : in  STD_LOGIC;
           B : in  STD_LOGIC;
           CIN : in  STD_LOGIC;
           S : out  STD_LOGIC;
           COUT : out  STD_LOGIC);
end component;
signal CINAUX: STD_LOGIC:='0';
signal COUTAUX: STD_LOGIC_VECTOR(15 downto 0);
begin
    FIRST: ADD1BIT port map (A(0), B(0), CINAUX, SUM(0), COUTAUX(0));
    Gen1: for I in 1 to 15 generate
         ADD1: ADD1BIT port map (A(I), B(I), COUTAUX(I-1), SUM(I), COUTAUX(I));
         end generate;
    COUT <= COUTAUX(15);
end Behavioral;