----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/09/2017 03:41:01 PM
-- Design Name: 
-- Module Name: CHECKCOMPONENT - Behavioral
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

entity CHECKCOMPONENT is
  GENERIC(N: natural);
  Port (A: in STD_LOGIC_VECTOR(n-1 downto 0);
        NEGATIVE: in STD_LOGIC;
        B: out STD_LOGIC_VECTOR(n-1 DOWNTO 0));
end CHECKCOMPONENT;

architecture Behavioral of CHECKCOMPONENT is

begin

final:  process(A, NEGATIVE)
        begin
           if (negative = '1') then
              B <= not(A) + '1';
           else
              B <= A;
           end if; 
        end process final;
end Behavioral;
