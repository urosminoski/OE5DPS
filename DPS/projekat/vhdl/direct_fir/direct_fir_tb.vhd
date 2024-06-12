
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;

entity direct_fir_tb is
end;

architecture bench of direct_fir_tb is

	component direct_fir 
		generic(
			IN_WIDTH 	: integer 	:= 16;
			OUT_WIDTH	: integer	:= 16;
			COEFF_WIDTH	: integer	:= 16;
			NUM_TAPS	: integer 	:= 27
		);
		port(
			clk 	: in std_logic;
			rst		: in std_logic;
			d_in	: in std_logic_vector(IN_WIDTH - 1 downto 0);
			d_out 	: out std_logic_vector(OUT_WIDTH - 1 downto 0)
		);
	end component;
	
	constant CLK_T			: time 		:= 10 ns;
	constant IN_WIDTH		: integer 	:= 4;
	constant OUT_WIDTH		: integer 	:= 4;
	constant COEFF_WIDTH	: integer 	:= 4;
	constant NUM_TAPS		: integer 	:= 5;

	signal clk		: std_logic := '0';
	signal rst		: std_logic := '1';
	signal d_in		: std_logic_vector(IN_WIDTH - 1 downto 0) := (others => 'Z');
	signal d_out	: std_logic_vector(OUT_WIDTH - 1 downto 0);
  
	signal out_ready : std_logic := '0';
  
	file in_file 	: TEXT open READ_MODE is "C:\Users\Korisnik\Desktop\FAKS\DPS\projekat\test_signal.txt";
	file out_file 	: TEXT open WRITE_MODE is "C:\Users\Korisnik\Desktop\FAKS\DPS\projekat\fir_test_signal.txt";

begin

	-- Insert values for generic parameters !!
	uut: direct_fir
	generic map( 
		IN_WIDTH    => IN_WIDTH,
		OUT_WIDTH   => OUT_WIDTH,
		COEFF_WIDTH => COEFF_WIDTH,
		NUM_TAPS    => NUM_TAPS
		)
		port map( 
			clk         => clk,
			rst         => rst,
			d_in        => d_in,
			d_out       => d_out
		);

	clk <= not clk after 10 ns;
	rst <= '1', '1' after 100 ns, '0' after 503 ns;

	process(clk)
		variable in_line	: LINE;
		variable input 		: integer;
	begin
		if rising_edge(clk) then
			if rst = '1' then
				d_in 		<= (others => '0');
				input		:= 0;
				out_ready	<= '0';
			else
				readline(in_file, in_line);
				read(in_line, input);
				d_in 		<= std_logic_vector(to_signed(input, IN_WIDTH));
				out_ready	<= '1';
			end if;
		end if;
	end process;
	
	process(clk)
		variable out_line	: LINE;
	begin
		if falling_edge(clk) then
			if out_ready = '1' then
				write(out_line, to_integer(signed(d_out)));
				writeline(out_file, out_line);
			end if;
		end if;
	end process;

end;