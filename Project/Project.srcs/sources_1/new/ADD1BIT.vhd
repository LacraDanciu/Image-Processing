----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/08/2017 04:09:44 PM
-- Design Name: 
-- Module Name: ADD1BIT - Behavioral
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

entity ADD1BIT is
  Port ( A : in  STD_LOGIC;
         B : in  STD_LOGIC;
         CIN : in  STD_LOGIC;
         S : out  STD_LOGIC;
         COUT : out  STD_LOGIC);
end ADD1BIT;

architecture Behavioral of ADD1BIT is

begin
    -- Calculate the sum of the 1-BIT adder.
    S <= A xor B xor CIN;

    -- Calculates the carry out of the 1-BIT adder.
    COUT <= (A and B) or (A and CIN) or (B and CIN);
    
end Behavioral;