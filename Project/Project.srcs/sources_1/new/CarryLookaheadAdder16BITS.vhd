----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2017 08:25:17 PM
-- Design Name: 
-- Module Name: CarryLookaheadAdder16BITS - Behavioral
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

entity CarryLookaheadAdder16BITS is
    Port (A : in  STD_LOGIC_VECTOR (15 downto 0);
          B : in  STD_LOGIC_VECTOR (15 downto 0);
          CIN : in  STD_LOGIC;
          S : out  STD_LOGIC_VECTOR (16 downto 0));
end CarryLookaheadAdder16BITS;

architecture Behavioral of CarryLookaheadAdder16BITS is

component HalfAdder1BIT is
    Port ( A : in  STD_LOGIC;
          B : in  STD_LOGIC;
          CIN : in  STD_LOGIC;
          S : out  STD_LOGIC);
end component;

signal c: STD_LOGIC_VECTOR(15 downto 0);
signal generateFun, propagateFun:STD_LOGIC_VECTOR(15 downto 0);

begin
    
    GP:process(a,b)
	begin
		for i in 0 to 15 loop
			generateFun(i) <= a(i) and b(i);
			propagateFun(i) <= a(i) or b(i);
		end loop;
	end process GP;
	
	
	c(0)<= generateFun(0) or (propagateFun(0) and cin);
	c(1)<= generateFun(1) or (propagateFun(1) and (generateFun(0) or (propagateFun(0) and cin)));
	c(2)<= generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and (generateFun(0) or (propagateFun(0) and cin)))));
	c(3)<= generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and (generateFun(0) or (propagateFun(0) and cin)))))));
	c(4)<= generateFun(4) or (propagateFun(4) and 
			(generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and (generateFun(0) or (propagateFun(0) and cin)))))))));
	c(5)<= generateFun(5) or (propagateFun(5) and (generateFun(4) or (propagateFun(4) and 
			(generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and (generateFun(0) or (propagateFun(0) and cin)))))))))));
	c(6)<= generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and (generateFun(4) or (propagateFun(4) and 
			(generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and (generateFun(0) or (propagateFun(0) and cin)))))))))))));
	c(7) <= generateFun(7) or (propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and (generateFun(4) or (propagateFun(4) and 
			(generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and (generateFun(0) or (propagateFun(0) and cin)))))))))))))));
	c(8)<= generateFun(8) or (propagateFun(8) and (generateFun(7) or (propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))));
	c(9)<= generateFun(9) or (propagateFun(9) and ( generateFun(8) or (propagateFun(8) and (generateFun(7) or (propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))))));
	c(10)<= generateFun(10) or (propagateFun(10) and (generateFun(9) or (propagateFun(9) and ( generateFun(8) or (propagateFun(8) and (generateFun(7) or (propagateFun(7) and 
			(generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))))))));
	c(11)<= generateFun(11) or (propagateFun(11) and (generateFun(10) or (propagateFun(10) and (generateFun(9) or (propagateFun(9) and ( generateFun(8) or (propagateFun(8) and (generateFun(7) or 
			(propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))))))))));
	c(12)<= generateFun(12) or (propagateFun(12) and (generateFun(11) or (propagateFun(11) and (generateFun(10) or (propagateFun(10) and (generateFun(9) or (propagateFun(9) and ( generateFun(8) or (propagateFun(8) and (generateFun(7) or 
			(propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))))))))))));
	c(13)<= generateFun(13) or (propagateFun(13) and (generateFun(12) or (propagateFun(12) and (generateFun(11) or (propagateFun(11) and (generateFun(10) or (propagateFun(10) and 
			(generateFun(9) or (propagateFun(9) and ( generateFun(8) or (propagateFun(8) and (generateFun(7) or 
			(propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))))))))))))));
	c(14)<= generateFun(14) or (propagateFun(14) and (generateFun(13) or (propagateFun(13) and (generateFun(12) or (propagateFun(12) and (generateFun(11) or (propagateFun(11) and 
			(generateFun(10) or (propagateFun(10) and (generateFun(9) or (propagateFun(9) and ( generateFun(8) or (propagateFun(8) and (generateFun(7) or 
			(propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))))))))))))))));
	s(16)<= generateFun(15) or (propagateFun(15) and (generateFun(14) or (propagateFun(14) and (generateFun(13) or (propagateFun(13) and (generateFun(12) or (propagateFun(12) and (generateFun(11) or 
			(propagateFun(11) and (generateFun(10) or (propagateFun(10) and (generateFun(9) or (propagateFun(9) and ( generateFun(8) or (propagateFun(8) and (generateFun(7) or 
			(propagateFun(7) and (generateFun(6) or (propagateFun(6) and (generateFun(5) or (propagateFun(5) and 
			(generateFun(4) or (propagateFun(4) and (generateFun(3) or (propagateFun(3) and (generateFun(2) or (propagateFun(2) and (generateFun(1) or (propagateFun(1) and 
			(generateFun(0) or (propagateFun(0) and cin)))))))))))))))))))))))))))))));
	
	HA1: HalfAdder1BIT port map (a => a(0), b => b(0), cin => cin, s => s(0));
	
	Gen1: for I in 1 to 15 generate
	       HA: HalfAdder1BIT port map (a(I), b(I), c(I-1), s(I));
    end generate;

end Behavioral;