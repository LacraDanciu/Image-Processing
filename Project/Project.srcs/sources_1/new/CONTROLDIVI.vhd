----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/06/2017 10:47:13 PM
-- Design Name: 
-- Module Name: CONTROLDIVI - Behavioral
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

entity CONTROLDIVI is
    Port (
      clk: in STD_LOGIC;
      rst: in STD_LOGIC;
      start: in STD_LOGIC;
      an: in STD_LOGIC;
      
      term: out STD_LOGIC;
      loadb: out STD_LOGIC;
      loadq: out STD_LOGIC;
      shlaq: out STD_LOGIC;
      subb: out STD_LOGIC;
      loada: out STD_LOGIC);
end CONTROLDIVI;

architecture Behavioral of CONTROLDIVI is

type state is (idle, init, shift, test, sub, add, dec, result);
signal stateVal: state;
signal c: natural;

begin

proc1:  process(clk, rst, start, an)
        begin
          if rising_edge(clk) then
            if (rst = '1') then
                stateVal <= idle;
                term <= '-';
                loadb <= '-';
                loadq <= '-';
                subb <= '-';
                loada <= '-';
                shlaq <= '-';
            else
                case stateVal is
                    when idle => 
                          term <= '0';
                          loadb <= '0';
                          loadq <= '0';
                          subb <= '0';
                          loada <= '0';
                          shlaq <= '0';
                         
                         if (start = '1') then
                            stateVal <= init;
                         else
                            stateVal <= idle;
                         end if; 
                         
                  when init => 
                         term <= '0';
                         loadb <= '1';
                         loadq <= '1';
                         subb <= '0';
                         loada <= '1';
                         shlaq <= '0';
                         c <= 8;
                         stateVal <= shift;
                         
                  when shift => 
                         term <= '0';
                         loadb <= '0';
                         loadq <= '0';
                         subb <= '0';
                         loada <= '0';
                         shlaq <= '1';
                         stateVal <= sub;
                      
                  when test => 
                         term <= '0';
                         loadb <= '0';
                         loadq <= '1';
                         subb <= '0';
                         loada <= '0';
                         shlaq <= '0'; 
                                                  
                         if (an = '1') then
                             stateVal <= add;
                         else
                             stateVal <= dec; 
                         end if;
                       
                  when add => 
                            term <= '0';
                            loadb <= '0';
                            loadq <= '0';
                            subb <= '0';
                            loada <= '1';
                            shlaq <= '0'; 
                                                  
                            stateVal <= dec;
                            
                 when sub => 
                            term <= '0';
                            loadb <= '0';
                            loadq <= '0';
                            subb <= '1';
                            loada <= '1';
                            shlaq <= '0';
                            
                            stateVal <= test;
                            
                 when dec => 
                            term <= '0';
                            loadb <= '0';
                            loadq <= '0';
                            subb <= '0';
                            loada <= '0';
                            shlaq <= '0'; 
                            c <= c-1;    
                                                     
                            if (c > 1) then
                                stateVal <= shift;
                            else
                                stateVal <= result;
                            end if;  
                           
                  when result => 
                             term <= '1';
                             loadb <= '0';
                             loadq <= '0';
                             subb <= '0';
                             loada <= '0';
                             shlaq <= '0';
                             stateVal <= idle;
             end case;
                                                                               
            end if;
         end if;
end process proc1;

end Behavioral;