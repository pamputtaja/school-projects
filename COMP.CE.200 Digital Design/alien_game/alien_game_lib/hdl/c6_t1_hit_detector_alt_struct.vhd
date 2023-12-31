-- VHDL Entity alien_game_lib.c6_t1_hit_detector_alt.symbol
--
-- Created:
--          by - PAMPPU.UNKNOWN (DESKTOP-3NB66EQ)
--          at - 18:41:40 30/11/2023
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c6_t1_hit_detector_alt IS
   PORT( 
      alien_x : IN     std_logic_vector (7 DOWNTO 0);
      btn     : IN     std_logic;
      clk     : IN     std_logic;
      gun_x   : IN     std_logic_vector (7 DOWNTO 0);
      rst_n   : IN     std_logic;
      hit     : OUT    std_logic
   );

-- Declarations

END c6_t1_hit_detector_alt ;

--
-- VHDL Architecture alien_game_lib.c6_t1_hit_detector_alt.struct
--
-- Created:
--          by - PAMPPU.UNKNOWN (DESKTOP-3NB66EQ)
--          at - 18:41:40 30/11/2023
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;


ARCHITECTURE struct OF c6_t1_hit_detector_alt IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL dout   : std_logic;
   SIGNAL dout1  : std_logic;
   SIGNAL dout10 : std_logic;
   SIGNAL dout2  : std_logic;
   SIGNAL dout3  : std_logic;
   SIGNAL dout4  : std_logic;
   SIGNAL dout5  : std_logic;
   SIGNAL dout6  : std_logic;
   SIGNAL dout7  : std_logic;
   SIGNAL dout8  : std_logic;
   SIGNAL dout9  : std_logic;
   SIGNAL q      : std_logic;


   -- ModuleWare signal declarations(v1.12) for instance 'U_11' of 'adff'
   SIGNAL mw_U_11reg_cval : std_logic;


BEGIN

   -- ModuleWare code(v1.12) for instance 'U_11' of 'adff'
   q <= mw_U_11reg_cval;
   u_11seq_proc: PROCESS (clk, rst_n)
   BEGIN
      IF (rst_n = '0') THEN
         mw_U_11reg_cval <= '0';
      ELSIF (clk'EVENT AND clk='1') THEN
         mw_U_11reg_cval <= dout9;
      END IF;
   END PROCESS u_11seq_proc;

   -- ModuleWare code(v1.12) for instance 'U_0' of 'and'
   dout <= gun_x(7) AND alien_x(7);

   -- ModuleWare code(v1.12) for instance 'U_1' of 'and'
   dout1 <= gun_x(6) AND alien_x(6);

   -- ModuleWare code(v1.12) for instance 'U_2' of 'and'
   dout2 <= gun_x(5) AND alien_x(5);

   -- ModuleWare code(v1.12) for instance 'U_3' of 'and'
   dout3 <= gun_x(4) AND alien_x(4);

   -- ModuleWare code(v1.12) for instance 'U_4' of 'and'
   dout4 <= gun_x(3) AND alien_x(3);

   -- ModuleWare code(v1.12) for instance 'U_5' of 'and'
   dout5 <= gun_x(2) AND alien_x(2);

   -- ModuleWare code(v1.12) for instance 'U_6' of 'and'
   dout6 <= gun_x(1) AND alien_x(1);

   -- ModuleWare code(v1.12) for instance 'U_7' of 'and'
   dout7 <= gun_x(0) AND alien_x(0);

   -- ModuleWare code(v1.12) for instance 'U_9' of 'and'
   dout9 <= btn AND dout8;

   -- ModuleWare code(v1.12) for instance 'U_12' of 'constval'
   dout10 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_10' of 'mux'
   u_10combo_proc: PROCESS(q, dout10, btn)
   BEGIN
      CASE btn IS
      WHEN '0' => hit <= q;
      WHEN '1' => hit <= dout10;
      WHEN OTHERS => hit <= 'X';
      END CASE;
   END PROCESS u_10combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_8' of 'or'
   dout8 <= dout OR dout1 OR dout2 OR dout3 OR dout4 OR dout5 OR dout6
            OR dout7;

   -- Instance port mappings.

END struct;
