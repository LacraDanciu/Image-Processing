----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/06/2017 11:25:15 PM
-- Design Name: 
-- Module Name: ADDWITHOVER - Behavioral
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

entity ADDWITHOVER is
 Port (a, b: in STD_LOGIC_VECTOR(8 downto 0);
       cin: in STD_LOGIC;
       s: out STD_LOGIC_VECTOR(8 downto 0);
       cout: out STD_LOGIC;
       overflow: out STD_LOGIC);
end ADDWITHOVER;

architecture Behavioral of ADDWITHOVER is

begin

process (a, b, cin)
 variable c: STD_LOGIC;
 variable c_1: STD_LOGIC;
 begin
    c := cin;
    for i in 0 to 8 loop
        s(i) <= a(i) xor b(i) xor c;
        c_1 := c;
        c := (a(i) and b(i)) or (a(i) and c) or (b(i) and c);
    end loop;
    cout <= c;
    overflow <= c xor c_1;
end process;

end Behavioral;
