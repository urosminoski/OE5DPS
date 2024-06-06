library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_signed.all;
use ieee.numeric_std.all;

entity direct_fir is 
	generic(
		IN_WIDTH 	: integer 	:= 16;
		OUT_WIDTH	: integer	:= 16;
		COEFF_WIDTH	: integer	:= 16;
		NUM_TAPS	: integer 	:= 51
	);
	port(
		clk 	: in std_logic;
		rst		: in std_logic;
		d_in	: in std_logic_vector(IN_WIDTH - 1 downto 0);
		d_out 	: out std_logic_vector(OUT_WIDTH - 1 downto 0)
	);
end entity direct_fir;

architecture behavioral of direct_fir is
	
	type coeff_type is array (0 to NUM_TAPS - 1) of std_logic_vector(COEFF_WIDTH - 1 downto 0);
	type shift_reg_type is array(0 to NUM_TAPS - 1) of std_logic_vector(IN_WIDTH - 1 downto 0);
	type muls_out_type is array(0 to NUM_TAPS - 1) of std_logic_vector(IN_WIDTH + COEFF_WIDTH - 1 downto 0);
	
	constant fir_coeff : coeff_type := ( x"0002",
										 x"0000",
										 x"FFF8",
										 x"0000",
										 x"0016",
										 x"0000",
										 x"FFD0",
										 x"0000",
										 x"005E",
										 x"0000",
										 x"FF57",
										 x"0000",
										 x"011C",
										 x"0000",
										 x"FE36",
										 x"0000",
										 x"02CD",
										 x"0000",
										 x"FBA2",
										 x"0000",
										 x"070C",
										 x"0000",
										 x"F31B",
										 x"0000",
										 x"2882",
										 x"4000",
										 x"2882",
										 x"0000",
										 x"F31B",
										 x"0000",
										 x"070C",
										 x"0000",
										 x"FBA2",
										 x"0000",
										 x"02CD",
										 x"0000",
										 x"FE36",
										 x"0000",
										 x"011C",
										 x"0000",
										 x"FF57",
										 x"0000",
										 x"005E",
										 x"0000",
										 x"FFD0",
										 x"0000",
										 x"0016",
										 x"0000",
										 x"FFF8",
										 x"0000",
										 x"0002");
	
	signal shift_reg 	: shift_reg_type;
	signal muls_out 	: muls_out_type;
	signal adders_out	: muls_out_type;
	
begin
	
	SHIFT_REG_PROC : process(clk)
	begin
		if rising_edge(clk) then
			if rst = '1' then
				shift_reg <= (others => (others => '0'));
			else
				for i in 0 to NUM_TAPS - 2 loop
					shift_reg(i + 1) <= shift_reg(i);
				end loop;
				shift_reg(0) <= d_in;
			end if;
		end if;
	end process SHIFT_REG_PROC;
	
	muls_out(0) 	<= d_in * fir_coeff(0);
	adders_out(0) 	<= muls_out(0);
	
	GEN_FIR: for i in 1 to NUM_TAPS - 1 generate
	begin
		muls_out(i) 	<= shift_reg(i) * fir_coeff(i);
		adders_out(i)	<= adders_out(i-1) + muls_out(i);
	end generate GEN_FIR;
	
	d_out <= adders_out(NUM_TAPS - 1)(adders_out(0)'length - 1 downto adders_out(0)'length - OUT_WIDTH);

end behavioral;