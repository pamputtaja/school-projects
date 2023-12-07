-- VHDL Entity alien_game_lib.c3_t1_basic_alien.symbol
--
-- Created:
--          by - koistin3.UNKNOWN (HTC219-304-SPC)
--          at - 13:03:42 13.10.2023
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c3_t1_basic_alien IS
   PORT( 
      clk           : IN     std_logic;
      enable        : IN     std_logic;
      hit           : IN     std_logic;
      rst_n         : IN     std_logic;
      alien_color   : OUT    std_logic_vector (23 DOWNTO 0);
      alien_defeted : OUT    std_logic;
      x_coord       : OUT    std_logic_vector (7 DOWNTO 0);
      y_coord       : OUT    std_logic_vector (7 DOWNTO 0)
   );

-- Declarations

END c3_t1_basic_alien ;

--
-- VHDL Architecture alien_game_lib.c3_t1_basic_alien.struct
--
-- Created:
--          by - koistin3.UNKNOWN (HTC219-304-SPC)
--          at - 13:03:42 13.10.2023
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

LIBRARY alien_game_lib;

ARCHITECTURE struct OF c3_t1_basic_alien IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL binary_in : std_logic_vector(2 DOWNTO 0);
   SIGNAL d         : std_logic_vector(2 DOWNTO 0);
   SIGNAL d1        : std_logic;
   SIGNAL d2        : std_logic_vector(23 DOWNTO 0);
   SIGNAL din1      : std_logic_vector(2 DOWNTO 0);
   SIGNAL din2      : std_logic;
   SIGNAL din3      : std_logic_vector(23 DOWNTO 0);
   SIGNAL direction : std_logic;
   SIGNAL result    : std_logic_vector(2 DOWNTO 0);
   SIGNAL result1   : std_logic_vector(2 DOWNTO 0);

   -- Implicit buffer signal declarations
   SIGNAL alien_color_internal   : std_logic_vector (23 DOWNTO 0);
   SIGNAL alien_defeted_internal : std_logic;
   SIGNAL x_coord_internal       : std_logic_vector (7 DOWNTO 0);


   -- ModuleWare signal declarations(v1.12) for instance 'U_1' of 'adff'
   SIGNAL mw_U_1reg_cval : std_logic_vector(2 DOWNTO 0);

   -- ModuleWare signal declarations(v1.12) for instance 'U_9' of 'adff'
   SIGNAL mw_U_9reg_cval : std_logic;

   -- ModuleWare signal declarations(v1.12) for instance 'U_13' of 'adff'
   SIGNAL mw_U_13reg_cval : std_logic_vector(23 DOWNTO 0);

   -- Component Declarations
   COMPONENT c1_b1_incrementer
   PORT (
      value  : IN     std_logic_vector (2 DOWNTO 0);
      result : OUT    std_logic_vector (2 DOWNTO 0)
   );
   END COMPONENT;
   COMPONENT c1_b2_decrementer
   PORT (
      value  : IN     std_logic_vector (2 DOWNTO 0);
      result : OUT    std_logic_vector (2 DOWNTO 0)
   );
   END COMPONENT;
   COMPONENT c2_b1_binary_to_onehot
   PORT (
      binary_in   : IN     std_logic_vector (2 DOWNTO 0);
      one_hot_out : OUT    std_logic_vector (7 DOWNTO 0)
   );
   END COMPONENT;
   COMPONENT c3_direction_block
   PORT (
      clk       : IN     std_logic ;
      rst_n     : IN     std_logic ;
      x_coord_0 : IN     std_logic ;
      x_coord_7 : IN     std_logic ;
      direction : OUT    std_logic 
   );
   END COMPONENT;

   -- Optional embedded configurations
   -- pragma synthesis_off
   FOR ALL : c1_b1_incrementer USE ENTITY alien_game_lib.c1_b1_incrementer;
   FOR ALL : c1_b2_decrementer USE ENTITY alien_game_lib.c1_b2_decrementer;
   FOR ALL : c2_b1_binary_to_onehot USE ENTITY alien_game_lib.c2_b1_binary_to_onehot;
   FOR ALL : c3_direction_block USE ENTITY alien_game_lib.c3_direction_block;
   -- pragma synthesis_on


BEGIN

   -- ModuleWare code(v1.12) for instance 'U_1' of 'adff'
   binary_in <= mw_U_1reg_cval;
   u_1seq_proc: PROCESS (clk, rst_n)
   BEGIN
      IF (rst_n = '0') THEN
         mw_U_1reg_cval <= "000";
      ELSIF (clk'EVENT AND clk='1') THEN
         mw_U_1reg_cval <= d;
      END IF;
   END PROCESS u_1seq_proc;

   -- ModuleWare code(v1.12) for instance 'U_9' of 'adff'
   alien_defeted_internal <= mw_U_9reg_cval;
   u_9seq_proc: PROCESS (clk, rst_n)
   BEGIN
      IF (rst_n = '0') THEN
         mw_U_9reg_cval <= '0';
      ELSIF (clk'EVENT AND clk='1') THEN
         mw_U_9reg_cval <= d1;
      END IF;
   END PROCESS u_9seq_proc;

   -- ModuleWare code(v1.12) for instance 'U_13' of 'adff'
   alien_color_internal <= mw_U_13reg_cval;
   u_13seq_proc: PROCESS (clk, rst_n)
   BEGIN
      IF (rst_n = '0') THEN
         mw_U_13reg_cval <= x"0000FF";
      ELSIF (clk'EVENT AND clk='1') THEN
         mw_U_13reg_cval <= d2;
      END IF;
   END PROCESS u_13seq_proc;

   -- ModuleWare code(v1.12) for instance 'U_2' of 'constval'
   y_coord <= "00000001";

   -- ModuleWare code(v1.12) for instance 'U_5' of 'constval'
   din3 <= x"000000";

   -- ModuleWare code(v1.12) for instance 'U_11' of 'constval'
   din2 <= '1';

   -- ModuleWare code(v1.12) for instance 'U_4' of 'mux'
   u_4combo_proc: PROCESS(binary_in, din1, enable)
   BEGIN
      CASE enable IS
      WHEN '0' => d <= binary_in;
      WHEN '1' => d <= din1;
      WHEN OTHERS => d <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_4combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_6' of 'mux'
   u_6combo_proc: PROCESS(result, result1, direction)
   BEGIN
      CASE direction IS
      WHEN '0' => din1 <= result;
      WHEN '1' => din1 <= result1;
      WHEN OTHERS => din1 <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_6combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_10' of 'mux'
   u_10combo_proc: PROCESS(alien_defeted_internal, din2, hit)
   BEGIN
      CASE hit IS
      WHEN '0' => d1 <= alien_defeted_internal;
      WHEN '1' => d1 <= din2;
      WHEN OTHERS => d1 <= 'X';
      END CASE;
   END PROCESS u_10combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_12' of 'mux'
   u_12combo_proc: PROCESS(alien_color_internal, din3, hit)
   BEGIN
      CASE hit IS
      WHEN '0' => d2 <= alien_color_internal;
      WHEN '1' => d2 <= din3;
      WHEN OTHERS => d2 <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_12combo_proc;

   -- Instance port mappings.
   U_3 : c1_b1_incrementer
      PORT MAP (
         value  => binary_in,
         result => result
      );
   U_7 : c1_b2_decrementer
      PORT MAP (
         value  => binary_in,
         result => result1
      );
   U_0 : c2_b1_binary_to_onehot
      PORT MAP (
         binary_in   => binary_in,
         one_hot_out => x_coord_internal
      );
   U_8 : c3_direction_block
      PORT MAP (
         clk       => clk,
         rst_n     => rst_n,
         x_coord_0 => x_coord_internal(0),
         x_coord_7 => x_coord_internal(7),
         direction => direction
      );

   -- Implicit buffered output assignments
   alien_color   <= alien_color_internal;
   alien_defeted <= alien_defeted_internal;
   x_coord       <= x_coord_internal;

END struct;
