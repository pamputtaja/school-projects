-- VHDL Entity alien_game_lib.c2_b1_binary_to_onehot.symbol
--
-- Created:
--          by - Jani Koistinen.UNKNOWN (DESKTOP-J0NR04D)
--          at - 09:04:44 24/09/2023
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c2_b1_binary_to_onehot IS
   PORT( 
      binary_in   : IN     std_logic_vector (2 DOWNTO 0);
      one_hot_out : OUT    std_logic_vector (7 DOWNTO 0)
   );

-- Declarations

END c2_b1_binary_to_onehot ;

--
-- VHDL Architecture alien_game_lib.c2_b1_binary_to_onehot.tbl
--
-- Created:
--          by - koistin3.UNKNOWN (HTC219-313-SPC)
--          at - 09:37:56 25.09.2023
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
ARCHITECTURE tbl OF c2_b1_binary_to_onehot IS
   
      -- Architecture declarations
    

BEGIN

   -----------------------------------------------------------------
   truth_process_proc: PROCESS(binary_in)
   -----------------------------------------------------------------
   BEGIN
      -- Block 1
      IF (binary_in = "000") THEN
         one_hot_out <= "00000001";
      ELSIF (binary_in = "001") THEN
         one_hot_out <= "00000010";
      ELSIF (binary_in = "010") THEN
         one_hot_out <= "00000100";
      ELSIF (binary_in = "011") THEN
         one_hot_out <= "00001000";
      ELSIF (binary_in = "100") THEN
         one_hot_out <= "00010000";
      ELSIF (binary_in = "101") THEN
         one_hot_out <= "00100000";
      ELSIF (binary_in = "110") THEN
         one_hot_out <= "01000000";
      ELSIF (binary_in = "111") THEN
         one_hot_out <= "10000000";
      END IF;

   END PROCESS truth_process_proc;

-- Architecture concurrent statements
 

END tbl;
