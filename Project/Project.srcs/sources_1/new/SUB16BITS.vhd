----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/08/2017 11:56:16 PM
-- Design Name: 
-- Module Name: SUB16BITS - Behavioral
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

entity SUB16BITS is
    Port (A, B : in STD_LOGIC_VECTOR(15 downto 0);
            CIN: in STD_LOGIC;
            F: out STD_LOGIC_VECTOR(15 downto 0);
            COUT : out STD_LOGIC);
end SUB16BITS;

architecture Behavioral of SUB16BITS is

component SUB1BIT is
    Port (A, B, CIN: in std_logic;
            F, COUT : out std_logic );
end component;

component ADD16BITS is
  Port (A, B: in STD_LOGIC_VECTOR(15 downto 0);
        CIN: in STD_LOGIC;
        SUM: out STD_LOGIC_VECTOR(15 downto 0);
        COUT: out STD_LOGIC);
end component;

signal COUTAUX: STD_LOGIC_VECTOR(15 downto 0);
signal aux: STD_LOGIC_VECTOR(15 downto 0);
begin
    FIRST: SUB1BIT port map (A(0), B(0), CIN, aux(0), COUTAUX(0));
    Gen1: for I in 1 to 15 generate
         SUB1: SUB1BIT port map (A(I), B(I), COUTAUX(I-1), aux(I), COUTAUX(I));
         end generate;
         
    ADD1TORESULT: ADD16BITS port map(aux, "0000000000000001", COUTAUX(15), F, COUT);
end Behavioral;