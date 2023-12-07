-- VHDL Entity tb_lib.tb_register_64.symbol
--
-- Created:
--          by - kayra.UNKNOWN (WS-11696-PC)
--          at - 16:33:24 06/04/18
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY tb_register_64 IS
-- Declarations

END tb_register_64 ;

--
-- VHDL Architecture tb_lib.tb_register_64.struct
--
-- Created:
--          by - kayra.UNKNOWN (WS-11696-PC)
--          at - 15:54:12  3.09.2020
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;

LIBRARY tb_lib;

ARCHITECTURE struct OF tb_register_64 IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL clk           : std_logic;
   SIGNAL pixd          : std_logic_vector(23 DOWNTO 0);
   SIGNAL pixd_from_duv : std_logic_vector(23 DOWNTO 0);
   SIGNAL rst_n         : std_logic;
   SIGNAL w_done        : std_logic;
   SIGNAL w_ready       : std_logic;
   SIGNAL write         : std_logic;
   SIGNAL x_read        : std_logic_vector(7 DOWNTO 0);
   SIGNAL x_write       : std_logic_vector(7 DOWNTO 0);
   SIGNAL y_read        : std_logic_vector(7 DOWNTO 0);
   SIGNAL y_write       : std_logic_vector(7 DOWNTO 0);


   -- Component Declarations
   COMPONENT register_tester
   PORT (
      pixd_from_duv : IN     std_logic_vector (23 DOWNTO 0);
      w_ready       : IN     std_logic ;
      clk           : OUT    std_logic ;
      pixd          : OUT    std_logic_vector (23 DOWNTO 0);
      rst_n         : OUT    std_logic ;
      w_done        : OUT    std_logic ;
      write         : OUT    std_logic ;
      x_read        : OUT    std_logic_vector (7 DOWNTO 0);
      x_write       : OUT    std_logic_vector (7 DOWNTO 0);
      y_read        : OUT    std_logic_vector (7 DOWNTO 0);
      y_write       : OUT    std_logic_vector (7 DOWNTO 0)
   );
   END COMPONENT;

   -- Optional embedded configurations
   -- pragma synthesis_off
   FOR ALL : register_tester USE ENTITY tb_lib.register_tester;
   -- pragma synthesis_on


BEGIN

   -- Instance port mappings.
   U_0 : register_tester
      PORT MAP (
         pixd_from_duv => pixd_from_duv,
         w_ready       => w_ready,
         clk           => clk,
         pixd          => pixd,
         rst_n         => rst_n,
         w_done        => w_done,
         write         => write,
         x_read        => x_read,
         x_write       => x_write,
         y_read        => y_read,
         y_write       => y_write
      );

END struct;