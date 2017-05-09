----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/07/2017 10:36:25 AM
-- Design Name: 
-- Module Name: TOP - Behavioral
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

entity TOP is
    port(CLK:in std_logic;
		btn:in std_logic_vector(4 downto 0);
		sw:in std_logic_vector(15 downto 0);
		led : out STD_LOGIC_VECTOR (15 downto 0);
		an:out std_logic_vector(3 downto 0);
		cat:out std_logic_vector(6 downto 0);
		dp:out std_logic);
end TOP;

architecture Behavioral of TOP is

component MULTIPLY is
    Port ( A : in  STD_LOGIC_VECTOR (7 downto 0);
           B : in  STD_LOGIC_VECTOR (7 downto 0);
           RES : out  STD_LOGIC_VECTOR (16 downto 0));
end component;

component DIVISION is
    Port (clk: in STD_LOGIC;
          reset: in STD_LOGIC;
          start: in STD_LOGIC;
          A: in STD_LOGIC_VECTOR(15 downto 0);
          B: in STD_LOGIC_VECTOR(7 downto 0);
          
          remainder: out STD_LOGIC_VECTOR(7 downto 0);
          quotient: out STD_LOGIC_VECTOR(7 downto 0);
          term: out STD_LOGIC);
end component;

component ADD16BITS is
  Port (A, B: in STD_LOGIC_VECTOR(15 downto 0);
        CIN: in STD_LOGIC;
        SUM: out STD_LOGIC_VECTOR(15 downto 0);
        COUT: out STD_LOGIC);
end component;

component AND16BITS is
  Port (A, B : in std_logic_vector(15 downto 0);
            F : out std_logic_vector(15 downto 0));
end component;

component NOT16BITS is
  Port (A: in std_logic_vector(15 downto 0);
        F : out std_logic_vector(15 downto 0));
end component;

component OR16BITS is
    Port (A, B : in std_logic_vector(15 downto 0);
            F : out std_logic_vector(15 downto 0) );
end component;

component DISPLAY is
    PORT ( digit0: in STD_LOGIC_VECTOR(3 downto 0);
           digit1: in STD_LOGIC_VECTOR(3 downto 0);
           digit2: in STD_LOGIC_VECTOR(3 downto 0);
           digit3: in STD_LOGIC_VECTOR(3 downto 0);
           clk: in STD_LOGIC;
           an : out  STD_LOGIC_VECTOR (3 downto 0);
           cat : out  STD_LOGIC_VECTOR (6 downto 0) );
end component;

component MPG is
	Port ( clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           enable : out STD_LOGIC_VECTOR (4 downto 0));
end component;

component SSD is
	port(digit0: in std_logic_vector(3 downto 0);
		digit1: in std_logic_vector(3 downto 0);
		digit2: in std_logic_vector(3 downto 0);
		digit3: in std_logic_vector(3 downto 0);
		clk: in std_logic;
		an: out std_logic_vector(3 downto 0);
		cat: out std_logic_vector(6 downto 0));
end component;

component ShiftRegister is
   port( clk: in STD_LOGIC;
         L: in STD_LOGIC; 
         Input: in STD_LOGIC_VECTOR(15 downto 0);
         Output: out STD_LOGIC_VECTOR(15 downto 0));
end component;

begin


end Behavioral;