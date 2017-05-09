----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/08/2017 04:33:26 PM
-- Design Name: 
-- Module Name: SUB1BIT - Behavioral
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

entity SUB1BIT is
    Port (A, B, CIN : in std_logic;
            F, COUT : out std_logic);
end SUB1BIT;

architecture Behavioral of SUB1BIT is

component ADD1BIT is
    Port (a, b, cin : in  STD_LOGIC;
          sum, cout : out STD_LOGIC  );
end component;

component NOT1BIT is
    Port (A: in std_logic;
          F : out std_logic);
end component;

signal aux1: std_logic := '0';
signal aux2: std_logic := '0';

begin
   
C2: NOT1BIT port map (A => B, F => aux1);
SUB: ADD1BIT port map(a => A, b => aux1, cin => CIN, sum => F, cout => COUT);           

end Behavioral;
