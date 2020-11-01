module DE1_SOC(
	//////////// CLOCK //////////
	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,
	input 		          		CLOCK4_50,
	input 		          		CLOCK_50,

	//////////// SEG7 //////////
	output		     [6:0]		HEX0,
	output		     [6:0]		HEX1,
	output		     [6:0]		HEX2,
	output		     [6:0]		HEX3,
	output		     [6:0]		HEX4,
	output		     [6:0]		HEX5,

	//////////// KEY //////////
	input 		     [3:0]		KEY,

	//////////// LED //////////
	output		     [9:0]		LEDR,

	//////////// SW //////////
	input 		     [9:0]		SW,

	//////////// VGA //////////
	output		          		VGA_BLANK_N,
	output		     [7:0]		VGA_B,
	output		          		VGA_CLK,
	output		     [7:0]		VGA_G,
	output		          		VGA_HS,
	output		     [7:0]		VGA_R,
	output		          		VGA_SYNC_N,
	output		          		VGA_VS
);

//=======================================================
//  REG/WIRE declarations
//=======================================================
    wire[10:0] vga_x, vga_y;
    reg[7:0] vga_r, vga_g, vga_b;
    
    divider #(0)d(CLOCK_50, CLK_25);
	  vga v(
		    .RST_N(RST_N), 
			  .CLK_25(CLK_25), 
			  .VGA_BLANK_N(VGA_BLANK_N),
			  .VGA_HS(VGA_HS),
			  .VGA_SYNC_N(VGA_SYNC_N),
			  .VGA_VS(VGA_VS),
			  .X(vga_x),
			  .Y(vga_y)
		);
			 
//=======================================================
//  Structural coding
//=======================================================
	
    //Select DAC CLOCK
    assign VGA_CLK     = CLK_25;
    assign RST_N       = KEY[0]; 
    assign VGA_R       = vga_r;
    assign VGA_G       = vga_g;
    assign VGA_B       = vga_b;

    // always@(posedge CLK_25, negedge RST_N) //Pattern Generator
    //   begin 
    //     if (!RST_N)
    //       begin
    //         vga_r <= 8'hff; 
    //         vga_g <= 8'hff; 
    //         vga_b <= 8'hff; 
    //       end
    //     else 
    //       begin 
    //         vga_r <= (Y < 120) ? 256 : 
    //             (Y >= 120 && Y < 240) ? 512 :
    //             (Y >= 240 && Y < 360) ? 768 : 102; 
    //         vga_g <= (X < 80) ? 128 :
    //             (X >= 80 && X < 160) ? 256 : 
		// 		        (X >= 160 && X < 240) ? 384 :
    //             (X >= 240 && X < 320) ? 512 : 
		// 		        (X >= 320 && X < 400) ? 640 :
    //             (X >= 400 && X < 480) ? 768 :
    //             (X >= 480 && X < 560) ? 896 : 102; 
    //         vga_b <= (Y < 60) ? 1023 :
    //             (Y >= 60 && Y < 120) ? 896 : 
		// 		        (Y >= 120 && Y < 180) ? 768 :
    //             (Y >= 180 && Y < 240) ? 640 :
    //             (Y >= 240 && Y < 300) ? 512 :
    //             (Y >= 300 && Y < 360) ? 384 :
    //             (Y >= 360 && Y < 420) ? 256 : 128; 
    //       end 
    //   end 

endmodule
