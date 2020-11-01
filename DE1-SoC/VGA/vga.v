module vga(input RST_N, CLK_25,
			  output VGA_BLANK_N, VGA_HS, VGA_SYNC_N, VGA_VS,
				output		[10:0] X,output [10:0] Y);
	 //Horizontal Parameter
    parameter H_FRONT = 16;
    parameter H_SYNC  = 96;
    parameter H_BACK  = 48;
    parameter H_ACT   = 640;
    parameter H_BLANK = H_FRONT + H_SYNC + H_BACK;
    parameter H_TOTAL = H_FRONT + H_SYNC + H_BACK + H_ACT;
    //Vertical Parameter
    parameter V_FRONT = 11;
    parameter V_SYNC  = 2;
    parameter V_BACK  = 32;
    parameter V_ACT   = 480;
    parameter V_BLANK = V_FRONT + V_SYNC + V_BACK;
    parameter V_TOTAL = V_FRONT + V_SYNC + V_BACK + V_ACT;
	 
    reg[9:0] H_Cont; //行扫描计数器
    reg[9:0] V_Cont; //列扫描计数器
    reg vga_hs;
    reg vga_vs;
    reg[10:0] active_x, active_y;
	 
    assign VGA_HS = vga_hs;
    assign VGA_VS = vga_vs;
	 assign Y = active_y;
	 assign X = active_x;
    assign VGA_BLANK_N = ~((H_Cont < H_BLANK) || (V_Cont < V_BLANK));
    assign VGA_SYNC_N  = 1'b0; //If not SOG, Sync input should be tied to 0;
	 
    always@(posedge CLK_25, negedge RST_N) //Horizontal Generator:Refer to the pixel clock
      begin
        if (!RST_N)
          begin
            H_Cont   <= 0;
            vga_hs   <= 1;
            active_x <= 0;
          end
        else
          begin
            if (H_Cont<H_TOTAL)
                H_Cont <= H_Cont + 1'b1;
            else
                H_Cont <= 0;
                //horizontal Sync
            if (H_Cont == H_FRONT - 1) //Front porch end
                vga_hs <= 1'b0;
            if (H_Cont == H_FRONT+H_SYNC - 1)
                vga_hs <= 1'b1; //Current X
            if (H_Cont >= H_BLANK)
                active_x <= H_Cont - H_BLANK;
            else
                active_x <= 0;
          end
      end 
                        
    always@(posedge VGA_HS, negedge RST_N) // vertical Generator: Refer to the horizontal sync
      begin
        if (!RST_N)
          begin
            V_Cont <= 0; 
            vga_vs <= 1;
            active_y <= 0;
          end    
        else 
          begin 
            if (V_Cont < V_TOTAL)
                V_Cont <= V_Cont + 1'b1;   
            else 
                 V_Cont <= 0; //Vertical Sync
            if (V_Cont == V_FRONT - 1) 
                vga_vs <= 1'b0;
            if (V_Cont == V_FRONT + V_SYNC - 1) 
                vga_vs <= 1'b1; //Current Y
            if (V_Cont >= V_BLANK) 
                active_y <= V_Cont - V_BLANK;
            else 
                active_y <= 0; 
         end 
      end 

endmodule
