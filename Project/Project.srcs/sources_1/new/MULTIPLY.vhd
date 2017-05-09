----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2017 08:01:00 PM
-- Design Name: 
-- Module Name: MULTIPLY - Behavioral
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

entity MULTIPLY is
    Port ( A : in  STD_LOGIC_VECTOR (7 downto 0);
           B : in  STD_LOGIC_VECTOR (7 downto 0);
           RES : out  STD_LOGIC_VECTOR (16 downto 0));
end MULTIPLY;

architecture Behavioral of MULTIPLY is

component CarrySaveAdder16BITS is
    GENERIC (N: natural);
    Port ( A : in  STD_LOGIC_VECTOR (N-1 downto 0);
           B : in  STD_LOGIC_VECTOR (N-1 downto 0);
           C : in  STD_LOGIC_VECTOR (N-1 downto 0);
           S : out  STD_LOGIC_VECTOR (N-1 downto 0);
           COUT : out  STD_LOGIC_VECTOR (N-1 downto 0));
end component;

component CarryLookaheadAdder16BITS is
    Port (A : in  STD_LOGIC_VECTOR (15 downto 0);
          B : in  STD_LOGIC_VECTOR (15 downto 0);
          CIN : in  STD_LOGIC;
          S : out  STD_LOGIC_VECTOR (16 downto 0));
end component;

component CHECKCOMPONENT is
  GENERIC(N: natural);
  Port (A: in STD_LOGIC_VECTOR(n-1 downto 0);
        NEGATIVE: in STD_LOGIC;
        B: out STD_LOGIC_VECTOR(n-1 DOWNTO 0));
end component;

signal ab0,ab1,ab2,ab3,ab4,ab5,ab6,ab7: std_logic_vector(15 downto 0);
signal s11,c11,c11s,s12,c12,c12s,s21,c21,c21s,c22,c22s,s22,s31,c31,c31s,s41,c41,c41s : std_logic_vector (15 downto 0);
signal negativeBoth, negativeOne: STD_LOGIC;
signal AUXA,AUXB: STD_LOGIC_VECTOR (7 downto 0);
signal AUXRESULT: STD_LOGIC_VECTOR (16 downto 0);

begin
	INITIALIZE: process(A,B,AUXA,AUXB,negativeBoth,negativeOne)
	begin
	        negativeBoth <= A(7) and B(7);
	        if (negativeBoth = '1') then
	           AUXA <= not(A) + '1';
	           AUXB <= not(B) + '1';
	        else
               AUXA <= A;
               AUXB <= B;
	        end if;
	        
	        negativeOne <= A(7) xor B(7);
	        if (negativeOne = '1') then
	           if (A(7) = '1') then
	               AUXA <= not(A) + '1';
	           elsif (B(7) = '1') then
	               AUXB <= not(B) + '1';
	           end if;
	        end if;
	        
			for i in 0 to 15 loop
				if (i<8)then
					ab0(i) <= AUXA(i) and AUXB(0);
				else
					ab0(i) <= '0';
				end if;
			end loop;
			
			for i in 0 to 15 loop
				if (i<1 or i>8)then
					ab1(i) <= '0';
				else
					ab1(i) <= AUXA(i-1) and AUXB(1);	
				end if;
			end loop;
			
			for i in 0 to 15 loop
				if (i<2 or i>9)then
					ab2(i) <= '0';
				else
					ab2(i) <= AUXA(i-2) and AUXB(2);	
				end if;
			end loop;
			
		   for i in 0 to 15 loop
				if (i<3 or i>10)then
					ab3(i) <= '0';
				else
					ab3(i) <= AUXA(i-3) and AUXB(3);	
				end if;
			end loop;
			
			for i in 0 to 15 loop
				if (i<4 or i>11)then
					ab4(i) <= '0';
				else
					ab4(i) <= AUXA(i-4) and AUXB(4);	
				end if;
			end loop;
		
			for i in 0 to 15 loop
				if (i<5 or i>12)then
					ab5(i) <= '0';
				else
					ab5(i) <= AUXA(i-5) and AUXB(5);	
				end if;
			end loop;
			
			for i in 0 to 15 loop
				if (i<6 or i>13)then
					ab6(i) <= '0';
				else
					ab6(i) <= AUXA(i-6) and AUXB(6);	
				end if;
			end loop;

			for i in 0 to 15 loop
				if (i<7 or i>14)then
					ab7(i) <= '0';
				else
					ab7(i) <= AUXA(i-7) and AUXB(7);	
				end if;
			end loop;
	end process INITIALIZE; 
	
	--first stage 
	CSA1: CarrySaveAdder16BITS generic map(n => 16) port map (a=>ab0,b=>ab1,c=>ab2,s=>s11,cout=>c11);
	CSA2: CarrySaveAdder16BITS generic map(n => 16)  port map (a=>ab3,b=>ab4,c=>ab5,s=>s12,cout=>c12);
	c11s<=(c11(14 downto 0)&'0');
	c12s<=(c12(14 downto 0)&'0');
	
	--second stage
	CSA3: CarrySaveAdder16BITS generic map(n => 16)  port map (a=>s11,b=>c11s,c=>s12,s=>s21,cout=>c21);
	CSA4: CarrySaveAdder16BITS generic map(n => 16)  port map (a=>c12s,b=>ab6,c=>ab7,s=>s22,cout=>c22);
	c21s<=(c21(14 downto 0)&'0');
	c22s<=(c22(14 downto 0)&'0');
	
	--third stage
	CSA5: CarrySaveAdder16BITS generic map(n => 16)  port map (a=>s21,b=>c21s,c=>c22s,s=>s31,cout=>c31);
	c31s<=(c31(14 downto 0)&'0');
	
	--fourth stage 
	CSA6: CarrySaveAdder16BITS generic map(n => 16)  port map (a=>s31,b=>c31s,c=>s22,s=>s41,cout=>c41);
	c41s<=(c41(14 downto 0)&'0');
	
	--RES <= c41s+s41;
	ADD: CarryLookaheadAdder16BITS port map (c41s,s41,'0',AUXRESULT);
	
	endF: CHECKCOMPONENT generic map(n => 17) port map (AUXRESULT, negativeOne, RES);
	
end Behavioral;